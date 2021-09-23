#include "mainwindow.h"
#include "cotorro.h"

Cotorro::Cotorro(QObject *parent) :
  QObject(parent),
  _pMainWindow(nullptr)
{

}

void
Cotorro::Start(QObject *parent)
{
  if(Cotorro::_Instance() != nullptr)
  {
    // Cotorro already started.
    return;
  }

  Cotorro::_Instance() = new Cotorro(parent);
  Cotorro::_Instance()->_onStart();
}

Cotorro*&
Cotorro::Instance()
{
  return Cotorro::_Instance();
}

void
Cotorro::Log(const eLOGTYPE::E &_type, const QString &_msg)
{
  Cotorro* pCotorro = Cotorro::Instance();
  if(pCotorro == nullptr) {
    return;
  }

  QString msgType;
  switch (_type) {
    case eLOGTYPE::kMessage:
      msgType = "";
    break;

    case eLOGTYPE::kWarning:
      msgType = "|Warning| ";
    break;

    case eLOGTYPE::kError:
      msgType = "|Error| ";
    break;
  }

  QPlainTextEdit* pLoggerWidget = pCotorro->_pMainWindow->getLoggerTextWidget();
  pLoggerWidget->appendPlainText(msgType + _msg);
}

void Cotorro::init(MainWindow* _pMain)
{
  this->_pMainWindow = _pMain;
  return;
}

void Cotorro::destroy()
{
  return;
}

Cotorro*&
Cotorro::_Instance()
{
  static Cotorro* _pINSTANCE = nullptr;
  return _pINSTANCE;
}

void
Cotorro::_onStart()
{
  // TODO
}
