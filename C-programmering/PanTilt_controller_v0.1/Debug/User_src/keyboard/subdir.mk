################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_src/keyboard/keyboard.c 

OBJS += \
./User_src/keyboard/keyboard.o 

C_DEPS += \
./User_src/keyboard/keyboard.d 


# Each subdirectory must supply rules for building sources it contributes
User_src/keyboard/%.o: ../User_src/keyboard/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DPACK_STRUCT_END=__attribute\(\(packed\)\) -D__CODE_RED -DGCC_ARMCM3 -DDEBUG -I"../User_src" -I"../FreeRTOS_include" -I"../FreeRTOS_portable" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


