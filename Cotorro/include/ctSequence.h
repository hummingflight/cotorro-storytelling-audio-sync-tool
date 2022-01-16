#pragma once

#include <qobject.h>

#include "ctCotorroUtilities.h"
#include "ctSequenceStage.h"

namespace ct
{

  /**
  * TODO
  */
  class Sequence {

  public:

    /**
    * TODO
    */
    Sequence();

    /**
    * TODO
    */
    Sequence&
    add(SequenceStage& _stage);

    /**
    * TODO
    */
    eSEQUENCE_RESULT::E
    exec() const;

  private:

    /**
    * TODO
    */
    QVector<SequenceStage&> _m_hStages;

  };
}