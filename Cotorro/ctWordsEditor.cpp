#include "ctWordsEditor.h"

#include "ctCotorro.h"
#include "ctStorySectionEditorWidget.h"
#include "ctStorySectionManager.h"
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
  StorySectionManager& storySectionManager = Cotorro::Instance()->getProject().getStorySectionManager();
  if(!storySectionManager.hasActiveSection()) {
    clearWordBlocks();
    // No active story section.
    return;
  }

  StorySection* pActiveStorySection = storySectionManager.getActiveSection();
  const QList<Word*>& wordList = pActiveStorySection->getWordsList();
  if(wordList.length() == 0) {
    clearWordBlocks();
    // Story section has no words.
    return;
  }

  float viewportPosition = _m_pStorySectionEditorWidget->getViewportPosition();
  float viewportEndPosition = viewportPosition
                            + _m_pStorySectionEditorWidget->getViewportLength();

  // Remove non visible word blocks.
  clipping(viewportPosition, viewportEndPosition);

  // Find the first vistible word to the left.
  Word* pFirstWord = findFirtWordInViewport(
    0,
    wordList.length() - 1,
    viewportPosition,
    viewportEndPosition,
    wordList
  );

  if(pFirstWord == nullptr) {
    // No visible word.
    return;
  }

  WordBlock* previousWordBlock = &_m_startWordBlock;
  Word* iWord = pFirstWord;
  quint32 iWordIndex = iWord->getIndex();

  while(iWord->isVisibleInViewport(viewportPosition, viewportEndPosition)) {

    WordBlock* pCurrentNext = previousWordBlock->getNext();
    if(pCurrentNext->getType() != eNODE_TYPE::kEnd) {
      Word* pCurrentNextWord = pCurrentNext->getWord();
      if(pCurrentNextWord->getIndex() == iWordIndex) {
        // The next word is already set.
        return;
      }
    }

    // Create and assign new word block.
    WordBlock* pNewWordBlock = getWordBlock();
    if(pNewWordBlock == nullptr) {
      Cotorro::Log(
        eLOGTYPE::kWarning,
        QObject::tr("| WordsEditor | Word blocks pool is out of elements.")
      );
      // No word blocks available.
      return;
    }

    pNewWordBlock->setWord(iWord);
    previousWordBlock->setNext(pNewWordBlock);

    iWordIndex++;
    if(iWordIndex >= wordList.length()) {
      // Final word was reach.
      return;
    }

    // Prepare for next iteration.
    previousWordBlock = pNewWordBlock;
    iWord = wordList.at(iWordIndex);
  }

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
  _m_startWordBlock.setNext(&_m_endWordBlock);
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

Word*
WordsEditor::findFirtWordInViewport
(
    const quint32 &_startIndex,
    const quint32 &_endIndex,
    const float &_viewportStart,
    const float &_viewportEnd,
    const QList<Word *> &_list
)
{

  // Indices are the same, check word.
  if(_startIndex == _endIndex) {
    Word* pWord = _list.at(_startIndex);
    if(pWord->isVisibleInViewport(_viewportStart, _viewportEnd)) {
      return pWord;
    }
    return nullptr;
  }

  // Get the middle index
  quint32 mid = qFloor((_endIndex - _startIndex)/2);
  mid += _startIndex;

  Word* pStartWord = _list.at(_startIndex);
  Word* pMidWord = _list.at(mid);
  Word* pMidPlusWord = _list.at(mid+1);
  Word* pEndWord = _list.at(_endIndex);

  // Check Left
  if(isRegionVisible(
       pStartWord->getStart(),
       pMidWord->getEnd(),
       _viewportStart,
       _viewportEnd
  )) {
    return findFirtWordInViewport(
          _startIndex,
          mid,
          _viewportStart,
          _viewportEnd,
          _list
    );
  }

  // Check Right
  else if(isRegionVisible(
            pMidPlusWord->getStart(),
            pEndWord->getEnd(),
            _viewportStart,
            _viewportEnd
  )) {
    return findFirtWordInViewport(
          mid+1,
          _endIndex,
          _viewportStart,
          _viewportEnd,
          _list
    );
  }

  // No visible region.
  return nullptr;
}

bool
WordsEditor::isRegionVisible
(
    const float& _start,
    const float& _end,
    const float &_viewportStart,
    const float &_viewportEnd
)
{
  if(_start >= _viewportStart && _start < _viewportEnd ) {
    return true;
  }
  else if(_start <= _viewportStart && _end > _viewportStart) {
    return true;
  }

  return false;
}

}

