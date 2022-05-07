#ifndef COTORRO_H
#define COTORRO_H

#include <QObject>
#include <QString>
#include <QPlainTextEdit>

#include "ctCotorroUtilities.h"
#include "ctProject.h"
#include "ctAudioManager.h"
#include "ctResourceManager.h"

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
   * @brief Safely destroys the module.
   */
  static void
  Destroy();

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
   * @brief Attemps to open a project.
   *
   * @param _projectFilePath Project's file path.
   *
   * @return Result.
   */
  eOPRESULT::E
  openProject(const QString &_projectFilePath);

  /**
   * @brief Attemps to save the project.
   *
   * @return Result.
   */
  eOPRESULT::E
  saveProject();

  /**
   * @brief Attemps to save the project in the given path.
   *
   * @param _m_path Path.
   *
   * @return Result.
   */
  eOPRESULT::E
  saveProject(const QString& _m_path);

  /**
   * @brief Get the project.
   *
   * @return Project.
   */
  Project&
  getProject();

  /**
   * @brief Get audio manager.
   *
   * @return Audio manager.
   */
  AudioManager&
  getAudioManager();

  /**
   * @brief Get resource manager.
   * @return
   */
  ResourceManager&
  getResourceManager();

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

  /**
   * @brief Audio manager.
   */
  AudioManager
  _m_audioManager;

  /**
   * @brief _m_resourceManager
   */
  ResourceManager
  _m_resourceManager;

};

}

#endif // COTORRO_H
