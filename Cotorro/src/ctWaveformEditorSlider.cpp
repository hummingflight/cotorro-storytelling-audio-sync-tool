#include "ctWaveformEditorSlider.h"

#include "ctStorySectionEditorWidget.h"
#include "ctStorySection.h"
#include "ctCotorro.h"

namespace ct {

WaveformEditorSlider::WaveformEditorSlider(StorySectionEditorWidget* _pStorySectionEditorWidget) :
  Frame(),
  _m_buttonArea(),
  _m_buttonShape(),
  _m_pStorySectionEditorWidget(_pStorySectionEditorWidget),
  _m_lastMousePosition(),
  _m_sliderPressed(false)
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
  QPoint mousePosition = e->pos();
  _m_lastMousePosition = mousePosition;

  if(_m_buttonArea.contains(mousePosition.x(), mousePosition.y())) {
    _m_sliderPressed = true;
  }

  return;
}

void
WaveformEditorSlider::onMouseMoved(QMouseEvent *e)
{
  QPoint mousePosition = e->pos();
  if(_m_sliderPressed) {
    _m_pStorySectionEditorWidget->moveViewport(
      _m_pStorySectionEditorWidget->getMediaLength()
      * (mousePosition.x() - _m_lastMousePosition.x())
      / _m_drawableArea.width
    );
  }
  _m_lastMousePosition = mousePosition;
  return;
}

void
WaveformEditorSlider::onMouseReleased(QMouseEvent *e)
{
  _m_sliderPressed = false;
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
  updateSlider();
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

  // Slider Color
  _m_buttonShape.setFillColor(sf::Color(80, 80, 80));
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


