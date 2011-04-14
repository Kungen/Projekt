################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include User_src/spi/subdir.mk
-include User_src/print/subdir.mk
-include User_src/subdir.mk
-include User_src/lcd/subdir.mk
-include User_src/keyboard/subdir.mk
-include User_src/emp_led/subdir.mk
-include User_src/cpu/subdir.mk
-include User_src/alive_task/subdir.mk
-include User_src/adc/subdir.mk
-include FreeRTOS_src/subdir.mk
-include FreeRTOS_portable/subdir.mk
-include FreeRTOS_MemMang/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: FreeRTOS-test.axf

# Tool invocations
FreeRTOS-test.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map=FreeRTOS-test.map -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "freertos-test_Debug.ld" -o"FreeRTOS-test.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) FreeRTOS-test.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size FreeRTOS-test.axf; # arm-none-eabi-objcopy -O binary FreeRTOS-test.axf FreeRTOS-test.bin ; checksum -d FreeRTOS-test.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
