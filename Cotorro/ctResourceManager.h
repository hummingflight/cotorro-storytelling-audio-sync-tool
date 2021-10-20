#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QObject>
#include <QMap>

#include <SFML/Graphics.hpp>

#include "ctFontResource.h"

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
   *
   **/
  ~ResourceManager();

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
   * @brief TODO
   *
   * @param _key
   * @return
   */
  FontResource&
  getFontData(const QString& _key);

signals:

private:

  /**
   * @brief _m_fontMap
   */
  QMap<QString, FontResource*>
  _m_fontMap;

};

}

#endif // RESOURCEMANAGER_H
