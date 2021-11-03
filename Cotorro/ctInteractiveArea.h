#ifndef INTERACTIVEAREA_H
#define INTERACTIVEAREA_H

#include <QMouseEvent>

#include "ctCotorroUtilities.h"
#include "ctTransformableNode.h"

namespace ct {

/**
 * @brief The InteractiveArea class
 */
class InteractiveArea : public TransformableNode
{
public:

  /**
   * @brief InteractiveArea
   */
  InteractiveArea();

  /**
   * @brief ~InteractiveArea
   */
  virtual
  ~InteractiveArea();

  /**
   * @brief setHeight
   */
  virtual void
  setHeight(const float& _height);

  /**
   * @brief setWidth
   * @param _width
   */
  virtual void
  setWidth(const float& _width);

  /**
   * @brief setSize
   * @param _height
   * @param _width
   */
  virtual void
  setAreaSize(const float& _height, const float& _width);

  /**
   * @brief onMousePressed
   * @param _e
   */
  void
  receiveMouseInput(const eMOUSE_EVENT::E& _key, QMouseEvent* _e);

  /**
   * @brief getArea
   * @return
   */
  const sf::FloatRect&
  getArea();

  /**
   * @brief getGlobalArea
   * @return
   */
  sf::FloatRect
  getGlobalArea();

protected:

  /**
   * @brief onAreaChanged
   */
  virtual void
  onAreaChanged();

  /**
   * @brief onMousePressed
   * @param e
   */
  virtual void
  onMousePressed(QMouseEvent* e);

  /**
   * @brief onMouseReleased
   * @param e
   */
  virtual void
  onMouseReleased(QMouseEvent* e);

  /**
   * @brief onMouseDoubleClicked
   * @param e
   */
  virtual void
  onMouseDoubleClicked(QMouseEvent* e);

  /**
   * @brief onMouseMoved
   * @param e
   */
  virtual void
  onMouseMoved(QMouseEvent* e);

  /**
   * @brief _m_area
   */
  sf::FloatRect
  _m_area;

  /**
   * @brief _m_lastMousePosition
   */
  QPointF
  _m_dragStartPosition;

  /**
   * @brief _m_dragDistance
   */
  QPointF
  _m_dragDistance;

};

}


#endif // INTERACTIVEAREA_H
