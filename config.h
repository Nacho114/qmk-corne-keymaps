/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define MASTER_LEFT

#define TAPPING_TERM 160 // Any tap that’s shorter than 200ms will be a tap
                         
#define COMBO_COUNT 1 // number of combo's defined
#define COMBO_TERM 10 // timeout for the Combos to be recognized
                         
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 350

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

    // These take up a lot of memory! (Roughly 12% of firmware size)
      
    /* #define RGBLIGHT_EFFECT_BREATHING */
    /* #define RGBLIGHT_EFFECT_RAINBOW_MOOD */
    /* #define RGBLIGHT_EFFECT_RAINBOW_SWIRL */
    /* #define RGBLIGHT_EFFECT_SNAKE */
    /* #define RGBLIGHT_EFFECT_KNIGHT */
    /* #define RGBLIGHT_EFFECT_CHRISTMAS */
    /* #define RGBLIGHT_EFFECT_STATIC_GRADIENT */
    /* #define RGBLIGHT_EFFECT_RGB_TEST */
    /* #define RGBLIGHT_EFFECT_ALTERNATING */
    /* #define RGBLIGHT_EFFECT_TWINKLE */

#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
