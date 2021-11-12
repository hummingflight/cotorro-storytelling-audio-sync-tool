#include "ctWaveformEditorSlider.h"

#include "ctStorySectionEditorWidget.h"
#include "ctStorySection.h"
#include "ctCotorro.h"

namespace ct {

WaveformEditorSlider::WaveformEditorSlider(StorySectionEditorWidget* _pStorySectionEditorWidget) :
  Frame(),
  _m_buttonArea(),
  _m_buttonShape(),
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
  _window.draw(_m_buttonShape);
  return;
}

void
WaveformEditorSlider::onDrawableAreaChanged()
{
  updateSlider();
  return;
}

void
WaveformEditorSlider::onMousePressed(QMouseEvent *e)
{
  // TODO
  return;
}

void
WaveformEditorSlider::onMouseMoved(QMouseEvent *e)
{
  // TODO
  return;
}

void
WaveformEditorSlider::onMouseReleased(QMouseEvent *e)
{
  // TODO
  return;
}

void
WaveformEditorSlider::onMouseDoubleClicked(QMouseEvent *e)
{
  // TODO
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

  // TODO

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
  updateSlider();
  return;
}

void
WaveformEditorSlider::updateSlider()
{
  float normViewportPosition = _m_pStorySectionEditorWidget->getViewportNormalizedPosition();
  float normViewportLength = _m_pStorySectionEditorWidget->getViewportNormalizedLength();

  if(normViewportLength > 1.0f || normViewportLength <= 0.0f) {
    normViewportLength = 1.0f;
  }

  // Update Button Area
  _m_buttonArea.left = _m_drawableArea.left + _m_drawableArea.width * normViewportPosition;
  _m_buttonArea.top = _m_drawableArea.top;
  _m_buttonArea.width = _m_drawableArea.width * normViewportLength;
  _m_buttonArea.height = _m_drawableArea.height;

  // Update Button Shape
  _m_buttonShape.setPosition(_m_buttonArea.left, _m_buttonArea.top);
  _m_buttonShape.setSize(_m_buttonArea.getSize());

  return;
}

}


