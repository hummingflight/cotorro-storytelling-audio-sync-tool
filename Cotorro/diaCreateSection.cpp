#include "diaCreateSection.h"
#include "ui_diaCreateSection.h"

DiaCreateSection::DiaCreateSection(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DiaCreateSection)
{
  ui->setupUi(this);
}

DiaCreateSection::~DiaCreateSection()
{
  delete ui;
}
