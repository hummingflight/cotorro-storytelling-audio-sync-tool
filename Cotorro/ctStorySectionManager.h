#ifndef STORYSECTIONMANAGER_H
#define STORYSECTIONMANAGER_H

#include <QObject>
#include <QMap>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "ctCotorroUtilities.h"

namespace ct {

class StorySection;

/**
 * @brief The StorySectionManager class
 */
class StorySectionManager : public QObject
{
  Q_OBJECT

public:

  /**
   * @brief Constructor.
   * @param parent
   */
  explicit StorySectionManager(QObject *parent = nullptr);

  /**
   * @brief init
   */
  void
  init();

  /**
   * @brief Open information from file.
   *
   * @param _reader XML stream reader.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  open(QXmlStreamReader& _reader);

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
   * @brief clear
   */
  void
  clear();

  /**
   * @brief Create a story section.
   *
   * @param _name Name of the new story section.
   *
   * @return Story section
   */
  StorySection*
  create(const QString& _name);

  /**
   * @brief Rename a story section.
   *
   * @param _name The actual name of the story section.
   * @param _newName The new name.
   */
  void
  rename(const QString& _name, const QString& _newName);

  /**
   * @brief Indicates if the manager has a story section.
   *
   * @param _name Story section's Name.
   *
   * @return True if the story section exists.
   */
  bool
  has(const QString& _name);

  /**
   * @brief Get a story section.
   *
   * @param _name Story section's Name.
   *
   * @return Pointer to the story section.
   */
  StorySection*
  get(const QString& _name);

  /**
   * @brief Get all story sections name.
   *
   * @return List with the name of all story sections.
   */
  QStringList
  getNames();

  /**
   * @brief Destroy a story section.
   *
   * @param _name Story section's Name.
   */
  void
  remove(const QString& _name);

  /**
   * @brief Get the number of story sections.
   *
   * @return The number of story sections.
   */
  qint32
  size();

signals:

  /**
   * @brief Called when one or more sections have changed.
   */
  void
  sectionsChanged();

private:

  /**
   * @brief Attemps to add the story section.
   *
   * @param _pStorySection Pointer to the story section.
   *
   * @return Result.
   */
  eOPRESULT::E
  add(StorySection* _pStorySection);

  /**
   * @brief Map of story sections.
   */
  QMap<QString, StorySection*>
  _m_hStorySections;

};

}

#endif // STORYSECTIONMANAGER_H
