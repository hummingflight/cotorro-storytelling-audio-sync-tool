#ifndef SLIDERBUTTON_H
#define SLIDERBUTTON_H

#include "ctButton.h"

namespace ct {

class WaveformEditorSlider;

/**
 * @brief The SliderButton class
 */
class SliderButton : public Button
{
public:

  /**
   * @brief SliderButton
   */
  SliderButton();

  /**
   * @brief ~SliderButton
   */
  virtual ~SliderButton();

  /**
   * @brief update
   * @param _window
   */
  virtual void
  update(sf::RenderWindow& _window) override;

  /**
   * @brief init
   * @param _m_waveformEditorSlider
   */
  void
  init(WaveformEditorSlider* _m_waveformEditorSlider);

protected:

  /**
   * @brief onMousePressed
   * @param e
   */
  virtual void
  onMousePressed(QMouseEvent* e) override;

  /**
   * @brief onMouseReleased
   * @param e
   */
  virtual void
  onMouseReleased(QMouseEvent* e) override;

  /**
   * @brief onMouseDoubleClicked
   * @param e
   */
  virtual void
  onMouseDoubleClicked(QMouseEvent* e) override;

  /**
   * @brief onMouseMoved
   * @param e
   */
  virtual void
  onMouseMoved(QMouseEvent* e) override;

  /**
   * @brief _m_pWaveformEditorSlider
   */
  WaveformEditorSlider*
  _m_pWaveformEditorSlider;
};

}

#endif // SLIDERBUTTON_H
