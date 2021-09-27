#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

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
MainWindow::on_actionNew_triggered()
{
  Project& project = Cotorro::Instance()->getProject();
  if(project.isDirty()) {
    // TODO Do you want to save the actual project?
  }

  NewProjectDialog dialog(this);
  if(dialog.exec()) {
    Cotorro::Log(eLOGTYPE::kMessage, "New project accepted");
  }

  return;
}

