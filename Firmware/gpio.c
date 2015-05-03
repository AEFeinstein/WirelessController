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
#include "gpio.h"

#define DEAD_ZONE 5

/**
 * Initialize GPIOs
 */
void gpio_init()
{
  /* Enable blinky LED gpio */
  DDRB |= _BV(DDB0);

  /* Disable output */
  DDRD &= ~(_BV(DDD3));
  DDRD &= ~(_BV(DDD4));
  DDRD &= ~(_BV(DDD5));
  DDRD &= ~(_BV(DDD6));
  DDRD &= ~(_BV(DDD7));

  /* Enable internal pullups */
  PORTD |= _BV(PORTD3);
  PORTD |= _BV(PORTD4);
  PORTD |= _BV(PORTD5);
  PORTD |= _BV(PORTD6);
  PORTD |= _BV(PORTD7);
}

/**
 * Read and store the state of the digital buttons
 *
 * @param inputState [out] The JoystickState struct to read the state into
 */
void digital_read(uint32_t* inputState)
{
  uint8_t input = PIND;
  uint8_t buttons = 0;

  if((input & _BV(PIND3)) == 0) {
    buttons |= STICK;
  }
  if((input & _BV(PIND4)) == 0) {
    buttons |= UP;
  }
  if((input & _BV(PIND5)) == 0) {
    buttons |= LEFT;
  }
  if((input & _BV(PIND6)) == 0) {
    buttons |= RIGHT;
  }
  if((input & _BV(PIND7)) == 0) {
    buttons |= DOWN;
  }

  SET_BUTTONS(*inputState, buttons);
}

/**
 * Read and store the state of the analog stick
 *
 * @param inputState [out] The JoystickState struct to read the state into
 * @param xCenter [in] The middle position of the X axis. Use 0 when calibrating
 * @param yCenter [in] The middle position of the Y axis. Use 0 when calibrating
 */
void analog_read(uint32_t* inputState, uint32_t xCenter, uint32_t yCenter)
{
  uint16_t adcRead;

  /* Disable power reduction ADC bit */
  PRR &= ~(_BV(PRADC));

  /* Enable ADC */
  ADCSRA |= _BV(ADEN);

  /* Read Joystick Vertical */
  ADMUX = (1 << MUX0)  | /* Select ADC1 */
          (0 << MUX1)  |
          (0 << MUX2)  |
          (0 << MUX3)  |
          (0 << ADLAR) | /* Right adjust the result */
          (0 << REFS0) | /* Compare against AREF, internal Vref is off */
          (0 << REFS1);

  /* Start ADC conversion, wait until it's done */
  ADCSRA |= _BV(ADSC);
  while(ADCSRA & _BV(ADSC)) {
    ;
  }

  /* Read the result */
  adcRead = ADC;

  /* Store the result, taking into account the dead zone */
  if (yCenter != 0 &&
      yCenter - DEAD_ZONE < adcRead && adcRead < yCenter + DEAD_ZONE) {
    SET_Y_AXIS(*inputState, 512);
  }
  else {
    SET_Y_AXIS(*inputState, adcRead);
  }

  /* Read Joystick Horizontal */
  ADMUX = (0 << MUX0)  | /* Select ADC2 */
          (1 << MUX1)  |
          (0 << MUX2)  |
          (0 << MUX3)  |
          (0 << ADLAR) | /* Right adjust the result */
          (0 << REFS0) | /* Compare against AREF, internal Vref is off */
          (0 << REFS1);

  /* Start ADC conversion, wait until it's done */
  ADCSRA |= _BV(ADSC);
  while(ADCSRA & _BV(ADSC)) {
    ;
  }

  /* Read the result */
  adcRead = ADC;

  /* Store the result, taking into account the dead zone */
  if (xCenter != 0 &&
      xCenter - DEAD_ZONE < adcRead && adcRead < xCenter + DEAD_ZONE) {
    SET_X_AXIS(*inputState, 512);
  }
  else {
    SET_X_AXIS(*inputState, adcRead);
  }

  /* Enable power reduction ADC bit */
  PRR |= _BV(PRADC);

  /* Disable ADC */
  ADCSRA &= ~(_BV(ADEN));
}
