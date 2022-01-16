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
  WordBlock(const eNODE_TYPE::E& _type);

  /**
   * @brief ~WordBlock
   */
  virtual
  ~WordBlock();

  /**
   * @brief Initialize the word block.
   */
  void
  init();

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
   * @brief Checks if this block has an assigned word.
   *
   * @return True if the block has an assigned word.
   */
  bool
  hasWord();

  /**
   * @brief Gets the assigned word. It will return nullptr
   * if there isn't any assigned word.
   *
   * @return Assigned word. Can returns nullptr.
   */
  Word*
  getWord();

  /**
   * @brief Detaches to the assigned word, if it has one.
   */
  void
  clearWord();

  /**
   * @brief Checks if the word block is being used.
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
   * @brief Deactivate the word block.
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
   * @brief Sets the word block status.
   *
   * @param _status Word block status.
   */
  void
  setStatus(const eBLOCK_STATUS::E& _status);

  /**
   * @brief Gets the word block status.
   *
   * @return Word block status.
   */
  const eBLOCK_STATUS::E&
  getStatus();

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
   * @brief Block's node status.
   */
  eBLOCK_STATUS::E
  _m_status;

};

}

#endif // WORDBLOCK_H
