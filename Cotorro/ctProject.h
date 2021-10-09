#ifndef CTPROJECT_H
#define CTPROJECT_H

#include <QObject>
#include <QDir>

#include "ctCotorroUtilities.h"
#include "ctStorySectionManager.h"

namespace ct {

/**
 * @brief The Project class
 */
class Project : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief ctProject
   * @param parent
   */
  explicit Project(QObject *parent = nullptr);

  /**
   * @brief Get the file extension of a Cotorro Project.
   *
   * @return File extension.
   */
  static const QString&
  ProjectExtension();  

  /**
   * @brief Initialize the class.
   */
  void
  init();

  /**
   * @brief Open a new project.
   *
   * @param _projectFilePath Project's file path.
   *
   * @return Opreation result.
   */
  eOPRESULT::E
  open
  (
    QXmlStreamReader& _reader,
    const QString& _name,
    const QString& _fileName,
    const QString& _fileFullPath,
    const QString& _projectDirectory
  );

  /**
   * @brief Save project.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  save(QXmlStreamWriter& _writer);

  /**
   * @brief Clears the project.
   */
  void
  clear();

  /**
   * @brief Sets the dirt flag to true.
   */
  void
  dirty();

  /**
   * @brief Indicates if the project is dirty.
   *
   * @return True if it is.
   */
  bool
  isDirty();

  /**
   * @brief Get Project's directory.
   *
   * @return Project's directory.
   */
  QString
  getProjectDirectory();

  /**
   * @brief Get Asset's directory.
   *
   * @return Asset's directory.
   */
  QString
  getAssetsDirectory();

  /**
   * @brief Get project's file's full path.
   *
   * @return Project's file's full path.
   */
  QString
  getProjectFileFullPath();

  /**
   * @brief Get the story section manager.
   *
   * @return Story section manager.
   */
  StorySectionManager&
  getStorySectionManager();

signals:

private:

  /**
   * @brief Project's name.
   */
  QString
  _m_name;

  /**
   * @brief Project's file's name.
   */
  QString
  _m_fileName;

  /**
   * @brief Project's file's full path.
   */
  QString
  _m_fileFullPath;

  /**
   * @brief Project's directory.
   */
  QString
  _m_projectDirectory;

  /**
   * @brief Asset's folder's name.
   */
  QString
  _m_assetsFolderName;

  /**
   * @brief Asset's directory.
   */
  QString
  _m_assetsDirectory;

  /**
   * @brief Indicates if the project is dirty.
  */
  bool
  _m_isDirty;

  /**
   * @brief Story Section Manager.
   */
  StorySectionManager
  _m_storySectionManager;

};

}

#endif // CTPROJECT_H
