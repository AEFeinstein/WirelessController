all:
	avr-gcc -Wall -Wextra -Werror -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=c99 -funsigned-char -funsigned-bitfields -v -mmcu=atmega328p -MMD -MP -MFmain.d -MTmain.d -c -o main.o main.c
	avr-gcc -Wall -Wextra -Werror -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=c99 -funsigned-char -funsigned-bitfields -v -mmcu=atmega328p -MMD -MP -MFgpio.d -MTgpio.d -c -o gpio.o gpio.c
	avr-gcc -Wall -Wextra -Werror -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=c99 -funsigned-char -funsigned-bitfields -v -mmcu=atmega328p -MMD -MP -MFuart.d -MTuart.d -c -o uart.o uart.c
	avr-gcc -Wall -Wextra -Werror -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=c99 -funsigned-char -funsigned-bitfields -v -mmcu=atmega328p -MMD -MP -MFtimer.d -MTtimer.d -c -o timer.o timer.c
	avr-gcc -Wall -Wextra -Werror -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=c99 -funsigned-char -funsigned-bitfields -v -mmcu=atmega328p -MMD -MP -MFnrf24.d -MTnrf24.d -c -o nrf24.o nrf24.c
	avr-gcc -Wall -Wextra -Werror -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=c99 -funsigned-char -funsigned-bitfields -v -mmcu=atmega328p -MMD -MP -MFradioPinFunctions.d -MTradioPinFunctions.d -c -o radioPinFunctions.o radioPinFunctions.c
	avr-gcc -Wl,-Map,WirelessController.map -mmcu=atmega328p -o WirelessController.elf main.o gpio.o uart.o nrf24.o timer.o radioPinFunctions.o
	avr-objdump -h -S WirelessController.elf  >WirelessController.lss
	avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex WirelessController.elf  WirelessController.hex
	avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex WirelessController.elf  WirelessController.eep
	avr-size --format=avr --mcu=atmega328p WirelessController.elf

program:
	avrdude -p m328p -c usbtiny -e -U flash:w:WirelessController.hex

clean:
	rm *.d *.o *.map *.hex *.elf *.eep *.lss *.orig