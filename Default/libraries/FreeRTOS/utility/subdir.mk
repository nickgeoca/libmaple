################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/FreeRTOS/utility/croutine.c \
../libraries/FreeRTOS/utility/heap_2.c \
../libraries/FreeRTOS/utility/list.c \
../libraries/FreeRTOS/utility/port.c \
../libraries/FreeRTOS/utility/queue.c \
../libraries/FreeRTOS/utility/tasks.c \
../libraries/FreeRTOS/utility/timers.c 

OBJS += \
./libraries/FreeRTOS/utility/croutine.o \
./libraries/FreeRTOS/utility/heap_2.o \
./libraries/FreeRTOS/utility/list.o \
./libraries/FreeRTOS/utility/port.o \
./libraries/FreeRTOS/utility/queue.o \
./libraries/FreeRTOS/utility/tasks.o \
./libraries/FreeRTOS/utility/timers.o 

C_DEPS += \
./libraries/FreeRTOS/utility/croutine.d \
./libraries/FreeRTOS/utility/heap_2.d \
./libraries/FreeRTOS/utility/list.d \
./libraries/FreeRTOS/utility/port.d \
./libraries/FreeRTOS/utility/queue.d \
./libraries/FreeRTOS/utility/tasks.d \
./libraries/FreeRTOS/utility/timers.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/FreeRTOS/utility/%.o: ../libraries/FreeRTOS/utility/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


