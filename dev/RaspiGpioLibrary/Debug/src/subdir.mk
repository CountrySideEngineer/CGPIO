################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CGpio.cpp \
../src/CGpioTimer.cpp \
../src/CPart.cpp \
../src/CSpi.cpp 

OBJS += \
./src/CGpio.o \
./src/CGpioTimer.o \
./src/CPart.o \
./src/CSpi.o 

CPP_DEPS += \
./src/CGpio.d \
./src/CGpioTimer.d \
./src/CPart.d \
./src/CSpi.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"E:\development\CGPIO\dev\RaspiGpioLibrary\include" -I"E:\development\CGPIO\dev\RaspiGpioLibrary\src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


