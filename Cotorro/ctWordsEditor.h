#ifndef WORDSEDITOR_H
#define WORDSEDITOR_H

#include <QMouseEvent>

#include "ctWordBlock.h"
#include "ctFrame.h"

namespace ct {

class StorySection;
class StorySectionEditorWidget;

/**
 * @brief The WordsEditor class
 */
class WordsEditor: public Frame
{
public:

  /**
   * @brief WordsEditor
   */
  WordsEditor(StorySectionEditorWidget* _pStorySectionEditorWidget);

  /**
   * @brief ~WordsEditor
   */
  virtual
  ~WordsEditor();

  /**
   * @brief Updates and draws word blocks in editor.
   *
   * @param _window SFML Render Window.
   */
  virtual void
  onUpdate(sf::RenderWindow& _window) override;

  /**
   * @brief Called when the drawable area has changed.
   */
  virtual void
  onDrawableAreaChanged() override;

  /**
   * @brief onMousePressed
   */
  void
  onMousePressed(QMouseEvent* e);

  /**
   * @brief onMouseMoved
   */
  void
  onMouseMoved(QMouseEvent* e);

  /**
   * @brief onMouseReleased
   */
  void
  onMouseReleased(QMouseEvent* e);

  /**
   * @brief onMouseDoubleClicked
   */
  void
  onMouseDoubleClicked(QMouseEvent* e);

  /**
   * @brief onStorySectionChanged
   * @param _pStorySection
   */
  void
  onStorySectionChanged(StorySection* _pStorySection);

  /**
   * @brief onViewportMoved
   */
  void
  onViewportMoved(const float& _newPosition);

  /**
   * @brief updateWordBlocks
   */
  void
  updateWordBlocks();

  /**
   * @brief Deactive the given word block.
   *
   * @param Word block.
   */
  void
  deactiveWordBlock(WordBlock* _pWordBlock);

  /**
   * @brief Gets an available word block pointer.
   *
   * @return Word block pointer. Returns nullptr if the editor has run out of blocks.
   */
  WordBlock*
  getWordBlock();

  /**
   * @brief Removes all word blocks from the scene.
   */
  void
  clearWordBlocks();

  /**
   * @brief destroy
   */
  void
  destroy();

  /**
   * @brief Maximum size of the word blocks pool.
   */
  static const quint32 _WORD_BLOCKS_POOL_SIZE = 250;

private:

  /**
   * @brief onInit
   */
  virtual void
  onInit() override;

  /**
   * @brief List of active word blocks.
   */
  QList<WordBlock*> _m_aActiveWordBlocks;

  /**
   * @brief List of deactive word blocks.
   */
  QList<WordBlock*> _m_aDeactiveWordBlocks;

  /**
   * @brief Word blocks group.
   */
  TransformableNode _m_wordBlocksGroup;

  /**
   * @brief Pointer to the story section editor widget.
   */
  StorySectionEditorWidget* _m_pStorySectionEditorWidget;

  /**
   * @brief Array of word blocks.
   */
  WordBlock _m_aWordBlockPool[WordsEditor::_WORD_BLOCKS_POOL_SIZE];
};

}

#endif // WORDSEDITOR_H
