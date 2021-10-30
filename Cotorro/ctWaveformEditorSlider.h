#ifndef WAVEFORMEDITORSLIDER_H
#define WAVEFORMEDITORSLIDER_H

#include "ctFrame.h"
#include "ctSliderButton.h"
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
   * @brief onUpdate
   * @param _window
   */
  virtual void
  onUpdate(sf::RenderWindow& _window) override;

  /**
   * @brief onDrawableAreaChanged
   */
  virtual void
  onDrawableAreaChanged() override;

  /**
   * @brief setStorySectionEditorWidget
   * @param _pStorySectionEditorWidget
   */
  void
  setStorySectionEditorWidget(StorySectionEditorWidget* _pStorySectionEditorWidget);

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
   * @brief _m_button
   */
  SliderButton
  _m_button;

  /**
   * @brief _m_pStorySectionEditorWidget
   */
  StorySectionEditorWidget*
  _m_pStorySectionEditorWidget;
};

}



#endif // WAVEFORMEDITORSLIDER_H
