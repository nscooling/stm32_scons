################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/freertos_cortex_m4/FreeRTOS/Source/croutine.c \
../Middleware/freertos_cortex_m4/FreeRTOS/Source/event_groups.c \
../Middleware/freertos_cortex_m4/FreeRTOS/Source/list.c \
../Middleware/freertos_cortex_m4/FreeRTOS/Source/queue.c \
../Middleware/freertos_cortex_m4/FreeRTOS/Source/tasks.c \
../Middleware/freertos_cortex_m4/FreeRTOS/Source/timers.c 

OBJS += \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/croutine.o \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/event_groups.o \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/list.o \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/queue.o \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/tasks.o \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/timers.o 

C_DEPS += \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/croutine.d \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/event_groups.d \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/list.d \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/queue.d \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/tasks.d \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/freertos_cortex_m4/FreeRTOS/Source/%.o: ../Middleware/freertos_cortex_m4/FreeRTOS/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DOS_USE_SEMIHOSTING -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F407xx -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C/common/inc" -I"../Drivers" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C/FreeRTOS/inc" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/freertos_cortex_m4/FreeRTOS/Source/include" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


