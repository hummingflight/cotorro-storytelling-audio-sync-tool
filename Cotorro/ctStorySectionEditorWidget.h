#ifndef STORYSECTIONEDITORWIDGET_H
#define STORYSECTIONEDITORWIDGET_H

#include "ctSfmlCanvas.h"
#include "ctFrame.h"

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

protected:

  /**
   * @brief resizeEvent
   * @param _event
   */
  void
  resizeEvent(QResizeEvent* _event) override;

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
  Frame
  _m_waveFormFrame;

};

}

#endif // STORYSECTIONEDITORWIDGET_H
