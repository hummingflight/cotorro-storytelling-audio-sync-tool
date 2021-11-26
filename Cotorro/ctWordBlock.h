#ifndef WORDBLOCK_H
#define WORDBLOCK_H

#include <SFML/Graphics.hpp>

namespace ct {

class Word;

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

  /**
   * @brief Sets the word to this word block. It can
   * be nullptr.
   *
   * @param _pWord Word. It can be nullptr for empty blocks.
   */
  void
  setWord(Word* _pWord);

  /**
   * @brief Checks if this block has an assignated word.
   *
   * @return True if the block has an assignated word.
   */
  bool
  hasWord();

  /**
   * @brief Gets the assignated word. It will return nullptr
   * if there isn't any assignated word.
   *
   * @return Assignated word. Can returns nullptr.
   */
  Word*
  getWord();

  /**
   * @brief Cheks if the word block is being used.
   *
   * @return True if the word block is currently being used.
   */
  bool
  isActive();

  /**
   * @brief Actives the word block.
   */
  void
  active();

  /**
   * @brief Deactives the word block.
   */
  void
  deactive();

  /**
   * @brief Safely destroys this object.
   */
  void
  destroy();

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
   * @brief _m_pWord
   */
  Word*
  _m_pWord;

  /**
   * @brief Indicates if the word block is active.
   */
  bool
  _m_isActive;

};

}

#endif // WORDBLOCK_H
