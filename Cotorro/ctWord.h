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
   * @param _index Word index.
   */
  void
  init
  (
    const QString& _word,
    const float& _start,
    const float& _end,
    const QString& _data,
    const quint32& _index
  );

  /**
   * @brief Initialize the Word. Fills the word with
   * the information comming from the XML Stream Reader.
   *
   * @param _reader XML Stream Reader.
   * @param _index Word index.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  init(QXmlStreamReader& _reader, const quint32& _index);

  /**
   * @brief Save infromation in the file.
   *
   * @param _writer XML stream writer.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  save(QXmlStreamWriter& _writer);

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

  /**
   * @brief Get the word index.
   * @return
   */
  const quint32&
  getIndex();

private:

  /**
   * @brief Word.
   */
  QString
  _m_word;

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

  /**
   * @brief Word index.
   */
  quint32
  _m_index;

};

}
#endif // WORD_H
