#include "ctStorySectionEditorWidget.h"

namespace ct {

StorySectionEditorWidget::StorySectionEditorWidget
(
  QWidget* _parent,
  const QPoint& _position,
  const QSize& _size
) :
  SfmlCanvas(_parent, _position, _size),
  _m_clearColor(148, 148, 148),
  _m_view(sf::Vector2f(0,0), sf::Vector2f(300.0f,200.0f))
{
  return;
}

void
StorySectionEditorWidget::resizeEvent(QResizeEvent *_event)
{
  // Resize SFML Window.
  sf::RenderWindow::setSize(sf::Vector2u(width(), height()));

  // Resize SFML View.
  resetView();
  return;
}

void
StorySectionEditorWidget::onInit()
{
  _m_elapsed = 0;

  // Set SFML View
  resetView();

  QWidget::setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  return;
}

void
StorySectionEditorWidget::onUpdate()
{
  _m_elapsed += getDeltaTime().asSeconds();

  sf::RenderWindow::clear(_m_clearColor);

  sf::CircleShape shape(50);

  // set the shape color to green
  shape.setFillColor(sf::Color(100, 250, 50));
  shape.setPosition(0,0);

  sf::RenderWindow::draw(shape);

  return;
}

void
StorySectionEditorWidget::resetView()
{
  quint32 w = width();
  quint32 h = height();

  _m_view.setSize(w, h);
  _m_view.setCenter(w * 0.5, h * 0.5);
  sf::RenderWindow::setView(_m_view);

  return;
}

}

