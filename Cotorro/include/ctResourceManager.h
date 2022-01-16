#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QObject>
#include <QMap>

#include <SFML/Graphics.hpp>

#include "ctFontResourceManager.h"

namespace ct {

/**
 * @brief The ResourceManager class
 */
class ResourceManager : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief ResourceManager
   * @param parent
   */
  explicit ResourceManager(QObject *parent = nullptr);

  /**
   * @brief TODO
   */
  void
  init();

  /**
   * @brief destroy
   */
  void
  destroy();

  /**
   * @brief fontResourceManager
   * @return
   */
  FontResourceManager&
  fontResourceManager();

signals:

private:

  /**
   * @brief _m_resourceManager
   */
  FontResourceManager
  _m_fontResourceManager;

};

}

#endif // RESOURCEMANAGER_H
