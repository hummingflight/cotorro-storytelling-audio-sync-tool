#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QDir>

#include "cotorroutilities.h"

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
  Q_OBJECT

public:

  /**
   * @brief Constructor
   *
   * @param parent
   */
  explicit NewProjectDialog(QWidget *parent = nullptr);

  /**
   * Destructor
   */
  ~NewProjectDialog();

  /**
   * @brief Project's path.
   */
  QString
  projectPath;

  /**
   * @brief Project's name.
   */
  QString
  projectName;

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
   * @brief Updates the project's path.
   *
   * @param _name Project's path.
   */
  void
  updateProjectPath();

private:

  /**
   * @brief Updates the accept button.
   */
  void
  updateAcceptButton();

  /**
   * @brief Setup the project's folder.
   */
  eOPRESULT::E
  setupProjectFolder(const QString& _projPath, const QString& _projName);

  /**
   * @brief Create the asset's folder.
   *
   * @param _projPath Project's path.
   *
   * @return Operation result.
   */
  eOPRESULT::E
  createAssetFolder(const QDir& _projPath);

  /**
   * @brief Creates the project's file.
   *
   * @param _projPath Project's path.
   * @param _projName Project's name.
   *
   * @return  Operation result.
   */
  eOPRESULT::E
  createProjectFile(const QDir& _projPath, const QString& _projName);

  /**
   * @brief ui
   */
  Ui::NewProjectDialog*
  ui;
};

#endif // NEWPROJECTDIALOG_H
