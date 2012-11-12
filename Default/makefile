################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include wirish/subdir.mk
-include wirish/stm32f2/subdir.mk
-include wirish/stm32f1/subdir.mk
-include wirish/sim3u1/subdir.mk
-include wirish/boards/st_stm3220g_eval/subdir.mk
-include wirish/boards/si_arduino/subdir.mk
-include wirish/boards/olimex_stm32_h103/subdir.mk
-include wirish/boards/maple_native/subdir.mk
-include wirish/boards/maple_mini/subdir.mk
-include wirish/boards/maple_RET6/subdir.mk
-include wirish/boards/maple/subdir.mk
-include wirish/boards/VLDiscovery/subdir.mk
-include libraries/Wire/subdir.mk
-include libraries/Servo/subdir.mk
-include libraries/LiquidCrystal/subdir.mk
-include libraries/FreeRTOS/utility/subdir.mk
-include libraries/FreeRTOS/subdir.mk
-include libmaple/subdir.mk
-include libmaple/usb/usb_lib/subdir.mk
-include libmaple/usb/stm32f1/subdir.mk
-include libmaple/usb/sim3u1/subdir.mk
-include libmaple/stm32f2/subdir.mk
-include libmaple/stm32f1/value/subdir.mk
-include libmaple/stm32f1/subdir.mk
-include libmaple/stm32f1/performance/subdir.mk
-include libmaple/sim3u1/subdir.mk
-include examples/subdir.mk
-include build/wirish/subdir.mk
-include build/wirish/sim3u1/subdir.mk
-include build/wirish/boards/si_arduino/subdir.mk
-include build/subdir.mk
-include build/libraries/Wire/subdir.mk
-include build/libmaple/subdir.mk
-include build/libmaple/usb/usb_lib/subdir.mk
-include build/libmaple/usb/sim3u1/subdir.mk
-include build/libmaple/sim3u1/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/thumb/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/fpu/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/armv7e-m/softfp/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/armv7e-m/fpu/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/armv7e-m/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/armv7-r/thumb/softfp/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/armv7-r/thumb/fpu/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/armv7-r/thumb/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/armv7-m/subdir.mk
-include arm/lib/gcc/arm-none-eabi/4.6.2/armv6-m/subdir.mk
-include arm/arm-none-eabi/lib/thumb/subdir.mk
-include arm/arm-none-eabi/lib/subdir.mk
-include arm/arm-none-eabi/lib/fpu/subdir.mk
-include arm/arm-none-eabi/lib/armv7e-m/softfp/subdir.mk
-include arm/arm-none-eabi/lib/armv7e-m/subdir.mk
-include arm/arm-none-eabi/lib/armv7e-m/fpu/subdir.mk
-include arm/arm-none-eabi/lib/armv7-r/thumb/softfp/subdir.mk
-include arm/arm-none-eabi/lib/armv7-r/thumb/subdir.mk
-include arm/arm-none-eabi/lib/armv7-r/thumb/fpu/subdir.mk
-include arm/arm-none-eabi/lib/armv7-m/subdir.mk
-include arm/arm-none-eabi/lib/armv6-m/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: libmaple-sim3

# Tool invocations
libmaple-sim3: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -mcpu=arm7tdmi -o"libmaple-sim3" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) libmaple-sim3
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
