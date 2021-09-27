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
   * @brief Prepares the project folder when a new project
   * is being created.
   *
   * @param _path Project's path.
   * @param _projectName Project's name.
   *
   * @return Operation result.
   */
  static eOPRESULT::E
  SetupProjectFolder(const QString& _path, const QString& _projectName);

  /**
   * @brief Initialize the class.
   */
  void
  init();

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
   * Project's name.
   */
  QString
  _m_name;

  /**
   * Indicates if the project is dirty.
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
