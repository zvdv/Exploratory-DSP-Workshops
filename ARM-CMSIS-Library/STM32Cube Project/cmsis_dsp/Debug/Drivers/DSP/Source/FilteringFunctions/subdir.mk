################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Source/FilteringFunctions/arm_fir_f32.c \
../Drivers/DSP/Source/FilteringFunctions/arm_fir_init_f32.c 

OBJS += \
./Drivers/DSP/Source/FilteringFunctions/arm_fir_f32.o \
./Drivers/DSP/Source/FilteringFunctions/arm_fir_init_f32.o 

C_DEPS += \
./Drivers/DSP/Source/FilteringFunctions/arm_fir_f32.d \
./Drivers/DSP/Source/FilteringFunctions/arm_fir_init_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Source/FilteringFunctions/%.o Drivers/DSP/Source/FilteringFunctions/%.su Drivers/DSP/Source/FilteringFunctions/%.cyclo: ../Drivers/DSP/Source/FilteringFunctions/%.c Drivers/DSP/Source/FilteringFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP/Include -I../Drivers/DSP/PrivateInclude -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Source-2f-FilteringFunctions

clean-Drivers-2f-DSP-2f-Source-2f-FilteringFunctions:
	-$(RM) ./Drivers/DSP/Source/FilteringFunctions/arm_fir_f32.cyclo ./Drivers/DSP/Source/FilteringFunctions/arm_fir_f32.d ./Drivers/DSP/Source/FilteringFunctions/arm_fir_f32.o ./Drivers/DSP/Source/FilteringFunctions/arm_fir_f32.su ./Drivers/DSP/Source/FilteringFunctions/arm_fir_init_f32.cyclo ./Drivers/DSP/Source/FilteringFunctions/arm_fir_init_f32.d ./Drivers/DSP/Source/FilteringFunctions/arm_fir_init_f32.o ./Drivers/DSP/Source/FilteringFunctions/arm_fir_init_f32.su

.PHONY: clean-Drivers-2f-DSP-2f-Source-2f-FilteringFunctions

