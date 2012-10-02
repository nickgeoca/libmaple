################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libmaple/stm32f1/adc.c \
../libmaple/stm32f1/bkp.c \
../libmaple/stm32f1/dma.c \
../libmaple/stm32f1/exti.c \
../libmaple/stm32f1/fsmc.c \
../libmaple/stm32f1/gpio.c \
../libmaple/stm32f1/i2c.c \
../libmaple/stm32f1/rcc.c \
../libmaple/stm32f1/spi.c \
../libmaple/stm32f1/timer.c \
../libmaple/stm32f1/usart.c 

OBJS += \
./libmaple/stm32f1/adc.o \
./libmaple/stm32f1/bkp.o \
./libmaple/stm32f1/dma.o \
./libmaple/stm32f1/exti.o \
./libmaple/stm32f1/fsmc.o \
./libmaple/stm32f1/gpio.o \
./libmaple/stm32f1/i2c.o \
./libmaple/stm32f1/rcc.o \
./libmaple/stm32f1/spi.o \
./libmaple/stm32f1/timer.o \
./libmaple/stm32f1/usart.o 

C_DEPS += \
./libmaple/stm32f1/adc.d \
./libmaple/stm32f1/bkp.d \
./libmaple/stm32f1/dma.d \
./libmaple/stm32f1/exti.d \
./libmaple/stm32f1/fsmc.d \
./libmaple/stm32f1/gpio.d \
./libmaple/stm32f1/i2c.d \
./libmaple/stm32f1/rcc.d \
./libmaple/stm32f1/spi.d \
./libmaple/stm32f1/timer.d \
./libmaple/stm32f1/usart.d 


# Each subdirectory must supply rules for building sources it contributes
libmaple/stm32f1/%.o: ../libmaple/stm32f1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


