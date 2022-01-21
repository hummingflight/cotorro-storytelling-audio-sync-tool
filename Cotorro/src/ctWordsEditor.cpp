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
  quint32 size = _m_aActiveWordBlocks.length();
  for(quint32 i = 0; i < size; ++i) {
    _m_aActiveWordBlocks[i]->update(_window);
  }
  return;
}

void
WordsEditor::onDrawableAreaChanged()
{
  // Update active word blocks.
  quint32 size = _m_aActiveWordBlocks.length();
  for(quint32 i = 0; i < size; ++i) {
    _m_aActiveWordBlocks[i]->setHeight(_m_drawableArea.height);
  }

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
  QPointF position = e->windowPos();
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
  //clearWordBlocks();
  //updateWordBlocks();
  return;
}

void
WordsEditor::onViewportMoved(const float &_newPosition)
{
  updateWordBlocks();
}

void
WordsEditor::updateWordBlocks()
{
  StorySectionManager& storySectionManager = Cotorro::Instance()->getProject().getStorySectionManager();
  if(!storySectionManager.hasActiveSection()) {
    clearWordBlocks();    
    return; // No active story section.
  }

  StorySection* pActiveStorySection = storySectionManager.getActiveSection();
  const QList<Word*>& wordList = pActiveStorySection->getWordsList();
  if(wordList.length() == 0) {
    clearWordBlocks();    
    return; // Story section has no words.
  }

  float viewportPosition = _m_pStorySectionEditorWidget->getViewportPosition();
  float viewportEndPosition = viewportPosition
                            + _m_pStorySectionEditorWidget->getViewportLength();

  _m_wordBlocksGroup.setPosition(-viewportPosition * _m_pStorySectionEditorWidget->getPixelsPerSecond(), 0.0f);
  _m_wordBlocksGroup.setScale(_m_pStorySectionEditorWidget->getPixelsPerSecond(), 1.0f);

  
  clipping(viewportPosition, viewportEndPosition);

  Word* pFirstWord = findFirtWordInViewport(
    0,
    wordList.length() - 1,
    viewportPosition,
    viewportEndPosition,
    wordList
  );

  if(pFirstWord == nullptr) {    
    return; // No visible word.
  }

  Word* iWord = pFirstWord;
  quint32 iWordIndex = iWord->getIndex();
  while(iWord->isVisibleInViewport(viewportPosition, viewportEndPosition)) {

    if(iWord->hasWordBlock()) {
      Cotorro::Log(
        eLOGTYPE::kMessage,
        QObject::tr("Word Ready: Index: %1 Word: %2").arg(iWordIndex).arg(iWord->getWord())
      );

      iWordIndex++;

      // Check if the last word in the linked list is the last word in the section.
      if(iWordIndex >= wordList.length()) {
        break;
      }

      // Continue.
      iWord = wordList.at(iWordIndex);
      continue;
    }

    // Create and assign new word block.
    WordBlock* pNewWordBlock = getWordBlock();
    if(pNewWordBlock == nullptr) {      
      return; // No word blocks available.
    }

    // Set word to word block.
    pNewWordBlock->setWord(iWord);

    // Step word index.
    iWordIndex++;
    if(iWordIndex >= wordList.length()) {      
      break; // Final word was reach.
    }

    // Prepare for next iteration.
    iWord = wordList.at(iWordIndex);
  }

  return;
}

void
WordsEditor::deactiveWordBlock(WordBlock *_pWordBlock)
{
  _pWordBlock->deactive();
  _m_aActiveWordBlocks.removeOne(_pWordBlock);
  _m_aDeactiveWordBlocks.push_back(_pWordBlock);
  return;
}

WordBlock*
WordsEditor::getWordBlock()
{
  if(!_m_aDeactiveWordBlocks.isEmpty()) {
    WordBlock* pWordBlock = _m_aDeactiveWordBlocks.takeLast();

    pWordBlock->active();
    pWordBlock->setHeight(_m_drawableArea.height);

    _m_aActiveWordBlocks.push_back(pWordBlock);
    return pWordBlock;
  }
  return nullptr;
}

void
WordsEditor::selectRange(WordBlock *_start, WordBlock *_final)
{

  return;
}

void
WordsEditor::clearWordBlocks()
{
  while(!_m_aActiveWordBlocks.empty()) {
    WordBlock* pWordBlock = _m_aActiveWordBlocks.takeFirst();
    pWordBlock->deactive();
    _m_aDeactiveWordBlocks.push_back(pWordBlock);
  }
  return;
}

void
WordsEditor::clearSelection()
{
  // TODO
  this->_m_selectionMode = eSELECTION_MODE::kIdle;
  return;
}

void
WordsEditor::destroy()
{
  clearSelection();
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
    _m_aWordBlockPool[i].init();
    _m_aWordBlockPool[i].deactive();
    _m_aWordBlockPool[i].setParent(_m_wordBlocksGroup);
    _m_aDeactiveWordBlocks.push_back(&(_m_aWordBlockPool[i]));
  }
  return;
}

void
WordsEditor::clipping(const float& _viewportStart, const float& _viewportEnd)
{
  QList<WordBlock*> toRemove;
  quint32 size = _m_aActiveWordBlocks.length();
  for(quint32 i = 0; i < size; ++i) {
    WordBlock* wordBlock = _m_aActiveWordBlocks[i];
    if(!wordBlock->isVisible(_viewportStart, _viewportEnd)) {
      toRemove.push_back(wordBlock);
    }
  }

  size = toRemove.length();
  for(quint32 i = 0; i < size; ++i) {
    deactiveWordBlock(toRemove[i]);
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

void
WordsEditor::printActiveBlocksNumber()
{
  Cotorro::Log(eLOGTYPE::kMessage, QObject::tr("Active word blocks: %1").arg(QString::number(_m_aActiveWordBlocks.length())));
}

}

