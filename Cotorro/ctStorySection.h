#ifndef STORYSECTION_H
#define STORYSECTION_H

#include <QObject>

namespace ct {

/**
 * @brief The StorySection class
 */
class StorySection : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief StorySection
   * @param parent
   */
  explicit StorySection(QObject *parent = nullptr);

  /**
   * @brief Initialize.
   */
  void
  init();

  /**
   * @brief Initialize
   *
   * @param _name Section's name.
   */
  void
  init(const QString& _name);

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

signals:

private:

  /**
   * @brief Pretty name.
   */
  QString _m_name;

  /**
   * @brief Stringified UUID in format in 128 format.
   */
  QString _m_uuid;

  /**
   * @brief Audio identifier.
   */
  QString _m_audioKey;

  /**
   * @brief Section content.
   */
  QString _m_content;

};

}

#endif // STORYSECTION_H
