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
   * @brief Removes non visible word blocks.
   */
  void
  clipping(const float& _viewportStart, const float& _viewportEnd);

  /**
   * @brief Finds the first visible word (the first one to the left) in the
   * given viewport. This is a recursive function.
   *
   * @param _startIndex Array segment start index.
   * @param _endIndex Array segment end index.
   * @param _viewportStart Viewport start point in seconds.
   * @param _viewportEnd Viewport final point in seconds.
   * @param _list Words list.
   *
   * @return The first visible word. Returns nullptr if there isn't any visible
   * word.
   */
  Word*
  findFirtWordInViewport(
      const quint32& _startIndex,
      const quint32& _endIndex,
      const float& _viewportStart,
      const float& _viewportEnd,
      const QList<Word*>& _list
  );

  /**
   * @brief Checks if region is visible in the given viewport.
   *
   * @param _start Region's start point in seconds.
   * @param _end Region's end point in seconds.
   * @param _viewportStart Viewport start point in seconds.
   * @param _viewportEnd Viewport final point in seconds.
   *
   * @return True if the word is visible in the viewport.
   */
  bool
  isRegionVisible(
      const float& _start,
      const float& _end,
      const float& _viewportStart,
      const float& _viewportEnd
  );

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

  /**
   * @brief The start node of the linked list.
   */
  WordBlock _m_startWordBlock;

  /**
   * @brief The final node of the linded list.
   */
  WordBlock _m_endWordBlock;
};

}

#endif // WORDSEDITOR_H
