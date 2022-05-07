#ifndef TIMELINELINE_H
#define TIMELINELINE_H

#include <SFML/Graphics.hpp>

#include <QObject>

#include "ctTransformableNode.h"


namespace ct {

/**
 * @brief The TimeLineLine class
 */
class TimeLineLine : public TransformableNode
{

public:

  /**
   * @brief Constructor.
   */
  TimeLineLine();

  /**
   * @brief Destructor.
   */
  virtual
  ~TimeLineLine();

  /**
   * @brief onDestroy
   */
  virtual void
  onDestroy() override;

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
   * @brief setHeight
   *
   * @param _height
   */
  void
  setHeight(const float& _height);

  /**
   * @brief Sets line's color
   * @param _color Color.
   */
  void
  setColor(const sf::Color& _color);

  /**
   * @brief Sets the label in the top of the line.
   *
   * @param _textOnTop True if you want to set the label at the top.
   */
  void
  setDisplayTextOnTop(const bool& _textOnTop);

  /**
   * @brief Setup the text size of the label.
   *
   * @param _size Text size.
   */
  void
  setTextSize(const quint32& _size);

private:

  /**
   * @brief Line's height.
   */
  float
  _m_height;

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

  /**
   * @brief Indicates if the text should be displayed at the top of the line.
   */
  bool
  _m_textOnTop;

};

}

#endif // TIMELINELINE_H
