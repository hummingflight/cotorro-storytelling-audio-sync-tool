#include "diaEditor.h"
#include "ctCotorro.h"

namespace ct {

Cotorro::Cotorro(QObject *parent) :
  QObject(parent),
  _pEditorWindow(nullptr)
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

  QString msgStyle = "<span style=\" color:#ffffff;\" >";
  switch (_type) {
    case eLOGTYPE::kMessage:
      msgStyle = "<span style=\" color:#ffffff;\" >";
    break;

    case eLOGTYPE::kWarning:
      msgStyle = "<span style=\" color:#ffff00;\" >";
    break;

    case eLOGTYPE::kError:
      msgStyle = "<span style=\" color:#ff0000;\" >";
    break;
  }

  QPlainTextEdit* pLoggerWidget = pCotorro->_pEditorWindow->getLoggerTextWidget();
  pLoggerWidget->appendHtml(msgStyle + _msg + "</span>");
}

void
Cotorro::init(Editor* _pMain)
{
  _pEditorWindow = _pMain;

  _m_project.init();
  return;
}

Project&
Cotorro::getProject()
{
  return _m_project;
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

}
