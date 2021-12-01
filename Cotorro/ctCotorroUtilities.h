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

}

#endif // COTORROUTILITIES_H
