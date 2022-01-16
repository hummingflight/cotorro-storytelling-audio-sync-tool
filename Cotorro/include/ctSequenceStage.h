#pragma once

#include <qobject.h>

#include "ctCotorroUtilities.h"

namespace ct {

  /**
  * TODO
  */
  class SequenceStage {

  public:

    /**
    * TODO
    */
    SequenceStage();

    /**
    * TODO
    */
    SequenceStage(const QString& _name);

    /**
    * TODO
    */
    virtual ~SequenceStage();

    /**
    * Executes stage.
    */
    virtual eSEQUENCE_RESULT::E
    exec() const;

    /**
    * TODO
    */
    const QString&
    getName() const;

  private:

    /**
    * TODO
    */
    QString _m_name;
  };
}