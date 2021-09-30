#include "ctStorySectionManager.h"

#include "cotorro.h"
#include "ctStorySection.h"

namespace ct {

StorySectionManager::StorySectionManager(QObject *parent) :
  QObject(parent),
  _m_hStorySections()
{

}

void
StorySectionManager::init()
{
  // TODO
  return;
}

eOPRESULT::E
StorySectionManager::open(QXmlStreamReader &_reader)
{
  return eOPRESULT::kOk;
}

eOPRESULT::E
StorySectionManager::save(QXmlStreamWriter &_writer)
{
  _writer.writeEmptyElement("StorySections");
  return eOPRESULT::kOk;
}

void
StorySectionManager::clear()
{
  qDeleteAll(_m_hStorySections);
  _m_hStorySections.clear();
  return;
}

StorySection*
StorySectionManager::create(const QString &_name)
{
  if(has(_name))
  {
    Cotorro::Log(eLOGTYPE::kError, "| StorySectionManager | A section with name: " + _name + " already exists.");
    return nullptr;
  }

  StorySection* pSection = new StorySection(this);
  pSection->init(_name);

  _m_hStorySections.insert(_name, pSection);
  return pSection;
}

void
StorySectionManager::rename(const QString &_name, const QString &_newName)
{
  if(_name == _newName) {
    return;
  }

  QMap<QString, StorySection*>::iterator section = _m_hStorySections.find(_name);
  if(section == _m_hStorySections.end()) {
    Cotorro::Log(eLOGTYPE::kError, "| StorySectionManager | Story section with name: " + _name + " not found.");
    return;
  }

  if(has(_newName)) {
    Cotorro::Log(eLOGTYPE::kError, "| StorySectionManager | A section with name: " + _name + " already exists.");
    return;
  }

  _m_hStorySections.remove(_name);
  _m_hStorySections.insert(_newName, section.value());

  return;
}

bool
StorySectionManager::has(const QString &_name)
{
  return _m_hStorySections.contains(_name);
}

StorySection*
StorySectionManager::get(const QString &_name)
{
  QMap<QString, StorySection*>::iterator section = _m_hStorySections.find(_name);
  if(section == _m_hStorySections.end()) {
    Cotorro::Log(eLOGTYPE::kError, "| StorySectionManager | Story section with name: " + _name + " not found.");
    return nullptr;
  }

  return section.value();
}

void
StorySectionManager::remove(const QString &_name)
{
  QMap<QString, StorySection*>::iterator section = _m_hStorySections.find(_name);
  if(section == _m_hStorySections.end()) {
    Cotorro::Log(eLOGTYPE::kError, "| StorySectionManager | Story section with name: " + _name + " not found.");
    return;
  }

  _m_hStorySections.remove(_name);
  delete section.value();

  return;
}

qint32
StorySectionManager::size()
{
  return _m_hStorySections.size();
}

}
