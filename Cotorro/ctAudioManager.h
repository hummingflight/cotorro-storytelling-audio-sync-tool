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
   * @brief Loads a sound from a file in the asset folder.
   *
   * @param _fileName FileName.
   *
   * @return Result.
   */
  eOPRESULT::E
  loadFromAssets(const QString& _fileName);

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

  /**
   * @brief Resume sound.
   */
  void
  play();

  /**
   * @brief Sets the ready flag to false.
   */
  void
  unload();

  /**
   * @brief Indicates if the player is paused.
   * @return
   */
  bool
  isPaused();

  /**
   * @brief Indicates if the player is playing.
   * @return
   */
  bool
  isPlaying();

  /**
   * @brief Indicates if the player is stopped.
   * @return
   */
  bool
  isStopped();

  /**
   * @brief Indicates if the player is ready.
   * @return
   */
  bool
  isReady();

  /**
   * @brief Gets the total duration of the music in seconds.
   * @return Total duration of the music in seconds.
   */
  float
  getDuration();

  /**
   * @brief Gets the playing position in seconds.
   *
   * @return Playing position in seconds.
   */
  float
  getPlayingPosition();

  /**
   * @brief Sets the volumen.
   *
   * @param _value Value.
   */
  void
  setVolumen(const qint32& _value);

signals:

private:

  /**
   * @brief Music player
   */
  Music
  _m_musicPlayer;

  /**
   * @brief Indicates if the audio manager is ready to play music.
   */
  bool
  _m_isReady;

};

}

#endif // CTAUDIOMANAGER_H
