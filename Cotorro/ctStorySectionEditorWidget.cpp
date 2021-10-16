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

  // Update frames
  updateFramesTransformations();
  return;
}

void
StorySectionEditorWidget::updateFrames()
{
  _m_waveFormFrame.onUpdate(*this);
  return;
}

void
StorySectionEditorWidget::updateFramesTransformations()
{
  quint32 w = width();
  quint32 h = height();

  _m_waveFormFrame.setPosition(0,0);
  _m_waveFormFrame.setSize(w, h);

  return;
}

void
StorySectionEditorWidget::onInit()
{
  _m_elapsed = 0;

  // Set SFML View
  resetView();

  // Init Frames.
  _m_waveFormFrame.init();
  _m_waveFormFrame.setMargin(10, 10, 10 ,10);

  // Widget properties.
  QWidget::setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  return;
}

void
StorySectionEditorWidget::onUpdate()
{
  // Delta time.
  _m_elapsed += getDeltaTime().asSeconds();

  // Clear canvas.
  sf::RenderWindow::clear(_m_clearColor);

  // Update Frames.
  updateFrames();

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

