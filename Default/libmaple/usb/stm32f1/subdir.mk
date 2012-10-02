################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libmaple/usb/stm32f1/usb.c \
../libmaple/usb/stm32f1/usb_cdcacm.c \
../libmaple/usb/stm32f1/usb_reg_map.c 

OBJS += \
./libmaple/usb/stm32f1/usb.o \
./libmaple/usb/stm32f1/usb_cdcacm.o \
./libmaple/usb/stm32f1/usb_reg_map.o 

C_DEPS += \
./libmaple/usb/stm32f1/usb.d \
./libmaple/usb/stm32f1/usb_cdcacm.d \
./libmaple/usb/stm32f1/usb_reg_map.d 


# Each subdirectory must supply rules for building sources it contributes
libmaple/usb/stm32f1/%.o: ../libmaple/usb/stm32f1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


