#include "ctMachineStateState.h"

namespace ct {

  MachineStateState::MachineStateState(const QString& _stateName) :
  _m_name(_stateName),
  _m_pStateMachine(nullptr)
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
  {
    _m_pStateMachine = nullptr;
    return;
  }

  const QString& 
  MachineStateState::getName() const
  {
    return _m_name;
  }
}