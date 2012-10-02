################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../libmaple/stm32f1/performance/isrs.S \
../libmaple/stm32f1/performance/vector_table.S 

OBJS += \
./libmaple/stm32f1/performance/isrs.o \
./libmaple/stm32f1/performance/vector_table.o 


# Each subdirectory must supply rules for building sources it contributes
libmaple/stm32f1/performance/%.o: ../libmaple/stm32f1/performance/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -g3 -mcpu=arm7tdmi -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


