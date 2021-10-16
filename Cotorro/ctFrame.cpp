#include "ctFrame.h"

namespace ct {

Frame::Frame() :
  _m_marginTopDown(),
  _m_marginLeftRight(),
  _m_position(0, 0),
  _m_size(100, 100),
  _m_minimumSize(100, 100),
  _m_drawableArea(),
  _m_frameBorder()
{
  return;
}

Frame::~Frame()
{
  return;
}

void
Frame::onUpdate(sf::RenderWindow& _window)
{
  _window.draw(_m_frameBorder);
  return;
}

void
Frame::onDrawableAreaChanged()
{
  _m_frameBorder.setPosition(_m_drawableArea.top, _m_drawableArea.left);
  _m_frameBorder.setSize(sf::Vector2f(_m_drawableArea.width, _m_drawableArea.height));
  return;
}

void
Frame::onInit()
{
  return;
}

void
Frame::setSize(const quint32 &_width, const quint32 _height)
{
  _m_size.x = (_width > _m_minimumSize.x ? _width : _m_minimumSize.x);
  _m_size.y = (_height > _m_minimumSize.y ? _height : _m_minimumSize.y);

  updateDrawableArea();
  return;
}

void
Frame::setPosition(const quint32 &_x, const quint32 &_y)
{
  _m_position.x = _x;
  _m_position.y = _y;

  updateDrawableArea();
  return;
}

void
Frame::setMargin
(
    const quint32 &_left,
    const quint32 &_top,
    const quint32 &_right,
    const quint32 &_bottom
)
{
  _m_marginTopDown.x = _top;
  _m_marginTopDown.y = _bottom;
  _m_marginLeftRight.x = _left;
  _m_marginLeftRight.y = _right;

  updateDrawableArea();
  return;
}

void
Frame::setMinimumSize(const quint32 &_width, const quint32 _height)
{
  _m_minimumSize.x = _width;
  _m_minimumSize.y = _height;

  _m_size.x = (_m_size.x >= _m_minimumSize.x ? _m_size.x : _m_minimumSize.x);
  _m_size.y = (_m_size.y >= _m_minimumSize.y ? _m_size.y : _m_minimumSize.y);

  updateDrawableArea();
  return;
}

void
Frame::init()
{
  _m_frameBorder.setOutlineThickness(3);
  _m_frameBorder.setOutlineColor(sf::Color::Black);
  _m_frameBorder.setFillColor(sf::Color(0,0,0,0));

  updateDrawableArea();

  onInit();
  return;
}

void
Frame::updateDrawableArea()
{
  _m_drawableArea.left = _m_position.x + _m_marginTopDown.x;
  _m_drawableArea.top = _m_position.y + _m_marginLeftRight.x;
  _m_drawableArea.width = _m_size.x - _m_marginLeftRight.x - _m_marginLeftRight.y;
  _m_drawableArea.height = _m_size.y - _m_marginTopDown.x - _m_marginTopDown.y;

  onDrawableAreaChanged();
  return;
}

}

