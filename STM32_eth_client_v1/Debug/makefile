################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include ioLibrary_Driver/Internet/httpServer/subdir.mk
-include ioLibrary_Driver/Internet/TFTP/subdir.mk
-include ioLibrary_Driver/Internet/SNTP/subdir.mk
-include ioLibrary_Driver/Internet/SNMP/subdir.mk
-include ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/subdir.mk
-include ioLibrary_Driver/Internet/MQTT/subdir.mk
-include ioLibrary_Driver/Internet/FTPServer/subdir.mk
-include ioLibrary_Driver/Internet/FTPClient/subdir.mk
-include ioLibrary_Driver/Internet/DNS/subdir.mk
-include ioLibrary_Driver/Internet/DHCP/subdir.mk
-include ioLibrary_Driver/Ethernet/W5500/subdir.mk
-include ioLibrary_Driver/Ethernet/W5300/subdir.mk
-include ioLibrary_Driver/Ethernet/W5200/subdir.mk
-include ioLibrary_Driver/Ethernet/W5100S/subdir.mk
-include ioLibrary_Driver/Ethernet/W5100/subdir.mk
-include ioLibrary_Driver/Ethernet/subdir.mk
-include ioLibrary_Driver/Application/multicast/subdir.mk
-include ioLibrary_Driver/Application/loopback/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32_eth_client_v1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32_eth_client_v1.list \

OBJCOPY_BIN += \
STM32_eth_client_v1.bin \


# All Target
all: STM32_eth_client_v1.elf secondary-outputs

# Tool invocations
STM32_eth_client_v1.elf: $(OBJS) $(USER_OBJS) /home/t440/Documentos/Git/STM32_eth_client_v1/STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "STM32_eth_client_v1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"/home/t440/Documentos/Git/STM32_eth_client_v1/STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32_eth_client_v1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32_eth_client_v1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32_eth_client_v1.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32_eth_client_v1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32_eth_client_v1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
