#include "diaEditor.h"
#include "ctCotorro.h"

namespace ct {

Cotorro::Cotorro(QObject *parent) :
  QObject(parent),
  _pEditorWindow(nullptr),
  _m_project(this),
  _m_audioManager(this)
{
  return;
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

void
Cotorro::Destroy()
{
  if(Cotorro::_Instance() != nullptr)
  {
    Cotorro::_Instance()->destroy();
  }
  return;
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

  // Read information coming from the file.
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
      Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | XmlStreamReader: Unexpected element."));
      break;

    case QXmlStreamReader::CustomError:
      Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | XmlStreamReader: Custom error."));
      break;

    case QXmlStreamReader::NotWellFormedError:
      Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | XmlStreamReader: Not well formed"));
      break;

    case QXmlStreamReader::PrematureEndOfDocumentError:
      Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | XmlStreamReader: Premature end of document."));
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
    Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | Project's path is empty."));
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
    Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | File doesn't exists: %1.").arg(_m_path));
    return eOPRESULT::kFileDoesntExists;
  }

  if(!projectInfo.isFile()) {
    Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | Is not a file path: %1.").arg(_m_path));
    return eOPRESULT::kIncompatibleObject;
  }

  if(!projectInfo.isReadable()) {
    Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | File is not readable: %1.").arg(_m_path));
    return eOPRESULT::kFileNotReadable;
  }

  if(!projectInfo.isWritable()) {
    Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | File is not writable: %1.").arg(_m_path));
    return eOPRESULT::kFileNotWritable;
  }

  if(projectInfo.suffix() != Project::ProjectExtension()) {
    Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | Invalid extension: %1.").arg(_m_path));
    return eOPRESULT::kIncompatibleObject;
  }

  // Open File.
  QFile projFile(_m_path);
  if(!projFile.open(QFile::WriteOnly)) {
    Cotorro::Log(eLOGTYPE::kError, tr("| Cotorro | Couldn't open file: %1.").arg(_m_path));
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

AudioManager&
Cotorro::getAudioManager()
{
  return _m_audioManager;
}

ResourceManager&
Cotorro::getResourceManager()
{
  return _m_resourceManager;
}

void
Cotorro::destroy()
{
  _m_project.destroy();
  _m_resourceManager.destroy();
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
  _m_project.init();
  _m_audioManager.init();
  _m_resourceManager.init();

  return;
}

}
