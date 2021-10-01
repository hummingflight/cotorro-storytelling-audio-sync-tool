#ifndef DIACREATESECTION_H
#define DIACREATESECTION_H

#include <QDialog>

namespace Ui {
class DiaCreateSection;
}

class DiaCreateSection : public QDialog
{
  Q_OBJECT

public:
  explicit DiaCreateSection(QWidget *parent = nullptr);
  ~DiaCreateSection();

private:
  Ui::DiaCreateSection *ui;
};

#endif // DIACREATESECTION_H
