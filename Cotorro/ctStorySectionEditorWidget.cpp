#include "ctStorySectionEditorWidget.h"

namespace ct {

StorySectionEditorWidget::StorySectionEditorWidget
(
  QWidget* _parent,
  const QPoint& _position,
  const QSize& _size
) :
  SfmlCanvas(_parent, _position, _size)
{
  return;
}

void
StorySectionEditorWidget::onInit()
{

  return;
}

void
StorySectionEditorWidget::onUpdate()
{
  sf::RenderWindow::clear(sf::Color::Red);
  return;
}

}

