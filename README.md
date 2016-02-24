# WirelessController
WirelessController is an ATmega328p based video game controller that controls a [PixelShirtV2](https://github.com/AEFeinstein/PixelShirtV2), which is Arduino based collection of games, using an nRF24L01+ wireless radio.

## The Firmware

The firmware is relatively simple. The main function initializes the hardware and calibrates the joystick. An infinite loop polls the digital buttons and analog X & Y values of the joystick. If any of the values change, a bitpacked message containing the controller's state is sent to the PixelShirtV2.

A timer interrupt is called once a second to toggle a heartbeat LED.

Each controller's ID must be hardcoded differently when compiling and flashing the firmware. The PixelShirtV2 can support up to four controllers simultaneously.

This project uses the [nrf24L01+ radio library](https://github.com/kehribar/nrf24L01_plus).

## The Hardware

The controller is powered by two AA batteries, which make nice grips on the bottom. The ATmega328p is populated underneath the PCB. The 3x2 header is an ISP header, and the 6x1 header is for serial debug over an FTDI cable.

I populated one of the controllers with red LEDs, and the other with blue LEDs. These are conveniently the two player colors used in all games, which made identifying player one and player two very easy.

Screenshots of the PCB layout. The top view is first, then the bottom view.
<br><img src="https://raw.githubusercontent.com/AEFeinstein/WirelessController/master/Hardware/Images/controller-top.png" width="850">
<br><img src="https://raw.githubusercontent.com/AEFeinstein/WirelessController/master/Hardware/Images/controller-bottom.png" width="850">

This is what it looks like all soldered together.
<br><img src="https://raw.githubusercontent.com/AEFeinstein/WirelessController/master/Hardware/Images/controller.png" width="850">

## Thanks
3D models and print courtesy of [gbsoares](https://github.com/gbsoares).<br>
[jgordo32](https://github.com/jgordo32) assisted with hardware design.
