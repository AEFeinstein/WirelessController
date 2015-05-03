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
#include <avr/interrupt.h>
#include "main.h"

/**
 * Initialize a timer on timer1 to call an interrupt once a second
 */
void timer_init()
{
  /* OCRn = [ (clock_speed / Prescaler_value) * Desired_time_in_Seconds ] - 1 */
  OCR1A = ((F_CPU / 1024UL) * 1UL) - 1UL;

  /* Mode 4, CTC on OCR1A */
  TCCR1B |= (1 << WGM12);

  /* Set interrupt on compare match */
  TIMSK1 |= (1 << OCIE1A);

  /* set prescaler to 1024 and start the timer */
  TCCR1B |= (1 << CS12) | (1 << CS10);

  /* enable interrupts */
  sei();
}

/**
 * An interrupt routine which is called once a second. It toggles the state
 * of an LED, blinking it at 0.5Hz
 *
 * @param TIMER1_COMPA_vect [in] The interrupt vector,
 *                               Timer/Counter1 Compare Match A
 */
ISR (TIMER1_COMPA_vect)
{
  /* toggle blinky LED gpio */
  PORTB ^= _BV(PB0);
}
