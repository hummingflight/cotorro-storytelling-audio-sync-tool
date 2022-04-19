#ifndef STORYSECTION_H
#define STORYSECTION_H

#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "ctCotorroUtilities.h"
#include "ctWord.h"

namespace ct {

/**
 * @brief The StorySection class
 */
class StorySection : public QObject
{
  Q_OBJECT

public:

  /**
   * @brief StorySection Create an empty story section.
   *
   * @param parent Parent.
   */
  explicit StorySection(QObject *parent = nullptr);

  /**
   * @brief Initialize the story section. Sets the uuid.
   */
  void
  init();

  /**
   * @brief Initialize the story section. Sets the uuid and name.
   *
   * @param _name Section's name.
   */
  void
  init(const QString& _name);

  /**
   * @brief Initialize the story section. Fill the story section with
   * the information coming from the XML Stream Reader.
   *
   * @param _reader XML Stream Reader.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  init(QXmlStreamReader& _reader);

  /**
   * @brief Get the name.
   *
   * @return Name.
   */
  QString
  getName();

  /**
   * @brief Set the name.
   *
   * @param _name Name.
   */
  void
  setName(const QString& _name);

  /**
   * @brief Get the stringified uuid in 128 format.
   *
   * @return Stringified uuid in 128 format.
   */
  QString
  getUuid();

  /**
   * @brief Get the audio key.
   *
   * @return Audio key.
   */
  QString
  getAudioKey();

  /**
   * @brief Set the audio key.
   *
   * @param Audio key.
   */
  void
  setAudioKey(const QString& _audioKey);

  /**
   * @brief Get the content.
   *
   * @return Content.
   */
  QString
  getContent();

  /**
   * @brief Set the content.
   *
   * @param _content Content.
   */
  void
  setContent(const QString& _content);

  /**
   * @brief Save information in the file.
   *
   * @param _writer XML stream writer.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  save(QXmlStreamWriter& _writer);

  /**
   * @brief Clear all generated words.
   */
  void
  clearWords();

  /**
   * @brief Resets the table of words according to the
   * actual content of the story sections. This will override
   * all actual words for new ones.
   */
  void
  resetWords();

  /**
   * @brief Get the list of words.
   *
   * @return List of words.
   */
  const QList<Word*>&
  getWordsList();

  /**
   * @brief Safely destroys this object.
   */
  void
  destroy();

signals:

private:  

  /**
   * @brief Pretty name.
   */
  QString
  _m_name;

  /**
   * @brief Stringified UUID in format in 128 format.
   */
  QString
  _m_uuid;

  /**
   * @brief Audio identifier.
   */
  QString
  _m_audioKey;

  /**
   * @brief Section content.
   */
  QString
  _m_content;

  /**
   * @brief Table of words that corresponds to the section content.
   */
  QList<Word*>
  _m_aWords;
};

}

#endif // STORYSECTION_H
