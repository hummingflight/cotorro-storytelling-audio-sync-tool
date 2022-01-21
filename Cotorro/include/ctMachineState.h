#pragma once

#include <QObject>
#include <QMap>

#include "ctCotorroUtilities.h"

namespace ct {

  class MachineStateState;
  
  /**
  * TODO
  */
  class MachineState {

  public: 

    /**
    * Constructor.
    */
    MachineState();

    /**
    * Destructor.
    */
    ~MachineState();

    /**
    * 
    */
    void
    init(QVector<MachineStateState*> _aStates);

    /**
    * 
    */
    eOPRESULT::E
    setActive(const QString& _stateName);

    /**
    * 
    */
    bool
    hasState(const QString& _stateName);

    /**
    * 
    */
    const QString&
    getActiveStateName();

    /**
    * 
    */
    void
    destroy();

  private:

    /**
    * 
    */
    QMap<QString, MachineStateState*> _m_hState;

    /**
    *
    */
    MachineStateState* _m_activeState;

  };
}