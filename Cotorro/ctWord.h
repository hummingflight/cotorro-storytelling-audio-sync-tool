#ifndef WORD_H
#define WORD_H

#include <QObject>
#include <QXmlStreamReader>

#include "ctCotorroUtilities.h"

namespace ct {

/**
 * @brief Defines a single word of the story section's content.
 */
class Word
{
public:

  /**
   * @brief Constructor
   */
  Word();

  /**
   * @brief Initialize the word, filling the object
   * with the given information.
   *
   * @param _word Word.
   * @param _start Start point in audio clip where this word should be pronounced.
   * @param _end End point in audio clip where this workd is no longer pronounced.
   * @param _data Word's stringified data.
   */
  void
  init
  (
    const QString& _word,
    const float& _start,
    const float& _end,
    const QString& _data
  );

  /**
   * @brief Initialize the Word. Fills the word with
   * the information comming from the XML Stream Reader.
   *
   * @param _reader XML Stream Reader.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  init(QXmlStreamReader& _reader);

  /**
   * @brief Sets the word.
   *
   * @param _word word.
   */
  void
  setWord(const QString& _word);

  /**
   * @brief Gets the word.
   *
   * @return Word.
   */
  QString
  getWord();

  /**
   * @brief Sets the word's stringified data.
   *
   * @param _data Stringified data.
   */
  void
  setData(const QString& _data);

  /**
   * @brief Gets the word's stringified data.
   *
   * @return Word's stringified data.
   */
  QString
  getData();

  /**
   * @brief Sets the start point in audio clip where this word
   * should be pronounced.
   *
   * @param _start Start point.
   */
  void
  setStart(const float& _start);

  /**
   * @brief Gets the start point in audio clip where this word
   * should be pronounced.
   *
   * @return Start point.
   */
  float
  getStart();

  /**
   * @brief Sets the end point in audio clip where this workd is
   * no longer pronounced.
   *
   * @param _end End point.
   */
  void
  setEnd(const float& _end);

  /**
   * @brief Gets the end point in audio clip where this workd is
   * no longer pronounced.
   *
   * @return End point.
   */
  float
  getEnd();

private:

  /**
   * @brief Word.
   */
  QString
  _m_word;

  /**
   * @brief UUID.
   */
  QString
  _m_uuid;

  /**
   * @brief Word's stringified data.
   */
  QString
  _m_data;

  /**
   * @brief Start point in audio clip where this word should be pronounced.
   */
  float
  _m_start;

  /**
   * @brief End point in audio clip where this workd is no longer pronounced.
   */
  float
  _m_end;

};

}
#endif // WORD_H