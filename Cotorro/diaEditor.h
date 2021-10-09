#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QMainWindow
{
  Q_OBJECT

public:
  /**
   * @brief Editor
   * @param parent
   */
  Editor(QWidget *parent = nullptr);


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
  onStoryManagerChanged();

  void
  onStorySectionDoubleClicked(QListWidgetItem *item);

  void
  on_actionRemoveSection_triggered();

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
   * @brief Clears story section's panel.
   */
  void
  clearStorySectionPanel();

  /**
   * @brief ui
   */
  Ui::Editor*
  ui;
};
#endif // EDITOR_H
