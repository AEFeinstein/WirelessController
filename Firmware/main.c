/**
 * Copyright 2011 Adam Feinstein
 *
 * This file is part of WirelessController.
 *
 * WirelessController is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WirelessController is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WirelessController.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#include "main.h"
#include "gpio.h"
#include "nrf24.h"
#include "timer.h"
#if DBG_PRINT == ENABLED
#include "uart.h"
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#endif

/* Number of ADC reads taken to calibrate the ADC's middle position */
#define NUM_CALIBRATIONS 10

int main(void)
{
  /* All the controller state is stored in 32 bits */
  uint32_t inputState, oldInputState;

  /* Used for calibrating the ADC */
  uint32_t xJoystickCenter, yJoystickCenter;
  uint8_t i;

  #if DBG_PRINT == ENABLED
  uint8_t msgStatus;
  char dbgstr[100];
  #endif

  /* Initialize everything */
  gpio_init();
  nrf24_init();
  timer_init();
  #if DBG_PRINT == ENABLED
  init_uart();
  #endif

  /* Calibrate joystick center */
  xJoystickCenter = 0;
  yJoystickCenter = 0;
  for(i = 0; i < NUM_CALIBRATIONS; i++) {
    analog_read(&inputState, 0, 0);
    xJoystickCenter += GET_X_AXIS(inputState);
    yJoystickCenter += GET_Y_AXIS(inputState);
  }
  xJoystickCenter /= NUM_CALIBRATIONS;
  yJoystickCenter /= NUM_CALIBRATIONS;

  /* Main Loop */
  while (1) {

    /* Save the prior state */
    oldInputState = inputState;

    /* Read Controller State */
    digital_read(&inputState);
    analog_read(&inputState, xJoystickCenter, yJoystickCenter);

    /* If any inputs have changed, send an RF message */
    if(oldInputState != inputState) {

      /* Send the controller's state. Automatically goes to TX mode */
      nrf24_send((uint8_t*)(&inputState));

      while(nrf24_isSending()) {
        ;/* Wait for transmission to end */
      }

      #if DBG_PRINT == ENABLED
      /* Make analysis on last transmission attempt */
      msgStatus = nrf24_lastMessageStatus();

      if(msgStatus == NRF24_TRANSMISSON_OK) {
        USART_putstring("transmission went OK\n");
      }
      else if(msgStatus == NRF24_MESSAGE_LOST) {
        USART_putstring("Message is lost\n");
      }

      /* Retransmission count indicates the transmission quality */
      msgStatus = nrf24_retransmissionCount();
      USART_putstring("Retransmission count: ");
      itoa(msgStatus, dbgstr, 16);
      USART_putstring(dbgstr);
      USART_putstring("\n");

      /* Print the analog stick position */
      itoa(GET_X_AXIS(inputState), dbgstr, 16);
      USART_putstring(dbgstr);
      USART_putstring(", ");
      itoa(GET_Y_AXIS(inputState), dbgstr, 16);
      USART_putstring(dbgstr);
      USART_send('\n');

      /* Print button positions */
      if(GET_BUTTONS(inputState) & UP) {
        USART_putstring("UP\n");
      }
      if(GET_BUTTONS(inputState) & DOWN) {
        USART_putstring("DOWN\n");
      }
      if(GET_BUTTONS(inputState) & LEFT) {
        USART_putstring("LEFT\n");
      }
      if(GET_BUTTONS(inputState) & RIGHT) {
        USART_putstring("RIGHT\n");
      }
      if(GET_BUTTONS(inputState) & STICK) {
        USART_putstring("STICK\n");
      }
      USART_send('\n');
      #endif
    }
  }
  return (0);
}
