#pragma once

#include <QMap>

#include "ctCotorroUtilities.h"
#include "ctSequence.h"

namespace ct {

  /**
  * TODO
  */
class Sequencer {

public:

  /**
  * TODO
  */
  Sequencer();

  /**
  * TODO
  */
  eOPRESULT::E
  add(const QString& _name, Sequence* _sequence);

  /**
  * TODO
  */
  eSEQUENCE_RESULT::E
  exec(const QString& _name);

private:

  QMap<QString, Sequence*> _m_hSequenceMap;
};

}