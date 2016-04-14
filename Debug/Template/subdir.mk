################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Template/ManualControl.c \
../Template/RC_DiagFuncs.c \
../Template/appl_basicDiag.c \
../Template/application.c 

OBJS += \
./Template/ManualControl.o \
./Template/RC_DiagFuncs.o \
./Template/appl_basicDiag.o \
./Template/application.o 

C_DEPS += \
./Template/ManualControl.d \
./Template/RC_DiagFuncs.d \
./Template/appl_basicDiag.d \
./Template/application.d 


# Each subdirectory must supply rules for building sources it contributes
Template/%.o: ../Template/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


