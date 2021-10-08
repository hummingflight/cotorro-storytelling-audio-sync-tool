#ifndef COTORRO_H
#define COTORRO_H

#include <QObject>
#include <QString>
#include <QPlainTextEdit>

#include "ctCotorroUtilities.h"
#include "ctProject.h"

class Editor;

namespace ct {

/**
 * @brief Cotorro's service locator.
 */
class Cotorro : public QObject
{
  Q_OBJECT

public:

  /**
   * @brief Start the Cotorro module
   */
  static void
  Start(QObject *parent);

  /**
   * @brief Get module instance.
   */
  static Cotorro*&
  Instance();

  /**
   * @brief Send a message to the logger.
   *
   * @param Message type.
   * @param Message content.
   */
  static void
  Log(const eLOGTYPE::E& _type, const QString& _msg);

  /**
   * @brief Initialize the module.
   */
  void
  init(Editor* _pMainWindow);

  /**
   * @brief Get the project.
   *
   * @return Project.
   */
  Project&
  getProject();

  /**
   * @brief Safely destroys the module.
   */
  void
  destroy();

signals:

private:

  /**
   * @brief Constructor.
   *
   * @param parent
   */
  explicit Cotorro(QObject *parent = nullptr);

  /**
   * @brief Get Instance.
   *
   * @return Instance.
   */
  static Cotorro*&
  _Instance();

  /**
   * @brief Called when the Module is being created.
   */
  void
  _onStart();

  /**
   * @brief Main Window pointer.
   */
  Editor*
  _pEditorWindow;

  /**
   * @brief Application project.
   */
  Project
  _m_project;

};

}

#endif // COTORRO_H