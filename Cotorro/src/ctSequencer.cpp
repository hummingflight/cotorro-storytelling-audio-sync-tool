#include "ctSequencer.h"

namespace ct {
  
  Sequencer::Sequencer():
    _m_hSequenceMap()
  {
  }

  eOPRESULT::E 
  Sequencer::add(const QString& _name, Sequence* _sequence)
  {
    if (_m_hSequenceMap.contains(_name)) {
      return eOPRESULT::kFail;
    }

    _m_hSequenceMap.insert(_name, _sequence);

    return eOPRESULT::kOk;
  }

  eSEQUENCE_RESULT::E
  Sequencer::exec(const QString& _name)
  {
    if (!_m_hSequenceMap.contains(_name)) {
      return eSEQUENCE_RESULT::kFail;
    }

    return _m_hSequenceMap.value(_name)->exec();
  }
}