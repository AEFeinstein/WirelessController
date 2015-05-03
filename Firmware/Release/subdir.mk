################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gpio.c \
../main.c \
../nrf24.c \
../radioPinFunctions.c \
../timer.c \
../uart.c 

OBJS += \
./gpio.o \
./main.o \
./nrf24.o \
./radioPinFunctions.o \
./timer.o \
./uart.o 

C_DEPS += \
./gpio.d \
./main.d \
./nrf24.d \
./radioPinFunctions.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Werror -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=c99 -funsigned-char -funsigned-bitfields -Wextra -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


