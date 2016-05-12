####################################################################################################
#
# Makefile for TriCore Projects
# (c) Copyright by BOSCH REXROTH AG, all rights reserved
#
# DESCRIPTION:
# This is the top makefile for making an application program.
# It will call all other necessarry makefiles to build the actual project.
#
# PROJECT: API RC30 platform
# Hardware: RC30-00D6
#
# FILE VERSION INFORMATION:
#   $Revision: 3336 $
#   $Date: 2011-02-01 17:09:16 +0100 (Di, 01 Feb 2011) $
#   $Author: gtg2si $
#
####################################################################################################

####################################################################################################
# Configuration
####################################################################################################

# path to the project (can be relative or absolute)
PLATFORM_PATH        = ..

# hex filename
MODULE_NAME          = appl_RC30-00D6_XT28ActiveDampening

# output path for compiler and linker (e.g. objects)
OUTPUT_PATH          = obj

# load compiler settings from another makefile (never touch this)
include compiler_settings.mak

####################################################################################################
# Include paths to header files
####################################################################################################

# assembler include directories
AS_INCLUDES      = 

# c compiler include directories
CC_INCLUDES      = -I$(PLATFORM_PATH)/Includes/core\
									 -I$(PLATFORM_PATH)/Includes\
									 -I$(PLATFORM_PATH)/XT28API\
									 -I$(PLATFORM_PATH)/XT28API\Sensors\
									 -I$(PLATFORM_PATH)/XT28API\Constants\
									 -I$(PLATFORM_PATH)/XT28API\Actuate\
									 -I$(PLATFORM_PATH)/XT28API\Excipad\
									 -I$(PLATFORM_PATH)/XT28API\ActiveDampening\
									 -I.
									 											

									 
####################################################################################################
# List of object files to create
####################################################################################################

# objects of the application to be generated by the c compiler (add an object file for every 
# c file here!)
OBJECTS          = $(OUTPUT_PATH)/App.o\
									 $(OUTPUT_PATH)/IMU.o\
									 $(OUTPUT_PATH)/XT28CANSupport.o\
									 $(OUTPUT_PATH)/PendelumArmPressure.o\
									 $(OUTPUT_PATH)/PendelumArmPosition.o\
									 $(OUTPUT_PATH)/PendelumArmForces.o\
									 $(OUTPUT_PATH)/PendelumArmActuate.o\
									 $(OUTPUT_PATH)/Excipad.o\
									 $(OUTPUT_PATH)/Display.o\
									 $(OUTPUT_PATH)/ActiveDampeningPID.o\
									 $(OUTPUT_PATH)/ActiveDampeningSkyhook.o\
									 $(OUTPUT_PATH)/ActiveDampeningSlidingMode.o\
									 $(OUTPUT_PATH)/ADCConfigurations.o\
									 $(OUTPUT_PATH)/ADCConfigCAN.o\
									 
####################################################################################################
# Path to libraries which should be included
####################################################################################################

# libraries to be included by the linker (additional libraries must be added here)
LIBRARIES        = $(PLATFORM_PATH)/Libs/lib_basic.a\
									 $(PLATFORM_PATH)/Libs/lib_diag.a\
									 $(PLATFORM_PATH)/Libs/lib_uds.a\
									 $(PLATFORM_PATH)/Libs/libm.a\
									 
###################################################################################################
# Compiler, assembler and linker options
###################################################################################################

# additional compiler flags (see compiler_settings.mak)
CC_FLAGS        += -I(PLATFORM_PATH)/XT28API/Sensors
# additional assembler flags (see compiler_settings.mak)
AS_FLAGS        +=
# additional linker flags (see compiler_settings.mak) 
LINKER_FLAGS    += -Wl,-Map,$(OUTPUT_PATH)/$(MODULE_NAME).map

####################################################################################################
# DON'T EDIT SOMETHING BELOW THIS LINE (ONLY FOR INTERNAL USE!)
####################################################################################################

all: cleanobj $(MODULE_NAME).elf $(MODULE_NAME).dump $(MODULE_NAME).hex clean end

.PHONY: $(MODULE_NAME).elf
$(MODULE_NAME).elf: $(OBJECTS)
	@echo $(LD) $(OBJECTS) -o $(OUTPUT_PATH)/$(MODULE_NAME).elf
	@$(LD) -Wl,--start-group $(OBJECTS) $(LIBRARIES) -Wl,--end-group -o $(OUTPUT_PATH)/$(MODULE_NAME).elf\
		$(LINKER_LNK) $(LINKER_FLAGS)

.PHONY: $(MODULE_NAME).dump
$(MODULE_NAME).dump: $(MODULE_NAME).elf
	@$(OBJDUMP) -D -t -z $(OUTPUT_PATH)/$(MODULE_NAME).elf > $(OUTPUT_PATH)/$(MODULE_NAME).dump

.PHONY: $(MODULE_NAME).hex
$(MODULE_NAME).hex: $(MODULE_NAME).elf
	@$(OBJCOPY) -O ihex $(OUTPUT_PATH)/$(MODULE_NAME).elf $(OUTPUT_PATH)/$(MODULE_NAME).hex
	@echo .
	@$(PLATFORM_PATH)/Tools/crc32.exe $(OUTPUT_PATH)/$(MODULE_NAME).map $(OUTPUT_PATH)/$(MODULE_NAME).hex FFFFFFFF 0

.PHONY: cleanall clean cleanobj
cleanall: clean cleanobj end

clean:
	@$(RM) -f *.i
	@$(RM) -f *.s
	@$(RM) -f *.bak

cleanobj:
	@$(RM) -f $(OUTPUT_PATH)/*.o
	@$(RM) -f $(OUTPUT_PATH)/*.elf
	@$(RM) -f $(OUTPUT_PATH)/*.hex
	@$(RM) -f $(OUTPUT_PATH)/*.map
	@$(RM) -f $(OUTPUT_PATH)/*.dump
	@$(RM) -f *.o

end:
	@echo .
	@echo #################################
	@echo # Successfully completed. $(shell time /t)#
	@echo #################################

$(OUTPUT_PATH)/%.o: %.S
	@echo $(AS) -c $< -o $@
	@$(CC) -c -o $@ $< $(AS_FLAGS) $(AS_INCLUDES)

$(OUTPUT_PATH)/%.o: %.ss
	@echo $(AS) -c $< -o $@
	@$(CC) -c -o $@ $< $(AS_FLAGS) $(AS_INCLUDES)

$(OUTPUT_PATH)/%.o: %.c
	@echo $(CC) -c $< -o $@
	@$(CC) -c -o $@ $< $(CC_FLAGS) $(CC_INCLUDES)

