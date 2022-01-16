#include "ctResourceManager.h"
#include "ctCotorro.h"

namespace ct {

ResourceManager::ResourceManager(QObject *parent) :
  QObject(parent),
  _m_fontResourceManager()
{
  return;
}

void
ResourceManager::init()
{
  _m_fontResourceManager.init();
  _m_fontResourceManager.load("arial_narrow_7.ttf");
  return;
}

void
ResourceManager::destroy()
{
  _m_fontResourceManager.destroy();
  return;
}

FontResourceManager&
ResourceManager::fontResourceManager()
{
  return _m_fontResourceManager;
}

}
