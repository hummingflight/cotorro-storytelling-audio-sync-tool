#ifndef CTAUDIOMANAGER_H
#define CTAUDIOMANAGER_H

#include <QObject>

#include <SFML/Audio.hpp>

#include "ctCotorroUtilities.h"

using sf::Music;

namespace ct {

class Project;

/**
 * @brief The AudioManager class
 */
class AudioManager : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief Audio Manager
   *
   * @param parent Pointer to parent.
   */
  explicit AudioManager(QObject *parent = nullptr);

  /**
   * @brief Initialize
   */
  void
  init();

  /**
   * @brief Play a sound from a file in the asset folder.
   *
   * @param _fileName FileName.
   *
   * @return Result.
   */
  eOPRESULT::E
  playFromFile(const QString& _fileName);

  /**
   * @brief Stop sound.
   */
  void
  stop();

  /**
   * @brief Pause sound.
   */
  void
  pause();

signals:

private:

  /**
   * @brief Music player
   */
  Music
  _m_musicPlayer;

};

}

#endif // CTAUDIOMANAGER_H
