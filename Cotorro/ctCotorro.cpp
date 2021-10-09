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

eOPRESULT::E
Cotorro::openProject(const QString &_projectFilePath)
{
  eOPRESULT::E result = eOPRESULT::kOk;

  // Check Project's file.
  QFileInfo projectInfo(_projectFilePath);

  if(!projectInfo.exists()) {
    return eOPRESULT::kFileDoesntExists;
  }

  if(!projectInfo.isFile()) {
    return eOPRESULT::kIncompatibleObject;
  }

  if(!projectInfo.isReadable()) {
    return eOPRESULT::kFileNotReadable;
  }

  if(projectInfo.suffix() != Project::ProjectExtension()) {
    return eOPRESULT::kIncompatibleObject;
  }

  // Attemps to open the Project's file.
  QFile projFile(_projectFilePath);
  if(!projFile.open(QFile::ReadOnly)) {
    return eOPRESULT::kFail;
  }

  // Set current path.
  QDir::setCurrent(projectInfo.path());

  // Read information comming from the file.
  QXmlStreamReader reader(&projFile);

  QXmlStreamReader::TokenType token = QXmlStreamReader::StartDocument;
  while(token != QXmlStreamReader::EndDocument && !reader.atEnd()) {
    token = reader.readNext();
    if(token == QXmlStreamReader::StartElement) {
      if(reader.name().toLatin1() == "Project") {

        // Load project.
        result = _m_project.open
        (
          reader,
          projectInfo.fileName(),
          projectInfo.fileName(),
          _projectFilePath,
          projectInfo.path()
        );

        // Check result.
        if(result != eOPRESULT::kOk) {

          Cotorro::Log(
            eLOGTYPE::kError,
            tr("| Cotorro | Something went wrog during loading.")
          );

          break;
        }
      }
    }
  }

  // Close file.
  projFile.close();

  // Error handling.
  if(reader.hasError()) {

    QXmlStreamReader::Error errorType = reader.error();
    switch(errorType) {

    case QXmlStreamReader::NoError:
      break;

    case QXmlStreamReader::UnexpectedElementError:
      Cotorro::Log(eLOGTYPE::kError, "| Cotorro | XmlStreamReader: Unexpected element.");
      break;

    case QXmlStreamReader::CustomError:
      Cotorro::Log(eLOGTYPE::kError, "| Cotorro | XmlStreamReader: Custom error.");
      break;

    case QXmlStreamReader::NotWellFormedError:
      Cotorro::Log(eLOGTYPE::kError, "| Cotorro | XmlStreamReader: Not well formed");
      break;

    case QXmlStreamReader::PrematureEndOfDocumentError:
      Cotorro::Log(eLOGTYPE::kError, "| Cotorro | XmlStreamReader: Premature end of document.");
      break;

    }

    return eOPRESULT::kFail;
  }

  return result;
}

eOPRESULT::E
Cotorro::saveProject()
{
  QString projectFileFullPath = _m_project.getProjectFileFullPath();
  if(projectFileFullPath.isEmpty()) {
    return eOPRESULT::kFail;
  }

  return saveProject(projectFileFullPath);
}

eOPRESULT::E
Cotorro::saveProject(const QString &_m_path)
{
  eOPRESULT::E result = eOPRESULT::kOk;
  QFileInfo projectInfo(_m_path);

  if(!projectInfo.exists()) {
    return eOPRESULT::kFileDoesntExists;
  }

  if(!projectInfo.isFile()) {
    return eOPRESULT::kIncompatibleObject;
  }

  if(!projectInfo.isReadable()) {
    return eOPRESULT::kFileNotReadable;
  }

  if(!projectInfo.isWritable()) {
    return eOPRESULT::kFileNotWritable;
  }

  if(projectInfo.suffix() != Project::ProjectExtension()) {
    return eOPRESULT::kIncompatibleObject;
  }

  // Open File.
  QFile projFile(_m_path);
  if(!projFile.open(QFile::ReadWrite)) {
    return eOPRESULT::kFail;
  }

  // Open Stream.
  QXmlStreamWriter stream(&projFile);
  stream.setAutoFormatting(true);

  // Start Document.
  stream.writeStartDocument();

  // Save Project.
  _m_project.save(stream);

  // End Document.
  stream.writeEndDocument();

  // Close file.
  projFile.flush();
  projFile.close();

  return result;
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
