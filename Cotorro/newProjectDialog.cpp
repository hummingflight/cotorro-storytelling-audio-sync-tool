#include "newProjectDialog.h"
#include "ui_newProjectDialog.h"

#include <QFileDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
  QDialog(parent),
  projectPath(""),
  projectName(""),
  ui(new Ui::NewProjectDialog)
{
  ui->setupUi(this);

  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  // Connections
  connect(ui->line_projectName, &QLineEdit::textChanged, this, &NewProjectDialog::updateProjectName);
  connect(ui->line_projectPath, &QLineEdit::textChanged, this, &NewProjectDialog::updateProjectPath);

  // FileName regular validator.
  // Source: https://richjenks.com/filename-regex/
  QRegularExpression rx("[a-zA-Z0-9_]+$");
  QValidator* validator = new QRegularExpressionValidator(rx, this);
  ui->line_projectName->setValidator(validator);

  updateAcceptButton();
  return;
}

NewProjectDialog::~NewProjectDialog()
{
  delete ui;
}

void
NewProjectDialog::on_pushButton_clicked()
{
  QFileDialog dialog(this, "Select project's directory");
  dialog.setFileMode(QFileDialog::FileMode::Directory);
  dialog.setOptions(QFileDialog::Option::ShowDirsOnly);

  if(!dialog.exec())
  {
    return;
  }

  QList<QString> allSelected = dialog.selectedFiles();
  if(allSelected.size() <= 0) {
    return;
  }

  ui->line_projectPath->setText(allSelected[0]);
  return;
}

void
NewProjectDialog::updateProjectPath()
{
  projectPath = ui->line_projectPath->text();
  updateAcceptButton();
  return;
}

void
NewProjectDialog::updateProjectName()
{
  projectName = ui->line_projectName->text();
  updateAcceptButton();
  return;
}

void
NewProjectDialog::updateAcceptButton()
{
  if(ui->line_projectName->hasAcceptableInput() && ui->line_projectPath->text() != "")
  {
    if(!ui->btn_accept->isEnabled())
    {
      ui->btn_accept->setEnabled(true);
    }
  }
  else
  {
    if(ui->btn_accept->isEnabled())
    {
      ui->btn_accept->setEnabled(false);
    }
  }

  return;
}


void
NewProjectDialog::on_btn_accept_clicked()
{
  accept();
}


void
NewProjectDialog::on_btn_cancel_clicked()
{
  reject();
}

