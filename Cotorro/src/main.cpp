#include "diaEditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  a.setOrganizationName("HummingFlight");
  a.setOrganizationDomain("https://hummingflight.com");
  a.setApplicationName("Cotorro");
  a.setApplicationDisplayName("Cotorro");
  a.setApplicationVersion("0.2.0");

  Editor w;
  w.show();
  return a.exec();
}
