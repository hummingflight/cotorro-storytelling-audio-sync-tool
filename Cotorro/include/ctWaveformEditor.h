#ifndef WAVEFORMEDITOR_H
#define WAVEFORMEDITOR_H

#include <SFML/Graphics.hpp>

#include <QMouseEvent>

#include "ctFrame.h"
#include "ctTimeLineLine.h"
#include "ctWaveWordShadow.h"

namespace ct {

class StorySection;
class Word;
class StorySectionEditorWidget;

/**
 * @brief The WaveformEditor class
 */
class WaveformEditor : public Frame
{
public:

  /**
   * @brief WaveformEditor
   */
  WaveformEditor(StorySectionEditorWidget* _pStorySectionEditorWidget);

  /**
   * @brief ~WaveformEditor
   */
  virtual
  ~WaveformEditor();

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
   * @brief updateTimeline
   */
  void
  updateTimeline();

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
   * @brief onActiveWordChanged
   * @param _pWord Active word.
   */
  void
  onActiveWordChanged(Word* _pWord);

  /**
   * @brief onViewportMoved
   */
  void
  onViewportMoved(const float& _newPosition);

  /**
   * Get the cursor position.
   */
  float
  getCursorPosition();

  /**
   * @brief destroy
   */
  void
  destroy();

  /**
   * @brief Maximum size of time line lines pool.
   */
  static quint32 _TIME_LINE_LINE_POOL_SIZE;

protected:

private:

  /**
   * @brief onInit
   */
  virtual void
  onInit() override;  

  /**
   * @brief hasAvailableLine
   * @return
   */
  bool
  hasAvailableLine();

  /**
   * @brief getAvailableLine
   * @return
   */
  TimeLineLine*
  getAvailableLine();

  /**
   * @brief deactiveLine
   * @param _pTimeLineLine
   */
  void
  deactiveLine(TimeLineLine* _pTimeLineLine);

  /**
   * @brief _m_cursor
   */
  TimeLineLine
  _m_cursor;

  /**
   * @brief _activeTimeLineLines
   */
  QList<TimeLineLine*>
  _m_activeTimeLineLines;

  /**
   * @brief _deactiveTimeLineLines
   */
  QList<TimeLineLine*>
  _m_deactiveTimeLineLines;

  /**
   * @brief _m_pStorySectionEditorWidget
   */
  StorySectionEditorWidget*
  _m_pStorySectionEditorWidget;

  /**
   * @brief _m_waveformNode
   */
  TransformableNode
  _m_waveformNode;

  /**
   * WaveFormShadow
   */
  WaveFormWordShadow
  _m_waveFormWordShadow;

  /**
   * @brief Space between lines in seconds.
   */
  float
  _m_lineSpacing;
};

}


#endif // WAVEFORMEDITOR_H
