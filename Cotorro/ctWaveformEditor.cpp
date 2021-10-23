#include "ctWaveformEditor.h"

#include "ctCotorro.h"
#include "ctStorySectionEditorWidget.h"

namespace ct {

// Static
quint32 WaveformEditor::_TIME_LINE_LINE_POOL_SIZE = 15;

WaveformEditor::WaveformEditor() :
  Frame(),
  _m_activeTimeLineLines(),
  _m_deactiveTimeLineLines(),
  _m_pStorySectionEditorWidget(nullptr),
  _m_waveformNode()
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

  for(quint32 ii = 0; ii < 15; ++ii) {
    if(hasAvailableLine()) {
      getAvailableLine();
    }
  }

  return;
}

void
WaveformEditor::updateTimeline()
{
  if(_m_pStorySectionEditorWidget == nullptr) {
    return;
  }

  _m_waveformNode.setPosition(0.0f, 0.0f);
  _m_waveformNode.setScale(_m_pStorySectionEditorWidget->getPixelsPerSecond(), 1.0f);

  QTime time(0,0,0);
  float stepSeconds = 15.0f;
  sf::Vector2f position(0.0f, 0.0f);
  foreach(TimeLineLine* _line, _m_activeTimeLineLines) {
    _line->setPosition(position.x, position.y);
    _line->setLabel(time.toString("mm::ss"));

    time = time.addSecs(stepSeconds);
    position.x += stepSeconds;
  }
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

