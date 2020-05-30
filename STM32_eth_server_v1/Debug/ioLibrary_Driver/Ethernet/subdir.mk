################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Ethernet/socket.c \
../ioLibrary_Driver/Ethernet/wizchip_conf.c 

OBJS += \
./ioLibrary_Driver/Ethernet/socket.o \
./ioLibrary_Driver/Ethernet/wizchip_conf.o 

C_DEPS += \
./ioLibrary_Driver/Ethernet/socket.d \
./ioLibrary_Driver/Ethernet/wizchip_conf.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Ethernet/socket.o: ../ioLibrary_Driver/Ethernet/socket.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet/W5500" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Application/loopback" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ioLibrary_Driver/Ethernet/socket.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ioLibrary_Driver/Ethernet/wizchip_conf.o: ../ioLibrary_Driver/Ethernet/wizchip_conf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet/W5500" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Application/loopback" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ioLibrary_Driver/Ethernet/wizchip_conf.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

