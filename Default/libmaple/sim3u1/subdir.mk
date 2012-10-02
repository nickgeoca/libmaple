################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libmaple/sim3u1/adc.c \
../libmaple/sim3u1/dma.c \
../libmaple/sim3u1/exti.c \
../libmaple/sim3u1/fsmc.c \
../libmaple/sim3u1/gpio.c \
../libmaple/sim3u1/rcc.c \
../libmaple/sim3u1/spi.c \
../libmaple/sim3u1/syscfg.c \
../libmaple/sim3u1/timer.c \
../libmaple/sim3u1/usart.c 

S_UPPER_SRCS += \
../libmaple/sim3u1/isrs.S \
../libmaple/sim3u1/vector_table.S 

OBJS += \
./libmaple/sim3u1/adc.o \
./libmaple/sim3u1/dma.o \
./libmaple/sim3u1/exti.o \
./libmaple/sim3u1/fsmc.o \
./libmaple/sim3u1/gpio.o \
./libmaple/sim3u1/isrs.o \
./libmaple/sim3u1/rcc.o \
./libmaple/sim3u1/spi.o \
./libmaple/sim3u1/syscfg.o \
./libmaple/sim3u1/timer.o \
./libmaple/sim3u1/usart.o \
./libmaple/sim3u1/vector_table.o 

C_DEPS += \
./libmaple/sim3u1/adc.d \
./libmaple/sim3u1/dma.d \
./libmaple/sim3u1/exti.d \
./libmaple/sim3u1/fsmc.d \
./libmaple/sim3u1/gpio.d \
./libmaple/sim3u1/rcc.d \
./libmaple/sim3u1/spi.d \
./libmaple/sim3u1/syscfg.d \
./libmaple/sim3u1/timer.d \
./libmaple/sim3u1/usart.d 


# Each subdirectory must supply rules for building sources it contributes
libmaple/sim3u1/%.o: ../libmaple/sim3u1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libmaple/sim3u1/%.o: ../libmaple/sim3u1/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -g3 -mcpu=arm7tdmi -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


