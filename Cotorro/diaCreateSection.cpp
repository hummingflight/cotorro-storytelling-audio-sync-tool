#include "diaCreateSection.h"
#include "ui_diaCreateSection.h"

#include <QDir>

#include "ctCotorro.h"
#include "ctProject.h"

using sf::SoundSource;

using ct::Cotorro;
using ct::Project;

DiaCreateSection::DiaCreateSection(QWidget *parent) :
  QDialog(parent),
  sectionName(""),
  sectionAudioPath(""),
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
  onClick_Stop();

  return;
}

void
DiaCreateSection::onClick_Create()
{
  // TODO
  accept();
}

void
DiaCreateSection::onClick_Cancel()
{
  reject();
}

void
DiaCreateSection::onClick_Play()
{
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

   SoundSource::Status status = _m_musicPlayer.getStatus();
   if(status == SoundSource::Status::Playing) {
     _m_musicPlayer.stop();
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
  SoundSource::Status status = _m_musicPlayer.getStatus();
  if(status == SoundSource::Status::Playing) {
    _m_musicPlayer.stop();
  }

  return;
}

void
DiaCreateSection::init()
{
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  // Connections
  connect(ui->btnCreate, &QPushButton::clicked, this, &DiaCreateSection::onClick_Create);
  connect(ui->btnCancel, &QPushButton::clicked, this, &DiaCreateSection::onClick_Cancel);
  connect(ui->btnPlayAudio, &QPushButton::clicked, this, &DiaCreateSection::onClick_Play);
  connect(ui->btnStopAudio, &QPushButton::clicked, this, &DiaCreateSection::onClick_Stop);

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










