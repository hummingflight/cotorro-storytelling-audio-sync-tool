#include "diaEditor.h"
#include "ui_diaEditor.h"

#include <QFileDialog>
#include <QMessageBox>

#include "diaNewProject.h"
#include "diaCreateSection.h"

#include "ctCotorro.h"
#include "ctProject.h"
#include "ctStorySection.h"

using ct::Cotorro;
using ct::Project;
using ct::StorySectionManager;
using ct::StorySection;

Editor::Editor(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::Editor)
{
  ui->setupUi(this);
  setCentralWidget(ui->mainSplitter);

  // Create Cotorro's module.
  Cotorro::Start(this);

  // Initialize
  init();
}

Editor::~Editor()
{
  delete ui;
}

QPlainTextEdit*
Editor::getLoggerTextWidget()
{
  return ui->pText_logger;
}

void
Editor::init()
{
  // Initialize Cotorro's module.
  Cotorro::Instance()->init(this);

  // Connections
  connect(ui->btn_addSection, &QPushButton::clicked, this, &Editor::on_actionAddSection_triggered);

  // Init Logger Widget
  QPalette p = ui->pText_logger->palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::white);
  ui->pText_logger->setPalette(p);

  Cotorro::Log(ct::eLOGTYPE::kMessage, "Application initialized.");
  return;
}

void
Editor::updateStorySectionPanel()
{
  clearStorySectionPanel();

  Project& project = Cotorro::Instance()->getProject();
  StorySectionManager& storySectionManager = project.getStorySectionManager();
  QStringList aSectionNames = storySectionManager.getNames();

  QStringList::iterator i;
  QIcon itemIcon(":/icons/assets/icons/document.ico");
  for(i = aSectionNames.begin(); i != aSectionNames.end(); ++i) {
    QListWidgetItem* pItem = new QListWidgetItem(*i, ui->list_storySections);
    pItem->setIcon(itemIcon);
  }

  return;
}

void
Editor::clearStorySectionPanel()
{
  ui->list_storySections->clear();
}

void
Editor::openProject(const QString &_path)
{
  Project& project = Cotorro::Instance()->getProject();
  project.clear();

  ct::eOPRESULT::E res = project.open(_path);
  if(res != ct::eOPRESULT::kOk) {
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
Editor::saveProject()
{
  Project& project = Cotorro::Instance()->getProject();
  ct::eOPRESULT::E res = project.save();
  if(res != ct::eOPRESULT::kOk) {
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
Editor::checkDirt()
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
Editor::on_actionNew_triggered()
{
  checkDirt();

  DiaNewProject dialog(this);
  if(dialog.exec()) {
    openProject(dialog.projectFullPath);
  }

  return;
}

void
Editor::on_actionOpen_triggered()
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
Editor::on_actionSave_triggered()
{
  Project& project = Cotorro::Instance()->getProject();
  if(project.isDirty()) {
    saveProject();
  }

  return;
}


void
Editor::on_actionAddSection_triggered()
{
  // Show Create Section Dialog.
  DiaCreateSection dia(this);
  if(dia.exec()) {

    // Create Story Section.
    Project& project = Cotorro::Instance()->getProject();
    StorySectionManager& storySectionManager = project.getStorySectionManager();
    StorySection* pStorySection = storySectionManager.create(dia.sectionName);
    if(pStorySection == nullptr) {
      QMessageBox errorMsg
        (
            QMessageBox::Icon::Critical,
            "Error",
            "Something went wrong. Could not create story section.",
            QMessageBox::Close,
            this
        );

      return;
    }

    // Fill Story Section.
    pStorySection->setAudioKey(dia.sectionAudioFileName);
    pStorySection->setContent(dia.sectionContent);

    // Update Story Section panel.
    updateStorySectionPanel();
  }

  return;
}
