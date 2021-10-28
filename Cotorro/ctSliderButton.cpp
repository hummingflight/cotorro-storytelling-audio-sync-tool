#include "ctSliderButton.h"
#include "ctCotorro.h"

namespace ct {

SliderButton::SliderButton() :
  Button()
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
  Cotorro::Log(eLOGTYPE::kMessage, "Mouse Moved!");
  return;
}

}


