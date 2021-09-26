#ifndef STORYSECTIONMANAGER_H
#define STORYSECTIONMANAGER_H

#include <QObject>

namespace ct {

class StorySectionManager : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief Constructor.
   * @param parent
   */
  explicit StorySectionManager(QObject *parent = nullptr);

  /**
   * @brief init
   */
  void
  init();

  /**
   * @brief clear
   */
  void
  clear();

signals:

};

}

#endif // STORYSECTIONMANAGER_H
