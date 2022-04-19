#include "ctWordsEditor.h"

#include "ctCotorro.h"
#include "ctStorySectionEditorWidget.h"
#include "ctStorySectionManager.h"
#include "ctStorySection.h"

namespace ct {

WordsEditor::WordsEditor(StorySectionEditorWidget* _pStorySectionEditorWidget) :
  Frame(),
  _m_wordBlock(),
  _m_wordBlocksGroup(),
  _m_pStorySectionEditorWidget(_pStorySectionEditorWidget)
{
  return;
}

WordsEditor::~WordsEditor()
{
  return;
}

void
WordsEditor::onUpdate(sf::RenderWindow &_window)
{
  _m_wordBlock.update(_window);
  return;
}

void
WordsEditor::onDrawableAreaChanged()
{
  _m_wordBlock.setHeight(_m_drawableArea.height);
  updateWordBlockGroupTransformation();
  return;
}

void
WordsEditor::onMousePressed(QMouseEvent *e)
{
  return;
}

void
WordsEditor::onMouseMoved(QMouseEvent *e)
{
  QPointF position = e->windowPos();
  return;
}

void
WordsEditor::onMouseReleased(QMouseEvent *e)
{
  return;
}

void
WordsEditor::onMouseDoubleClicked(QMouseEvent *e)
{
  return;
}

void
WordsEditor::onViewportMoved(const float &_newPosition)
{
  updateWordBlockGroupTransformation();
}

void 
WordsEditor::onActiveWordChanged(Word* _pWord)
{
  _m_wordBlock.setWord(_pWord);
  updateWordBlockVisibility();
  return;
}

void
WordsEditor::updateWordBlockVisibility()
{
  _m_wordBlock.setActive(_m_wordBlock.hasWord());
  return;
}

void
WordsEditor::updateWordBlockGroupTransformation()
{
  float viewportPosition = _m_pStorySectionEditorWidget->getViewportPosition();
  float viewportEndPosition = viewportPosition
                              + _m_pStorySectionEditorWidget->getViewportLength();

  _m_wordBlocksGroup.setPosition(-viewportPosition * _m_pStorySectionEditorWidget->getPixelsPerSecond(), 0.0f);
  _m_wordBlocksGroup.setScale(_m_pStorySectionEditorWidget->getPixelsPerSecond(), 1.0f);
  return;
}

void
WordsEditor::destroy()
{
  _m_wordBlock.destroy();
  return;
}

void
WordsEditor::onInit()
{  
  _m_wordBlocksGroup.setParent(_m_frameNode);
  _m_wordBlock.init();
  _m_wordBlock.setParent(_m_wordBlocksGroup);
  return;
}
}

