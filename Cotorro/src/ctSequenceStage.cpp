#include "ctSequenceStage.h"

namespace ct {
  
  SequenceStage::SequenceStage()
    : _m_name("UNDEFINED NAME")
  {
  }

  SequenceStage::SequenceStage(const QString& _name) :
    _m_name(_name)
  {
  }

  SequenceStage::~SequenceStage()
  {
  }
  
  eSEQUENCE_RESULT::E
  SequenceStage::exec() const
  {
    return eSEQUENCE_RESULT::kOk;
  }

  const QString& 
  SequenceStage::getName() const
  {
    return _m_name;
  }
}