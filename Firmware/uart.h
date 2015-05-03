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

#ifndef _UART_H_
#define _UART_H_

#if DBG_PRINT == ENABLED

/* The baud rate for the debug uart */
#define BAUD 9600

/* Function declarations */
void init_uart(void);
void USART_send(uint8_t data);
void USART_putstring(char* StringPtr);

#endif

#endif /* _UART_H_ */
