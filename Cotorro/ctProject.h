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
  open(const QString& _projectFilePath);

  /**
   * @brief Save project.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  save();

  /**
   * @brief Save project in the given path.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  save(const QString& _m_path);

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
