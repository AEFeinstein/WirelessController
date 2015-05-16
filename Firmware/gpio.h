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

#ifndef _GPIO_H_
#define _GPIO_H_

/* Bitflags of possible button presses */
#define UP    0x01
#define DOWN  0x02
#define LEFT  0x04
#define RIGHT 0x08
#define STICK 0x10

/* Bitfield definitions for a uint32_t which holds all input state */
#define BUTTON_MASK  0x0000001Ful
#define X_AXIS_MASK  0x00007FE0ul
#define X_AXIS_SHIFT 5
#define Y_AXIS_MASK  0x01FF8000ul
#define Y_AXIS_SHIFT 15
#define PLAYER_MASK  0x06000000ul
#define PLAYER_SHIFT 25

/* Getter and setter for 5 bit field which holds button presses */
#define SET_BUTTONS(js, b) { \
    (js) &= ~BUTTON_MASK; \
    (js) |= (b); \
  }

#define GET_BUTTONS(js) ((js) & BUTTON_MASK)

/* Getter and setter for 10 bit field which holds the X axis ADC value */
#define SET_X_AXIS(js, x) { \
    (js) &= ~X_AXIS_MASK; \
    (js) |= (((uint32_t)x) << X_AXIS_SHIFT); \
  }

#define GET_X_AXIS(js) (((js) & X_AXIS_MASK) >> X_AXIS_SHIFT)

/* Getter and setter for 10 bit field which holds the Y axis ADC value */
#define SET_Y_AXIS(js, y) { \
    (js) &= ~Y_AXIS_MASK; \
    (js) |= (((uint32_t)y) << Y_AXIS_SHIFT); \
  }

#define GET_Y_AXIS(js) (((js) & Y_AXIS_MASK) >> Y_AXIS_SHIFT)

/* Getter and setter for 2 bit field which holds the player value */
#define SET_PLAYER(js, pl) { \
    (js) &= ~PLAYER_MASK; \
    (js) |= (((uint32_t)pl) << PLAYER_SHIFT); \
  }

#define GET_PLAYER(js) (((js) & PLAYER_MASK) >> PLAYER_SHIFT)

/* Function declarations */
void gpio_init(void);
void digital_read(uint32_t* inputState);
void analog_read(uint32_t* inputState, uint32_t xAvg, uint32_t yAvg);

#endif /* _GPIO_H_ */
