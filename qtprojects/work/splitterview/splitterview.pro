TEMPLATE = app

TARGET = splitterviews
CONFIG += c++11 c++14
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

MIDDIR=./middir
MOC_DIR=$$MIDDIR/moc
UI_DIR =$$MIDDIR/ui
OBJECTS_DIR = $$MIDDIR/obj
DESTDIR = ./bin
