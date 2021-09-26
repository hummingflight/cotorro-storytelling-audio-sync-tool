#include "ctProject.h"

namespace ct {

Project::Project(QObject *parent) :
  QObject(parent),
  _m_name(""),
  _m_isDirty(false)
{
  return;
}

void
ct::Project::init()
{
  _m_storySectionManager.init();

  clear();

  return;
}

void
ct::Project::clear()
{
  _m_storySectionManager.clear();

  _m_name = "";
  _m_isDirty = true;

  return;
}

void Project::dirty()
{
  if(!_m_isDirty) {
    _m_isDirty = !_m_isDirty;
  }

  return;
}

bool Project::isDirty()
{
  return _m_isDirty;
}

}

