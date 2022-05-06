#include "ctStorySectionManager.h"

#include "ctCotorro.h"
#include "ctWord.h"
#include "ctStorySection.h"
#include "ctAudioManager.h"

namespace ct {

StorySectionManager::StorySectionManager(QObject *parent) :
  QObject(parent),
  _m_hStorySections(),
  _m_pActiveSection(nullptr),
  _m_pActiveWord(nullptr)
{
  return;
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
  eOPRESULT::E result = eOPRESULT::kOk;

  // Clear any previous information.
  clear();

  // Get attributes
  QXmlStreamAttributes attributes = _reader.attributes();

  // Check that all attributes exists.
  if(!attributes.hasAttribute("size")) {

    // Error log.
    Cotorro::Log(
      eLOGTYPE::kError,
      tr("| StorySectionManager | One or more attributes were not found in the XML.")
    );

    return result;
  }

  // Get the size of elements.
  qsizetype size = attributes.value("size").toUInt();

  // Skip all the process in case the number of sections is equal or lower than zero.
  if(size <= 0) {

    // Reach the end of the element.
    while(!_reader.atEnd()) {
      QXmlStreamReader::TokenType token = _reader.readNext();
      if(token == QXmlStreamReader::EndElement) {
        return result;
      }
    }

    // Return failure if the end of the document is reached.
    return eOPRESULT::kFail;
  }

  // Iterates over each section until it find the end of the element
  // or reach the end of the document.
  QXmlStreamReader::TokenType token = QXmlStreamReader::StartElement;
  while(!_reader.atEnd() && token != QXmlStreamReader::EndElement) {

    // Next token.
    token = _reader.readNext();

    // Load story section.
    if(token == QXmlStreamReader::StartElement) {

      // Check element's name.
      if(_reader.name().toLatin1() == "StorySection") {

        // Create Story section.
        StorySection* storySection = new StorySection(this);
        result = storySection->init(_reader);

        // Check result.
        if(result != eOPRESULT::kOk) {

          // Error log.
          Cotorro::Log(
            eLOGTYPE::kError,
            tr("| StorySectionManager | Something went wrong during loading. Couldn't load Story Section Manager.")
          );

          return result;
        }

        // Attempt to add story section.
        result = add(storySection);
        if(result != eOPRESULT::kOk) {

          // Delete story section.
          delete storySection;

          // Error log.
          Cotorro::Log(
            eLOGTYPE::kError,
            tr("| StorySectionManager | Something went wrong during loading. Couldn't load Story Section Manager.")
          );

          return result;
        }
      }
    }
  }

  // Emit signal.
  emit sectionsChanged();

  return result;
}

eOPRESULT::E
StorySectionManager::save(QXmlStreamWriter &_writer)
{
  _writer.writeStartElement(tr("StorySections"));

  // Save the size of story sections.
  _writer.writeAttribute(tr("size"), QString::number(_m_hStorySections.size()));

  // Save each story section.
  eOPRESULT::E result = eOPRESULT::kOk;
  QMap<QString, StorySection*>::iterator it;
  for(it = _m_hStorySections.begin(); it != _m_hStorySections.end(); ++it) {

    // Save story section item.
    result = it.value()->save(_writer);

    // Check result.
    if(result != eOPRESULT::kOk) {
      _writer.writeEndElement();

      return result;
    }
  }

  _writer.writeEndElement();

  return result;
}

void
StorySectionManager::clear()
{
  // Set active section to null.
  setActiveSectionToNull();
  setActiveWordToNull();

  foreach(StorySection* storySection, _m_hStorySections.values()) {
    storySection->destroy();
  }

  // Destroys story sections.
  qDeleteAll(_m_hStorySections);
  _m_hStorySections.clear(); 

  // Emit signal.
  emit sectionsChanged();

  return;
}

StorySection*
StorySectionManager::create(const QString &_name)
{
  if(has(_name))
  {
    Cotorro::Log(
     eLOGTYPE::kError,
     tr("| StorySectionManager | A section with name: %1 already exists.").arg(_name)
    );

    return nullptr;
  }

  StorySection* pSection = new StorySection(this);
  pSection->init(_name);

  _m_hStorySections.insert(_name, pSection);

  // Dirts project.
  Cotorro::Instance()->getProject().dirty();

  // Emit signal.
  emit sectionsChanged();

  Cotorro::Log(
    eLOGTYPE::kMessage,
    tr("| StorySectionManager | Section created : %1").arg(_name)
  );

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
    Cotorro::Log(
      eLOGTYPE::kError,
      tr("| StorySectionManager | Story section with name: %1 not found.").arg(_name)
    );

    return;
  }

  if(has(_newName)) {
    Cotorro::Log(
      eLOGTYPE::kError,
      tr("| StorySectionManager | A section with name: %1 already exists.").arg(_newName)
    );
    return;
  }

  StorySection* pStorySection = section.value();

  _m_hStorySections.remove(_name);
  pStorySection->setName(_newName);
  _m_hStorySections.insert(_newName, pStorySection);

  // Dirts project.
  Cotorro::Instance()->getProject().dirty();

  // Emit signal.
  emit sectionsChanged();

  Cotorro::Log(
    eLOGTYPE::kMessage,
    tr("| StorySectionManager | Section renamed from : %1 to %2")
        .arg(_name, _newName)
  );

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
    Cotorro::Log(
      eLOGTYPE::kError,
      tr("| StorySectionManager | Story section with name: %1 not found.").arg(_name)
    );

    return nullptr;
  }

  return section.value();
}

QStringList
StorySectionManager::getNames()
{
  return _m_hStorySections.keys();
}

