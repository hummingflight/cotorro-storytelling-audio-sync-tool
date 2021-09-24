#ifndef CTPROJECT_H
#define CTPROJECT_H

#include <QObject>

namespace ct {

/**
 * @brief The ctProject class
 */
class Project : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief ctProject
   * @param parent
   */
  explicit Project(QObject *parent = nullptr);

  /**
   * @brief Initialize the class.
   */
  void
  init();

  /**
   * @brief Clears the project.
   */
  void
  clear();

  /**
   * @brief Sets the dirt flag to true.
   */
  void
  dirty();

signals:

private:

  /**
   * Project's name.
   */
  QString
  _m_name;

  /**
   * Indicates if the project is dirty.
  */
  bool
  _m_isDirty;

};

}

#endif // CTPROJECT_H
