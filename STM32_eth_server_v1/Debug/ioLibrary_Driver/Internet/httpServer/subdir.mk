################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Internet/httpServer/httpParser.c \
../ioLibrary_Driver/Internet/httpServer/httpServer.c \
../ioLibrary_Driver/Internet/httpServer/httpUtil.c 

OBJS += \
./ioLibrary_Driver/Internet/httpServer/httpParser.o \
./ioLibrary_Driver/Internet/httpServer/httpServer.o \
./ioLibrary_Driver/Internet/httpServer/httpUtil.o 

C_DEPS += \
./ioLibrary_Driver/Internet/httpServer/httpParser.d \
./ioLibrary_Driver/Internet/httpServer/httpServer.d \
./ioLibrary_Driver/Internet/httpServer/httpUtil.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Internet/httpServer/httpParser.o: ../ioLibrary_Driver/Internet/httpServer/httpParser.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet/W5500" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Application/loopback" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ioLibrary_Driver/Internet/httpServer/httpParser.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ioLibrary_Driver/Internet/httpServer/httpServer.o: ../ioLibrary_Driver/Internet/httpServer/httpServer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet/W5500" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Application/loopback" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ioLibrary_Driver/Internet/httpServer/httpServer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ioLibrary_Driver/Internet/httpServer/httpUtil.o: ../ioLibrary_Driver/Internet/httpServer/httpUtil.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Ethernet/W5500" -I"/home/t440/Documentos/Git/STM32_eth_server_v1/ioLibrary_Driver/Application/loopback" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ioLibrary_Driver/Internet/httpServer/httpUtil.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

