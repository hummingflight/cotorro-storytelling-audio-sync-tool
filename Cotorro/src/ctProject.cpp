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
Project::open
(
  QXmlStreamReader& _reader,
  const QString& _name,
  const QString& _fileName,
  const QString& _fileFullPath,
  const QString& _projectDirectory
)
{
  // Clears current information.
  clear();

  // Checks that all attributes exists.
  QXmlStreamAttributes attritbutes = _reader.attributes();
  if(!attritbutes.hasAttribute("assetsFolderName")) {

    Cotorro::Log
    (
      eLOGTYPE::kError,
      tr("| Project | One or more attributes were not found in the XML.")
    );

    return eOPRESULT::kIncompatibleObject;
  }

  // Save information.
  _m_name = _name;
  _m_fileName = _fileName;
  _m_fileFullPath = _fileFullPath;
  _m_projectDirectory = _projectDirectory;
  _m_assetsFolderName = attritbutes.value("assetsFolderName").toString();
  _m_assetsDirectory = _m_projectDirectory + QDir::separator() + _m_assetsFolderName;

  // Iterates until it reach the end of the element or the end of the document.
  eOPRESULT::E result = eOPRESULT::kOk;
  QXmlStreamReader::TokenType token = QXmlStreamReader::StartElement;
  while(!_reader.atEnd() && token != QXmlStreamReader::EndElement) {

    // Next token.
    QXmlStreamReader::TokenType token = _reader.readNext();

    if(token == QXmlStreamReader::StartElement) {
      if(_reader.name().toLatin1() == "StorySections")  {

        // Load story section manager.
        result = _m_storySectionManager.open(_reader);

        // Check result.
        if(result != eOPRESULT::kOk) {
          return result;
        }
      }
    }
  }

  // Project was succesfully opened
  Cotorro::Log(eLOGTYPE::kMessage,"Project was successfully opened.");
  Cotorro::Log(eLOGTYPE::kMessage,"Project path: " + _m_fileFullPath);

  return result;
}

eOPRESULT::E
Project::save(QXmlStreamWriter& _writer)
{
  eOPRESULT::E result = eOPRESULT::kOk;

  // Start project's element.
  _writer.writeStartElement(tr("Project"));

  // Application and Organization information.
  _writer.writeAttribute(tr("application"), QApplication::applicationDisplayName());
  _writer.writeAttribute(tr("organization"), QApplication::organizationName());
  _writer.writeAttribute(tr("website"), QApplication::organizationDomain());
  _writer.writeAttribute(tr("version"), QApplication::applicationVersion());
  _writer.writeAttribute(tr("assetsFolderName"), "assets");

  // Save story section manager.
  result = _m_storySectionManager.save(_writer);

  // End project's element.
  _writer.writeEndElement();

  // Check result.
  if(result == eOPRESULT::kOk) {

    // Project was succesfully saved
    Cotorro::Log (
      eLOGTYPE::kMessage,
      tr("Project was successfully saved.")
    );

  }

  _m_isDirty = false;

  return result;
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

QString
Project::getProjectFileFullPath()
{
  return _m_fileFullPath;
}

StorySectionManager&
Project::getStorySectionManager()
{
  return _m_storySectionManager;
}

void
Project::destroy()
{
  _m_storySectionManager.destroy();
  return;
}

}

