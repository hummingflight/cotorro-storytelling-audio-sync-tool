#include "ctInteractiveArea.h"

namespace ct {

InteractiveArea::InteractiveArea():
  TransformableNode(),
  _m_area(),
  _m_dragStartPosition()
{
  return;
}

InteractiveArea::~InteractiveArea()
{
  return;
}

void
InteractiveArea::setHeight(const float &_height)
{
  _m_area.height = _height;
  return;
}

void
InteractiveArea::setWidth(const float &_width)
{
  _m_area.width = _width;
  return;
}

void
InteractiveArea::setAreaSize(const float &_height, const float &_width)
{
  _m_area.width = _width;
  _m_area.height = _height;
  return;
}

void
InteractiveArea::receiveMouseInput(const eMOUSE_EVENT::E& _key, QMouseEvent *_e)
{
  sf::FloatRect globalArea = getGlobalArea();
  QPointF position = _e->position();
  if(globalArea.contains(position.x(), position.y())) {    

    switch (_key) {

      case eMOUSE_EVENT::kPressed:
        if(_e->button() == Qt::LeftButton) {
          _m_dragStartPosition = position;
        }

        onMousePressed(_e);
        break;

      case eMOUSE_EVENT::kReleased:
        onMouseReleased(_e);
        break;

      case eMOUSE_EVENT::kMoved:
        if(_e->buttons() & Qt::LeftButton) {
          _m_dragDistance = _e->pos() - _m_dragStartPosition;
        }

        onMouseMoved(_e);
        break;

      case eMOUSE_EVENT::kDoubleClicked:
        onMouseDoubleClicked(_e);
        break;
    }
  }

  return;
}

const sf::FloatRect&
InteractiveArea::getArea()
{
  return _m_area;
}

sf::FloatRect
InteractiveArea::getGlobalArea()
{
  sf::Transform global = getGlobalTransform();
  sf::FloatRect area(_m_area.left, _m_area.top,_m_area.width,_m_area.height);
  return global.transformRect(area);
}

void
InteractiveArea::onAreaChanged()
{
  // Implement in derived class.
  return;
}

void
InteractiveArea::onMousePressed(QMouseEvent *e)
{
  // Implement in derived class.
  return;
}

void
InteractiveArea::onMouseReleased(QMouseEvent *e)
{
  // Implement in derived class.
  return;
}

void
InteractiveArea::onMouseDoubleClicked(QMouseEvent *e)
{
  // Implement in derived class.
  return;
}

void
InteractiveArea::onMouseMoved(QMouseEvent *e)
{
  // Implement in derived class.
  return;
}

}


