#ifndef WORDBLOCK_H
#define WORDBLOCK_H

#include <SFML/Graphics.hpp>

namespace ct {

/**
 * @brief The WordBlock class
 */
class WordBlock
{
public:

  /**
   * @brief WordBlock
   */
  WordBlock();

private:

  /**
   * @brief Block shape.
   */
  sf::RectangleShape
  _m_blockShape;

  /**
   * @brief Word block label.
   */
  sf::Text
  _m_text;

  /**
   * @brief Indicates if the word block is active.
   */
  bool
  _m_isActive;

};

}

#endif // WORDBLOCK_H
