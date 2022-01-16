#ifndef COTORROUTILITIES_H
#define COTORROUTILITIES_H

namespace ct {

namespace eLOGTYPE {
enum E {
    kMessage = 0,
    kError,
    kWarning
};
}

namespace eOPRESULT {
enum E {
  kOk = 0,
  kFail,
  kDirectoryNotReadable,
  kDirectoryDoesntExists,
  kFileNotReadable,
  kFileNotWritable,
  kFileDoesntExists,
  kIncompatibleObject
};
}

namespace eMOUSE_EVENT {
enum E {
  kPressed = 0,
  kReleased,
  kMoved,
  kDoubleClicked
};
}

namespace eNODE_TYPE {
enum E {
  kStart,
  kEnd,
  kNull,
  kNode
};
}

namespace eBLOCK_STATUS {
enum E {
  kIdle,
  kSelected,
  kGrouped
};
}

namespace eSELECTION_MODE {
enum E {
  kIdle,
  kSingle,
  kGroup
};
}
}

#endif // COTORROUTILITIES_H
