#include "ctButton.h"

namespace ct {

Button::Button() :
  InteractiveArea(),
  _m_rectangle()
{
  return;
}

Button::~Button()
{
  return;
}

void
Button::update(sf::RenderWindow& _window)
{
  // Calculate global area.
  sf::FloatRect globalArea = getGlobalArea();

  // Update Rectangle.
  _m_rectangle.setPosition(globalArea.left, globalArea.top);
  _m_rectangle.setSize(globalArea.getSize());

  // Draw Rectangle.
  _window.draw(_m_rectangle);

  return;
}

}


