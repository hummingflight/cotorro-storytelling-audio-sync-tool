#include "ctResourceManager.h"
#include "ctCotorro.h"

namespace ct {

ResourceManager::ResourceManager(QObject *parent) : QObject(parent)
{

}

ResourceManager::~ResourceManager()
{
  destroy();
  return;
}

void
ResourceManager::init()
{
  QFile file(":/fonts/assets/fonts/arial.ttf");
  if(file.open(QFile::ReadOnly)) {

    FontResource* fontResource = new FontResource();
    fontResource->data = file.readAll();

    if(!fontResource->sfmlFont.loadFromMemory(fontResource->data.data(), fontResource->data.size())) {
      // TODO ERROR

      fontResource->destroy();
      delete fontResource;

      return;
    }

    _m_fontMap.insert("arial.ttf", fontResource);
    file.close();
  }

  return;
}

void
ResourceManager::destroy()
{
  qDeleteAll(_m_fontMap);
  _m_fontMap.clear();

  return;
}

FontResource&
ResourceManager::getFontData(const QString &_key)
{
  QMap<QString, FontResource*>::iterator it = _m_fontMap.find(_key);
  if(it == _m_fontMap.end()) {
    Cotorro::Log(eLOGTYPE::kError, "ERROR");
  }

  return *it.value();
}

}
