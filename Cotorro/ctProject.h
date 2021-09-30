#ifndef CTPROJECT_H
#define CTPROJECT_H

#include <QObject>
#include <QDir>

#include "cotorroutilities.h"
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
   * @brief Project's path.
   */
  QString
  _m_projectPath;

  /**
   * @brief _m_assetsFolderName
   */
  QString
  _m_assetsFolderName;

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
