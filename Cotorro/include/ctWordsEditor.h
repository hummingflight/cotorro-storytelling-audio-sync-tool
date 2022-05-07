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
   * @brief onViewportMoved
   */
  void
  onViewportMoved(const float& _newPosition);

  /**
   * Updates the active word.
   */
  void
  onActiveWordChanged(Word*);

  /**
   * @brief Update the Word Block content and visibility.
   */
  void
  updateWordBlockVisibility();

  /**
   * Updates the Word Block Group transformation.
   */
  void
  updateWordBlockGroupTransformation();

  /**
   * @brief destroy
   */
  void
  destroy();

private:

  /**
   * @brief onInit
   */
  virtual void
  onInit() override;

  /**
   * @brief Word blocks group.
   */
  TransformableNode 
  _m_wordBlocksGroup;

  /**
   * @brief Pointer to the story section editor widget.
   */
  StorySectionEditorWidget* 
  _m_pStorySectionEditorWidget;

  /**
   * TODO
   */
  WordBlock
  _m_wordBlock;
};

}

#endif // WORDSEDITOR_H
