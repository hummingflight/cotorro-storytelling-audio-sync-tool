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
  _m_isActive(false)
{
  return;
}

WordBlock::~WordBlock()
{
  return;
}

void
WordBlock::init()
{
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

  if (!_m_isActive) {
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

  sf::FloatRect textBounds = _m_text.getGlobalBounds();
  if(textBounds.width < blockShapeFloatRect.width) {
    _m_text.setPosition(
      blockShapeFloatRect.left + (blockShapeFloatRect.width * 0.5f) - textBounds.width * 0.5,
      blockShapeFloatRect.top + (blockShapeFloatRect.height * 0.5f) - textBounds.height
    );

    _window.draw(_m_text);
  }
  return;
}

void
WordBlock::setWord(Word *_pWord)
{
  _m_pWord = _pWord;

  if (_pWord != nullptr)
  {
    _m_text.setString(_m_pWord->getWord().toStdWString());
  }
  else
  {
    _m_text.setString(sf::String(""));
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

bool
WordBlock::isActive()
{
  return _m_isActive;
}

void
WordBlock::setActive(const bool& _active)
{
  _m_isActive = _active;
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
WordBlock::destroy()
{
  _m_pWord = nullptr;
  return;
}

}

