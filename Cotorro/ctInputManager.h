#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Graphics.hpp>

#include <QObject>

namespace ct {

/**
 * @brief The InputManager class
 */
class InputManager : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief InputManager
   * @param parent
   */
  explicit InputManager(QObject *parent = nullptr);

  /**
   * @brief onEvent
   */
  void
  onEvent(sf::Event);

signals:



};

}

#endif // INPUTMANAGER_H
