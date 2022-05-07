#include "ctWaveWordShadow.h"

#include "ctWord.h"

namespace ct
{
  WaveFormWordShadow::WaveFormWordShadow():
    _m_blockShape(),
    _m_pWord(nullptr),
    _m_height(10.0f),
    _m_isActive(false)
  {
  }

  WaveFormWordShadow::~WaveFormWordShadow()
  { }

  void 
  WaveFormWordShadow::init()
  { 
    _m_blockShape.setFillColor(sf::Color(0, 0, 255, 35));
  }

  void 
  WaveFormWordShadow::update(sf::RenderWindow& _window)
  {
    if (!_m_isActive) {
      return;
    }
    
    if (_m_pWord == nullptr) {
      return;
    }

    setPosition(_m_pWord->getStart(), 0.0f);
    _updateTransform();

    sf::FloatRect blockShapeFloatRect(
      0.0f,
      0.0f,
      _m_pWord->getEnd() - _m_pWord->getStart(),
      _m_height
    );

    blockShapeFloatRect = _m_global.transformRect(blockShapeFloatRect);
    _m_blockShape.setPosition(
      static_cast<sf::Int32>(blockShapeFloatRect.left),
      static_cast<sf::Int32>(blockShapeFloatRect.top)
    );
    _m_blockShape.setSize(blockShapeFloatRect.getSize());

    _window.draw(_m_blockShape);
  }

  void 
  WaveFormWordShadow::setWord(Word* _pWord)
  {
    _m_pWord = _pWord;
  }

  bool 
  WaveFormWordShadow::hasWord()
  {
    return _m_pWord != nullptr;
  }

  Word* 
  WaveFormWordShadow::getWord()
  {
    return _m_pWord;
  }

  bool 
  WaveFormWordShadow::isActive()
  {
    return _m_isActive;
  }

  void 
  WaveFormWordShadow::setActive(const bool& _active)
  {
    _m_isActive = _active;
  }

  void 
  WaveFormWordShadow::setHeight(const float& _height)
  {
    _m_height = _height;
  }

  void 
  WaveFormWordShadow::destroy()
  {
    _m_pWord = nullptr;
  }
}