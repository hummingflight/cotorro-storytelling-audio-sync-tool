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
  _m_view(sf::Vector2f(0,0), sf::Vector2f(300.0f,200.0f)),
  _m_waveFormEditor(),
  _m_wordsEditor()
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
  _m_waveFormEditor.onUpdate(*this);
  _m_wordsEditor.onUpdate(*this);
  return;
}

void
StorySectionEditorWidget::updateFramesTransformations()
{
  quint32 w = width();
  quint32 h = height();

  sf::Vector2u position(0, 0);
  quint32 frameH = h * 0.75f;

  _m_waveFormEditor.setPosition(position.x, position.y);
  _m_waveFormEditor.setSize(w, frameH);

  position.y += frameH;
  frameH = h * 0.25f;

  _m_wordsEditor.setPosition(position.x, position.y);
  _m_wordsEditor.setSize(w, frameH);

  return;
}

void
StorySectionEditorWidget::onInit()
{
  _m_elapsed = 0;

  // Set SFML View
  resetView();

  // Init Frames.
  _m_waveFormEditor.init();
  _m_waveFormEditor.setMargin(10, 10, 10 , 5);

  _m_wordsEditor.init();
  _m_wordsEditor.setMargin(10, 5, 10, 10);

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

