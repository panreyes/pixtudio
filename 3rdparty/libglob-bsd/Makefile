#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

# Directories.
OBJ_DIR			:= obj
LIB_DIR			:= lib
BIN_DIR			:= bin
SRC_DIR			:= src
INCLUDE_DIR		:= include

# Tools.
PIPE_TO_SED := 2>&1 | sed "s/:\([0-9]*\):/\(\1\) :/"

# Library source files.
SRCS	:= $(SRC_DIR)/glob.c

# Library object files.
OBJS	:= $(subst $(SRC_DIR),$(OBJ_DIR),$(SRCS:.c=.o))

# What's a full build?
all: $(LIB_DIR)/libglob.a

# How to delete the intermediate files.
clean:
	@echo Cleaning $(LIB_DIR)/libglob.a $(OBJ_DIR)
	@rm -f $(LIB_DIR)/libglob.a $(OBJS) $(TEST_OBJS)
	
install:
	@mkdir -p $(INSTALL_HEADER_DIR) $(INSTALL_LIB_DIR)
	@cp -frv $(LIB_DIR)/*.* $(INSTALL_LIB_DIR)
	@cp -frv $(INCLUDE_DIR)/*.* $(INSTALL_HEADER_DIR)

# How to build a library.
$(LIB_DIR)/libglob.a: $(OBJS)
	@echo Archiving $@
	@-mkdir -p $(dir $@)
	powerpc-eabi-ar crs $@ $(OBJS)
	@echo ----

# Compilation flags.
COMMON_FLAGS	:= -g -O3 -mrvl -Wall $(MACHDEP)
INCLUDES		:= -Iinclude -I$(DEVKITPRO)/libogc/include
# -include sys/wait.h 
# -include sys/syslimits.h

DEFINES			:= -DGEKKO -DTARGET_WII

CFLAGS			:= $(COMMON_FLAGS) $(INCLUDES) $(DEFINES)

# How to compile C file (SDL library).
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $<
	@-mkdir -p $(dir $@)
	powerpc-eabi-gcc $(CFLAGS) -c $< -o $@ $(PIPE_TO_SED)

