TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBEVENT_DIR = /home/ds/github.com/libevent/build
INCLUDEPATH += $$LIBEVENT_DIR/include
LIBS += -L$$LIBEVENT_DIR/lib -levent

SOURCES += main.c
