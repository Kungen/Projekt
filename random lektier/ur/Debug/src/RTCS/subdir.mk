################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/RTCS/schedule.c \
../src/RTCS/systick.c 

OBJS += \
./src/RTCS/schedule.o \
./src/RTCS/systick.o 

C_DEPS += \
./src/RTCS/schedule.d \
./src/RTCS/systick.d 


# Each subdirectory must supply rules for building sources it contributes
src/RTCS/%.o: ../src/RTCS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -I"C:\StellarisWare" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


