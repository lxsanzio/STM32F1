################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Internet/FTPClient/ftpc.c 

OBJS += \
./ioLibrary_Driver/Internet/FTPClient/ftpc.o 

C_DEPS += \
./ioLibrary_Driver/Internet/FTPClient/ftpc.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Internet/FTPClient/ftpc.o: ../ioLibrary_Driver/Internet/FTPClient/ftpc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I"/home/t440/Documentos/Git/STM32_eth_client_v1/ioLibrary_Driver/Ethernet/W5500" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"/home/t440/Documentos/Git/STM32_eth_client_v1/ioLibrary_Driver/Ethernet" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ioLibrary_Driver/Internet/FTPClient/ftpc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

