#include "diaEditor.h"
#include "ui_diaEditor.h"

#include <QFileDialog>
#include <QMessageBox>

#include "diaNewProject.h"
#include "diaCreateSection.h"

#include "ctCotorro.h"
#include "ctProject.h"
#include "ctStorySection.h"
#include "ctStorySectionEditorWidget.h"

using ct::Cotorro;
using ct::Project;
using ct::AudioManager;
using ct::StorySectionManager;
using ct::StorySection;
using ct::StorySectionEditorWidget;

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
  Cotorro* pCotorro = Cotorro::Instance();
  pCotorro->init(this);

  // Create SFML Canvas Widget
  ui->frameStorySectionEditor->show();
  StorySectionEditorWidget* pStorySectionEditorWidget
      = new StorySectionEditorWidget(
          ui->frameStorySectionEditor,
          QPoint(0,0),
          QSize(100, 100)
  );
  pStorySectionEditorWidget->show();
  pStorySectionEditorWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


  Project& project = pCotorro->getProject();

  StorySectionManager& storySectionManager = project.getStorySectionManager();

  // Connections
  connect(ui->btn_addSection, &QPushButton::clicked, this, &Editor::on_actionAddSection_triggered);
  connect(ui->btn_removeSection, &QPushButton::clicked, this, &Editor::on_actionRemoveSection_triggered);
  connect(ui->list_storySections, &QListWidget::itemDoubleClicked, this, &Editor::onStorySectionDoubleClicked);  
  connect(ui->btnRename, &QPushButton::clicked, this, &Editor::onRenameButtonClick);
  connect(ui->btnPlaySimulation, &QPushButton::clicked, this, &Editor::onPlaySimulation);
  connect(ui->btnPauseSimulation, &QPushButton::clicked, this, &Editor::onPauseSimulation);
  connect(ui->btnStopSimulation, &QPushButton::clicked, this, &Editor::onStopSimulation);
  connect(ui->sliderVolumen, &QSlider::valueChanged, this, &Editor::onVolumenValueChanged);

  connect(&storySectionManager, &StorySectionManager::sectionsChanged, this, &Editor::onStoryManagerChanged);
  connect(&storySectionManager, &StorySectionManager::activeSectionChanged, this, &Editor::onActiveSectionChanged);

  // Init Logger Widget
  QPalette p = ui->pText_logger->palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::white);
  ui->pText_logger->setPalette(p);

  // Validator for section's name line widget
  QRegularExpression rx("[a-zA-Z0-9_]+$");
  QValidator* validator = new QRegularExpressionValidator(rx, this);
  ui->lineSectionName->setValidator(validator);

  Cotorro::Log(ct::eLOGTYPE::kMessage, tr("Application initialized."));

  clearEditorPanel();
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
  QIcon itemIcon(tr(":/icons/assets/icons/document.ico"));
  for(i = aSectionNames.begin(); i != aSectionNames.end(); ++i) {
    QListWidgetItem* pItem = new QListWidgetItem(*i, ui->list_storySections);
    pItem->setIcon(itemIcon);
  }

  return;
}

void
Editor::updateEditorPanel(StorySection* _pActiveSection)
{
  clearEditorPanel();

  if(_pActiveSection == nullptr) {
    return;
  }

  ui->lineSectionName->setText(_pActiveSection->getName());
  ui->lblAudioKey->setText(_pActiveSection->getAudioKey());

  return;
}

void
Editor::clearStorySectionPanel()
{
  ui->list_storySections->clear();
}

void
Editor::clearEditorPanel()
{
  ui->lineSectionName->setText(tr(""));
  ui->lblAudioKey->setText(tr(""));

  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  audioManager.unload();

  return;
}

void
Editor::openProject(const QString &_path)
{
  ct::eOPRESULT::E res = Cotorro::Instance()->openProject(_path);
  if(res != ct::eOPRESULT::kOk) {
    QMessageBox errorMsg
      (
          QMessageBox::Icon::Critical,
          tr("Project creation failed"),
          tr("Something went wrong during the project's preparation."),
          QMessageBox::Close,
          this
      );

    errorMsg.exec();
  }
  else {
    QMessageBox infoMsg
      (
          QMessageBox::Icon::Information,
          tr("Project opened"),
          tr("The project was successfully opened."),
          QMessageBox::Ok,
          this
      );

    infoMsg.exec();
  }
  return;
}

void
Editor::saveProject()
{
  ct::eOPRESULT::E res = Cotorro::Instance()->saveProject();
  if(res != ct::eOPRESULT::kOk) {
    QMessageBox errorMsg
      (
          QMessageBox::Icon::Critical,
          tr("Save Error"),
          tr("Something went wrong. The project couldn't be saved."),
          QMessageBox::Close,
          this
      );

    errorMsg.exec();
  }
  else {
    QMessageBox infoMsg
      (
          QMessageBox::Icon::Information,
          tr("Project saved"),
          tr("The project was successfully saved."),
          QMessageBox::Ok,
          this
      );

    infoMsg.exec();
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
          tr("Save current project"),
          tr("Do you want to save the current project?"),
          QMessageBox::Yes | QMessageBox::No,
          this
      );

    if(warnMsg.exec() == QMessageBox::Yes) {
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
  // Stop Simulation
  onStopSimulation();

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
        tr("Error"),
        tr("Something went wrong. Could not create story section."),
        QMessageBox::Close,
        this
      );

      errorMsg.exec();

      return;
    }

    // Fill Story Section.
    pStorySection->setAudioKey(dia.sectionAudioFileName);
    pStorySection->setContent(dia.sectionContent);

    // Update Story Section panel.
    updateStorySectionPanel();
  }

  // Unload any audio comming from the previous dialog.
  // This will force the audio manager to load the active section's
  // audio again when the user hits the "play" simulation button.
  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  audioManager.unload();

  return;
}

