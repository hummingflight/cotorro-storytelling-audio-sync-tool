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
#include "ctWord.h"

using ct::Cotorro;
using ct::Project;
using ct::AudioManager;
using ct::StorySectionManager;
using ct::StorySection;
using ct::StorySectionEditorWidget;

Editor::Editor(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::Editor),
    _m_pStorySectionEditorWidget(nullptr)
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
  Cotorro::Destroy();
  delete ui;
  return;
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

  // Story Section Widget Editor.
  StorySectionEditorWidget* pStorySectionEditorWidget
      = new StorySectionEditorWidget(
          ui->groupSFMLCanvas,
          QPoint(0,0),
          QSize(100, 100)
  );

  QHBoxLayout* pLayout = new QHBoxLayout(ui->groupSFMLCanvas);
  pLayout->addWidget(pStorySectionEditorWidget);

  pStorySectionEditorWidget->show();
  _m_pStorySectionEditorWidget = pStorySectionEditorWidget;

  // Connections
  connect(ui->btn_addSection, &QPushButton::clicked, this, &Editor::on_actionAddSection_triggered);
  connect(ui->btn_removeSection, &QPushButton::clicked, this, &Editor::on_actionRemoveSection_triggered);
  connect(ui->list_storySections, &QListWidget::itemDoubleClicked, this, &Editor::onStorySectionDoubleClicked);  
  connect(ui->list_storySectionWords, &QListWidget::itemSelectionChanged, this, &Editor::onWordSelectionChanged);
  connect(ui->btnRename, &QPushButton::clicked, this, &Editor::onRenameButtonClick);
  connect(ui->btnPlaySimulation, &QPushButton::clicked, this, &Editor::onPlaySimulation);
  connect(ui->btnPauseSimulation, &QPushButton::clicked, this, &Editor::onPauseSimulation);
  connect(ui->btnStopSimulation, &QPushButton::clicked, this, &Editor::onStopSimulation);
  connect(ui->sliderVolumen, &QSlider::valueChanged, this, &Editor::onVolumenValueChanged);
  connect(ui->sliderZoom, &QSlider::valueChanged, this, &Editor::onZoomValueChanged);
  connect(ui->slider_pitch, &QSlider::valueChanged, this, &Editor::onSpeedValueChanged);
  connect(ui->lineEdit_wordStart, &QLineEdit::editingFinished, this, &Editor::onLineEditorWordStartChanged);
  connect(ui->lineEdit_wordEnd, &QLineEdit::editingFinished, this, &Editor::onLineEditorWordEndChanged);
  connect(ui->lineEdit_wordData, &QLineEdit::editingFinished, this, &Editor::onLineEditorWordDataChanged);
  connect(ui->btnStartKey, &QPushButton::clicked, this, &Editor::onWordStartKeyButtonPressed);
  connect(ui->btnEndKey, &QPushButton::clicked, this, &Editor::onWordEndKeyButtonPressed);

  Project& project = pCotorro->getProject();
  StorySectionManager& storySectionManager = project.getStorySectionManager();

  connect(&storySectionManager, &StorySectionManager::sectionsChanged, this, &Editor::onStoryManagerChanged);
  connect(&storySectionManager, &StorySectionManager::activeSectionChanged, this, &Editor::onActiveSectionChanged);
  connect(&storySectionManager, &StorySectionManager::activeWordChanged, this, &Editor::onActiveWordChanged);
  connect(&storySectionManager, &StorySectionManager::activeWordContentChanged, this, &Editor::onActiveWordContentChanged);

  // Init Logger Widget
  QPalette p = ui->pText_logger->palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::white);
  ui->pText_logger->setPalette(p);

  // Validator for section's name line widget
  QRegularExpression rx("[a-zA-Z0-9_]+$");
  QValidator* validator = new QRegularExpressionValidator(rx, this);
  ui->lineSectionName->setValidator(validator);

  QRegularExpression wordRx("^[+-]?([0-9]*[.])?[0-9]+$");
  QValidator* wordTime = new QRegularExpressionValidator(wordRx, this);
  ui->lineEdit_wordStart->setValidator(wordTime);
  ui->lineEdit_wordEnd->setValidator(wordTime);

  Cotorro::Log(ct::eLOGTYPE::kMessage, tr("Application initialized."));

  ui->lineEdit_wordStart->setDisabled(true);
  ui->lineEdit_wordEnd->setDisabled(true);
  ui->lineEdit_wordData->setDisabled(true);
  ui->btnStartKey->setDisabled(true);
  ui->btnEndKey->setDisabled(true);

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
    pStorySection->resetWords();

    // Update Story Section panel.
    updateStorySectionPanel();
  }

  // Unload any audio coming from the previous dialog.
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
Editor::onWordSelectionChanged()
{
  Project& project = Cotorro::Instance()->getProject();
  StorySectionManager& storySectionManager = project.getStorySectionManager();
  QItemSelectionModel* model = ui->list_storySectionWords->selectionModel();
  if (model->hasSelection()) {
    QModelIndex index = model->currentIndex();
    storySectionManager.setActiveWord(index.row());
  }
  else {
    storySectionManager.setActiveWordToNull();
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
      tr("| Editor | Active story section is nullptr.")
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

  // Fill the editor's list of words with the content from the current
  // story section.
  ui->list_storySectionWords->clear();
  if (_pActiveSection != nullptr) {
    QList<ct::Word*> aWords = _pActiveSection->getWordsList();
    QListIterator<ct::Word*> it(aWords);
    while (it.hasNext()) {
      ct::Word* pWord = it.next();
      ui->list_storySectionWords->addItem(pWord->getWord());
    }
  }

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
Editor::onSpeedValueChanged(qint32 value)
{
  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  audioManager.setPitch(static_cast<float>(value)/100.0f);
}

void
Editor::onZoomValueChanged(qint32 value)
{
  if(_m_pStorySectionEditorWidget != nullptr) {
    _m_pStorySectionEditorWidget->setZoom(value * 0.01f);
  }
  return;
}

void 
Editor::onLineEditorWordStartChanged()
{
  Cotorro* cotorro = Cotorro::Instance();
  StorySectionManager& storySectionMngr = cotorro->getProject().getStorySectionManager();

  storySectionMngr.setActiveWordStart(ui->lineEdit_wordStart->text().toFloat());
}

void 
Editor::onLineEditorWordEndChanged()
{
  Cotorro* cotorro = Cotorro::Instance();
  StorySectionManager& storySectionMngr = cotorro->getProject().getStorySectionManager();

  storySectionMngr.setActiveWordEnd(ui->lineEdit_wordEnd->text().toFloat());
}

void 
Editor::onLineEditorWordDataChanged()
{
  Cotorro* cotorro = Cotorro::Instance();
  StorySectionManager& storySectionMngr = cotorro->getProject().getStorySectionManager();

  storySectionMngr.setActiveWordData(ui->lineEdit_wordData->text());
}

void 
Editor::onActiveWordChanged(ct::Word* _activeWord)
{
  if (_activeWord == nullptr) {
    ui->lineEdit_wordStart->setText(tr(""));
    ui->lineEdit_wordEnd->setText(tr(""));

    ui->lineEdit_wordStart->setDisabled(true);
    ui->lineEdit_wordData->setDisabled(true);
    ui->lineEdit_wordEnd->setDisabled(true);
    ui->btnStartKey->setDisabled(true);
    ui->btnEndKey->setDisabled(true);
    
    return;
  }

  ui->lineEdit_wordStart->setText(QString::number(_activeWord->getStart()));
  ui->lineEdit_wordEnd->setText(QString::number(_activeWord->getEnd()));
  ui->lineEdit_wordData->setText(_activeWord->getData());
  ui->lineEdit_wordStart->setDisabled(false);
  ui->lineEdit_wordData->setDisabled(false);
  ui->lineEdit_wordEnd->setDisabled(false);
  ui->btnStartKey->setDisabled(false);
  ui->btnEndKey->setDisabled(false);
}

void 
Editor::onActiveWordContentChanged(ct::Word* _activeWord)
{
  ui->lineEdit_wordStart->setText(QString::number(_activeWord->getStart()));
  ui->lineEdit_wordEnd->setText(QString::number(_activeWord->getEnd()));
  ui->lineEdit_wordData->setText(_activeWord->getData());
}

void 
Editor::onWordStartKeyButtonPressed()
{
  Cotorro* pCotorro = Cotorro::Instance();
  StorySectionManager& storySectionManager = pCotorro->getProject().getStorySectionManager();
  storySectionManager.setActiveWordStart(_m_pStorySectionEditorWidget->getCursorPosition());
}

void 
Editor::onWordEndKeyButtonPressed()
{
  Cotorro* pCotorro = Cotorro::Instance();
  StorySectionManager& storySectionManager = pCotorro->getProject().getStorySectionManager();
  storySectionManager.setActiveWordEnd(_m_pStorySectionEditorWidget->getCursorPosition());
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