void
StorySectionManager::remove(const QString &_name)
{
  // Find section.
  QMap<QString, StorySection*>::iterator section = _m_hStorySections.find(_name);
  if(section == _m_hStorySections.end()) {

    // Error log.
    Cotorro::Log(
      eLOGTYPE::kError,
      tr("| StorySectionManager | Story section with name: not found.").arg(_name)
    );

    return;
  }

  StorySection* pSection = section.value();

  // Remove section from the map.
  _m_hStorySections.remove(_name);

  // Check active section.
  if(_m_pActiveSection != nullptr) {
    if(pSection->getName() == _m_pActiveSection->getName()) {
      setActiveSectionToNull();
    }
  }

  // Delete section.
  delete pSection;

  // Dirts project.
  Cotorro::Instance()->getProject().dirty();

  // Emit signal.
  emit sectionsChanged();

  return;
}

void
StorySectionManager::setActiveSectionByName(const QString &_name)
{
  if(!has(_name)) {
    Cotorro::Log(
          eLOGTYPE::kError,
          tr("| StorySectionManager | No story section was found: %1").arg(_name)
    );

    return;
  }

  // Set active section.
  setActiveSection(get(_name));
  return;
}

void
StorySectionManager::setActiveSectionToNull()
{
  setActiveSection(nullptr);  
}

bool
StorySectionManager::hasActiveSection()
{
  return _m_pActiveSection != nullptr;
}

StorySection*
StorySectionManager::getActiveSection()
{
  return _m_pActiveSection;
}

void 
StorySectionManager::setActiveWord(const quint32& _index)
{
  if (_m_pActiveSection == nullptr)
  {
    Cotorro::Log(
      eLOGTYPE::kWarning,
      QObject::tr("| StorySectionManager | No Active Section found.")
    );
    return;
  }

  const QList<Word*> wordList = _m_pActiveSection->getWordsList();
  if (wordList.length() <= _index)
  {
    Cotorro::Log(
      eLOGTYPE::kWarning,
      QObject::tr("| StorySectionManager | Index out of range.")
    );
    return;
  }

  _m_pActiveWord = wordList.at(_index);

  emit activeWordChanged(_m_pActiveWord);
  return;
}

  void 
  StorySectionManager::setActiveWordStart(const float& _start)
  {
    if (_m_pActiveWord == nullptr) {
      return;
    }

    _m_pActiveWord->setStart(_start);
    if (_start >= _m_pActiveWord->getEnd()) {
      _m_pActiveWord->setEnd(_start + 1.0f);
    }

    activeWordContentChanged(_m_pActiveWord);
  }

  void 
  StorySectionManager::setActiveWordEnd(const float& _end)
  {
    if (_m_pActiveWord == nullptr)
    {
      return;
    }

    _m_pActiveWord->setEnd(_end);
    if (_end <= _m_pActiveWord->getStart())
    {
      _m_pActiveWord->setStart(qMax(0.0f, _end - 1.0f));
    }

    activeWordContentChanged(_m_pActiveWord);
  }

  void 
  StorySectionManager::setActiveWordData(const QString& _data)
  {
    if (_m_pActiveWord == nullptr)
    {
      return;
    }

    _m_pActiveWord->setData(_data);

    activeWordContentChanged(_m_pActiveWord);
  }

void 
StorySectionManager::setActiveWordToNull()
{
  if (_m_pActiveWord != nullptr)
  {
    _m_pActiveWord = nullptr;
    emit activeWordChanged(_m_pActiveWord);
  }  
  return;
}

bool 
StorySectionManager::hasActiveWord()
{
  return _m_pActiveWord != nullptr;
}

Word* 
StorySectionManager::getActiveWord()
{
  return _m_pActiveWord;
}

qint32
StorySectionManager::size()
{
  return _m_hStorySections.size();
}

void
StorySectionManager::destroy()
{
  clear();
  return;
}

eOPRESULT::E
StorySectionManager::add(StorySection *_pStorySection)
{
  // Check if name already exists.
  if(has(_pStorySection->getName())) {

    // Error log.
    Cotorro::Log(
      eLOGTYPE::kError,
      tr("| StorySectionManager | A section with name: %1 already exists.").arg(_pStorySection->getName())
    );

    return eOPRESULT::kFail;
  }

  // Add story section into the map.
  _m_hStorySections.insert(_pStorySection->getName(), _pStorySection);

  // Dirts project.
  Cotorro::Instance()->getProject().dirty();

  return eOPRESULT::kOk;
}

void
StorySectionManager::setActiveSection(StorySection *_pStorySection)
{
  if(_m_pActiveSection != nullptr && _pStorySection != nullptr) {
    if(_pStorySection->getUuid() == _m_pActiveSection->getUuid()){
      return;
    }
  }
  else if(_m_pActiveSection == nullptr && _pStorySection == nullptr) {
    return;
  }

  _m_pActiveSection = _pStorySection;

  if(_m_pActiveSection != nullptr) {

    // Load audio.
    AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
    if(!audioManager.isReady()) {
      audioManager.loadFromAssets(_m_pActiveSection->getAudioKey());
    }

    Cotorro::Log(
          eLOGTYPE::kMessage,
          tr("| StorySectionManager | Active Section: %1").arg(_m_pActiveSection->getName())
    );
  }
  else {
    Cotorro::Log(
          eLOGTYPE::kMessage,
          tr("| StorySectionManager | Active Section: undefined.")
    );
  }

  setActiveWordToNull();

  // Emit signals.
  emit activeSectionChanged(_pStorySection);

  return;
}

}
