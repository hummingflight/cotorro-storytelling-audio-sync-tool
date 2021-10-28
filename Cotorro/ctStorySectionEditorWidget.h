#ifndef STORYSECTIONEDITORWIDGET_H
#define STORYSECTIONEDITORWIDGET_H

#include "ctSfmlCanvas.h"
#include "ctFrame.h"
#include "ctWaveformEditor.h"
#include "ctWaveformEditorSlider.h"
#include "ctWordsEditor.h"
#include "ctTimeLineLine.h"

namespace ct {

/**
 * @brief The StorySectionEditorWidget class
 */
class StorySectionEditorWidget :
    public SfmlCanvas
{
  Q_OBJECT

public:

  /**
   * @brief Constructor
   *
   * @param _parent
   * @param _position
   * @param _size
   */
  explicit StorySectionEditorWidget
  (
    QWidget* _parent,
    const QPoint& _position,
    const QSize& _size
  );

  /**
   * @brief Sets the zoom value. It should be in a range from 0.0 to 1.0.
   * @param Zoom value.
   */
  void
  setZoom(const float& _zoom);

  /**
   * @brief Gets the number of pixels per second. It takes into account the
   * zoom value.
   */
  float
  getPixelsPerSecond();

  /**
   * @brief Get the zoom value.
   *
   * @return Zoom value.
   */
  const float&
  getZoom();

protected:

  /**
   * @brief resizeEvent
   * @param _event
   */
  void
  resizeEvent(QResizeEvent* _event) override;

  /**
   * @brief mousePressEvent
   * @param e
   */
  void
  mousePressEvent(QMouseEvent* e) override;

  /**
   * @brief mouseMoveEvent
   * @param e
   */
  void
  mouseMoveEvent(QMouseEvent* e) override;

  /**
   * @brief mouseReleaseEvent
   * @param e
   */
  void
  mouseReleaseEvent(QMouseEvent* e) override;

  /**
   * @brief mouseDoubleClickEvent
   * @param e
   */
  void
  mouseDoubleClickEvent(QMouseEvent* e) override;

  /**
   * @brief Update frames.
   */
  void
  updateFrames();

  /**
   * @brief Update Frame's transformations.
   */
  void
  updateFramesTransformations();


private:

  /**
   * @brief onInit
   */
  void
  onInit() override;

  /**
   * @brief onUpdate
   */
  void
  onUpdate() override;

  /**
   * @brief resetView
   */
  void
  resetView();

  /**
   * @brief Canvas's clear color.
   */
  sf::Color
  _m_clearColor;

  /**
   * @brief _m_elapsed
   */
  float
  _m_elapsed;

  /**
   * @brief _m_view
   */
  sf::View
  _m_view;

  /**
   * @brief _m_waveFormFrame
   */
  WaveformEditor
  _m_waveFormEditor;

  /**
   * @brief _m_wordsFrame
   */
  WordsEditor
  _m_wordsEditor;

  /**
   * @brief _M_waveFormEditorSlider
   */
  WaveformEditorSlider
  _m_waveFormEditorSlider;

  /**
   * @brief _m_pixelsPerSecond
   */
  float
  _m_pixelsPerSecond;

  /**
   * @brief _m_scale
   */
  float
  _m_zoom;

  /**
   * @brief _MIN_PIXEL_PER_SECOND
   */
  static float _MIN_PIXEL_PER_SECOND;

  /**
   * @brief _MAX_PIXEL_PER_SECOND
   */
  static float _MAX_PIXEL_PER_SECOND;

};

}

#endif // STORYSECTIONEDITORWIDGET_H
