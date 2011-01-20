# USED_LIBS - a list of libraries to link with
# LIB_DIRS - a list of additional library directories

OSTYPE := $(shell uname -s)

BIN_DIR = build

INC_DIRS = /usr/include/ni

SRC_FILES = src/*.cpp

EXE_NAME = phinect

USED_LIBS += OpenNI
USED_LIBS += zmq

#this should be last
include CommonMakefile

