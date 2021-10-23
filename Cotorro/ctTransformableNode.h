#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H

#include <SFML/Graphics.hpp>

#include <QMap>

namespace ct {

/**
 * @brief The TransformableObject class
 */
class TransformableNode : public sf::Transformable
{
public:

  /**
   * @brief TransformableObject
   */
  TransformableNode();

  /**
   * @brief ~TransformableObject
   */
  virtual ~TransformableNode();

  /**
   * @brief onDestroy
   */
  virtual void
  onDestroy();

  /**
   * @brief setParent
   * @param _transformableNode
   */
  void
  setParent(TransformableNode& _transformableNode);

  /**
   * @brief addChild
   * @param _transformableNode
   */
  void
  addChild(TransformableNode* _transformableNode);

  /**
   * @brief getGlobalTransform
   * @return
   */
  const sf::Transform&
  getGlobalTransform();

  /**
   * @brief getUuid
   * @return
   */
  QString
  getUuid();

  /**
   * @brief destroy
   */
  void
  destroy();

protected:

  /**
   * Updates transform.
   */
  void
  _updateTransform();

  /**
   * @brief _m_uuid
   */
  QString
  _m_uuid;

  /**
  * Parent.
  */
  TransformableNode*
  _m_pParent;

  /**
   * @brief _m_global
   */
  sf::Transform
  _m_global;

  /**
   * @brief _m_hChildren
   */
  QMap<QString, TransformableNode*>
  _m_hChildren;

  /**
   * @brief _m_isDirty
   */
  bool
  _m_isDirty;

};

}



#endif // TRANSFORMABLEOBJECT_H
