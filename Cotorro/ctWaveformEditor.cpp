#include "ctWaveformEditor.h"

#include "ctCotorro.h"
#include "ctStorySectionEditorWidget.h"

namespace ct {

quint32 WaveformEditor::_TIME_LINE_LINE_POOL_SIZE = 30;

WaveformEditor::WaveformEditor(StorySectionEditorWidget* _pStorySectionEditorWidget) :
  Frame(),
  _m_activeTimeLineLines(),
  _m_deactiveTimeLineLines(),
  _m_pStorySectionEditorWidget(_pStorySectionEditorWidget),
  _m_waveformNode(),
  _m_lineSpacing(15.0f)
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
  // Draw each active line.
  foreach(TimeLineLine* _line, _m_activeTimeLineLines) {
    _line->update(_window);
  }
  return;
}

void
WaveformEditor::onDrawableAreaChanged()
{
  Frame::onDrawableAreaChanged();

  foreach(TimeLineLine* _line, _m_activeTimeLineLines) {
    _line->setHeight(_m_drawableArea.height);
  }

  foreach(TimeLineLine* _line, _m_deactiveTimeLineLines) {
    _line->setHeight(_m_drawableArea.height);
  }

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
  return;
}

void
WaveformEditor::onInit()
{
  _m_waveformNode.setParent(_m_frameNode);

  // Create pool of time line lines.
  for(quint32 ii = 0; ii < WaveformEditor::_TIME_LINE_LINE_POOL_SIZE; ++ii) {
    TimeLineLine* pTimeLineLine = new TimeLineLine();
    pTimeLineLine->init();
    pTimeLineLine->setParent(_m_waveformNode);
    _m_deactiveTimeLineLines.push_back(
      pTimeLineLine
    );

  }

  return;
}

void
WaveformEditor::updateTimeline()
{
  float viewportPosition = _m_pStorySectionEditorWidget->getViewportPosition();
  float viewportEndPosition = viewportPosition + _m_pStorySectionEditorWidget->getViewportLength();

  // Remove lines that are out of viewport
  QListIterator<TimeLineLine*> iActiveLine(_m_activeTimeLineLines);
  QList<TimeLineLine*> toRemove;
  while(iActiveLine.hasNext()) {
    TimeLineLine* pLine = iActiveLine.next();
    float linePosition = pLine->getPosition().x;

    if(viewportPosition > linePosition || linePosition >= viewportEndPosition){
      toRemove.push_back(pLine);
    }
  }

  QListIterator<TimeLineLine*> iToRemove(toRemove);
  while(iToRemove.hasNext()) {
    TimeLineLine* pLine = iToRemove.next();
    deactiveLine(pLine);
  }

  // Initial line position
  float linePosition = qCeil(viewportPosition / _m_lineSpacing) * _m_lineSpacing;
  QTime time(0, 0);
  time = time.addSecs(linePosition);

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
          pLine->setLabel(time.toString("mm::ss"));
          break;
      }
    }

    // If line doesn't exists, put a new one.
    if(!exists) {
      TimeLineLine* pNewLine = getAvailableLine();
      if(pNewLine != nullptr) {
        pNewLine->setPosition(linePosition, 0.0f);
        pNewLine->setLabel(time.toString("mm::ss"));
      }
    }

    time = time.addSecs(_m_lineSpacing);
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
  // TODO
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

void WaveformEditor::onViewportMoved(const float &_newPosition)
{
  updateTimeline();
  return;
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
    Cotorro::Log(
          eLOGTYPE::kError,
          QObject::tr("| WaveformEditor | No lines available.")
    );
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

