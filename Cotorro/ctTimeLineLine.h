#ifndef TIMELINELINE_H
#define TIMELINELINE_H

#include <QObject>
#include <SFML/Graphics.hpp>

namespace ct {

/**
 * @brief The TimeLineLine class
 */
class TimeLineLine
{

public:

  /**
   * @brief Constructor.
   */
  TimeLineLine();

  /**
   * @brief init
   */
  void
  init();

  /**
   * @brief Set line label.
   *
   * @param _string Line label.
   */
  void
  setLabel(const QString& _string);

  /**
   * @brief Draw.
   *
   * @param _window
   */
  void
  update(sf::RenderWindow& _window);

  /**
   * @brief destroy
   */
  void
  destroy();

  /**
   * @brief setPosition
   * @param _x
   * @param _y
   */
  void
  setPosition(const float& _x, const float& _y);

  /**
   * @brief setHeight
   *
   * @param _height
   */
  void
  setHeight(const float& _height);

private:

  /**
   * @brief Updates line.
   */
  void
  _updateLine();

  /**
   * @brief Line's height.
   */
  float
  _m_height;

  /**
   * @brief _m_position
   */
  sf::Vector2f
  _m_position;

  /**
   * @brief Line vertices.
   */
  sf::Vertex
  _m_vertices[2];

  /**
   * @brief Label.
   */
  sf::Text
  _m_text;

};

}

#endif // TIMELINELINE_H
