################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o: ../Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DRTOS -DOS_USE_SEMIHOSTING -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F407xx -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"/home/ubuntu/workspace/c-501/Middleware/feabhos/C/common/inc" -I"../Drivers" -I"/home/ubuntu/workspace/c-501/Middleware/feabhos/C/FreeRTOS/inc" -I"/home/ubuntu/workspace/c-501/Middleware/freertos_cortex_m4/FreeRTOS/Source/include" -I"/home/ubuntu/workspace/c-501/Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


