QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ctAudioManager.cpp \
    ctButton.cpp \
    ctFontResource.cpp \
    ctFontResourceManager.cpp \
    ctFrame.cpp \
    ctInteractiveArea.cpp \
    ctResourceManager.cpp \
    ctSfmlCanvas.cpp \
    ctStorySectionEditorWidget.cpp \
    ctTimeLineLine.cpp \
    ctTransformableNode.cpp \
    ctWaveformEditor.cpp \
    ctWaveformEditorSlider.cpp \
    ctWord.cpp \
    ctWordBlock.cpp \
    ctWordsEditor.cpp \
    main.cpp \
    ctCotorro.cpp \
    ctProject.cpp \
    ctStorySection.cpp \
    ctStorySectionManager.cpp \
    diaEditor.cpp \
    diaNewProject.cpp \
    diaCreateSection.cpp

HEADERS += \
    ctAudioManager.h \
    ctButton.h \
    ctCotorro.h\
    ctCotorroUtilities.h \
    ctFontResource.h \
    ctFontResourceManager.h \
    ctFrame.h \
    ctInteractiveArea.h \
    ctProject.h \
    ctResourceManager.h \
    ctSfmlCanvas.h \
    ctStorySection.h \
    ctStorySectionEditorWidget.h \
    ctStorySectionManager.h \
    ctTimeLineLine.h \
    ctTransformableNode.h \
    ctWaveformEditor.h \
    ctWaveformEditorSlider.h \
    ctWord.h \
    ctWordBlock.h \
    ctWordsEditor.h \
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

LIBS += -L$$PWD/dependencies/sfml/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-system -lsfml-graphics -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-system-d -lsfml-graphics-d -lsfml-window-d

INCLUDEPATH += $$PWD/dependencies/sfml/include
DEPENDPATH += $$PWD/dependencies/sfml/include
