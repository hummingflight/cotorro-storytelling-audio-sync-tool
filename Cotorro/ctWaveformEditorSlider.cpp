#include "ctWaveformEditorSlider.h"

namespace ct {

WaveformEditorSlider::WaveformEditorSlider() :
  Frame(),
  _m_button()
{
  return;
}

WaveformEditorSlider::~WaveformEditorSlider()
{
  return;
}

void
WaveformEditorSlider::onUpdate(sf::RenderWindow &_window)
{
  _m_button.update(_window);
  return;
}

void
WaveformEditorSlider::onDrawableAreaChanged()
{
  _m_button.setHeight(_m_drawableArea.height);
  _m_button.setWidth(_m_drawableArea.width * 0.5f);

  return;
}

void
WaveformEditorSlider::setStorySectionEditorWidget(StorySectionEditorWidget *_pStorySectionEditorWidget)
{
  return;
}

void
WaveformEditorSlider::onMousePressed(QMouseEvent *e)
{
  _m_button.receiveMouseInput(eMOUSE_EVENT::kPressed, e);
  return;
}

void
WaveformEditorSlider::onMouseMoved(QMouseEvent *e)
{
  _m_button.receiveMouseInput(eMOUSE_EVENT::kMoved, e);
  return;
}

void
WaveformEditorSlider::onMouseReleased(QMouseEvent *e)
{
  _m_button.receiveMouseInput(eMOUSE_EVENT::kReleased, e);
  return;
}

void
WaveformEditorSlider::onMouseDoubleClicked(QMouseEvent *e)
{
  _m_button.receiveMouseInput(eMOUSE_EVENT::kDoubleClicked, e);
  return;
}

void
WaveformEditorSlider::destroy()
{
  return;
}

void
WaveformEditorSlider::onInit()
{
  _m_button.setParent(_m_frameNode);
  return;
}

}


