#include "ctWordBlock.h"

#include "ctCotorro.h"
#include "ctResourceManager.h"
#include "ctWord.h"

namespace ct {

WordBlock::WordBlock() :
  TransformableNode(),
  _m_blockShape(),
  _m_text(),
  _m_pWord(nullptr),
  _m_height(10.0f),
  _m_isActive(false),
  _m_status(eBLOCK_STATUS::kIdle)
{
  setStatus(eBLOCK_STATUS::kIdle);
  return;
}

WordBlock::WordBlock(const eNODE_TYPE::E& _type) :
  TransformableNode(),
  _m_blockShape(),
  _m_text(),
  _m_pWord(nullptr),
  _m_height(1.0f),
  _m_isActive(false),
  _m_status(eBLOCK_STATUS::kIdle)
{
  setStatus(eBLOCK_STATUS::kIdle);
  return;
}

WordBlock::~WordBlock()
{
  return;
}

void
WordBlock::init()
{
  // Setup Label.
  ResourceManager& resourceManager = Cotorro::Instance()->getResourceManager();
  FontResourceManager& fontManager = resourceManager.fontResourceManager();
  if(!fontManager.has("arial_narrow_7.ttf")) {
    Cotorro::Log(
      eLOGTYPE::kError,
      QObject::tr("| TimeLineLine | Font was not found: arial_narrow_7.ttf")
    );
    return;
  }

  const FontResource& fontResource = fontManager.get("arial_narrow_7.ttf");
  _m_text.setFont(fontResource.sfmlFont);
  _m_text.setString("");
  _m_text.setCharacterSize(13);
  _m_text.setFillColor(sf::Color::Black);

  return;
}

void
WordBlock::update(sf::RenderWindow &_window)
{
  if(_m_pWord == nullptr) {
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

  // Setup label position.
  sf::FloatRect textBounds = _m_text.getGlobalBounds();
  if(textBounds.width < blockShapeFloatRect.width) {
    _m_text.setPosition(
      blockShapeFloatRect.left + (blockShapeFloatRect.width * 0.5f) - textBounds.width * 0.5,
      blockShapeFloatRect.top + (blockShapeFloatRect.height * 0.5f) - textBounds.height
    );
    // Draw label.
    _window.draw(_m_text);
  }
  return;
}

void
WordBlock::setWord(Word *_pWord)
{
  clearWord();

  if(_pWord != nullptr) {
    if(_pWord->getWordBlock() != nullptr) {
      _pWord->getWordBlock()->clearWord();
    }

    _m_pWord = _pWord;
    _m_pWord->setWordBlock(this);
    _m_text.setString(_m_pWord->getWord().toStdWString());
  }
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
WordBlock::clearWord()
{
  if(_m_pWord != nullptr) {
    _m_pWord->setWordBlock(nullptr);
    _m_pWord = nullptr;
  }
  return;
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
  clearWord();
  setStatus(eBLOCK_STATUS::kIdle);
  return;
}

void
WordBlock::setHeight(const float &_height)
{
  _m_height = _height;
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

void
WordBlock::setStatus(const eBLOCK_STATUS::E &_status)
{
  _m_status = _status;
  switch (_m_status) {
  case eBLOCK_STATUS::kIdle:
    _m_blockShape.setOutlineThickness(1.0f);
    _m_blockShape.setOutlineColor(sf::Color::Black);
    _m_blockShape.setFillColor(sf::Color(220, 220, 220));
    _m_text.setFillColor(sf::Color::Black);
    break;

  case eBLOCK_STATUS::kSelected:
    _m_blockShape.setOutlineThickness(1.0f);
    _m_blockShape.setOutlineColor(sf::Color::White);
    _m_blockShape.setFillColor(sf::Color(0, 174, 255));
    _m_text.setFillColor(sf::Color::White);
    break;

  case eBLOCK_STATUS::kGrouped:
    _m_blockShape.setOutlineThickness(1.0f);
    _m_blockShape.setOutlineColor(sf::Color::Black);
    _m_blockShape.setFillColor(sf::Color(0, 206, 255));
    _m_text.setFillColor(sf::Color::Black);
    break;

  default:
    _m_blockShape.setOutlineThickness(1.0f);
    _m_blockShape.setOutlineColor(sf::Color::Black);
    _m_blockShape.setFillColor(sf::Color(220, 220, 220));
    _m_text.setFillColor(sf::Color::Black);
    break;
  }
  return;
}

const eBLOCK_STATUS::E&
WordBlock::getStatus()
{
  return _m_status;
}

void
WordBlock::destroy()
{
  _m_pWord = nullptr;
  return;
}

}

