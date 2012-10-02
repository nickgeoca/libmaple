################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../wirish/boards/st_stm3220g_eval/board.cpp 

OBJS += \
./wirish/boards/st_stm3220g_eval/board.o 

CPP_DEPS += \
./wirish/boards/st_stm3220g_eval/board.d 


# Each subdirectory must supply rules for building sources it contributes
wirish/boards/st_stm3220g_eval/%.o: ../wirish/boards/st_stm3220g_eval/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


