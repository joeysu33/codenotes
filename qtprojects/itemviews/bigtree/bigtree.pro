TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    treemodel.cpp


FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    treemodel.h

QT += widgets core gui

DEFINES += QT_DEPRECATED_WARNINGS


include(../../configs.pri)
