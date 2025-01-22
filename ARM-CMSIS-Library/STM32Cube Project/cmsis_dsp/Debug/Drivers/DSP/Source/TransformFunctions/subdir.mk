################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Source/TransformFunctions/arm_bitreversal.c \
../Drivers/DSP/Source/TransformFunctions/arm_bitreversal2.c \
../Drivers/DSP/Source/TransformFunctions/arm_cfft_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_cfft_init_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_rfft_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.c \
../Drivers/DSP/Source/TransformFunctions/arm_rfft_init_f32.c 

OBJS += \
./Drivers/DSP/Source/TransformFunctions/arm_bitreversal.o \
./Drivers/DSP/Source/TransformFunctions/arm_bitreversal2.o \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_init_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_rfft_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.o \
./Drivers/DSP/Source/TransformFunctions/arm_rfft_init_f32.o 

C_DEPS += \
./Drivers/DSP/Source/TransformFunctions/arm_bitreversal.d \
./Drivers/DSP/Source/TransformFunctions/arm_bitreversal2.d \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_init_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_rfft_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.d \
./Drivers/DSP/Source/TransformFunctions/arm_rfft_init_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Source/TransformFunctions/%.o Drivers/DSP/Source/TransformFunctions/%.su Drivers/DSP/Source/TransformFunctions/%.cyclo: ../Drivers/DSP/Source/TransformFunctions/%.c Drivers/DSP/Source/TransformFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP/Include -I../Drivers/DSP/PrivateInclude -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Source-2f-TransformFunctions

clean-Drivers-2f-DSP-2f-Source-2f-TransformFunctions:
	-$(RM) ./Drivers/DSP/Source/TransformFunctions/arm_bitreversal.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_bitreversal.d ./Drivers/DSP/Source/TransformFunctions/arm_bitreversal.o ./Drivers/DSP/Source/TransformFunctions/arm_bitreversal.su ./Drivers/DSP/Source/TransformFunctions/arm_bitreversal2.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_bitreversal2.d ./Drivers/DSP/Source/TransformFunctions/arm_bitreversal2.o ./Drivers/DSP/Source/TransformFunctions/arm_bitreversal2.su ./Drivers/DSP/Source/TransformFunctions/arm_cfft_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_cfft_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_cfft_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_cfft_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_cfft_init_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_cfft_init_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_cfft_init_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_cfft_init_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_rfft_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_rfft_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_rfft_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_rfft_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.su ./Drivers/DSP/Source/TransformFunctions/arm_rfft_init_f32.cyclo ./Drivers/DSP/Source/TransformFunctions/arm_rfft_init_f32.d ./Drivers/DSP/Source/TransformFunctions/arm_rfft_init_f32.o ./Drivers/DSP/Source/TransformFunctions/arm_rfft_init_f32.su

.PHONY: clean-Drivers-2f-DSP-2f-Source-2f-TransformFunctions

