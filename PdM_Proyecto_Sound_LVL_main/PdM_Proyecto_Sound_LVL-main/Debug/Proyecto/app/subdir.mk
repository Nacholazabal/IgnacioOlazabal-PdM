################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Proyecto/app/app.c \
../Proyecto/app/app_isr.c 

OBJS += \
./Proyecto/app/app.o \
./Proyecto/app/app_isr.o 

C_DEPS += \
./Proyecto/app/app.d \
./Proyecto/app/app_isr.d 


# Each subdirectory must supply rules for building sources it contributes
Proyecto/app/%.o Proyecto/app/%.su Proyecto/app/%.cyclo: ../Proyecto/app/%.c Proyecto/app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto" -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto/app" -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto/drivers" -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto/API/Inc" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto/drivers/button/Inc" -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto/drivers/uart/Inc" -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto/drivers/usb_cdc/Inc" -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto/drivers/rtc/Inc" -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto/drivers/eeprom/Inc" -I"C:/Users/nacho/PdM_Proyecto_Sound_LVL/Proyecto/drivers/bt/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Proyecto-2f-app

clean-Proyecto-2f-app:
	-$(RM) ./Proyecto/app/app.cyclo ./Proyecto/app/app.d ./Proyecto/app/app.o ./Proyecto/app/app.su ./Proyecto/app/app_isr.cyclo ./Proyecto/app/app_isr.d ./Proyecto/app/app_isr.o ./Proyecto/app/app_isr.su

.PHONY: clean-Proyecto-2f-app

