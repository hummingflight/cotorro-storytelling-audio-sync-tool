#include "ctWaveformEditorSlider.h"

#include "ctStorySectionEditorWidget.h"
#include "ctStorySection.h"
#include "ctCotorro.h"

namespace ct {

WaveformEditorSlider::WaveformEditorSlider(StorySectionEditorWidget* _pStorySectionEditorWidget) :
  Frame(),
  _m_button(),
  _m_pStorySectionEditorWidget(_pStorySectionEditorWidget)
{
  return;
}

WaveformEditorSlider::~WaveformEditorSlider()
{
  return;
}

void
WaveformEditorSlider::onUpdate(sf::RenderWindow &_window)
{
  _m_button.update(_window);
  return;
}

void
WaveformEditorSlider::onDrawableAreaChanged()
{
  updateSlider();
  return;
}

void
WaveformEditorSlider::setStorySectionEditorWidget(StorySectionEditorWidget *_pStorySectionEditorWidget)
{
  _m_pStorySectionEditorWidget = _pStorySectionEditorWidget;
  return;
}

void
WaveformEditorSlider::onMousePressed(QMouseEvent *e)
{
  _m_button.receiveMouseInput(eMOUSE_EVENT::kPressed, e);
  return;
}

void
WaveformEditorSlider::onMouseMoved(QMouseEvent *e)
{
  _m_button.receiveMouseInput(eMOUSE_EVENT::kMoved, e);
  return;
}

void
WaveformEditorSlider::onMouseReleased(QMouseEvent *e)
{
  _m_button.receiveMouseInput(eMOUSE_EVENT::kReleased, e);
  return;
}

void
WaveformEditorSlider::onMouseDoubleClicked(QMouseEvent *e)
{
  _m_button.receiveMouseInput(eMOUSE_EVENT::kDoubleClicked, e);
  return;
}

void
WaveformEditorSlider::onStorySectionChanged(StorySection *_pStorySection)
{
  updateSlider();
  return;
}

void
WaveformEditorSlider::onViewportMoved(const float& _newPosition)
{
  if(_m_pStorySectionEditorWidget == nullptr) {
    Cotorro::Log(
      eLOGTYPE::kError,
      QObject::tr("| WaveformEditorSlider | Story section editor widget is not defined.")
    );
    return;
  }

  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  float trackDuration = audioManager.getDuration();
  if(trackDuration > 0.0f) {
    float positionX = (_newPosition / trackDuration) * _m_drawableArea.width;
    _m_button.setPosition(positionX, _m_button.getPosition().y);
  }

  return;
}

void
WaveformEditorSlider::destroy()
{
  return;
}

void
WaveformEditorSlider::onInit()
{
  _m_button.setParent(_m_frameNode);
  return;
}

void
WaveformEditorSlider::updateSlider()
{
  if(_m_pStorySectionEditorWidget == nullptr) {
    Cotorro::Log(
      eLOGTYPE::kError,
      QObject::tr("| WaveformEditorSlider | Story section editor widget is not defined.")
    );
    return;
  }

  // Set slider height.
  _m_button.setHeight(_m_drawableArea.height);

  // Set slider width.
  StorySection* pActiveSection = _m_pStorySectionEditorWidget->getActiveStorySection();
  if(pActiveSection == nullptr) {
    // No Active section: Slider fill all the drawable area.
    _m_button.setWidth(_m_drawableArea.width);
  }
  else {

    float viewWidthInSeconds = _m_pStorySectionEditorWidget->getViewWidthInSeconds();

    AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
    float trackDuration = audioManager.getDuration();
    float sliderScale = 1.0f;
    if(trackDuration > 0.0f) {
      sliderScale = viewWidthInSeconds / trackDuration;

      // Truncate scale.
      if(sliderScale > 1.0f) {
        sliderScale = 1.0f;
      }
    }

    _m_button.setWidth(_m_drawableArea.width * sliderScale);
  }

  return;
}

}


