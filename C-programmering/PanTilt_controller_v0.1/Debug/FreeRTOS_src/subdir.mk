################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS_src/croutine.c \
../FreeRTOS_src/list.c \
../FreeRTOS_src/queue.c \
../FreeRTOS_src/tasks.c 

OBJS += \
./FreeRTOS_src/croutine.o \
./FreeRTOS_src/list.o \
./FreeRTOS_src/queue.o \
./FreeRTOS_src/tasks.o 

C_DEPS += \
./FreeRTOS_src/croutine.d \
./FreeRTOS_src/list.d \
./FreeRTOS_src/queue.d \
./FreeRTOS_src/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_src/%.o: ../FreeRTOS_src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DPACK_STRUCT_END=__attribute\(\(packed\)\) -D__CODE_RED -DGCC_ARMCM3 -DDEBUG -I"../User_src" -I"../FreeRTOS_include" -I"../FreeRTOS_portable" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


