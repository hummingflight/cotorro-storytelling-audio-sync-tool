#ifndef COTORROUTILITIES_H
#define COTORROUTILITIES_H

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
  kFileDoesntExists,
  kIncompatibleObject
};
}

#endif // COTORROUTILITIES_H
