################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/feabhos/C/POSIX/src/feabhOS_condition.c \
../Middleware/feabhos/C/POSIX/src/feabhOS_interrupts.c \
../Middleware/feabhos/C/POSIX/src/feabhOS_memory.c \
../Middleware/feabhos/C/POSIX/src/feabhOS_mutex.c \
../Middleware/feabhos/C/POSIX/src/feabhOS_queue.c \
../Middleware/feabhos/C/POSIX/src/feabhOS_scheduler.c \
../Middleware/feabhos/C/POSIX/src/feabhOS_semaphore.c \
../Middleware/feabhos/C/POSIX/src/feabhOS_signal.c \
../Middleware/feabhos/C/POSIX/src/feabhOS_task.c 

OBJS += \
./Middleware/feabhos/C/POSIX/src/feabhOS_condition.o \
./Middleware/feabhos/C/POSIX/src/feabhOS_interrupts.o \
./Middleware/feabhos/C/POSIX/src/feabhOS_memory.o \
./Middleware/feabhos/C/POSIX/src/feabhOS_mutex.o \
./Middleware/feabhos/C/POSIX/src/feabhOS_queue.o \
./Middleware/feabhos/C/POSIX/src/feabhOS_scheduler.o \
./Middleware/feabhos/C/POSIX/src/feabhOS_semaphore.o \
./Middleware/feabhos/C/POSIX/src/feabhOS_signal.o \
./Middleware/feabhos/C/POSIX/src/feabhOS_task.o 

C_DEPS += \
./Middleware/feabhos/C/POSIX/src/feabhOS_condition.d \
./Middleware/feabhos/C/POSIX/src/feabhOS_interrupts.d \
./Middleware/feabhos/C/POSIX/src/feabhOS_memory.d \
./Middleware/feabhos/C/POSIX/src/feabhOS_mutex.d \
./Middleware/feabhos/C/POSIX/src/feabhOS_queue.d \
./Middleware/feabhos/C/POSIX/src/feabhOS_scheduler.d \
./Middleware/feabhos/C/POSIX/src/feabhOS_semaphore.d \
./Middleware/feabhos/C/POSIX/src/feabhOS_signal.d \
./Middleware/feabhos/C/POSIX/src/feabhOS_task.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/feabhos/C/POSIX/src/%.o: ../Middleware/feabhos/C/POSIX/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F407xx -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"/home/glennan/workspace/cpp-501_QEMU/Middleware/feabhos/C/common/inc" -I"/home/glennan/workspace/cpp-501_QEMU/Middleware/feabhos/C/FreeRTOS/inc" -I"/home/glennan/workspace/cpp-501_QEMU/Middleware/freertos_cortex_m4/FreeRTOS/Source/include" -I"/home/glennan/workspace/cpp-501_QEMU/Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


