#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

  /**
   * @brief Constructor.
   *
   * @param parent
   */
  MainWindow(QWidget *parent = nullptr);

  /**
   *
   */
  ~MainWindow();

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
   * @brief ui
   */
  Ui::MainWindow *ui;

  /**
   * @brief init
   */
  void
  init();

};
#endif // MAINWINDOW_H
