# USED_LIBS - a list of libraries to link with
# LIB_DIRS - a list of additional library directories

OSTYPE := $(shell uname -s)

BIN_DIR = ../build

#INC_DIRS = /usr/include/ni

SRC_FILES = *.cpp

EXE_NAME = coordinate_testing

#USED_LIBS += OpenNI

# some defaults
ifndef SSE_GENERATION
	SSE_GENERATION = 3
endif

ifndef TARGET_SYS_ROOT
	TARGET_SYS_ROOT = /
endif

# tools
RM = rm -rf
CP = cp

# expand file list
SRC_FILES_LIST = $(wildcard $(SRC_FILES))

OSTYPE := $(shell uname -s)

# change c struct alignment options to be compatable with Win32
ifneq ("$(OSTYPE)","Darwin")
	CFLAGS += -malign-double
else
	#CFLAGS += -arch i386 -arch x86_64
	#LDFLAGS += -arch i386 -arch x86_64
	#My changes...
	CFLAGS += -arch x86_64
	LDFLAGS += -arch x86_64
endif

# tell compiler to use the target system root
ifneq ("$(TARGET_SYS_ROOT)","/")
	CFLAGS += --sysroot=$(TARGET_SYS_ROOT)
	LDFLAGS += --sysroot=$(TARGET_SYS_ROOT)
endif

# define the intermediate directory
INT_DIR = $(BIN_DIR)/obj/$(EXE_NAME)

# define output directory
OUT_DIR = $(BIN_DIR)

# define a function to figure .o file for each source file (placed under intermediate directory)
SRC_TO_OBJ = $(addprefix ./$(INT_DIR)/,$(addsuffix .o,$(notdir $(basename $1))))

# create a list of all object files
OBJ_FILES = $(call SRC_TO_OBJ,$(SRC_FILES_LIST))

# define a function to translate any source file to its dependency file (note that the way we create
# dep files, as a side affect of compilation, always puts the files in the INT_DIR with suffix .d)
SRC_TO_DEP = $(addprefix ./$(INT_DIR)/,$(addsuffix .d,$(notdir $(basename $1))))

# create a list of all dependency files
DEP_FILES = $(call SRC_TO_DEP,$(SRC_FILES_LIST))

# append the -I switch to each include directory
INC_DIRS_OPTION = $(foreach dir,$(INC_DIRS),-I$(dir))

# append the -L switch to each library directory
LIB_DIRS_OPTION = $(foreach dir,$(LIB_DIRS),-L$(dir)) -L$(OUT_DIR)

# append the -l switch to each library used
USED_LIBS_OPTION = $(foreach lib,$(USED_LIBS),-l$(lib))

# append the -D switch to each define
DEFINES_OPTION = $(foreach def,$(DEFINES),-D$(def))

# some lib / exe specifics
ifneq "$(EXE_NAME)" ""
	OUTPUT_NAME = $(EXE_NAME)
	OUTPUT_COMMAND = $(CXX) -o $(OUTPUT_FILE) $(OBJ_FILES) $(LDFLAGS)
endif

# full path to output file
OUTPUT_FILE = $(OUT_DIR)/$(OUTPUT_NAME)

# set Debug / Release flags
CFLAGS += -O2 -DNDEBUG
ifeq ($(SSE_GENERATION), 2)
	CFLAGS += -msse2
else
	ifeq ($(SSE_GENERATION), 3)
		CFLAGS += -msse3
	else
		($error "Only SSE2 and SSE3 are supported")
	endif
endif
CSFLAGS += -o+

CFLAGS += $(INC_DIRS_OPTION) $(DEFINES_OPTION)
LDFLAGS += $(LIB_DIRS_OPTION) $(USED_LIBS_OPTION)

ifeq "$(NET)" "1"
define CREATE_SRC_TARGETS
$(call SRC_TO_OBJ,$1) : $1 | $(INT_DIR)
	touch $(call SRC_TO_OBJ,$1)
endef
else
define CREATE_SRC_TARGETS
# create a target for the object file (the CXX command creates both an .o file
# and a .d file)
ifneq ("$(OSTYPE)","Darwin")
$(call SRC_TO_OBJ,$1) : $1 | $(INT_DIR)
	$(CXX) -MD -MP -MT "$(call SRC_TO_DEP,$1) $$@" -c $(CFLAGS) -o $$@ $$<
else
$(call SRC_TO_OBJ,$1) : $1 | $(INT_DIR)
	$(CXX) -c $(CFLAGS) -o $$@ $$<
endif
endef
endif

#############################################################################
# Targets
#############################################################################
.PHONY: all clean

# define the target 'all' (it is first, and so, default)
all: $(OUTPUT_FILE)

# Intermediate directory
$(INT_DIR):
	mkdir -p $(INT_DIR)

# create targets for each source file
$(foreach src,$(SRC_FILES_LIST),$(eval $(call CREATE_SRC_TARGETS,$(src))))

# include all dependency files (we don't need them the first time, so we can use -include)
-include $(DEP_FILES)

# Output directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Final output file
$(OUTPUT_FILE): $(OBJ_FILES) | $(OUT_DIR)
	$(OUTPUT_COMMAND)

clean:
	$(RM) $(OUTPUT_FILE) $(OBJ_FILES) $(DEP_FILES)
