BIN_DIR = ./bin
OBJ_DIR = ./obj
COMMON_DIR = ./common
SINGLE_SRCS = $(shell ls *.c)
CHAPTER_DIRS = $(shell find . -type d -iname "chap*")
CFLAGS = -c -std=c99 -Wall -Wextra
LIB_COMMON_NAME = libcommon.a
CLIBS = $(LIB_COMMON_NAME)
AR = ar 
AR_FLAGS = -rcs
CC = gcc
