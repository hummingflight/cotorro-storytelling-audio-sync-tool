#include "ctTimeLineLine.h"

#include <QFile>
#include <QString>

#include "ctCotorro.h"
#include "ctFontResource.h"

namespace ct {

TimeLineLine::TimeLineLine()
{

}

void
TimeLineLine::init()
{

  ResourceManager& resourceManager = Cotorro::Instance()->getResourceManager();
  FontResource& fontResource = resourceManager.getFontData("arial.ttf");

  _m_text.setFont(fontResource.sfmlFont);
  _m_text.setString("Hello Wooooooooooooooooooooooooooooorld");
  _m_text.setCharacterSize(24);
  _m_text.setFillColor(sf::Color::Red);
  _m_text.setPosition(100, 100);

}

void
TimeLineLine::setPosition(const qint32 &_x, const qint32 &_y)
{

}

void
TimeLineLine::setLabel(const QString &_string)
{

}

void
TimeLineLine::update(sf::RenderWindow &_window)
{
  _window.draw(_m_text);
  return;
}

}

