################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../examples/blinky.cpp \
../examples/debug-dtrrts.cpp \
../examples/exti-interrupt-callback.cpp \
../examples/exti-interrupt.cpp \
../examples/freertos-blinky.cpp \
../examples/fsmc-stress-test.cpp \
../examples/i2c-mcp4725-dac.cpp \
../examples/mini-exti-test.cpp \
../examples/qa-slave-shield.cpp \
../examples/serial-echo.cpp \
../examples/spi_master.cpp \
../examples/test-bkp.cpp \
../examples/test-dac.cpp \
../examples/test-fsmc.cpp \
../examples/test-print.cpp \
../examples/test-ring-buffer-insertion.cpp \
../examples/test-serial-flush.cpp \
../examples/test-serialusb.cpp \
../examples/test-servo.cpp \
../examples/test-session.cpp \
../examples/test-spi-roundtrip.cpp \
../examples/test-systick.cpp \
../examples/test-timers.cpp \
../examples/test-usart-dma.cpp \
../examples/vga-leaf.cpp \
../examples/vga-scope.cpp 

OBJS += \
./examples/blinky.o \
./examples/debug-dtrrts.o \
./examples/exti-interrupt-callback.o \
./examples/exti-interrupt.o \
./examples/freertos-blinky.o \
./examples/fsmc-stress-test.o \
./examples/i2c-mcp4725-dac.o \
./examples/mini-exti-test.o \
./examples/qa-slave-shield.o \
./examples/serial-echo.o \
./examples/spi_master.o \
./examples/test-bkp.o \
./examples/test-dac.o \
./examples/test-fsmc.o \
./examples/test-print.o \
./examples/test-ring-buffer-insertion.o \
./examples/test-serial-flush.o \
./examples/test-serialusb.o \
./examples/test-servo.o \
./examples/test-session.o \
./examples/test-spi-roundtrip.o \
./examples/test-systick.o \
./examples/test-timers.o \
./examples/test-usart-dma.o \
./examples/vga-leaf.o \
./examples/vga-scope.o 

CPP_DEPS += \
./examples/blinky.d \
./examples/debug-dtrrts.d \
./examples/exti-interrupt-callback.d \
./examples/exti-interrupt.d \
./examples/freertos-blinky.d \
./examples/fsmc-stress-test.d \
./examples/i2c-mcp4725-dac.d \
./examples/mini-exti-test.d \
./examples/qa-slave-shield.d \
./examples/serial-echo.d \
./examples/spi_master.d \
./examples/test-bkp.d \
./examples/test-dac.d \
./examples/test-fsmc.d \
./examples/test-print.d \
./examples/test-ring-buffer-insertion.d \
./examples/test-serial-flush.d \
./examples/test-serialusb.d \
./examples/test-servo.d \
./examples/test-session.d \
./examples/test-spi-roundtrip.d \
./examples/test-systick.d \
./examples/test-timers.d \
./examples/test-usart-dma.d \
./examples/vga-leaf.d \
./examples/vga-scope.d 


# Each subdirectory must supply rules for building sources it contributes
examples/%.o: ../examples/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


