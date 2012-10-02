################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libmaple/adc.c \
../libmaple/dac.c \
../libmaple/dma.c \
../libmaple/exti.c \
../libmaple/flash.c \
../libmaple/gpio.c \
../libmaple/i2c.c \
../libmaple/iwdg.c \
../libmaple/nvic.c \
../libmaple/pwr.c \
../libmaple/rcc.c \
../libmaple/spi.c \
../libmaple/systick.c \
../libmaple/timer.c \
../libmaple/usart.c \
../libmaple/usart_private.c \
../libmaple/util.c 

S_UPPER_SRCS += \
../libmaple/exc.S 

OBJS += \
./libmaple/adc.o \
./libmaple/dac.o \
./libmaple/dma.o \
./libmaple/exc.o \
./libmaple/exti.o \
./libmaple/flash.o \
./libmaple/gpio.o \
./libmaple/i2c.o \
./libmaple/iwdg.o \
./libmaple/nvic.o \
./libmaple/pwr.o \
./libmaple/rcc.o \
./libmaple/spi.o \
./libmaple/systick.o \
./libmaple/timer.o \
./libmaple/usart.o \
./libmaple/usart_private.o \
./libmaple/util.o 

C_DEPS += \
./libmaple/adc.d \
./libmaple/dac.d \
./libmaple/dma.d \
./libmaple/exti.d \
./libmaple/flash.d \
./libmaple/gpio.d \
./libmaple/i2c.d \
./libmaple/iwdg.d \
./libmaple/nvic.d \
./libmaple/pwr.d \
./libmaple/rcc.d \
./libmaple/spi.d \
./libmaple/systick.d \
./libmaple/timer.d \
./libmaple/usart.d \
./libmaple/usart_private.d \
./libmaple/util.d 


# Each subdirectory must supply rules for building sources it contributes
libmaple/%.o: ../libmaple/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libmaple/%.o: ../libmaple/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -g3 -mcpu=arm7tdmi -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


