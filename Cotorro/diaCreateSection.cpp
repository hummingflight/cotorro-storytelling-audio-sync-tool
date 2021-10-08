#include "diaCreateSection.h"
#include "ui_diaCreateSection.h"

#include <QDir>
#include <QMessageBox>

#include "ctCotorro.h"
#include "ctProject.h"

using sf::SoundSource;

using ct::Cotorro;
using ct::Project;
using ct::StorySectionManager;

DiaCreateSection::DiaCreateSection(QWidget *parent) :
  QDialog(parent),
  sectionName(""),
  sectionAudioFileName(""),
  sectionContent(""),
  ui(new Ui::DiaCreateSection),
  _m_musicPlayer()
{
  ui->setupUi(this);
  init();
  return;
}

DiaCreateSection::~DiaCreateSection()
{
  delete ui;
  stopMusic();
  return;
}

void
DiaCreateSection::onClick_Create()
{
  stopMusic();

  if(checkFields()) {
    sectionName = ui->lineName->text();
    sectionAudioFileName = ui->comboAudio->currentText();
    sectionContent = ui->txtContent->toPlainText();

    accept();
  }

  return;
}

void
DiaCreateSection::onClick_Cancel()
{
  stopMusic();
  reject();

  return;
}

void
DiaCreateSection::onClick_Play()
{
  stopMusic();

  QString selectedFile = ui->comboAudio->currentText();
  if(selectedFile == "") {
    return;
  }

  Project& project = Cotorro::Instance()->getProject();
  QFileInfo fileInfo(project.getAssetsDirectory() + QDir::separator() + selectedFile);

  if(!fileInfo.exists()) {
    return;
  }

  if(!fileInfo.isReadable()) {
    // TODO Not readeable.
    return;
  }   

   if(!_m_musicPlayer.openFromFile(fileInfo.filePath().toStdString())) {
     // TODO Couldn't open file.
     return;
   }

   _m_musicPlayer.play();

  return;
}

void
DiaCreateSection::onClick_Stop()
{
  stopMusic();
  return;
}

void
DiaCreateSection::onMusicComboCurrentTextChanged()
{
  stopMusic();
  return;
}

void
DiaCreateSection::init()
{
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  // Section's name validator
  QRegularExpression rx("[a-zA-Z0-9_]+$");
  QValidator* validator = new QRegularExpressionValidator(rx, this);
  ui->lineName->setValidator(validator);

  // Connections
  connect(ui->btnCreate, &QPushButton::clicked, this, &DiaCreateSection::onClick_Create);
  connect(ui->btnCancel, &QPushButton::clicked, this, &DiaCreateSection::onClick_Cancel);
  connect(ui->btnPlayAudio, &QPushButton::clicked, this, &DiaCreateSection::onClick_Play);
  connect(ui->btnStopAudio, &QPushButton::clicked, this, &DiaCreateSection::onClick_Stop);
  connect(ui->comboAudio, &QComboBox::currentTextChanged, this, &DiaCreateSection::onMusicComboCurrentTextChanged);

  updateAudioCombo();

  return;
}

void
DiaCreateSection::updateAudioCombo()
{
  ui->comboAudio->clear();
  ui->comboAudio->clearEditText();

  Project& project = Cotorro::Instance()->getProject();
  QDir projectDir(project.getAssetsDirectory());
  if(!projectDir.exists()) {
    return;
  }

  if(!projectDir.isReadable()) {
    return;
  }

  projectDir.setNameFilters(QStringList()<<"*.wav"<<"*.ogg"<<"*.m4a");
  projectDir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Readable);

  QStringList aFiles = projectDir.entryList();
  ui->comboAudio->insertItems(0, aFiles);

  return;
}

void
DiaCreateSection::stopMusic()
{
  SoundSource::Status status = _m_musicPlayer.getStatus();
  if(status == SoundSource::Status::Playing) {
    _m_musicPlayer.stop();
  }

  return;
}

bool
DiaCreateSection::checkFields()
{
  if(!ui->lineName->hasAcceptableInput() || ui->lineName->text().isEmpty()) {
    QMessageBox errorBox(this);
    errorBox.setText(tr("Name has invalid characters."));
    errorBox.setInformativeText(tr("Use only alphanumeric characters. Spaces are not allowed."));
    errorBox.setStandardButtons(QMessageBox::Ok);
    errorBox.setIcon(QMessageBox::Warning);

    errorBox.exec();
    return false;
  }

  if(ui->txtContent->toPlainText().isEmpty()) {
    QMessageBox errorBox(this);
    errorBox.setText(tr("Content is empty."));
    errorBox.setInformativeText(tr("Add the story section's content."));
    errorBox.setStandardButtons(QMessageBox::Ok);
    errorBox.setIcon(QMessageBox::Warning);

    errorBox.exec();
    return false;
  }

  if(ui->comboAudio->currentText().isEmpty()) {
    QMessageBox errorBox(this);
    errorBox.setText(tr("No audio selected."));
    errorBox.setInformativeText(tr("Select an audio file of the combo box."));
    errorBox.setStandardButtons(QMessageBox::Ok);
    errorBox.setIcon(QMessageBox::Warning);

    errorBox.exec();
    return false;
  }

  Project& project = Cotorro::Instance()->getProject();
  StorySectionManager& storySectionManager = project.getStorySectionManager();
  if(storySectionManager.has(ui->lineName->text())) {
    QMessageBox errorBox(this);
    errorBox.setText(tr("A story section with that name already exists."));
    errorBox.setInformativeText(tr("Write another name."));
    errorBox.setStandardButtons(QMessageBox::Ok);
    errorBox.setIcon(QMessageBox::Warning);

    errorBox.exec();
    return false;
  }

  return true;
}










