################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libmaple/stm32f2/adc.c \
../libmaple/stm32f2/dma.c \
../libmaple/stm32f2/exti.c \
../libmaple/stm32f2/fsmc.c \
../libmaple/stm32f2/gpio.c \
../libmaple/stm32f2/rcc.c \
../libmaple/stm32f2/spi.c \
../libmaple/stm32f2/syscfg.c \
../libmaple/stm32f2/timer.c \
../libmaple/stm32f2/usart.c 

S_UPPER_SRCS += \
../libmaple/stm32f2/isrs.S \
../libmaple/stm32f2/vector_table.S 

OBJS += \
./libmaple/stm32f2/adc.o \
./libmaple/stm32f2/dma.o \
./libmaple/stm32f2/exti.o \
./libmaple/stm32f2/fsmc.o \
./libmaple/stm32f2/gpio.o \
./libmaple/stm32f2/isrs.o \
./libmaple/stm32f2/rcc.o \
./libmaple/stm32f2/spi.o \
./libmaple/stm32f2/syscfg.o \
./libmaple/stm32f2/timer.o \
./libmaple/stm32f2/usart.o \
./libmaple/stm32f2/vector_table.o 

C_DEPS += \
./libmaple/stm32f2/adc.d \
./libmaple/stm32f2/dma.d \
./libmaple/stm32f2/exti.d \
./libmaple/stm32f2/fsmc.d \
./libmaple/stm32f2/gpio.d \
./libmaple/stm32f2/rcc.d \
./libmaple/stm32f2/spi.d \
./libmaple/stm32f2/syscfg.d \
./libmaple/stm32f2/timer.d \
./libmaple/stm32f2/usart.d 


# Each subdirectory must supply rules for building sources it contributes
libmaple/stm32f2/%.o: ../libmaple/stm32f2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libmaple/stm32f2/%.o: ../libmaple/stm32f2/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -g3 -mcpu=arm7tdmi -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


