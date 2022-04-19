#include "ctMachineStateState.h"
#include "..\include\ctWordInputState.h"

namespace ct {

  WordInputState::WordInputState(const QString& _stateName) :
    MachineStateState(_stateName)
  {
  }

  WordInputState::~WordInputState()
  {
  }
}