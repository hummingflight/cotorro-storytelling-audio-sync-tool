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
  clear();

  return;
}

void
ct::Project::clear()
{
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

}

