#include "ctSliderButton.h"

#include "ctCotorro.h"
#include "ctWaveformEditorSlider.h"

namespace ct {

SliderButton::SliderButton() :
  Button(),
  _m_pWaveformEditorSlider(nullptr)
{
  return;
}

SliderButton::~SliderButton()
{
  return;
}

void
SliderButton::update(sf::RenderWindow &_window)
{
  Button::update(_window);
  return;
}

void
SliderButton::onMousePressed(QMouseEvent *e)
{
  Cotorro::Log(eLOGTYPE::kMessage, "Mouse Pressed!");
  return;
}

void
SliderButton::onMouseReleased(QMouseEvent *e)
{
  Cotorro::Log(eLOGTYPE::kMessage, "Mouse Released!");
  return;;
}

void
SliderButton::onMouseDoubleClicked(QMouseEvent *e)
{
  Cotorro::Log(eLOGTYPE::kMessage, "Mouse Double Clicked!");
  return;
}

void
SliderButton::onMouseMoved(QMouseEvent *e)
{
  if(_m_pWaveformEditorSlider == nullptr) {
    return;
  }

  float pixelsPerSecond =
  _m_dragStartPosition =
  return;
}

}