void
Editor::onStoryManagerChanged()
{
  updateStorySectionPanel();
  return;
}

void
Editor::onStorySectionDoubleClicked(QListWidgetItem *item)
{
  Project& project = Cotorro::Instance()->getProject();
  StorySectionManager& storySectionManager = project.getStorySectionManager();

  if(item != nullptr) {
    storySectionManager.setActiveSectionByName(item->text());
  }
  else {
    storySectionManager.setActiveSectionToNull();
  }

  return;
}

void
Editor::on_actionRemoveSection_triggered()
{
  QListWidgetItem* pItem = ui->list_storySections->currentItem();
  if(pItem == nullptr) {
    return;
  }

  Project& project = Cotorro::Instance()->getProject();
  StorySectionManager& storySectionManager = project.getStorySectionManager();

  if(storySectionManager.has(pItem->text())) {

    QMessageBox infoMsg
    (
      QMessageBox::Icon::Warning,
      tr("Warning"),
      tr("Are you sure to remove story section with name: ").append(pItem->text()),
      QMessageBox::Yes | QMessageBox::No,
      this
    );

    if(infoMsg.exec() == QMessageBox::Yes) {
      storySectionManager.remove(pItem->text());

      QMessageBox removeMsg
      (
        QMessageBox::Icon::Information,
        tr("Section removed"),
        tr("Story section was removed"),
        QMessageBox::Ok,
        this
      );

      removeMsg.exec();
    }
  }

  return;
}

void
Editor::onRenameButtonClick()
{
  Project& project = Cotorro::Instance()->getProject();
  StorySectionManager& storySectionManager = project.getStorySectionManager();

  if(!storySectionManager.hasActiveSection()) {
    return;
  }

  if(!ui->lineSectionName->hasAcceptableInput()) {
    QMessageBox msgBox
    (
      QMessageBox::Icon::Warning,
      tr("Invalid Name"),
      tr("Write a valid name."),
      QMessageBox::Ok,
      this
    );
    msgBox.exec();

    return;
  }

  QString newName = ui->lineSectionName->text();
  if(newName.isEmpty()) {
    QMessageBox msgBox
    (
      QMessageBox::Icon::Warning,
      tr("Invalid Name"),
      tr("Write a name."),
      QMessageBox::Ok,
      this
    );
    msgBox.exec();

    return;
  }

  StorySection* pActiveSection = storySectionManager.getActiveSection();
  if(pActiveSection == nullptr) {
    Cotorro::Log(
      ct::eLOGTYPE::kError,
      "| Editor | Active story section is nullptr."
    );

    return;
  }

  if(pActiveSection->getName() == newName) {
    return;
  }

  if(storySectionManager.has(newName)) {
    QMessageBox msgBox
    (
      QMessageBox::Icon::Warning,
      tr("Invalid Name"),
      tr("A story section with that name already exists."),
      QMessageBox::Ok,
      this
    );
    msgBox.exec();

    return;
  }

  storySectionManager.rename(pActiveSection->getName(), newName);
  return;
}

void
Editor::onActiveSectionChanged(ct::StorySection *_pActiveSection)
{
  updateEditorPanel(_pActiveSection);
  return;
}

void
Editor::onPlaySimulation()
{
  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  if(!audioManager.isReady()) {

    Project& project = Cotorro::Instance()->getProject();
    StorySectionManager& storySectionManager = project.getStorySectionManager();

    if(!storySectionManager.hasActiveSection()) {
      return;
    }

    StorySection* pStorySection = storySectionManager.getActiveSection();
    if(audioManager.loadFromAssets(pStorySection->getAudioKey()) == ct::eOPRESULT::kOk) {
      audioManager.play();
    }
    else {
      return;
    }
  }

  if(audioManager.isPaused() || audioManager.isStopped()) {
    audioManager.play();
  }

  return;
}

void
Editor::onStopSimulation()
{
  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  audioManager.stop();
  return;
}

void
Editor::onPauseSimulation()
{
  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  audioManager.pause();
  return;
}

void
Editor::onVolumenValueChanged(qint32 value)
{
  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  audioManager.setVolumen(value);
  return;
}


void
Editor::on_actionPlaySimulation_triggered()
{
  onPlaySimulation();
  return;
}


void
Editor::on_actionPauseSimulation_triggered()
{
  onPauseSimulation();
  return;
}


void
Editor::on_actionStopSimulation_triggered()
{
  onStopSimulation();
  return;
}

