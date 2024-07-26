################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/src/app.c \
../App/src/i2c_master.c \
../App/src/i2c_slave.c \
../App/src/sensor.c \
../App/src/serialization.c \
../App/src/slip_packet.c 

OBJS += \
./App/src/app.o \
./App/src/i2c_master.o \
./App/src/i2c_slave.o \
./App/src/sensor.o \
./App/src/serialization.o \
./App/src/slip_packet.o 

C_DEPS += \
./App/src/app.d \
./App/src/i2c_master.d \
./App/src/i2c_slave.d \
./App/src/sensor.d \
./App/src/serialization.d \
./App/src/slip_packet.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/%.o App/src/%.su App/src/%.cyclo: ../App/src/%.c App/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../STM32_WPAN/App -I../USB_Device/App -I../USB_Device/Target -I../Utilities/lpm/tiny_lpm -I../Middlewares/ST/STM32_WPAN -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../Middlewares/ST/STM32_WPAN/utilities -I../Middlewares/ST/STM32_WPAN/ble/core -I../Middlewares/ST/STM32_WPAN/ble/core/auto -I../Middlewares/ST/STM32_WPAN/ble/core/template -I../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/STM32_WPAN/ble -I../Utilities/sequencer -I"/home/mlundh/BLEtarget/fw/BleTarget/App" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-src

clean-App-2f-src:
	-$(RM) ./App/src/app.cyclo ./App/src/app.d ./App/src/app.o ./App/src/app.su ./App/src/i2c_master.cyclo ./App/src/i2c_master.d ./App/src/i2c_master.o ./App/src/i2c_master.su ./App/src/i2c_slave.cyclo ./App/src/i2c_slave.d ./App/src/i2c_slave.o ./App/src/i2c_slave.su ./App/src/sensor.cyclo ./App/src/sensor.d ./App/src/sensor.o ./App/src/sensor.su ./App/src/serialization.cyclo ./App/src/serialization.d ./App/src/serialization.o ./App/src/serialization.su ./App/src/slip_packet.cyclo ./App/src/slip_packet.d ./App/src/slip_packet.o ./App/src/slip_packet.su

.PHONY: clean-App-2f-src

