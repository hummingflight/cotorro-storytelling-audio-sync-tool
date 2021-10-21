#ifndef WAVEFORMEDITOR_H
#define WAVEFORMEDITOR_H

#include <SFML/Graphics.hpp>

#include "ctFrame.h"
#include "ctTimeLineLine.h"

namespace ct {

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
  WaveformEditor();

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
   * @brief destroy
   */
  void
  destroy();

  /**
   * @brief _TIME_LINE_LINE_POOL_SIZE
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
};

}


#endif // WAVEFORMEDITOR_H
