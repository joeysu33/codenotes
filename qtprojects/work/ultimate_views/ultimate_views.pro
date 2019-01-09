TEMPLATE = app
TARGET = ultimate_views

QT += gui core widgets
CONFIG += c++11
HEADERS += mainwindow.h \
            minisplitter.h \
            editorview.h \
            styledbar.h \
            editortoolbar.h \
            ultimateviewstr.h \
            iview.h \
            iconprovider.h \
            qtcassert.h \
            utils.h \
            ultraviewmanager.h

SOURCES += main.cpp \
            mainwindow.cpp \
            minisplitter.cpp \
            editorview.cpp \
            styledbar.cpp \
            editortoolbar.cpp \
            ultimateviewstr.cpp \
            iview.cpp \
            iconprovider.cpp \
            utils.cpp \
            ultraviewmanager.cpp

RESOURCES += \
    utlis.qrc


include(../../configs.pri)
