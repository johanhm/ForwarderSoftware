####################################################################################################
#
# Makefile for RC_30 platform modules
#
# (c) Copyright by BOSCH REXROTH AG, all rights reserved
#
# DESCRIPTION:
#   Make of separate module. A library will be generated.
#
#   $Revision: 2911 $
#   $Date: 2010-08-30 17:57:10 +0200 (Mo, 30 Aug 2010) $
#   $Author: gtg2si $
#
####################################################################################################

####################################################################################################
# Configuration
####################################################################################################

PLATFORM_PATH    = ..
MODULE_NAME      = library_name
LIBRARY_PATH     =
OUTPUT_PATH      = obj

include compiler_settings.mak

####################################################################################################
# Include paths for header files
####################################################################################################

CC_INCLUDES      = -I$(PLATFORM_PATH)/Includes/core\
									 -I$(PLATFORM_PATH)/Includes\
									 -I.

####################################################################################################
# List of object files to create
####################################################################################################

OBJECTS          = $(OUTPUT_PATH)/application.o\

###################################################################################################
# Compiler and linker options
###################################################################################################

CC_FLAGS        +=

####################################################################################################
# DON'T EDIT SOMETHING BELOW THIS LINE
####################################################################################################

all: cleanobj $(OBJECTS) clean

.PHONY: cleanall clean cleanobj
cleanall: clean cleanobj

clean:
	@$(RM) -f *.i
	@$(RM) -f *.s
	@$(RM) -f *.bak

cleanobj:
	@$(RM) -f $(OUTPUT_PATH)/*.a
	@$(RM) -f $(OUTPUT_PATH)/*.o
	@$(RM) -f *.o

$(OUTPUT_PATH)/%.o: %.c
	@echo $(CC) -c $< -o $@
	@$(CC) -c -o $@ $< $(CC_FLAGS) $(CC_INCLUDES)
	@$(AR) -r $(OUTPUT_PATH)/lib_$(MODULE_NAME).a $(OUTPUT_PATH)/*.o
	@$(AR) -t $(OUTPUT_PATH)/lib_$(MODULE_NAME).a > $(OUTPUT_PATH)/lib_$(MODULE_NAME)_list.txt
