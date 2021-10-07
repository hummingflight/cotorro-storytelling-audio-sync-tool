#include "diaCreateSection.h"
#include "ui_diaCreateSection.h"

#include <QDir>

#include "ctCotorro.h"
#include "ctProject.h"

using ct::Cotorro;
using ct::Project;

DiaCreateSection::DiaCreateSection(QWidget *parent) :
  QDialog(parent),
  sectionName(""),
  sectionAudioPath(""),
  sectionContent(""),
  ui(new Ui::DiaCreateSection)
{
  ui->setupUi(this);
  init();
  return;
}

DiaCreateSection::~DiaCreateSection()
{
  delete ui;
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
DiaCreateSection::init()
{
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  // Connections
  connect(ui->btnCreate, &QPushButton::clicked, this, &DiaCreateSection::onClick_Create);
  connect(ui->btnCancel, &QPushButton::clicked, this, &DiaCreateSection::onClick_Cancel);

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

  projectDir.setNameFilters(QStringList()<<"*.mp3"<<"*.ogg"<<"*.m4a");
  projectDir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Readable);

  QStringList aFiles = projectDir.entryList();
  ui->comboAudio->insertItems(0, aFiles);

  return;
}










