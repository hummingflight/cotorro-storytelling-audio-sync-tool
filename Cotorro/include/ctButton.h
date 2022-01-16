#ifndef CTBUTTON_H
#define CTBUTTON_H

#include <SFML/Graphics.hpp>

#include "ctInteractiveArea.h"

namespace ct {

/**
 * @brief The Button Class
 */
class Button : public InteractiveArea
{
public:

  /**
   * @brief Button
   */
  Button();

  /**
   * @brief ~Button
   */
  virtual ~Button();

  /**
   * @brief update
   * @param _window
   */
  virtual void
  update(sf::RenderWindow& _window);

protected:

  /**
   * @brief Rectangle
   */
  sf::RectangleShape _m_rectangle;

};

}



#endif // CTBUTTON_H
