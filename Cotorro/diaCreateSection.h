#ifndef DIACREATESECTION_H
#define DIACREATESECTION_H

#include <QDialog>
#include <SFML/Audio.hpp>

using sf::Music;

namespace Ui {
class DiaCreateSection;
}

/**
 * @brief Creates a new story section.
 */
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
  sectionAudioPath;

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
   * @brief ui
   */
  Ui::DiaCreateSection*
  ui;

  /**
   * @brief _m_musicPlayer
   */
  Music
  _m_musicPlayer;
};

#endif // DIACREATESECTION_H
