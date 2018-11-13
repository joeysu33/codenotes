INCLUDEPATH *= ../../  \
                                ..

isEmpty(PROJECT_NAME) {
    va = $$basename(_PRO_FILE_)
    vb = $$split(va, .)
    PROJECT_NAME = $$first(vb)
}

MIDDLE_OBJ_DIR = ./middle
OBJECTS_DIR = $$MIDDLE_OBJ_DIR/obj
MOC_DIR = $$MIDDLE_OBJ_DIR/moc
UI_DIR = $$MIDDLE_OBJ_DIR/ui
RCC_DIR = $$MIDDLE_OBJ_DIR/rcc

CONFIG *= c++11 c++14

ROOT_DIR = $$absolute_path(.)
BIN_DIR = $$ROOT_DIR/bin
LIB_DIR  = $$ROOT_DIR/bin/lib

isEqual(TEMPLATE, app) {
    DESTDIR = $$BIN_DIR
}

isEqual(TEMPLATE, lib) {
    DESTDIR = $$LIB_DIR
}

LIBS *= -L$$LIB_DIR

DEBUG_MSG =
!isEmpty(DEBUG_MSG) {
    message(PROJECT_NAME = $$PROJECT_NAME)
    message(_PRO_FILE_PWD_ = $$_PRO_FILE_PWD_)
    message(absolute_path = $$absolute_path(.))
}

