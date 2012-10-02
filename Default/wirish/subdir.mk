################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../wirish/HardwareSPI.cpp \
../wirish/HardwareSerial.cpp \
../wirish/HardwareTimer.cpp \
../wirish/Print.cpp \
../wirish/boards.cpp \
../wirish/cxxabi-compat.cpp \
../wirish/ext_interrupts.cpp \
../wirish/pwm.cpp \
../wirish/usb_serial.cpp \
../wirish/wirish_analog.cpp \
../wirish/wirish_digital.cpp \
../wirish/wirish_math.cpp \
../wirish/wirish_shift.cpp \
../wirish/wirish_time.cpp 

C_SRCS += \
../wirish/start_c.c \
../wirish/syscalls.c 

S_UPPER_SRCS += \
../wirish/start.S 

CXX_SRCS += \
../wirish/main.cxx 

OBJS += \
./wirish/HardwareSPI.o \
./wirish/HardwareSerial.o \
./wirish/HardwareTimer.o \
./wirish/Print.o \
./wirish/boards.o \
./wirish/cxxabi-compat.o \
./wirish/ext_interrupts.o \
./wirish/main.o \
./wirish/pwm.o \
./wirish/start.o \
./wirish/start_c.o \
./wirish/syscalls.o \
./wirish/usb_serial.o \
./wirish/wirish_analog.o \
./wirish/wirish_digital.o \
./wirish/wirish_math.o \
./wirish/wirish_shift.o \
./wirish/wirish_time.o 

C_DEPS += \
./wirish/start_c.d \
./wirish/syscalls.d 

CPP_DEPS += \
./wirish/HardwareSPI.d \
./wirish/HardwareSerial.d \
./wirish/HardwareTimer.d \
./wirish/Print.d \
./wirish/boards.d \
./wirish/cxxabi-compat.d \
./wirish/ext_interrupts.d \
./wirish/pwm.d \
./wirish/usb_serial.d \
./wirish/wirish_analog.d \
./wirish/wirish_digital.d \
./wirish/wirish_math.d \
./wirish/wirish_shift.d \
./wirish/wirish_time.d 

CXX_DEPS += \
./wirish/main.d 


# Each subdirectory must supply rules for building sources it contributes
wirish/%.o: ../wirish/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

wirish/%.o: ../wirish/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

wirish/%.o: ../wirish/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -g3 -mcpu=arm7tdmi -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

wirish/%.o: ../wirish/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=arm7tdmi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


