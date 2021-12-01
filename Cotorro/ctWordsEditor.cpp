#include "ctWordsEditor.h"

#include "ctStorySectionEditorWidget.h"
#include "ctStorySection.h"

namespace ct {

const quint32 WordsEditor::_WORD_BLOCKS_POOL_SIZE;

WordsEditor::WordsEditor(StorySectionEditorWidget* _pStorySectionEditorWidget) :
  Frame(),
  _m_aActiveWordBlocks(),
  _m_aDeactiveWordBlocks(),
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
  // Update active word blocks.
  QListIterator<WordBlock*> it(_m_aActiveWordBlocks);
  while(it.hasNext()) {
    it.next()->update(_window);
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
  float viewportEndPosition = viewportPosition + _m_pStorySectionEditorWidget->getViewportLength();


  return;
}

void
WordsEditor::deactiveWordBlock(WordBlock *_pWordBlock)
{
  if(_m_aActiveWordBlocks.removeOne(_pWordBlock)) {
    _pWordBlock->deactive();
    _m_aDeactiveWordBlocks.push_back(_pWordBlock);
  }
  return;
}

WordBlock *WordsEditor::getWordBlock()
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
  QListIterator<WordBlock*> it(_m_aActiveWordBlocks);
  while(it.hasNext()) {
    WordBlock* pWordBlock = it.next();

    pWordBlock->deactive();
    _m_aDeactiveWordBlocks.push_back(pWordBlock);
  }
  _m_aActiveWordBlocks.clear();
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
  _m_aActiveWordBlocks.clear();

  for(qint32 i = 0; i < WordsEditor::_WORD_BLOCKS_POOL_SIZE; ++i) {
    _m_aWordBlockPool[i].deactive();
    _m_aWordBlockPool[i].setParent(_m_wordBlocksGroup);
    _m_aDeactiveWordBlocks.push_back(&(_m_aWordBlockPool[i]));
  }
  return;
}

}

