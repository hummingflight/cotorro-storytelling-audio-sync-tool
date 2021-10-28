#ifndef SLIDERBUTTON_H
#define SLIDERBUTTON_H

#include "ctButton.h"

namespace ct {

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
};

}

#endif // SLIDERBUTTON_H
