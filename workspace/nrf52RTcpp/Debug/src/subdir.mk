################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp 

OBJS += \
./src/main.o 

CPP_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs -O0 -ffunction-sections -fdata-sections -fno-builtin -fno-strict-aliasing -Wall -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable  -g3 -DBOARD_PCA10040 -DNRF52 -DNRF52832 -I"C:/Users/user/Documents/Software_Devel/nrf_dev/workspace/nrf52RTcpp\inc" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\toolchain\cmsis\include" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\device" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\toolchain" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\drivers_nrf\delay" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\boards" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\drivers_nrf\hal" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\util" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\drivers_nrf\nrf_soc_nosd" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\bsp" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\timer" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\button" -std=gnu++11 -fabi-version=0 --short-enums -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


