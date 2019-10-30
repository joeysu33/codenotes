TEMPLATE = lib

SOURCES += $$PWD/*.cpp
HEADERS += $$PWD/*.h

DESTDIR = ./bin
MOC_DIR = ./inter/moc
OBJECTS_DIR = ./inter/obj
RCC_DIR = ./inter/rcc
UI_DIR = ./inter/ui

CONFIG += plugin
