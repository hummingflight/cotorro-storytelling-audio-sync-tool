#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

namespace ct {
  class StorySection;
  class StorySectionEditorWidget;
  class Word;
}

class Editor : public QMainWindow
{
  Q_OBJECT

public:
  /**
   * @brief Editor
   * @param parent
   */
  Editor(QWidget *parent = nullptr);

  /**
   *
   */
  ~Editor();

  /**
   * @brief Get the logger plain text edit widget.
   *
   * @return Logger plain text edit widget.
   */
  QPlainTextEdit*
  getLoggerTextWidget();

private slots:

  void
  on_actionNew_triggered();

  void
  on_actionOpen_triggered();

  void
  on_actionSave_triggered();

  void
  on_actionAddSection_triggered();

  void
  on_actionPlaySimulation_triggered();

  void
  on_actionPauseSimulation_triggered();

  void
  on_actionStopSimulation_triggered();

  void
  on_actionRemoveSection_triggered();

  void
  onStoryManagerChanged();

  void
  onStorySectionDoubleClicked(QListWidgetItem *item);

  void
  onWordSelectionChanged();

  void
  onRenameButtonClick();

  void
  onActiveSectionChanged(ct::StorySection* _pActiveSection);

  void
  onPlaySimulation();

  void
  onStopSimulation();

  void
  onPauseSimulation();

  void
  onVolumenValueChanged(qint32 value);

  void
  onSpeedValueChanged(qint32 value);

  void
  onZoomValueChanged(qint32 value);

  void
  onLineEditorWordStartChanged();

  void
  onLineEditorWordEndChanged();

  void
  onLineEditorWordDataChanged();

  void
  onActiveWordChanged(ct::Word*);

  void
  onActiveWordContentChanged(ct::Word*);

  void
  onWordStartKeyButtonPressed();

  void
  onWordEndKeyButtonPressed();

private:

  /**
   * @brief Open a new project.
   *
   * @param _path Project File's path.
   */
  void
  openProject(const QString& _path);

  /**
   * @brief Save project.
   */
  void
  saveProject();

  /**
   * @brief Check if the project is dirty and
   * ask to the user if he wants to save it.
   */
  void
  checkDirt();

  /**
   * @brief init
   */
  void
  init();

  /**
   * @brief Updates story section's panel.
   */
  void
  updateStorySectionPanel();

  /**
   * @brief Updates story section editor panel.
   */
  void
  updateEditorPanel(ct::StorySection* _pStorySection);

  /**
   * @brief Clears story section's panel.
   */
  void
  clearStorySectionPanel();

  /**
   * @brief Clears story section editor panel.
   */
  void
  clearEditorPanel();

  /**
   * @brief ui
   */
  Ui::Editor*
  ui;

  ct::StorySectionEditorWidget*
  _m_pStorySectionEditorWidget;
};
#endif // EDITOR_H
