#ifndef WORDSEDITOR_H
#define WORDSEDITOR_H

#include "ctFrame.h"

namespace ct {

class StorySection;

/**
 * @brief The WordsEditor class
 */
class WordsEditor: public Frame
{
public:

  /**
   * @brief WordsEditor
   */
  WordsEditor();

  /**
   * @brief ~WordsEditor
   */
  virtual
  ~WordsEditor();

  /**
   * @brief onStorySectionChanged
   * @param _pStorySection
   */
  void
  onStorySectionChanged(StorySection* _pStorySection);
};

}

#endif // WORDSEDITOR_H
