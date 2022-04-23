#ifndef STORYSECTIONMANAGER_H
#define STORYSECTIONMANAGER_H

#include <QObject>
#include <QMap>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "ctCotorroUtilities.h"

namespace ct {

class StorySection;
class Word;

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
   * @brief Save information in the file.
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
   * @brief Sets the active section by its name.
   *
   * @param _name Story section name.
   */
  void
  setActiveSectionByName(const QString& _name);

  /**
   * @brief Set active section to nullptr.
   */
  void
  setActiveSectionToNull();

  /**
   * @brief Indicates if has an active story section.
   *
   * @return True if it has an active story section.
   */
  bool
  hasActiveSection();

  /**
   * @brief Get the active section.
   *
   * @return Returns the active section. Returns undefined
   * if no section is selected.
   */
  StorySection*
  getActiveSection();

  /**
   * @brief Set the active word from the active story section.
   */
  void
  setActiveWord(const quint32&);

  /**
   * TODO
   */
  void
  setActiveWordStart(const float&);

  /**
   * TODO
   */
  void
  setActiveWordEnd(const float&);

  /**
   * @brief Set the active word to nullptr.
   */
  void
  setActiveWordToNull();

  /**
   * @brief Checks if has an active word.
   * 
   * @return True if it has an active word.
   */
  bool
  hasActiveWord();

  /**
   * @brief Gets the active word.
   * 
   * @return Pointer to the active word. Could return nullptr
   * if it doesn't have any active word.
   */
  Word*
  getActiveWord();

  /**
   * @brief Get the number of story sections.
   *
   * @return The number of story sections.
   */
  qint32
  size();

  /**
   * @brief Safely destroys this instance.
   */
  void
  destroy();

signals:

  /**
   * @brief Emitted when one or more sections have changed.
   */
  void
  sectionsChanged();

  /**
   * @brief Emitted when the active section has changed.
   */
  void
  activeSectionChanged(ct::StorySection* _pStorySection);

  /**
   * @brief Emitted when the active section has changed.
   */
  void
  activeWordChanged(ct::Word* _pWord);

  /**
   * @brief Emitted when the active word content has changed.
   */
  void
  activeWordContentChanged(ct::Word* _pWord);

private:

  /**
   * @brief attempts to add the story section.
   *
   * @param _pStorySection Pointer to the story section.
   *
   * @return Result.
   */
  eOPRESULT::E
  add(StorySection* _pStorySection);

  /**
   * @brief Sets the active story section.
   *
   * @param _pStorySection Pointer to the active story section.
   */
  void
  setActiveSection(StorySection* _pStorySection);

  /**
   * @brief Map of story sections.
   */
  QMap<QString, StorySection*>
  _m_hStorySections;

  /**
   * @brief Pointer to the active section.
   * */
  StorySection*
  _m_pActiveSection;

  /**
   * @brief Pointer to the active word.
   */
  Word*
  _m_pActiveWord;

};

}

#endif // STORYSECTIONMANAGER_H
