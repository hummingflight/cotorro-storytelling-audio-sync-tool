QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    ctCotorro.cpp \
    ctProject.cpp \
    ctStorySection.cpp \
    ctStorySectionManager.cpp \
    diaEditor.cpp \
    diaNewProject.cpp \
    diaCreateSection.cpp

HEADERS += \
    ctCotorro.h\
    ctCotorroUtilities.h \
    ctProject.h \
    ctStorySection.h \
    ctStorySectionManager.h \
    diaEditor.h \
    diaNewProject.h \
    diaCreateSection.h

FORMS += \
    diaEditor.ui \
    diaNewProject.ui \
    diaCreateSection.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  app-resources.qrc
