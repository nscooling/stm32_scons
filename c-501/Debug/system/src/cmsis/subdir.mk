################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/cmsis/system_stm32f4xx.c \
../system/src/cmsis/vectors_stm32f4xx.c 

OBJS += \
./system/src/cmsis/system_stm32f4xx.o \
./system/src/cmsis/vectors_stm32f4xx.o 

C_DEPS += \
./system/src/cmsis/system_stm32f4xx.d \
./system/src/cmsis/vectors_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/cmsis/%.o: ../system/src/cmsis/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DOS_USE_SEMIHOSTING -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F407xx -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C/common/inc" -I"../Drivers" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/feabhos/C/FreeRTOS/inc" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/freertos_cortex_m4/FreeRTOS/Source/include" -I"/Users/PhilipK/Documents/workspace/c-501 Template/Middleware/freertos_cortex_m4/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


