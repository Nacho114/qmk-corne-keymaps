/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include <stdio.h>

enum userspace_layers {
   _DEFAULTS = 0,    // This is required.
   _COLEMAKDHM = 0,  // Default layout
   _QWERTY,
   _NUM,
   _SYM,
   _MENU,
};

//-------------------------------------------
//---------------- COMBO
//-------------------------------------------

const uint16_t PROGMEM combo_kj[] = {KC_K, KC_J, COMBO_END};
const uint16_t PROGMEM combo_ei[] = {KC_E, KC_I, COMBO_END};
// COMBO_COUNT is set in config.h
combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_kj, KC_ESC),
    // TODO: there might be a better combo...
    COMBO(combo_ei, KC_ESC), 
};

//-------------------------------------------
//---------------- Leader
//-------------------------------------------

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // osx screen shot
    SEQ_TWO_KEYS(KC_S, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_LSFT);
      register_code(KC_4);
      clear_keyboard();
    }

    // Alt+space -> search alfred osx
    SEQ_TWO_KEYS(KC_F, KC_D) {
      register_code(KC_LALT);
      register_code(KC_SPC);
      clear_keyboard();
    }

    SEQ_TWO_KEYS(KC_G, KC_S) {
      layer_on(_SYM);
    }

    SEQ_TWO_KEYS(KC_G, KC_N) {
      layer_on(_NUM);
    }

    SEQ_TWO_KEYS(KC_G, KC_M) {
      layer_on(_MENU);
    }

  }
}

//-------------------------------------------
//---------------- MACROS
//-------------------------------------------

enum custom_keycodes {
    S_QK_LEAD = SAFE_RANGE,
};

// If in a layer other than default, using S_QK_LEAD 
// will switch to the default layer and press QK_LEAD.
void s_qk_lead_macro(void) {
    layer_clear();
    qk_leader_start();
};

//-------------------------------------------
//---------------- LAYOUT
//-------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAKDHM] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
LT(_MENU,KC_TAB), KC_Q,	   KC_W,   	KC_F,    KC_P,    KC_B, 					              KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, KC_BSPC,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G, 						            KC_M,    KC_N,    KC_E,    KC_I,   KC_O,  KC_SCLN,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		  KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V, 						            KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_NUBS,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                               KC_LALT, LT(_NUM, KC_BSPC), KC_LGUI,     KC_ENT,  LT(_SYM, KC_SPC),  QK_LEAD
                                      //`--------------------------'  `--------------------------'
  ),

  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
LT(_MENU,KC_TAB), KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_NUBS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                               KC_LALT, LT(_NUM, KC_BSPC), KC_LGUI,     KC_ENT,  LT(_SYM, KC_SPC),  QK_LEAD
                                      //`--------------------------'  `--------------------------'
	),
	
  [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,   TO(0),      TO(0), _______, S_QK_LEAD
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_GRV,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_UNDS,   KC_LT,   KC_GT, KC_LCBR, KC_RCBR, KC_QUES,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_MINS, KC_PLUS,KC_EQUAL, KC_LBRC, KC_RBRC, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,   TO(0),      TO(0), _______, S_QK_LEAD
                                      //`--------------------------'  `--------------------------'
  ),

  [_MENU] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_BRMD, KC_BRMU,   KC_NO,   KC_NO,   KC_NO,                      KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO, RGB_TOG, RGB_VAD, RGB_VAI,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  QK_RBT, DF(_QWERTY), DF(_COLEMAKDHM), KC_NO, KC_NO, KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,   TO(0),      TO(0), _______, S_QK_LEAD
                                      //`--------------------------'  `--------------------------'
  )
};

//-------------------------------------------
//---------------- RGB Colors
//-------------------------------------------

#ifdef RGBLIGHT_ENABLE

// Default color
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_CYAN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

// Menu color
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _NUM:
        rgblight_sethsv_noeeprom(HSV_ORANGE);
        break;
    case _SYM:
        rgblight_sethsv_noeeprom(HSV_MAGENTA);
        break;
    case _MENU:
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
    default: 
        rgblight_sethsv_noeeprom(HSV_CYAN);
        break;
    }
  return state;
}
#endif // RGBLIGHT_ENABLE

//-------------------------------------------
//---------------- OLED settings
//-------------------------------------------

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(default_layer_state|layer_state)) {
        case _COLEMAKDHM:
            oled_write_ln_P(PSTR("COLEMAK-DHm"), false);
            break;
        case _QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case _MENU:
            oled_write_ln_P(PSTR("Menu"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined! :("), false);
            break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "\n%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM nacho_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
        0x80, 0x80, 0x80, 0x80, 0x86, 0x9e, 0xf8, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x00, 0xc0, 0xf0, 0xf8, 0xfe, 0xfe, 
        0xfe, 0xf8, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1c, 0x1c, 0x30, 0x30, 0xe0, 0x80, 0xc0, 0xc0, 0xf0, 
        0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 
        0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f, 0x03, 
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0xe0, 0xf0, 0xfd, 0xff, 0xff, 0xff, 0xbf, 0x3f, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf3, 0xe1, 0xc0, 0x40, 0x60, 0x78, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
        0xc0, 0xc0, 0xf0, 0xf0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xbe, 0xff, 0xff, 0x3f, 0x7f, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0x60, 0x60, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0x83, 0x47, 0x7f, 0x7f, 0xff, 
        0xff, 0xff, 0xfd, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x8f, 0x87, 0x83, 0x87, 0x06, 0x06, 0x02, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0xc0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfb, 0xff, 0xff, 0xfc, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf0, 0xc0, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 
        0x03, 0x07, 0x07, 0x0f, 0x0f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7d, 0xff, 0xff, 0xfc, 0xfe, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0x08, 0x08, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
        0x07, 0x1f, 0x3f, 0x3f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x30, 0x3e, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x03, 0x03, 0x07, 
        0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(nacho_logo, sizeof(nacho_logo));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  // Handle macros 
  switch (keycode) {
    case S_QK_LEAD:
        if (record->event.pressed) {
          s_qk_lead_macro();
          // Important! 
          // If true is returned, then the macro keycode would also be returned
          // which will interfere with the leader behavior (although it could also
          // be a feature if it is part of the leader sequence).
          return false; 
        } 
        break;
    }

  return true;
}
#endif // OLED_ENABLE
