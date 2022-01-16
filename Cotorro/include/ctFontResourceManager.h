#ifndef FONTRESOURCEMANAGER_H
#define FONTRESOURCEMANAGER_H

#include <SFML/Graphics.hpp>

#include <QString>
#include <QMap>

#include "ctCotorroUtilities.h"
#include "ctFontResource.h"

namespace ct {

/**
 * @brief The FontResourceManager class
 */
class FontResourceManager
{
public:

  /**
   * @brief FontResourceManager
   */
  FontResourceManager();

  /**
   *
   */
  ~FontResourceManager();

  /**
   * @brief init
   */
  void
  init();

  /**
   * @brief load
   * @param _key
   * @return
   */
  eOPRESULT::E
  load(const QString& _key);

  /**
   * @brief has
   * @param _key
   * @return
   */
  bool
  has(const QString& _key);

  /**
   * @brief get
   * @param _key
   * @return
   */
  const FontResource&
  get(const QString& _key);

  /**
   * @brief destroy
   */
  void
  destroy();

private:

  /**
   * @brief _m_fontMap
   */
  QMap<QString, FontResource*>
  _m_fontMap;

};

}


#endif // FONTRESOURCEMANAGER_H
