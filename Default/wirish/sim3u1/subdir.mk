################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../wirish/sim3u1/boards_setup.cpp \
../wirish/sim3u1/wirish_debug.cpp \
../wirish/sim3u1/wirish_digital.cpp 

C_SRCS += \
../wirish/sim3u1/util_hooks.c 

OBJS += \
./wirish/sim3u1/boards_setup.o \
./wirish/sim3u1/util_hooks.o \
./wirish/sim3u1/wirish_debug.o \
./wirish/sim3u1/wirish_digital.o 

C_DEPS += \
./wirish/sim3u1/util_hooks.d 

CPP_DEPS += \
./wirish/sim3u1/boards_setup.d \
./wirish/sim3u1/wirish_debug.d \
./wirish/sim3u1/wirish_digital.d 


# Each subdirectory must supply rules for building sources it contributes
wirish/sim3u1/%.o: ../wirish/sim3u1/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

wirish/sim3u1/%.o: ../wirish/sim3u1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


