#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include <SFML/Graphics.hpp>

#include <QByteArray>

namespace ct {

/**
 * @brief The FontResource class
 */
class FontResource
{
public:

  /**
   * @brief FontResource
   */
  FontResource();

  /**
   *
  */
  ~FontResource();

  /**
   * @brief destroy
   */
  void
  destroy();

  /**
   * @brief Font file data.
   */
  QByteArray
  data;

  /**
   * @brief SFML Font.
   */
  sf::Font
  sfmlFont;

};

}

#endif // FONTRESOURCE_H
