#include "diaCreateSection.h"
#include "ui_diaCreateSection.h"

#include <QDir>
#include <QMessageBox>

#include "ctCotorro.h"
#include "ctProject.h"

using sf::SoundSource;

using ct::Cotorro;
using ct::Project;
using ct::AudioManager;
using ct::StorySectionManager;
using ct::eLOGTYPE::E;

DiaCreateSection::DiaCreateSection(QWidget* parent) :
  QDialog(parent),
  sectionName(""),
  sectionAudioFileName(""),
  sectionContent(""),
  ui(new Ui::DiaCreateSection),
  _m_musicPlayerState(ct::eMUSIC_PLAYER_STATE::kWaitingTrack),
  _m_musicPlayer()
{
  ui->setupUi(this);
  init();
  return;
}

DiaCreateSection::~DiaCreateSection()
{
  delete ui;
  stopTrack();
  return;
}

void
DiaCreateSection::onClick_Create()
{
  stopTrack();

  if(checkFields()) {
    sectionName = ui->lineName->text();
    sectionAudioFileName = ui->comboAudio->currentText();
    sectionContent = ui->txtContent->toPlainText();

    accept();
  }
}

void
DiaCreateSection::onClick_Cancel()
{
  stopTrack();
  reject();
}

void
DiaCreateSection::onClick_Play()
{
  stopTrack();
  playTrack();
}

void
DiaCreateSection::onClick_Stop()
{
  stopTrack();
}

void
DiaCreateSection::onMusicComboCurrentTextChanged()
{
  stopTrack();
  loadTrack(ui->comboAudio->currentText());
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
}

void 
DiaCreateSection::loadTrack(const QString& _fileName)
{
  _m_musicPlayer.stop();
  _m_musicPlayerState = ct::eMUSIC_PLAYER_STATE::kWaitingTrack;

  if (_fileName.isEmpty())
  {
    return;
  }

  Project& project = Cotorro::Instance()->getProject();
  QFileInfo fileInfo(project.getAssetsDirectory() + QDir::separator() + _fileName);
  if (!fileInfo.exists()) {
    Cotorro::Log(
      ct::eLOGTYPE::kError,
      tr("| diaCreateSection | File doesn't exists: %1").arg(fileInfo.filePath())
    );
    return;
  }

  if (!fileInfo.isReadable()) {
    Cotorro::Log(
      ct::eLOGTYPE::kError,
      tr("| diaCreateSection | Couldn't read sound file: %1").arg(fileInfo.filePath())
    );
    return;
  }

  if (!_m_musicPlayer.openFromFile(fileInfo.filePath().toStdString().c_str())) {
    Cotorro::Log(
      ct::eLOGTYPE::kError,
      tr("| diaCreateSection | Couldn't open sound file: %1").arg(fileInfo.filePath())
    );
    return;
  }

  _m_musicPlayerState = ct::eMUSIC_PLAYER_STATE::kReady;
}

void
DiaCreateSection::stopTrack()
{
  _m_musicPlayer.stop();
}

void
DiaCreateSection::playTrack()
{
  if (_m_musicPlayerState == ct::eMUSIC_PLAYER_STATE::kReady) {
    _m_musicPlayer.play();
  }
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










