#include "ctTimeLineLine.h"

#include <QFile>
#include <QString>

#include "ctCotorro.h"
#include "ctFontResource.h"

namespace ct {

TimeLineLine::TimeLineLine() :
  _m_height(100),
  _m_position(),
  _m_text()
{
  return;
}

void
TimeLineLine::init()
{
  // Setup vertices.
  _m_vertices[0].color = sf::Color::Black;
  _m_vertices[1].color = sf::Color::Black;

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
  _m_text.setString("0:00");
  _m_text.setCharacterSize(12);
  _m_text.setFillColor(sf::Color::Black);

  _updateLine();
  return;
}

void
TimeLineLine::setLabel(const QString &_string)
{
  _m_text.setString(_string.toStdString());
  return;
}

void
TimeLineLine::update(sf::RenderWindow &_window)
{
  _window.draw(_m_vertices, 2, sf::Lines);
  _window.draw(_m_text);
  return;
}

void
TimeLineLine::setPosition(const float &_x, const float &_y)
{
  _m_position.x = _x;
  _m_position.y = _y;
  _updateLine();
  return;
}

void
TimeLineLine::setHeight(const float &_height)
{
  _m_height = _height;
  _updateLine();
  return;
}

void
TimeLineLine::_updateLine()
{
  _m_vertices[0].position.x = _m_position.x;
  _m_vertices[0].position.y = _m_position.y;

  _m_vertices[1].position.x = _m_position.x;
  _m_vertices[1].position.y = _m_position.y + _m_height;

  sf::FloatRect globalBounds = _m_text.getGlobalBounds();
  _m_text.setPosition(
      _m_vertices[1].position.x + 3.0f,
      _m_vertices[1].position.y - globalBounds.height * 2
  );

  return;
}
}

