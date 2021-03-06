#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QDir>

#include "ctCotorroUtilities.h"

namespace Ui {
class DiaNewProject;
}

class DiaNewProject : public QDialog
{
  Q_OBJECT

public:

  /**
   * @brief Constructor
   *
   * @param parent
   */
  explicit DiaNewProject(QWidget *parent = nullptr);

  /**
   * Destructor
   */
  ~DiaNewProject();

  /**
   * @brief Project's path.
   */
  QString
  projectDirectory;

  /**
   * @brief Project's name.
   */
  QString
  projectName;

  /**
   * @brief Project's file's name.
   */
  QString
  projectFileName;

  /**
   * @brief Project's full path.
   */
  QString
  projectFullPath;

private slots:

  /**
   * @brief on_pushButton_clicked
   */
  void
  on_pushButton_clicked();

  /**
   * @brief on_btn_accept_clicked
   */
  void
  on_btn_accept_clicked();

  /**
   * @brief on_btn_cancel_clicked
   */
  void
  on_btn_cancel_clicked();

  /**
   * @brief Updates the project's name.
   *
   * @param _name Project's name.
   */
  void
  updateProjectName();

  /**
   * @brief Updates the project's directory.
   *
   * @param _name Project's directory.
   */
  void
  updateProjectDirectory();

private:

  /**
   * @brief Updates the accept button.
   */
  void
  updateAcceptButton();

  /**
   * @brief Setup the project's folder.
   */
  ct::eOPRESULT::E
  setupProjectFolder(const QString& _projPath, const QString& _projName);

  /**
   * @brief Create the asset's folder.
   *
   * @param _projPath Project's path.
   *
   * @return Operation result.
   */
  ct::eOPRESULT::E
  createAssetFolder(const QDir& _projPath);

  /**
   * @brief Creates the project's file.
   *
   * @param _projPath Project's file path.
   *
   * @return  Operation result.
   */
  ct::eOPRESULT::E
  createProjectFile(const QString& _path);

  /**
   * @brief ui
   */
  Ui::DiaNewProject*
  ui;
};

#endif // NEWPROJECTDIALOG_H
