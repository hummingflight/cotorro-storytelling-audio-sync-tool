#ifndef WAVEFORMWORDSHADOW_H
#define WAVEFORMWORDSHADOW_H

#include <SFML/Graphics.hpp>

#include "ctCotorroUtilities.h"
#include "ctTransformableNode.h"

namespace ct
{

  class Word;

  /**
   * TODO
   */
  class WaveFormWordShadow : public TransformableNode
  {
  public:

    /**
     * TODO
     */
    WaveFormWordShadow();

    /**
     * TODO
     */
    ~WaveFormWordShadow();

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
     * TODO
     */
    bool
    isActive();

    /**
     * TODO
     */
    void
    setActive(const bool& _active);

    /**
     * @brief Set the block height.
     *
     * @param _height Height.
     */
    void
    setHeight(const float& _height);

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
     * @brief Is active?
     */
    bool
    _m_isActive;
  };
}

#endif

