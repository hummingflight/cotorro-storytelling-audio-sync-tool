#ifndef FRAME_H
#define FRAME_H

#include <QObject>

#include <SFML/Graphics.hpp>

namespace ct {

/**
 * @brief The Frame class
 */
class Frame
{
public:

  /**
   * @brief Constructor.
   */
  Frame();

  /**
   * @brief Destructor.
   */
  virtual
  ~Frame();

  /**
   * @brief onUpdate
   */
  virtual void
  onUpdate(sf::RenderWindow& _window);

  /**
   * @brief onDrawableAreaChanged
   */
  virtual void
  onDrawableAreaChanged();

  /**
   * @brief Init
   */
  void
  init();

  /**
   * @brief setSize
   *
   * @param _width
   * @param _height
   */
  void
  setSize(const quint32& _width, const quint32 _height);

  /**
   * @brief setPosition
   *
   * @param _x
   * @param _y
   */
  void
  setPosition(const quint32& _x, const quint32& _y);

  /**
   * @brief setMargin
   *
   * @param _left
   * @param _top
   * @param _right
   * @param _bottom
   */
  void
  setMargin(
      const quint32& _left,
      const quint32& _top,
      const quint32& _right,
      const quint32& _bottom
  );

  /**
   * @brief Set the minimum size.
   *
   * @param _width
   * @param _height
   */
  void
  setMinimumSize(const quint32& _width, const quint32 _height);

protected:

  /**
   * @brief onInit
   */
  virtual void
  onInit();

  /**
   * @brief Update drawable area.
   */
  void
  updateDrawableArea();

  /**
   * @brief _m_marginTopDown
   */
  sf::Vector2u
  _m_marginTopDown;

  /**
   * @brief _m_marginLeftRight
   */
  sf::Vector2u
  _m_marginLeftRight;

  /**
   * @brief Frame's position.
   */
  sf::Vector2u
  _m_position;

  /**
   * @brief Frame's size.
   */
  sf::Vector2u
  _m_size;

  /**
   * @brief _m_minimumSize
   */
  sf::Vector2u
  _m_minimumSize;

  /**
   * @brief _m_drawArea
   */
  sf::Rect<quint32>
  _m_drawableArea;

  /**
   * @brief Frame's border.
   */
  sf::RectangleShape
  _m_frameBorder;
};

}


#endif // FRAME_H
