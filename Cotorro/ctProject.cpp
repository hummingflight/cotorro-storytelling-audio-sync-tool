#include "ctProject.h"

#include <QApplication>
#include <QFile>
#include <QChar>

#include "ctCotorro.h"

namespace ct {

Project::Project(QObject *parent) :
  QObject(parent),
  _m_name(""),
  _m_fileName(""),
  _m_fileFullPath(""),
  _m_projectDirectory(""),
  _m_assetsFolderName(""),
  _m_assetsDirectory(""),
  _m_isDirty(false)
{
  return;
}

const QString&
Project::ProjectExtension()
{
  static const QString _PROJECT_EXTENSION = "cotorro";
  return _PROJECT_EXTENSION;
}

void
ct::Project::init()
{
  _m_storySectionManager.init();
  clear();
  return;
}

eOPRESULT::E
Project::open(const QString &_projectFilePath)
{
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

  QFile projFile(_projectFilePath);
  if(!projFile.open(QFile::ReadOnly)) {
    return eOPRESULT::kFail;
  }

  // Clear current information.
  clear();

  _m_name = projectInfo.fileName();
  _m_fileName = projectInfo.fileName();
  _m_fileFullPath = _projectFilePath;
  _m_projectDirectory = projectInfo.path();

  // Set current path.
  QDir::setCurrent(_m_projectDirectory);

  // Read and save information from file.
  QXmlStreamReader reader(&projFile);

  while(!reader.atEnd()) {
    QXmlStreamReader::TokenType token = reader.readNext();

    if(token == QXmlStreamReader::StartElement) {
      if(reader.name().toLatin1() == "Project") {
          _m_assetsFolderName = reader.attributes().value("assetsFolderName").toString();
          _m_assetsDirectory = _m_projectDirectory + QDir::separator() + _m_assetsFolderName;
      }
      else if(reader.name().toLatin1() == "StorySections")  {
        _m_storySectionManager.open(reader);
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
      Cotorro::Log(eLOGTYPE::kError, "| Project | XmlStreamReader: Unexpected element.");
      break;

    case QXmlStreamReader::CustomError:
      Cotorro::Log(eLOGTYPE::kError, "| Project | XmlStreamReader: Custom error.");
      break;

    case QXmlStreamReader::NotWellFormedError:
      Cotorro::Log(eLOGTYPE::kError, "| Project | XmlStreamReader: Not well formed");
      break;

    case QXmlStreamReader::PrematureEndOfDocumentError:
      Cotorro::Log(eLOGTYPE::kError, "| Project | XmlStreamReader: Premature end of document.");
      break;

    }

    return eOPRESULT::kFail;
  }

  // Project was succesfully opened
  Cotorro::Log(eLOGTYPE::kMessage,"Project was successfully opened.");
  Cotorro::Log(eLOGTYPE::kMessage,"Project path: " + _m_fileFullPath);

  return eOPRESULT::kOk;
}

eOPRESULT::E
Project::save()
{
  return save(_m_fileFullPath);
}

eOPRESULT::E
Project::save(const QString& _m_path)
{
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

  QFile projFile(_m_path);
  if(!projFile.open(QFile::ReadWrite)) {
    return eOPRESULT::kFail;
  }

  QXmlStreamWriter stream(&projFile);
  stream.setAutoFormatting(true);
  stream.writeStartDocument();
  stream.writeStartElement("Project");

  // Application and Organization information.
  stream.writeAttribute("application", QApplication::applicationDisplayName());
  stream.writeAttribute("organization", QApplication::organizationName());
  stream.writeAttribute("website", QApplication::organizationDomain());
  stream.writeAttribute("version", QApplication::applicationVersion());
  stream.writeAttribute("assetsFolderName", "assets");

  _m_storySectionManager.save(stream);

  stream.writeEndElement();
  stream.writeEndDocument();

  projFile.flush();
  projFile.close();

  _m_isDirty = false;

  // Project was succesfully saved
  Cotorro::Log(eLOGTYPE::kMessage,"Project was successfully saved.");
  Cotorro::Log(eLOGTYPE::kMessage,"Project path: " + _m_path);

  return eOPRESULT::kOk;
}

void
ct::Project::clear()
{
  _m_storySectionManager.clear();

  _m_name = "";
  _m_fileName = "";
  _m_fileFullPath = "";
  _m_projectDirectory = "";
  _m_assetsFolderName = "";
  _m_assetsDirectory = "";
  _m_isDirty = false;

  return;
}

void
Project::dirty()
{
  if(!_m_isDirty) {
    _m_isDirty = !_m_isDirty;
  }

  return;
}

bool
Project::isDirty()
{
  return _m_isDirty;
}

QString
Project::getProjectDirectory()
{
  return _m_projectDirectory;
}

QString
Project::getAssetsDirectory()
{
  return _m_assetsDirectory;
}

StorySectionManager&
Project::getStorySectionManager()
{
  return _m_storySectionManager;
}

}

