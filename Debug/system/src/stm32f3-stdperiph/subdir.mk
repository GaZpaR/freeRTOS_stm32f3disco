################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/stm32f3-stdperiph/stm32f30x_exti.c \
../system/src/stm32f3-stdperiph/stm32f30x_gpio.c \
../system/src/stm32f3-stdperiph/stm32f30x_misc.c \
../system/src/stm32f3-stdperiph/stm32f30x_rcc.c \
../system/src/stm32f3-stdperiph/stm32f30x_syscfg.c \
../system/src/stm32f3-stdperiph/stm32f30x_usart.c 

OBJS += \
./system/src/stm32f3-stdperiph/stm32f30x_exti.o \
./system/src/stm32f3-stdperiph/stm32f30x_gpio.o \
./system/src/stm32f3-stdperiph/stm32f30x_misc.o \
./system/src/stm32f3-stdperiph/stm32f30x_rcc.o \
./system/src/stm32f3-stdperiph/stm32f30x_syscfg.o \
./system/src/stm32f3-stdperiph/stm32f30x_usart.o 

C_DEPS += \
./system/src/stm32f3-stdperiph/stm32f30x_exti.d \
./system/src/stm32f3-stdperiph/stm32f30x_gpio.d \
./system/src/stm32f3-stdperiph/stm32f30x_misc.d \
./system/src/stm32f3-stdperiph/stm32f30x_rcc.d \
./system/src/stm32f3-stdperiph/stm32f30x_syscfg.d \
./system/src/stm32f3-stdperiph/stm32f30x_usart.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/stm32f3-stdperiph/%.o: ../system/src/stm32f3-stdperiph/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_STM32303C_EVAL -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F30X -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I../system/include/cmsis -I../include -I../system/include -I../system/include/stm32f3-stdperiph -I../FreeRTOS/include -I../FreeRTOS -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


