#pragma once

#include <QString>

namespace ct {

  class MachineState;

  class MachineStateState {

    friend MachineState;

  public:

    /**
    * 
    */
    MachineStateState(const QString& _stateName);

    /**
    * 
    */
    virtual ~MachineStateState();

    /**
    *
    */
    virtual void
    onEnter();

    /**
    * 
    */
    virtual void
    update();

    /**
    *
    */
    virtual void
    onExit();

    /**
    *
    */
    virtual void
    destroy();

    /**
    * Get the state's name.
    */
    const QString&
    getName() const;

  protected:

    /**
    * State's name.
    */
    QString _m_name;

    /**
    * Pointer to the state machine.
    */
    MachineState* _m_pStateMachine;
  };

}