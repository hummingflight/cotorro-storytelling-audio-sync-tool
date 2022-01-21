#include "ctMachineStateState.h"

namespace ct {

  MachineStateState::MachineStateState(const QString& _stateName) :
  _m_name(_stateName)
  { }

  MachineStateState::~MachineStateState()
  { }

  void 
  MachineStateState::onEnter()
  { }

  void 
  MachineStateState::update()
  { }

  void 
  MachineStateState::onExit()
  { }

  void 
  MachineStateState::destroy()
  { }

  const QString& 
  MachineStateState::getName() const
  {
    return _m_name;
  }
}