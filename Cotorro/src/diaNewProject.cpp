#include "diaNewProject.h"
#include "ui_diaNewProject.h"

#include <QFileDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QFile>
#include <QXmlStreamWriter>

#include "ctCotorro.h"
#include "ctProject.h"

using ct::Cotorro;
using ct::Project;

DiaNewProject::DiaNewProject(QWidget *parent) :
  QDialog(parent),
  projectDirectory(""),
  projectName(""),
  projectFileName(""),
  projectFullPath(""),
  ui(new Ui::DiaNewProject)
{
  ui->setupUi(this);

  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  // Connections
  connect(ui->line_projectName, &QLineEdit::textChanged, this, &DiaNewProject::updateProjectName);
  connect(ui->line_projectPath, &QLineEdit::textChanged, this, &DiaNewProject::updateProjectDirectory);

  // FileName regular validator.
  // Source: https://richjenks.com/filename-regex/
  QRegularExpression rx("[a-zA-Z0-9_]+$");
  QValidator* validator = new QRegularExpressionValidator(rx, this);
  ui->line_projectName->setValidator(validator);

  updateAcceptButton();
  return;
}

DiaNewProject::~DiaNewProject()
{
  delete ui;
}

void
DiaNewProject::on_pushButton_clicked()
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
DiaNewProject::updateProjectDirectory()
{
  projectDirectory = ui->line_projectPath->text();
  updateAcceptButton();
  return;
}

void
DiaNewProject::updateProjectName()
{
  projectName = ui->line_projectName->text();
  updateAcceptButton();
  return;
}

void
DiaNewProject::updateAcceptButton()
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

ct::eOPRESULT::E
DiaNewProject::setupProjectFolder
  (
    const QString& _projDir,
    const QString& _projName
  )
{

  QDir projectDir(_projDir);
  if(!projectDir.exists()) {
    return ct::eOPRESULT::kDirectoryDoesntExists;
  }

  if(!projectDir.isReadable()) {
    return ct::eOPRESULT::kDirectoryNotReadable;
  }

  ct::eOPRESULT::E opRes = createAssetFolder(projectDir);
  if(opRes != ct::eOPRESULT::kOk) {
    return opRes;
  }

  projectFileName = _projName + "." + Project::ProjectExtension();
  projectFullPath = _projDir + QDir::separator() + projectFileName;

  // Create File.
  QFile projectFile(projectFullPath);
  if(!projectFile.open(QFile::ReadWrite)) {
    return ct::eOPRESULT::kFail;
  }
  projectFile.close();

  // Save File.
  opRes = Cotorro::Instance()->saveProject(projectFullPath);
  if(opRes != ct::eOPRESULT::kOk) {
    return opRes;
  }

  return ct::eOPRESULT::kOk;
}

ct::eOPRESULT::E
DiaNewProject::createAssetFolder(const QDir &_projDir)
{
  QString assetFolderName = "assets";
  if(_projDir.exists(assetFolderName)) {
    return ct::eOPRESULT::kOk;
  }

  if(!_projDir.mkdir(assetFolderName)) {
    return ct::eOPRESULT::kFail;
  }

  return ct::eOPRESULT::kOk;
}

ct::eOPRESULT::E
DiaNewProject::createProjectFile
  (
    const QString &_projPath
  )
{
  QFile projFile(_projPath);

  if(!projFile.open(QIODevice::ReadWrite)) {
    return ct::eOPRESULT::kFail;
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

  return ct::eOPRESULT::kOk;
}


void
DiaNewProject::on_btn_accept_clicked()
{
  ct::eOPRESULT::E result = this->setupProjectFolder
    (
        ui->line_projectPath->text(),
        ui->line_projectName->text()
    );

  if(result != ct::eOPRESULT::kOk) {
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
DiaNewProject::on_btn_cancel_clicked()
{
  reject();
}

