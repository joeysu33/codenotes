BIN_DIR = ../bin_dir/
OBJ_DIR = ../obj_dir/
#CFLAGS = -Wall -Wextra 
CLIBFLAGS =  -L$(BIN_DIR) $(BIN_DIR)libcommon.a

fnc_add_obj_dir = $(OBJ_DIR)$(1)
fnc_add_bin_dir = $(BIN_DIR)$(1)

