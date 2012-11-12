################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libmaple/usb/sim3u1/usb.c \
../libmaple/usb/sim3u1/usb_cdcacm.c \
../libmaple/usb/sim3u1/usb_reg_map.c 

OBJS += \
./libmaple/usb/sim3u1/usb.o \
./libmaple/usb/sim3u1/usb_cdcacm.o \
./libmaple/usb/sim3u1/usb_reg_map.o 

C_DEPS += \
./libmaple/usb/sim3u1/usb.d \
./libmaple/usb/sim3u1/usb_cdcacm.d \
./libmaple/usb/sim3u1/usb_reg_map.d 


# Each subdirectory must supply rules for building sources it contributes
libmaple/usb/sim3u1/%.o: ../libmaple/usb/sim3u1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


