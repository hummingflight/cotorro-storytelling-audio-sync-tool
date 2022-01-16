#include "ctTransformableNode.h"

#include <QUuid>

namespace ct {

TransformableNode::TransformableNode() :
  _m_uuid(QUuid::createUuid().toString(QUuid::StringFormat::Id128)),
  _m_pParent(nullptr),
  _m_isDirty(true)
{
  return;
}

TransformableNode::~TransformableNode()
{
  return;
}

void
TransformableNode::onDestroy()
{
  // Implement in derived class.
  return;
}

void
TransformableNode::setParent(TransformableNode &_transformableNode)
{
  _m_pParent = &_transformableNode;
  return;
}

const sf::Transform&
TransformableNode::getGlobalTransform()
{
  _updateTransform();
  return _m_global;
}

QString
TransformableNode::getUuid()
{
  return _m_uuid;
}

void
TransformableNode::destroy()
{
  onDestroy();
  return;
}

void
TransformableNode::_updateTransform()
{
  if(_m_pParent != nullptr) {
    _m_global = _m_pParent->getGlobalTransform() * getTransform();
  }
  else {
    _m_global = getTransform();
  }
  return;
}

}

