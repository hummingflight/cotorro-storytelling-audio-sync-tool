#include "ctFontResourceManager.h"


#include "ctCotorro.h"

namespace ct {

FontResourceManager::FontResourceManager() :
  _m_fontMap()
{
  return;
}

FontResourceManager::~FontResourceManager()
{
  destroy();
  return;
}

void
FontResourceManager::init()
{
  return;
}

eOPRESULT::E
FontResourceManager::load(const QString &_key)
{
  if(has(_key)) {
    Cotorro::Log(
          eLOGTYPE::kError,
          QObject::tr("| FontResourceManager | There is already a font with the same name: %1").arg(_key)
    );

    return eOPRESULT::kFail;
  }

  QFile file(QObject::tr(":/fonts/assets/fonts/%1").arg(_key));
  if(!file.exists()) {
    Cotorro::Log(
          eLOGTYPE::kError,
          QObject::tr("| FontResourceManager | The Font was not found within the app resources: %1").arg(_key)
    );

    return eOPRESULT::kFileDoesntExists;
  }

  if(!file.open(QFile::ReadOnly)) {
    Cotorro::Log(
          eLOGTYPE::kError,
          QObject::tr("| FontResourceManager | The file couldn't be opened: %1").arg(_key)
    );

    return eOPRESULT::kFail;
  }

  // Create font resource.
  FontResource* fontResource = new FontResource();

  // Read all data from file.
  fontResource->data = file.readAll();

  // Load font.
  if(!fontResource->sfmlFont.loadFromMemory(fontResource->data.data(), fontResource->data.size())) {

    Cotorro::Log(
          eLOGTYPE::kError,
          QObject::tr("| FontResourceManager | The font couldn't be loaded into the sfml font: %1").arg(_key)
    );

    fontResource->destroy();
    delete fontResource;

    // Close file.
    file.close();

    return eOPRESULT::kFail;
  }

  // Save font.
  _m_fontMap.insert(_key, fontResource);

  // Close file.
  file.close();

  return eOPRESULT::kOk;
}

bool
FontResourceManager::has(const QString &_key)
{
  return _m_fontMap.find(_key) != _m_fontMap.end();
}

const FontResource&
FontResourceManager::get(const QString &_key)
{
  return *_m_fontMap.find(_key).value();
}

void
FontResourceManager::destroy()
{
  foreach(FontResource* pResource, _m_fontMap.values()) {
    pResource->destroy();
    delete pResource;
  }

  _m_fontMap.clear();
  return;
}

}

