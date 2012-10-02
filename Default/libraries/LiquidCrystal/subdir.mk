################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libraries/LiquidCrystal/LiquidCrystal.cpp 

OBJS += \
./libraries/LiquidCrystal/LiquidCrystal.o 

CPP_DEPS += \
./libraries/LiquidCrystal/LiquidCrystal.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/LiquidCrystal/%.o: ../libraries/LiquidCrystal/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


