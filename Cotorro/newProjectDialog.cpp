#include "newProjectDialog.h"
#include "ui_newProjectDialog.h"

#include <QFileDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QFile>
#include <QXmlStreamWriter>

#include "ctProject.h"

using ct::Project;

NewProjectDialog::NewProjectDialog(QWidget *parent) :
  QDialog(parent),
  projectDirectory(""),
  projectName(""),
  projectFileName(""),
  projectFullPath(""),
  ui(new Ui::NewProjectDialog)
{
  ui->setupUi(this);

  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  // Connections
  connect(ui->line_projectName, &QLineEdit::textChanged, this, &NewProjectDialog::updateProjectName);
  connect(ui->line_projectPath, &QLineEdit::textChanged, this, &NewProjectDialog::updateProjectDirectory);

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
NewProjectDialog::updateProjectDirectory()
{
  projectDirectory = ui->line_projectPath->text();
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

eOPRESULT::E
NewProjectDialog::setupProjectFolder
  (
    const QString& _projDir,
    const QString& _projName
  )
{

  QDir projectDir(_projDir);
  if(!projectDir.exists()) {
    return eOPRESULT::kDirectoryDoesntExists;
  }

  if(!projectDir.isReadable()) {
    return eOPRESULT::kDirectoryNotReadable;
  }

  eOPRESULT::E opRes = createAssetFolder(projectDir);
  if(opRes != eOPRESULT::kOk) {
    return opRes;
  }

  projectFileName = _projName + "." + Project::ProjectExtension();
  projectFullPath = _projDir + QDir::separator() + projectFileName;

  opRes = createProjectFile(projectFullPath);
  if(opRes != eOPRESULT::kOk) {
    return opRes;
  }

  return eOPRESULT::kOk;
}

eOPRESULT::E
NewProjectDialog::createAssetFolder(const QDir &_projDir)
{
  QString assetFolderName = "assets";
  if(_projDir.exists(assetFolderName)) {
    return eOPRESULT::kOk;
  }

  if(!_projDir.mkdir(assetFolderName)) {
    return eOPRESULT::kFail;
  }

  return eOPRESULT::kOk;
}

eOPRESULT::E
NewProjectDialog::createProjectFile
  (
    const QString &_projPath
  )
{
  QFile projFile(_projPath);

  if(!projFile.open(QIODevice::ReadWrite)) {
    return eOPRESULT::kFail;
  }

  QXmlStreamWriter stream(&projFile);
  stream.setAutoFormatting(true);
  stream.writeStartDocument();
  stream.writeStartElement("Project");

  // Application and Organization information.
  stream.writeAttribute("application", QApplication::applicationDisplayName());
  stream.writeAttribute("organization", QApplication::organizationName());
  stream.writeAttribute("website", QApplication::organizationDomain());
  stream.writeAttribute("version", QApplication::applicationVersion());
  stream.writeAttribute("assetsFolderName", "assets");

  // Project elements.
  stream.writeEmptyElement("StorySections");

  stream.writeEndElement();
  stream.writeEndDocument();

  projFile.flush();
  projFile.close();

  return eOPRESULT::kOk;
}


void
NewProjectDialog::on_btn_accept_clicked()
{
  eOPRESULT::E result = this->setupProjectFolder
    (
        ui->line_projectPath->text(),
        ui->line_projectName->text()
    );

  if(result != eOPRESULT::kOk) {
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
  else {
    accept();
  }

  return;
}


void
NewProjectDialog::on_btn_cancel_clicked()
{
  reject();
}

