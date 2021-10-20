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
   * @brief Set Position.
   *
   * @param _x
   * @param _y
   */
  void
  setPosition(const qint32& _x, const qint32& _y);

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

private:

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
