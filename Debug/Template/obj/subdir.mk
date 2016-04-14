################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Template/obj/application.o 

C_SRCS += \
../Template/obj/manual_pendelurm_arm_kontroll_17oct2014cfile.c 

OBJS += \
./Template/obj/manual_pendelurm_arm_kontroll_17oct2014cfile.o 

C_DEPS += \
./Template/obj/manual_pendelurm_arm_kontroll_17oct2014cfile.d 


# Each subdirectory must supply rules for building sources it contributes
Template/obj/%.o: ../Template/obj/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


