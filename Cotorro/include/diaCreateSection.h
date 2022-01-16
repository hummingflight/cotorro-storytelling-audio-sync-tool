#ifndef DIACREATESECTION_H
#define DIACREATESECTION_H

#include <QDialog>

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
   * @brief Stops music.
   */
  void
  stopMusic();

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
};

#endif // DIACREATESECTION_H
