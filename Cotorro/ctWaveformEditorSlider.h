#ifndef WAVEFORMEDITORSLIDER_H
#define WAVEFORMEDITORSLIDER_H

#include <QMouseEvent>

#include "ctFrame.h"
#include "ctStorySection.h"

namespace ct {

class StorySectionEditorWidget;

/**
 * @brief The WaveformEditorSlider class
 */
class WaveformEditorSlider : public Frame
{
public:

  /**
   * @brief WaveformEditorSlider
   */
  WaveformEditorSlider(StorySectionEditorWidget* _pStorySectionEditorWidget);

  /**
   * @brief ~WaveformEditorSlider
   */
  virtual
  ~WaveformEditorSlider();

  /**
   * @brief Draws the button in the SFML Canvas
   *
   * @param _window SFML Render Window.
   */
  virtual void
  onUpdate(sf::RenderWindow& _window) override;

  /**
   * @brief onDrawableAreaChanged
   */
  virtual void
  onDrawableAreaChanged() override;

  /**
   * @brief onMousePressed
   */
  void
  onMousePressed(QMouseEvent* e);

  /**
   * @brief onMouseMoved
   */
  void
  onMouseMoved(QMouseEvent* e);

  /**
   * @brief onMouseReleased
   */
  void
  onMouseReleased(QMouseEvent* e);

  /**
   * @brief onMouseDoubleClicked
   */
  void
  onMouseDoubleClicked(QMouseEvent* e);

  /**
   * @brief onStorySectionChanged
   * @param _pStorySection
   */
  void
  onStorySectionChanged(StorySection* _pStorySection);

  /**
   * @brief onViewportMoved
   */
  void
  onViewportMoved(const float& _newPosition);

  /**
   * @brief updateSliderProperties
   */
  void
  updateSlider();

  /**
   * @brief destroy
   */
  void
  destroy();

protected:

  /**
   * @brief onInit
   */
  virtual void
  onInit() override;

  /**
   * @brief Represent the area of the slider button.
   */
  sf::FloatRect
  _m_buttonArea;

  /**
   * @brief Slider button shape, which is used to draw the button using
   * the SFML render.
   */
  sf::RectangleShape
  _m_buttonShape;

  /**
   * @brief _m_pStorySectionEditorWidget
   */
  StorySectionEditorWidget*
  _m_pStorySectionEditorWidget;

  /**
   * @brief Save the last mouse position.
   */
  QPoint
  _m_lastMousePosition;

  /**
   * @brief Indicates if the slider was pressed.
   */
  bool
  _m_sliderPressed;
};

}



#endif // WAVEFORMEDITORSLIDER_H
