#include "ctWordBlock.h"

#include "ctWord.h"

namespace ct {

WordBlock::WordBlock() :
  TransformableNode(),
  _m_blockShape(),
  _m_text(),
  _m_pWord(nullptr),
  _m_height(10.0f),
  _m_isActive(false),
  _m_next(nullptr),
  _m_prev(nullptr),
  _m_type(eNODE_TYPE::kNode)
{

  _m_blockShape.setOutlineThickness(1.0f);
  _m_blockShape.setOutlineColor(sf::Color::Black);
  _m_blockShape.setFillColor(sf::Color(220, 220, 220));
  return;
}

WordBlock::WordBlock(eNODE_TYPE::E _type) :
  TransformableNode(),
  _m_blockShape(),
  _m_text(),
  _m_pWord(nullptr),
  _m_height(1.0f),
  _m_isActive(false),
  _m_next(nullptr),
  _m_prev(nullptr),
  _m_type(_type)
{
  return;
}

WordBlock::~WordBlock()
{
  return;
}

void
WordBlock::update(sf::RenderWindow &_window)
{
  setPosition(_m_pWord->getStart(), 0.0f);

  _updateTransform();

  sf::FloatRect blockShapeFloatRect(
        0.0f,
        0.0f,
        _m_pWord->getEnd() - _m_pWord->getStart(),
        _m_height
  );

  // Transform Rect
  blockShapeFloatRect = _m_global.transformRect(blockShapeFloatRect);

  // Assign to texture.
  _m_blockShape.setPosition(
        static_cast<sf::Int32>(blockShapeFloatRect.left),
        static_cast<sf::Int32>(blockShapeFloatRect.top)
  );
  _m_blockShape.setSize(blockShapeFloatRect.getSize());

  // Draw word block.
  _window.draw(_m_blockShape);
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

bool
WordBlock::isActive()
{
  return _m_isActive;
}

void
WordBlock::active()
{
  _m_isActive = true;
  return;
}

void
WordBlock::deactive()
{
  _m_isActive = false;
  return;
}

void
WordBlock::setHeight(const float &_height)
{
  _m_height = _height;
  return;
}

WordBlock*
WordBlock::getNext()
{
  return _m_next;
}

WordBlock*
WordBlock::getPrev()
{
  return _m_prev;
}

void
WordBlock::setNext(WordBlock* _pWordBlock)
{
  if(_m_next != nullptr) {
    _m_next->_m_prev = _pWordBlock;
  }

  if(_pWordBlock != nullptr) {
    _pWordBlock->_m_next = _m_next;
    _pWordBlock->_m_prev = this;
  }

  _m_next = _pWordBlock;
  return;
}

void
WordBlock::dettach()
{
  if(_m_prev != nullptr) {
    _m_prev->_m_next = _m_next;
  }
  if(_m_next != nullptr) {
    _m_next->_m_prev = _m_prev;
  }

  _m_prev = nullptr;
  _m_next = nullptr;

  return;
}

bool
WordBlock::isVisible(const float &_viewportStart, const float &_viewportEnd)
{
  if(_m_pWord == nullptr) {
    return false;
  }

  return _m_pWord->isVisibleInViewport(_viewportStart, _viewportEnd);
}

const eNODE_TYPE::E&
WordBlock::getType()
{
  return _m_type;
}

void
WordBlock::destroy()
{
  _m_pWord = nullptr;
  return;
}

}

