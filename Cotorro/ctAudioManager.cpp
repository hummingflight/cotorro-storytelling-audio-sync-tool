#include "ctAudioManager.h"

#include "ctCotorro.h"

namespace ct {

AudioManager::AudioManager(QObject *parent) :
  QObject(parent),
  _m_musicPlayer()
{
  // TODO
  return;
}

void
AudioManager::init()
{
  // TODO
  return;
}

eOPRESULT::E
AudioManager::playFromFile(const QString &_fileName)
{
  // Stop current track.
  stop();

  if(_fileName.isEmpty()) {
    Cotorro::Log(
      eLOGTYPE::kWarning,
      tr("| AudioManager | File shouldn't be empty.")
    );

    return eOPRESULT::kFail;
  }

  Project& project = Cotorro::Instance()->getProject();
  QFileInfo fileInfo(project.getAssetsDirectory() + QDir::separator() + _fileName);
  if(!fileInfo.exists()) {
    Cotorro::Log(
      ct::eLOGTYPE::kError,
      tr("| AudioManager | File doesn't exists: %1").arg(fileInfo.filePath())
    );

    return eOPRESULT::kFileDoesntExists;
  }

  if(!fileInfo.isReadable()) {
    Cotorro::Log(
      ct::eLOGTYPE::kError,
      tr("| AudioManager | Couldn't read sound file: %1").arg(fileInfo.filePath())
    );

    return eOPRESULT::kDirectoryNotReadable;
  }

   if(!_m_musicPlayer.openFromFile(fileInfo.filePath().toStdString().c_str())) {
     Cotorro::Log(
       ct::eLOGTYPE::kError,
       tr("| AudiManager | Couldn't open sound file: %1").arg(fileInfo.filePath())
     );

     return eOPRESULT::kFail;
   }

   _m_musicPlayer.play();

   return eOPRESULT::kOk;
}

void
AudioManager::stop()
{
  if(_m_musicPlayer.getStatus() != Music::Stopped) {
    _m_musicPlayer.stop();
  }
  return;
}

void
AudioManager::pause()
{
  if(_m_musicPlayer.getStatus() != Music::Paused) {
    _m_musicPlayer.pause();
  }
  return;
}

}
