#ifndef DIACREATESECTION_H
#define DIACREATESECTION_H

#include <SFML/Audio.hpp>

#include <QDialog>

#include "ctCotorroUtilities.h"

using sf::Music;

namespace Ui {
	
class DiaCreateSection;
}

class DiaCreateSection : public QDialog
{
  Q_OBJECT

public:
  /**
   * @brief DiaCreateSection
   * @param parent
   */
  explicit DiaCreateSection(QWidget *parent = nullptr);

  /**
   *
   */
  ~DiaCreateSection();

  /**
   * @brief Section's name.
   */
  QString
  sectionName;

  /**
   * @brief Section's Audio's path.
   */
  QString
  sectionAudioFileName;

  /**
   * @brief Section's content.
   */
  QString
  sectionContent;

private slots:

  void
  onClick_Create();

  void
  onClick_Cancel();

  void
  onClick_Play();

  void
  onClick_Stop();

  void
  onMusicComboCurrentTextChanged();

private:

  /**
   * @brief Initialize
   */
  void
  init();

  /**
   * @brief Updates the audio combo box.
   */
  void
  updateAudioCombo();

  /**
   * 
   */
  void
  loadTrack(const QString& _fileName);

  /**
   * @brief Stops music.
   */
  void
  stopTrack();

  /**
   * Play a track.
   */
  void
  playTrack();

  /**
   * @brief Checks the "accept" button availability.
   */
  bool
  checkFields();

  /**
   * @brief ui
   */
  Ui::DiaCreateSection*
  ui;

  /**
   * 
   */
  ct::eMUSIC_PLAYER_STATE::E
  _m_musicPlayerState;

  /**
   * Music Player.
   */
  Music
  _m_musicPlayer;
};

#endif // DIACREATESECTION_H
