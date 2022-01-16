#pragma once

#include <qmap.h>

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
  const eOPRESULT::E
  add(const QString& _name, const Sequence& _sequence);

  /**
  * TODO
  */
  const eSEQUENCE_RESULT::E
  exec(const QString& _name);

private:

  QMap<QString, const Sequence&> _m_hSequenceMap;
};

}