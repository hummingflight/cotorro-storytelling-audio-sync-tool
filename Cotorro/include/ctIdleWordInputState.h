#pragma once

#include "ctWordInputState.h"

namespace ct
{
  /**
  * TODO
  * 
  * key: "Idle"
  */
  class IdleWordInputState :
    public WordInputState 
  {

  public:

    IdleWordInputState();

    virtual ~IdleWordInputState();

  };
}