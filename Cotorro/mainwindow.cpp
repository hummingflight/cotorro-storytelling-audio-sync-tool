#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "newProjectDialog.h"

#include "cotorro.h"
#include "ctProject.h"

using ct::Cotorro;
using ct::Project;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setCentralWidget(ui->mainSplitter);

  // Create Cotorro's module.
  Cotorro::Start(this);

  // Initialize
  init();
}

MainWindow::~MainWindow()
{
  delete ui;
}

QPlainTextEdit*
MainWindow::getLoggerTextWidget()
{
  return ui->pText_logger;
}

void
MainWindow::init()
{
  // Initialize Cotorro's module.
  Cotorro::Instance()->init(this);

  // Init Logger Widget
  QPalette p = ui->pText_logger->palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::white);
  ui->pText_logger->setPalette(p);

  Cotorro::Log(eLOGTYPE::kMessage, "Application initialized.");
  return;
}

void
MainWindow::openProject(const QString &_path)
{
  Project& project = Cotorro::Instance()->getProject();
  project.clear();

  eOPRESULT::E res = project.open(_path);
  if(res != eOPRESULT::kOk) {
    QMessageBox errorMsg
      (
          QMessageBox::Icon::Critical,
          "Project creation failed",
          "Something went wrong during the project's preparation.",
          QMessageBox::Close,
          this
      );

    errorMsg.exec();
  }

  return;
}

void
MainWindow::saveProject()
{
  Project& project = Cotorro::Instance()->getProject();
  eOPRESULT::E res = project.save();
  if(res != eOPRESULT::kOk) {
    QMessageBox errorMsg
      (
          QMessageBox::Icon::Critical,
          "Save Error",
          "Something went wrong. The project couldn't be saved.",
          QMessageBox::Close,
          this
      );

    errorMsg.exec();
  }

  return;
}

void
MainWindow::checkDirt()
{
  Project& project = Cotorro::Instance()->getProject();
  if(project.isDirty()) {

    QMessageBox warnMsg
      (
          QMessageBox::Icon::Warning,
          "Save current project",
          "Do you want to save the current project?",
          QMessageBox::Yes | QMessageBox::No,
          this
      );

    if(warnMsg.exec()) {
      saveProject();
    }
  }

  return;
}

void
MainWindow::on_actionNew_triggered()
{
  checkDirt();

  NewProjectDialog dialog(this);
  if(dialog.exec()) {
    openProject(dialog.projectFullPath);
  }

  return;
}

void
MainWindow::on_actionOpen_triggered()
{
  checkDirt();

  QFileDialog dialog(this, tr("Select project file"), QDir::home().path());
  dialog.setFileMode(QFileDialog::FileMode::ExistingFile);
  dialog.setNameFilter(tr("Cotorro Projects (*.cotorro)"));

  if(!dialog.exec())
  {
    return;
  }

  QList<QString> allSelected = dialog.selectedFiles();
  if(allSelected.size() <= 0) {
    return;
  }

  openProject(allSelected[0]);
}

void
MainWindow::on_actionSave_triggered()
{
  Project& project = Cotorro::Instance()->getProject();
  if(project.isDirty()) {
    saveProject();
  }

  return;
}

