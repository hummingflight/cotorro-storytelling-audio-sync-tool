#ifndef WAVEFORMEDITOR_H
#define WAVEFORMEDITOR_H

#include <SFML/Graphics.hpp>

#include "ctFrame.h"

namespace ct {

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
   * @brief onDrawableAreaChanged
   */
  virtual void
  onDrawableAreaChanged() override;

protected:

private:

  /**
   * @brief updateTimeline
   */
  virtual void
  updateTimeline();
};

}


#endif // WAVEFORMEDITOR_H
