#include "ctMachineState.h"

#include <QVector>

#include "ctMachineStateState.h"

#include "ctCotorro.h"

namespace ct {

  MachineState::MachineState():
  _m_hState(),
  _m_activeState(nullptr)
  { }

  MachineState::~MachineState()
  {
    destroy();
    return;
  }

  void 
  MachineState::init(QVector<MachineStateState*> _aStates)
  {
    QVectorIterator<MachineStateState*> i(_aStates);
    while (i.hasNext()) {
      MachineStateState* pState = i.next();
      if (!_m_hState.contains(pState->getName())) {
        _m_hState.insert(pState->getName(), pState);
      }
      else {
        Cotorro::Log(
          eLOGTYPE::kWarning,
          QObject::tr("| MachineStage | State with name $1, already exists.")
                   .arg(pState->getName())
        );
      }
    }
    return;
  }

  eOPRESULT::E 
  MachineState::setActive(const QString& _stateName)
  {
    if (!_m_hState.contains(_stateName)) {
      Cotorro::Log(
        eLOGTYPE::kWarning,
        QObject::tr("| MachineStage | State Machine doesn't have any state with name $1.")
        .arg(_stateName)
      );
      return eOPRESULT::kFail;
    }

    if (_m_activeState != nullptr) {
      _m_activeState->onExit();
    }

    _m_activeState = _m_hState.value(_stateName);
    _m_activeState->onEnter();

    return eOPRESULT::kOk;
  }

  bool 
  MachineState::hasState(const QString& _stateName)
  {
    return _m_hState.contains(_stateName);
  }

  const QString& 
  MachineState::getActiveStateName()
  {
    if (_m_activeState != nullptr) {
      return _m_activeState->getName();
    }
    
    return QObject::tr("");
  }

  void 
  MachineState::destroy()
  {
    _m_activeState = nullptr;
    qDeleteAll(_m_hState);
    _m_hState.clear();
    return;
  }
}