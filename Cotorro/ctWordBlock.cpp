#include "ctWordBlock.h"

namespace ct {

WordBlock::WordBlock() :
  _m_blockShape(),
  _m_text(),
  _m_pWord(nullptr),
  _m_isActive(false)
{
  return;
}

void
WordBlock::setWord(Word *_pWord)
{
  _m_pWord = _pWord;
  return;
}

bool
WordBlock::hasWord()
{
  return _m_pWord != nullptr;
}

Word*
WordBlock::getWord()
{
  return _m_pWord;
}

void
WordBlock::destroy()
{
  _m_pWord = nullptr;
  return;
}

}

