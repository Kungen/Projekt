################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/watch/subdir.mk
-include src/subdir.mk
-include src/lcd/subdir.mk
-include src/event/subdir.mk
-include src/cpu/subdir.mk
-include src/RTCS/subdir.mk
-include src/LED/subdir.mk
-include src/Drehimpulsgeber/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ur.axf

# Tool invocations
ur.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map=ur.map -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "ur_Debug.ld" -o"ur.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) ur.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size ur.axf; # arm-none-eabi-objcopy -O binary ur.axf ur.bin ; checksum -d ur.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
