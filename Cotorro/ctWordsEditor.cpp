#include "ctWordsEditor.h"

#include "ctStorySectionEditorWidget.h"
#include "ctStorySection.h"

namespace ct {

const quint32 WordsEditor::_WORD_BLOCKS_POOL_SIZE;

WordsEditor::WordsEditor(StorySectionEditorWidget* _pStorySectionEditorWidget) :
  Frame(),
  _m_aDeactiveWordBlocks(),
  _m_wordBlocksGroup(),
  _m_pStorySectionEditorWidget(_pStorySectionEditorWidget),
  _m_startWordBlock(eNODE_TYPE::kStart),
  _m_endWordBlock(eNODE_TYPE::kEnd)
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
  // Update active word blocks.
  WordBlock* pWordBlock = _m_startWordBlock.getNext();
  while(pWordBlock->getType() != eNODE_TYPE::kEnd) {
    pWordBlock->update(_window);
    pWordBlock = pWordBlock->getNext();
  }
  return;
}

void
WordsEditor::onDrawableAreaChanged()
{
  updateWordBlocks();
  return;
}

void
WordsEditor::onMousePressed(QMouseEvent *e)
{

}

void
WordsEditor::onMouseMoved(QMouseEvent *e)
{

}

void
WordsEditor::onMouseReleased(QMouseEvent *e)
{

}

void
WordsEditor::onMouseDoubleClicked(QMouseEvent *e)
{

}

void
WordsEditor::onStorySectionChanged(StorySection *_pStorySection)
{
  // TODO
  return;
}

void
WordsEditor::onViewportMoved(const float &_newPosition)
{

}

void
WordsEditor::updateWordBlocks()
{
  float viewportPosition = _m_pStorySectionEditorWidget->getViewportPosition();
  float viewportEndPosition = viewportPosition
                            + _m_pStorySectionEditorWidget->getViewportLength();

  clipping(viewportPosition, viewportEndPosition);


  return;
}

void
WordsEditor::deactiveWordBlock(WordBlock *_pWordBlock)
{
  _pWordBlock->deactive();
  _pWordBlock->dettach();
  _m_aDeactiveWordBlocks.push_back(_pWordBlock);
  return;
}

WordBlock*
WordsEditor::getWordBlock()
{
  if(!_m_aDeactiveWordBlocks.isEmpty()) {
    WordBlock* pWordBlock = _m_aDeactiveWordBlocks.takeLast();

    pWordBlock->active();
    return pWordBlock;
  }
  return nullptr;
}

void
WordsEditor::clearWordBlocks()
{
  WordBlock* pWordBlock = _m_startWordBlock.getNext();
  while(pWordBlock->getType() != eNODE_TYPE::kEnd) {
    WordBlock* pNext = pWordBlock->getNext();
    deactiveWordBlock(pWordBlock);
    pWordBlock = pNext;
  }
  return;
}

void
WordsEditor::destroy()
{
  clearWordBlocks();
  for(qint32 i = 0; i < WordsEditor::_WORD_BLOCKS_POOL_SIZE; ++i) {
    _m_aWordBlockPool[i].destroy();
  }
  return;
}

void
WordsEditor::onInit()
{
  _m_wordBlocksGroup.setParent(_m_frameNode);
  _m_aDeactiveWordBlocks.clear();

  for(qint32 i = 0; i < WordsEditor::_WORD_BLOCKS_POOL_SIZE; ++i) {
    _m_aWordBlockPool[i].deactive();
    _m_aWordBlockPool[i].setParent(_m_wordBlocksGroup);
    _m_aDeactiveWordBlocks.push_back(&(_m_aWordBlockPool[i]));
  }
  return;
}

void
WordsEditor::clipping(const float& _viewportStart, const float& _viewportEnd)
{
  WordBlock* pWordBlock = _m_startWordBlock.getNext();
  while(pWordBlock->getType() != eNODE_TYPE::kEnd) {
    if(!pWordBlock->isVisible(_viewportStart, _viewportEnd)) {
      pWordBlock = pWordBlock->getNext();
    }
    else {
      WordBlock* next = pWordBlock->getNext();
      deactiveWordBlock(pWordBlock);
      pWordBlock = next;
    }
  }
  return;
}

}

