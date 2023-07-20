QT += core gui
QT += 3dcore 3drender 3dinput 3dextras multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += \
        std=c11 \
        c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    parser.c \
    main.cpp \
    mainwindow.cpp \
    settingswindow.cpp \
    transformations.c

HEADERS += \
    auxiliary_modules.h \
    mainwindow.h \
    settingswindow.h

FORMS += \
    MainWindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

DISTFILES +=
