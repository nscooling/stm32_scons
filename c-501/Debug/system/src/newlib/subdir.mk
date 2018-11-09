################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/newlib/__dso_handle.c \
../system/src/newlib/_exit.c \
../system/src/newlib/_sbrk.c \
../system/src/newlib/_startup.c \
../system/src/newlib/_syscalls.c \
../system/src/newlib/assert.c 

CPP_SRCS += \
../system/src/newlib/_cxx.cpp 

OBJS += \
./system/src/newlib/__dso_handle.o \
./system/src/newlib/_cxx.o \
./system/src/newlib/_exit.o \
./system/src/newlib/_sbrk.o \
./system/src/newlib/_startup.o \
./system/src/newlib/_syscalls.o \
./system/src/newlib/assert.o 

C_DEPS += \
./system/src/newlib/__dso_handle.d \
./system/src/newlib/_exit.d \
./system/src/newlib/_sbrk.d \
./system/src/newlib/_startup.d \
./system/src/newlib/_syscalls.d \
./system/src/newlib/assert.d 

CPP_DEPS += \
./system/src/newlib/_cxx.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/newlib/%.o: ../system/src/newlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DOS_USE_SEMIHOSTING -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F407xx -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C/common/inc" -I"../Drivers" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C/FreeRTOS/inc" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/freertos_cortex_m4/FreeRTOS/Source/include" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/src/newlib/%.o: ../system/src/newlib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DSTM32F407xx -DUSE_FULL_ASSERT -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DOS_USE_SEMIHOSTING -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../Drivers" -I../src -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/freertos_cortex_m4/FreeRTOS/Source/include" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C/common/inc" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C/FreeRTOS/inc" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C/FreeRTOS/inc" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C++/inc" -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -fabi-version=0 -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


