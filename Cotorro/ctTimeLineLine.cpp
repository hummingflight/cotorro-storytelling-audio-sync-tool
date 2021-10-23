#include "ctTimeLineLine.h"

#include <QFile>
#include <QString>

#include "ctCotorro.h"
#include "ctFontResource.h"

namespace ct {

TimeLineLine::TimeLineLine() :
  TransformableNode(),
  _m_height(100),
  _m_text()
{
  return;
}

TimeLineLine::~TimeLineLine()
{
  destroy();
  return;
}

void
TimeLineLine::onDestroy()
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
  // Calculate vertices.
  _m_vertices[0].position.x = 0.0f;
  _m_vertices[0].position.y = 0.0f;

  _m_vertices[1].position.x = 0.0f;
  _m_vertices[1].position.y = _m_height;

  sf::FloatRect globalBounds = _m_text.getGlobalBounds();
  _m_text.setPosition(
      _m_vertices[1].position.x + 3.0f,
      _m_vertices[1].position.y - globalBounds.height * 2.0f
  );

  // Transform vertices.
  _updateTransform();
  _m_vertices[0].position = _m_global.transformPoint(_m_vertices[0].position);
  _m_vertices[1].position = _m_global.transformPoint(_m_vertices[1].position);
  _m_text.setPosition(_m_global.transformPoint(_m_text.getPosition()));

  // Draw Vertices
  _window.draw(_m_vertices, 2, sf::Lines);
  _window.draw(_m_text);
  return;
}

void
TimeLineLine::setHeight(const float &_height)
{
  _m_height = _height;
  return;
}

}

