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
   * @brief MainWindow
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

private:

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
