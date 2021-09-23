#ifndef COTORRO_H
#define COTORRO_H

#include <QObject>

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
   * @brief Initialize the module.
   */
  void
  init();

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

};

#endif // COTORRO_H
