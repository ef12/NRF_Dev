################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/user/Documents/Software_Devel/nrf_dev/nrfSDK_V13_2_0/components/boards/boards.c \
C:/Users/user/Documents/Software_Devel/nrf_dev/nrfSDK_V13_2_0/components/toolchain/system_nrf52.c 

S_UPPER_SRCS += \
C:/Users/user/Documents/Software_Devel/nrf_dev/nrfSDK_V13_2_0/components/toolchain/gcc/gcc_startup_nrf52.S 

OBJS += \
./sdk/boards.o \
./sdk/gcc_startup_nrf52.o \
./sdk/system_nrf52.o 

S_UPPER_DEPS += \
./sdk/gcc_startup_nrf52.d 

C_DEPS += \
./sdk/boards.d \
./sdk/system_nrf52.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/boards.o: C:/Users/user/Documents/Software_Devel/nrf_dev/nrfSDK_V13_2_0/components/boards/boards.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs -O0 -ffunction-sections -fdata-sections -fno-builtin -fno-strict-aliasing -Wall -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable  -g3 -DBOARD_PCA10040 -DNRF52 -DNRF52832 -I"C:/Users/user/Documents/Software_Devel/nrf_dev/workspace/nrf52RTcpp\inc" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\toolchain\cmsis\include" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\device" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\toolchain" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\drivers_nrf\delay" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\boards" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\drivers_nrf\hal" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\util" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\drivers_nrf\nrf_soc_nosd" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\bsp" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\timer" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\button" -std=gnu99 --short-enums -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

sdk/gcc_startup_nrf52.o: C:/Users/user/Documents/Software_Devel/nrf_dev/nrfSDK_V13_2_0/components/toolchain/gcc/gcc_startup_nrf52.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs -O0 -ffunction-sections -fdata-sections -fno-builtin -fno-strict-aliasing -Wall -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable  -g3 -x assembler-with-cpp -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

sdk/system_nrf52.o: C:/Users/user/Documents/Software_Devel/nrf_dev/nrfSDK_V13_2_0/components/toolchain/system_nrf52.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs -O0 -ffunction-sections -fdata-sections -fno-builtin -fno-strict-aliasing -Wall -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable  -g3 -DBOARD_PCA10040 -DNRF52 -DNRF52832 -I"C:/Users/user/Documents/Software_Devel/nrf_dev/workspace/nrf52RTcpp\inc" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\toolchain\cmsis\include" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\device" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\toolchain" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\drivers_nrf\delay" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\boards" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\drivers_nrf\hal" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\util" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\drivers_nrf\nrf_soc_nosd" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\bsp" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\timer" -I"C:\Users\user\Documents\Software_Devel\nrf_dev\nrfSDK_V13_2_0\components\libraries\button" -std=gnu99 --short-enums -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


