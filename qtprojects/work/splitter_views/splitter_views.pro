TEMPLATE = app

TARGET = splitter_views
CONFIG += c++11
QT += core gui widgets

SOURCES += ngpspview.cpp \
    test_mainwindow.cpp \
    main.cpp \
    ngpspviewmanager.cpp \
    ngpminisplitter.cpp \
    ispview.cpp
HEADERS += ngpspview.h \
    test_mainwindow.h \
    ngpspviewmanager.h \
    ngpminisplitter.h \
    ispview.h

include(../../configs.pri)
