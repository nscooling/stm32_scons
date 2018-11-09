################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middleware/feabhos/C++/src/Condition.cpp \
../Middleware/feabhos/C++/src/Mutex.cpp \
../Middleware/feabhos/C++/src/Scheduler.cpp \
../Middleware/feabhos/C++/src/Signal.cpp \
../Middleware/feabhos/C++/src/Thread.cpp 

OBJS += \
./Middleware/feabhos/C++/src/Condition.o \
./Middleware/feabhos/C++/src/Mutex.o \
./Middleware/feabhos/C++/src/Scheduler.o \
./Middleware/feabhos/C++/src/Signal.o \
./Middleware/feabhos/C++/src/Thread.o 

CPP_DEPS += \
./Middleware/feabhos/C++/src/Condition.d \
./Middleware/feabhos/C++/src/Mutex.d \
./Middleware/feabhos/C++/src/Scheduler.d \
./Middleware/feabhos/C++/src/Signal.d \
./Middleware/feabhos/C++/src/Thread.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/feabhos/C++/src/%.o: ../Middleware/feabhos/C++/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DSTM32F407xx -DUSE_FULL_ASSERT -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DOS_USE_SEMIHOSTING -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../Drivers" -I../src -I"/home/ubuntu/workspace/c-501/Middleware/freertos_cortex_m4/FreeRTOS/Source/include" -I"/home/ubuntu/workspace/c-501/Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/ubuntu/workspace/c-501/Middleware/feabhos/C/common/inc" -I"/home/ubuntu/workspace/c-501/Middleware/feabhos/C/FreeRTOS/inc" -I"/home/ubuntu/workspace/c-501/Middleware/feabhos/C/FreeRTOS/inc" -I"/home/ubuntu/workspace/c-501/Middleware/feabhos/C++/inc" -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -fabi-version=0 -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


