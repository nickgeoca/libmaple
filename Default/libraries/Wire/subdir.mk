################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libraries/Wire/HardWire.cpp \
../libraries/Wire/Wire.cpp \
../libraries/Wire/WireBase.cpp 

OBJS += \
./libraries/Wire/HardWire.o \
./libraries/Wire/Wire.o \
./libraries/Wire/WireBase.o 

CPP_DEPS += \
./libraries/Wire/HardWire.d \
./libraries/Wire/Wire.d \
./libraries/Wire/WireBase.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Wire/%.o: ../libraries/Wire/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


