#include "cotorro.h"

Cotorro::Cotorro(QObject *parent) : QObject(parent)
{

}

void
Cotorro::Start(QObject *parent)
{
  if(Cotorro::_Instance() != nullptr)
  {
    // Cotorro already started.
    return;
  }

  Cotorro::_Instance() = new Cotorro(parent);
  Cotorro::_Instance()->_onStart();
}

Cotorro*&
Cotorro::Instance()
{
  return Cotorro::_Instance();
}

void Cotorro::init()
{
  return;
}

void Cotorro::destroy()
{
  return;
}

Cotorro*&
Cotorro::_Instance()
{
  static Cotorro* _pINSTANCE = nullptr;
  return _pINSTANCE;
}

void
Cotorro::_onStart()
{
  // TODO
}
