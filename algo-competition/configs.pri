INCLUDEPATH *=  $$_PRO_FILE_PWD_/../../ \
                $$_PRO_FILE_PWD_/../ \
                $$_PRO_FILE_PWD_/

isEmpty(PROJECT_NAME) {
    b = $$basename(_PRO_FILE_)
    a = $$split(b,.)
    PROJECT_NAME = $$first(a)
}

PROJECT_ROOT = $$PWD/bin
PROJECT_BIN_DIR = $$PROJECT_ROOT
PROJECT_LIB_DIR = $$PROJECT_ROOT/lib
PROJECT_HEADER_DIR = $$PROJECT_ROOT/include

MID_FILES_DIR = ./middle/$$PROJECT_NAME
MOC_DIR = $$MID_FILES_DIR/moc
RCC_DIR = $$MID_FILES_DIR/rcc
OBJECTS_DIR = $$MID_FILES_DIR/obj
UI_DIR = $$MID_FILES_DIR/ui


isEqual(TEMPLATE, app) {
    DESTDIR = $$PROJECT_BIN_DIR
    CONFIG *= app_bundle
}

isEqual(TEMPLATE, lib) {
    DESTDIR = $$PROJECT_LIB_DIR
    CONFIG *= lib_bundle
}

CONFIG *= c++11 c++14
!isEmpty(PROJECT_DEBUG) {
    message(PROJECT_NAME=$$PROJECT_NAME)
    message(DESTDIR=$$DESTDIR)
}
