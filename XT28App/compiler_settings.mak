####################################################################################################
#
# Makefile for TriCore Projects
# (c) Copyright by BOSCH REXROTH AG, all rights reserved
#
# Compiler settings for make of the RC30 platform.
#
# Sub dir: Project
#
# FILENAME: compiler_settings.mak
#
# FILE VERSION INFORMATION:
#   $Revision: 5791 $
#   $Date: 2013-04-30 15:21:10 +0200 (Di, 30 Apr 2013) $
#   $Author: gtg2si $
#
####################################################################################################

####################################################################################################
# compiler path
####################################################################################################

CC_PATH        = C:/HighTec/TriCore
CC_PATH_BIN    = $(CC_PATH)/bin

####################################################################################################
# Tools for the complete project
####################################################################################################

export CROSS     = $(CC_PATH_BIN)/tricore-
export CC        = $(CROSS)gcc
export AS        = $(CROSS)as
export AR        = $(CROSS)ar
export LD        = $(CROSS)gcc
export OBJCOPY   = $(CROSS)objcopy
export OBJDUMP   = $(CROSS)objdump
export CP        = $(CC_PATH_BIN)/cp
export RM        = $(CC_PATH_BIN)/rm

# check if compiler exists
$(if $(wildcard $(CC).exe),,$(error Hightec TriCore compiler not found in path $(CC).exe (open \
compiler_settings.mak and adapt the variable CC_PATH)!))

CC_SUITE         = $(shell $(CC) -dumpversion)

####################################################################################################
# switch for debug and release for the complete project
####################################################################################################

DEBUG     = -O0 -g2
RELEASE   = -O2
#BUILD     = $(DEBUG)
BUILD     = $(RELEASE)

####################################################################################################
# Flags for assembler, compiler and linker for the complete project
# For verification if the linker flags are really passed to the linker use the linker option -v and
# compare the specified flags.
####################################################################################################

ifneq (,$(findstring 3.3,$(CC_SUITE))) 
  # compiler settings for hightec compiler suite v3.3.7
  export WARNINGS     = -Wall -W -Wmissing-prototypes -Wundef -Wpointer-arith -Wbad-function-cast\
                        -Wcast-qual -Wcast-align -Wstrict-prototypes -Wnested-externs -Wfloat-equal\
                        -Wsign-compare
  export AS_FLAGS     =
  export CC_FLAGS     = $(BUILD) $(WARNINGS) ${CC_FLAGS_EXT} -mtc13 -finline -mcpu=tc1796 -DGNU\
                        -mhard-float -fmessage-length=0
  export LINKER_FLAGS = -Wl,-relax -nostartfiles -Wl,--pcpmap -Wl,--extmap=a
  export LINKER_LNK   = -T linker.inv
endif

ifneq (,$(findstring 3.4.5,$(CC_SUITE)))
  # compiler settings for hightec compiler suite v3.4.5
  export WARNINGS     = -Wall -W -Wmissing-prototypes -Wundef -Wpointer-arith -Wbad-function-cast\
                        -Wcast-qual -Wcast-align -Wstrict-prototypes -Wnested-externs\
                        -Wsign-compare -Wmissing-prototypes -Werror-implicit-function-declaration\
                        -Winline
  export AS_FLAGS     =
  export CC_FLAGS     = $(BUILD) $(WARNINGS) ${CC_FLAGS_EXT} -mcpu24 -mcpu=TC13-FPU_ERR13X_OP1\
                        -mhard-float -finline -fno-common -mwarnprqa=off -maligned-access\
                        -fmessage-length=0 -maligned-data-sections -mno-warn-smalldata-initializers\
                        -fno-builtin -gdwarf-2 -DGNU
  export LINKER_FLAGS = -Wl,-relax -nostartfiles -Wl,--warn-once -Wl,--no-demangle -Wl,--relax\
                        -Wl,--cref -Wl,--pcpmap -Wl,--extmap=a -Wl,--warn-section-align
  export LINKER_LNK   = -T linker.inv
endif

ifeq (,$(findstring 3.3,$(CC_SUITE)))
ifeq (,$(findstring 3.4.5,$(CC_SUITE)))
$(error No valid Hightec Compiler Suite found in $(CC_PATH) (supported are V3.3.X and V3.4.X)!)
endif
endif
