#ifndef STORYSECTION_H
#define STORYSECTION_H

#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <ctCotorroUtilities.h>

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
   * @brief Initiale the story section. Fill the story section with
   * the information comming from the XML Stream Reader.
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
   * @brief Save infromation in the file.
   *
   * @param _writer XML stream writer.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  save(QXmlStreamWriter& _writer);

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

};

}

#endif // STORYSECTION_H
