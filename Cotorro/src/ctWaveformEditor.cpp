#include "ctWaveformEditor.h"

#include "ctCotorro.h"
#include "ctWord.h"
#include "ctStorySectionEditorWidget.h"

using sf::Vector2u;
using sf::Vector2f;
using sf::Vector2i;

namespace ct 
{

quint32 WaveformEditor::_TIME_LINE_LINE_POOL_SIZE = 60;
float WaveformEditor::_MAX_LINE_SPACING = 15.0f;
float WaveformEditor::_MIN_LINE_SPACING = 0.25f;
float WaveformEditor::_LINE_SPACING_FACTOR = 0.1f;

WaveformEditor::WaveformEditor(StorySectionEditorWidget* _pStorySectionEditorWidget) :
  Frame(),
  _m_cursor(),
  _m_activeTimeLineLines(),
  _m_deactiveTimeLineLines(),
  _m_pStorySectionEditorWidget(_pStorySectionEditorWidget),
  _m_waveformNode(),
  _m_lineSpacing(15.0f),
  _m_waveFormWordShadow()
{
  return;
}

WaveformEditor::~WaveformEditor()
{
  destroy();
  return;
}

void
WaveformEditor::onUpdate(sf::RenderWindow &_window)
{  
  _m_waveFormWordShadow.update(_window);

  // Draw each active line.
  foreach(TimeLineLine* _line, _m_activeTimeLineLines) {
    _line->update(_window);
  }  

  // Update cursor
  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  float cursorPosition = audioManager.getPlayingPosition();
  _m_cursor.setPosition(cursorPosition, 0.0f);
  
  QString strTime = QString::number(cursorPosition, 'f', 2);
  _m_cursor.setLabel(QObject::tr("%1s.").arg(strTime));

  // Draw cursor
  _m_cursor.update(_window);
  return;
}

void
WaveformEditor::onDrawableAreaChanged()
{
  Frame::onDrawableAreaChanged();

  _m_cursor.setHeight(_m_drawableArea.height);

  foreach(TimeLineLine* _line, _m_activeTimeLineLines) {
    _line->setHeight(_m_drawableArea.height);
  }

  foreach(TimeLineLine* _line, _m_deactiveTimeLineLines) {
    _line->setHeight(_m_drawableArea.height);
  }

  _m_waveFormWordShadow.setHeight(_m_drawableArea.height);  

  updateTimeline();
  return;
}

void WaveformEditor::setStorySectionEditorWidget
(
  StorySectionEditorWidget *_pStorySectionEditorWidget
)
{
  this->_m_pStorySectionEditorWidget = _pStorySectionEditorWidget;
  return;
}

void
WaveformEditor::destroy()
{
  qDeleteAll(_m_activeTimeLineLines);
  qDeleteAll(_m_deactiveTimeLineLines);

  _m_activeTimeLineLines.clear();
  _m_deactiveTimeLineLines.clear();

  _m_waveFormWordShadow.destroy();
  return;
}

void
WaveformEditor::onInit()
{
  _m_waveformNode.setParent(_m_frameNode);  

  // Setup cursor
  _m_cursor.init();
  _m_cursor.setParent(_m_waveformNode);
  _m_cursor.setColor(sf::Color::Red);
  _m_cursor.setDisplayTextOnTop(true);

  // Create pool of time line lines.
  for(quint32 ii = 0; ii < WaveformEditor::_TIME_LINE_LINE_POOL_SIZE; ++ii) {
    TimeLineLine* pTimeLineLine = new TimeLineLine();
    pTimeLineLine->init();
    pTimeLineLine->setParent(_m_waveformNode);
    _m_deactiveTimeLineLines.push_back(
      pTimeLineLine
    );

  }

  _m_waveFormWordShadow.init();
  _m_waveFormWordShadow.setParent(_m_waveformNode);
  
  return;
}

void
WaveformEditor::updateTimeline()
{
  float viewportPosition = _m_pStorySectionEditorWidget->getViewportPosition();
  float viewportLength = _m_pStorySectionEditorWidget->getViewportLength();
  float viewportEndPosition = viewportPosition + viewportLength;
  float pixelsPerSecond = _m_pStorySectionEditorWidget->getPixelsPerSecond();

  float W = viewportLength;
  float w = 15.0f;

  float desireLineSpacing = qFloor(_LINE_SPACING_FACTOR * viewportLength);
  if (_MAX_LINE_SPACING < desireLineSpacing) {
    desireLineSpacing = _MAX_LINE_SPACING;
  }
  else if (_MIN_LINE_SPACING > desireLineSpacing) {
    desireLineSpacing = _MIN_LINE_SPACING;
  }

  // if Line Spacing have changed, remove all lines from viewport.
  if (desireLineSpacing != _m_lineSpacing) {
    QListIterator<TimeLineLine*> iActiveLine(_m_activeTimeLineLines);
    QList<TimeLineLine*> toRemove;
    while (iActiveLine.hasNext()) {
      TimeLineLine* pLine = iActiveLine.next();
      toRemove.push_back(pLine);
    }

    QListIterator<TimeLineLine*> iToRemove(toRemove);
    while (iToRemove.hasNext()) {
      TimeLineLine* pLine = iToRemove.next();
      deactiveLine(pLine);
    }

    _m_lineSpacing = desireLineSpacing;
  }

  // Remove lines that are out of viewport
  QListIterator<TimeLineLine*> iActiveLine(_m_activeTimeLineLines);
  QList<TimeLineLine*> toRemove;
  while(iActiveLine.hasNext()) {
    TimeLineLine* pLine = iActiveLine.next();
    float linePosition = pLine->getPosition().x;

    if(viewportPosition > linePosition || linePosition >= viewportEndPosition){
      toRemove.push_back(pLine);
    }
    toRemove.push_back(pLine);
  }

  QListIterator<TimeLineLine*> iToRemove(toRemove);
  while(iToRemove.hasNext()) {
    TimeLineLine* pLine = iToRemove.next();
    deactiveLine(pLine);
  }

  // Initial line position
  float linePosition = qCeil(viewportPosition / _m_lineSpacing) * _m_lineSpacing;

  // Create time line lines
  while(linePosition < viewportEndPosition) {

    // Check if an active line already exists in the given position.
    float exists = false;
    QListIterator<TimeLineLine*> i(_m_activeTimeLineLines);
    while(i.hasNext()) {
      TimeLineLine* pLine = i.next();
      sf::Vector2f otherLinePosition = pLine->getPosition();
      float delta = linePosition - otherLinePosition.x;

      if(-0.01f < delta && delta < 0.01f) {
          exists = true;
          pLine->setPosition(linePosition, 0.0f);
          QString strTime = QString::number(linePosition, 'f', 2);
          pLine->setLabel(QObject::tr("%1s.").arg(strTime));
          break;
      }
    }

    // If line doesn't exists, put a new one.
    if(!exists) {
      TimeLineLine* pNewLine = getAvailableLine();
      if(pNewLine != nullptr) {
        pNewLine->setPosition(linePosition, 0.0f);
        QString strTime = QString::number(linePosition, 'f', 2);
        pNewLine->setLabel(QObject::tr("%1s.").arg(strTime));
      }
    }

    linePosition += _m_lineSpacing;
  }

  // Setup position and scale to the waveform container
  _m_waveformNode.setPosition(-viewportPosition * _m_pStorySectionEditorWidget->getPixelsPerSecond(), 0.0f);
  _m_waveformNode.setScale(_m_pStorySectionEditorWidget->getPixelsPerSecond(), 1.0f);
  return;
}

void
WaveformEditor::onMousePressed(QMouseEvent* e)
{
  // TODO
  return;
}

void
WaveformEditor::onMouseMoved(QMouseEvent* e)
{
  // TODO
  return;
}

void
WaveformEditor::onMouseReleased(QMouseEvent* e)
{
  QPoint mousePositionPoint = e->pos();
  if (!_m_drawableArea.contains(static_cast<sf::Uint32>(mousePositionPoint.x()),
                                static_cast<sf::Uint32>(mousePositionPoint.y()))) {
    return;
  }
  
  Vector2f mousePosition = Vector2f(static_cast<float>(mousePositionPoint.x()),
                                    static_cast<float>(mousePositionPoint.y()));
  Vector2f waveformPositionF = _m_waveformNode.getPosition() + _m_frameNode.getPosition();

  mousePosition = mousePosition - waveformPositionF;
  float desireAudioTimePosition = mousePosition.x / _m_pStorySectionEditorWidget->getPixelsPerSecond();

  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  audioManager.setPlayingPosition(desireAudioTimePosition);
  
  return;
}

void
WaveformEditor::onMouseDoubleClicked(QMouseEvent* e)
{
  // TODO
  return;
}

void
WaveformEditor::onStorySectionChanged(StorySection *_pStorySection)
{
  updateTimeline();
  return;
}

void 
WaveformEditor::onActiveWordChanged(Word* _pWord)
{
  _m_waveFormWordShadow.setWord(_pWord);
  _m_waveFormWordShadow.setActive(_pWord != nullptr);
}

void WaveformEditor::onViewportMoved(const float &_newPosition)
{
  updateTimeline();
}

float 
WaveformEditor::getCursorPosition()
{
  return _m_cursor.getPosition().x;
}

bool
WaveformEditor::hasAvailableLine()
{
  return !_m_deactiveTimeLineLines.isEmpty();
}

TimeLineLine*
WaveformEditor::getAvailableLine()
{
  if(_m_deactiveTimeLineLines.isEmpty()) {
    return nullptr;
  }

  TimeLineLine* pLine = _m_deactiveTimeLineLines.takeFirst();
  _m_activeTimeLineLines.push_back(pLine);

  return pLine;
}

void
WaveformEditor::deactiveLine(TimeLineLine *_pTimeLineLine)
{
  if(_m_activeTimeLineLines.removeOne(_pTimeLineLine)) {
    _m_deactiveTimeLineLines.push_back(_pTimeLineLine);
  }
  return;
}

}

