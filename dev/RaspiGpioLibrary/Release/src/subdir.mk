################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CGpio.cpp \
../src/CPart.cpp \
../src/CSpi.cpp 

OBJS += \
./src/CGpio.o \
./src/CPart.o \
./src/CSpi.o 

CPP_DEPS += \
./src/CGpio.d \
./src/CPart.d \
./src/CSpi.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"E:\development\CGPIO\dev\RaspiGpioLibrary\include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


