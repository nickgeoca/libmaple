################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libmaple/usb/usb_lib/usb_core.c \
../libmaple/usb/usb_lib/usb_init.c \
../libmaple/usb/usb_lib/usb_mem.c \
../libmaple/usb/usb_lib/usb_regs.c 

OBJS += \
./libmaple/usb/usb_lib/usb_core.o \
./libmaple/usb/usb_lib/usb_init.o \
./libmaple/usb/usb_lib/usb_mem.o \
./libmaple/usb/usb_lib/usb_regs.o 

C_DEPS += \
./libmaple/usb/usb_lib/usb_core.d \
./libmaple/usb/usb_lib/usb_init.d \
./libmaple/usb/usb_lib/usb_mem.d \
./libmaple/usb/usb_lib/usb_regs.d 


# Each subdirectory must supply rules for building sources it contributes
libmaple/usb/usb_lib/%.o: ../libmaple/usb/usb_lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


