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

#include <avr/io.h>
#include "main.h"
#include "uart.h"

#if DBG_PRINT == ENABLED

#include <util/setbaud.h>

/**
 * Initialize the uart's baud and frame info
 * BAUD is defined in uart.h
 */
void init_uart(void)
{
  /* Use the values calculated in setbaud.h */
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  #if USE_2X
  UCSR0A |= (1 << U2X0);
  #else
  UCSR0A &= ~(1 << U2X0);
  #endif

  /* Enable receiver and transmitter */
  UCSR0B = (0 << RXEN0) | /* Disable RX */
           (1 << TXEN0) ; /* Enable TX */

  /* Set frame format */
  UCSR0C = (0 << UCPOL0)  | /* Send on rising edge, receive on falling edge */
           (1 << UCSZ00)  | /* 8 data bits */
           (1 << UCSZ01)  |
           (0 << USBS0)   | /* 1 stop bit */
           (1 << UPM00)   | /* Enable odd parity */
           (1 << UPM01)   |
           (0 << UMSEL00) | /* Asynchronous uart mode */
           (0 << UMSEL01) ;
}

/**
 * Send a single uint8_t over the uart
 *
 * @param [in] data The uint8_t to send over the uart
 */
void USART_send(uint8_t data)
{
  /* Wait until the transmit buffer is ready to receive new data */
  while (!(UCSR0A & (1 << UDRE0))) {
    ; /* Spin around in circles */
  }
  UDR0 = data;
}

/**
 * Send a string of data over the uart
 *
 * @param [in] StringPtr A pointer to a null terminated string to send over the
 *             uart
 */
void USART_putstring(char* StringPtr)
{
  /* Until we hit the null terminator, iterate through the string and send each
   * char
   */
  while (*StringPtr != 0x00) {
    USART_send(*StringPtr);
    StringPtr++;
  }
}

#endif
