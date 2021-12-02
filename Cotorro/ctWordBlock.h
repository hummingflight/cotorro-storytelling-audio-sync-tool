#ifndef WORDBLOCK_H
#define WORDBLOCK_H

#include <SFML/Graphics.hpp>

#include "ctCotorroUtilities.h"
#include "ctTransformableNode.h"

namespace ct {

class Word;

/**
 * @brief The WordBlock class
 */
class WordBlock : public TransformableNode
{
public:

  /**
   * @brief WordBlock
   */
  WordBlock();

  /**
   * @brief WordBlock
   */
  WordBlock(eNODE_TYPE::E _type);

  /**
   * @brief ~WordBlock
   */
  virtual
  ~WordBlock();

  /**
   * @brief Updates and draw the word block.
   */
  void
  update(sf::RenderWindow& _window);

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
   * @brief Set the block height.
   *
   * @param _height Height.
   */
  void
  setHeight(const float& _height);

  /**
   * @brief Gets the next word block.
   *
   * @return Next word block.
   */
  WordBlock*
  getNext();

  /**
   * @brief Gets the previous word block.
   *
   * @return Previous word block.
   */
  WordBlock*
  getPrev();

  /**
   * @brief Sets the next word block.
   */
  void
  setNext(WordBlock*);

  /**
   * @brief Dettaches this word block.
   */
  void
  dettach();

  /**
   * @brief Checks if the word block is visible in the
   * given viewport.
   *
   * @param _viewportStart Viewport start in seconds.
   * @param _viewportEnd Viewport end in seconds.
   *
   * @return True if the word bloc is visible in the given viewport.
   */
  bool
  isVisible(const float& _viewportStart, const float& _viewportEnd);

  /**
   * @brief Gets the word block type.
   *
   * @return Word block type.
   */
  const eNODE_TYPE::E&
  getType();

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
   * @brief Word block height.
   */
  float
  _m_height;

  /**
   * @brief Indicates if the word block is active.
   */
  bool
  _m_isActive;

  /**
   * @brief Reference to the next word block.
   */
  WordBlock*
  _m_next;

  /**
   * @brief Reference to the prev word block.
   */
  WordBlock*
  _m_prev;

  /**
   * @brief Node's type.
   */
  eNODE_TYPE::E
  _m_type;

};

}

#endif // WORDBLOCK_H
