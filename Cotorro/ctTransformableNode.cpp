#include "ctTransformableNode.h"

#include <QUuid>

namespace ct {

TransformableNode::TransformableNode() :
  _m_uuid(QUuid::createUuid().toString(QUuid::StringFormat::Id128)),
  _m_pParent(nullptr),
  _m_hChildren(),
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

void
TransformableNode::addChild(TransformableNode *_transformableNode)
{
  QString uuid = _transformableNode->getUuid();
  if(_m_hChildren.find(uuid) != _m_hChildren.end()) {
    return;
  }

  _m_hChildren.insert(uuid, _transformableNode);
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

  foreach(TransformableNode* _object, _m_hChildren) {
    _object->destroy();
  }

  qDeleteAll(_m_hChildren);
  _m_hChildren.clear();
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

