#ifndef STORYSECTIONEDITORWIDGET_H
#define STORYSECTIONEDITORWIDGET_H

#include "ctSfmlCanvas.h"
#include "ctFrame.h"
#include "ctWaveformEditor.h"
#include "ctWaveformEditorSlider.h"
#include "ctWordsEditor.h"
#include "ctTimeLineLine.h"

namespace ct {

class StorySection;

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
   * @brief Get the zoom value.
   *
   * @return Zoom value.
   */
  const float&
  getZoom();

  /**
   * @brief Gets the number of pixels per second. It takes into account the
   * zoom value.
   */
  float
  getPixelsPerSecond();

  /**
   * @brief Set the viewport position in the timeline.
   *
   * @param _time The viewport position in the timeline.
   */
  const void
  setViewportPosition(const float& _time);

  /**
   * @brief Moves the viewport an x number of seconds.
   *
   * @param _seconds Seconds to move.
   */
  void
  moveViewport(const float& _seconds);  

  /**
   * @brief Get reference to the active story section
   *
   * @return Reference to the active story section.
   */
  StorySection*
  getActiveStorySection();

  /**
   * Gets the pointer to the active word.
   * 
   * @return Pointer to the actice word.
   */
  Word*
  getActiveWord();

  /**
   * @brief Gets the viewport position in the timeline (seconds).
   *
   * @return The position of the viewport in the timeline (seconds).
   */
  float
  getViewportPosition();

  /**
   * @brief Gets the viewport position in the timeline relative to the media duration.
   *
   * @return The viewport position in the timeline relative to the media duration
   */
  float
  getViewportNormalizedPosition();

  /**
   * @brief Gets the viewport length in the timeline (seconds).
   *
   * @return The viewpor length in the timeline (seconds).
   */
  float
  getViewportLength();

  /**
   * @brief Get the viewport length in the timeline relative to the media duration.
   *
   * @return The viewport length in the timeline relative to the media duration.
   */
  float
  getViewportNormalizedLength();

  /**
   * @brief Get the media length in seconds.
   *
   * @return The media length in seconds.
   */
  float
  getMediaLength();

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

private slots:

  /**
   * @brief onActiveSectionChanged
   * @param _pStorySection
   */
  void
  onActiveSectionChanged(ct::StorySection* _pStorySection);

  /**
   * TODO
   */
  void
  onActiveWordChanged(ct::Word* _pWord);


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
   * @brief TODO
   */
  void
  updateViewportPosition(const float& _time);

  /**
   * @brief Make sure viewport position doesn't cross media duration.
   */
  void
  adjustViewportPosition();

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
   * @brief _pActiveStorySection
   */
  StorySection*
  _m_pActiveStorySection;

  /**
   * Active Word.
   */
  Word*
  _m_pActiveWord;

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
   * @brief Defines the second which the viewport start.
   */
  float
  _m_viewportTimePosition;

  /**
   * @brief _MIN_PIXEL_PER_SECOND
   */
  static float _MIN_PIXEL_PER_SECOND;

  /**
   * @brief _MAX_PIXEL_PER_SECOND
   */
  static float _MAX_PIXEL_PER_SECOND;

  /**
   * @brief _PADDING_TOP
   */
  static float _PADDING_TOP;

  /**
   * @brief _PADDING_BOTTOM
   */
  static float _PADDING_BOTTOM;

  /**
   * @brief _PADDING_LEFT
   */
  static float _PADDING_LEFT;

  /**
   * @brief _PADDING_RIGHT
   */
  static float _PADDING_RIGHT;

  /**
   * @brief _PADDING_BETWEEN
   */
  static float _PADDING_BETWEEN;

};

}

#endif // STORYSECTIONEDITORWIDGET_H
