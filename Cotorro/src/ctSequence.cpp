#include "ctSequence.h"

#include "ctCotorro.h"

namespace ct {
  Sequence::Sequence() 
    : _m_hStages()
  {
  }

  Sequence& 
  Sequence::add(SequenceStage* _stage)
  {
    _m_hStages.push_back(_stage);
    return *this;
  }

  eSEQUENCE_RESULT::E 
  Sequence::exec() const
  {
    QVectorIterator<SequenceStage*> i(_m_hStages);
    eSEQUENCE_RESULT::E result = eSEQUENCE_RESULT::kOk;

    while (i.hasNext()) {

      SequenceStage* stage = i.next();

      Cotorro::Log(
        eLOGTYPE::kMessage,
        QObject::tr("| Sequence | Executing Stage: %1.").arg(stage->getName())
      );

      result = stage->exec();

      if (result != eSEQUENCE_RESULT::kOk) {
       
        Cotorro::Log(
          eLOGTYPE::kMessage,
          QObject::tr("| Sequence | Sequence Aborted.")
        );

        break;
      }
    }

    return result;
  }
}