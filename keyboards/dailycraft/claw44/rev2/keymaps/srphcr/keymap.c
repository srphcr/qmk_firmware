/*
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

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _DEFAULT = 0,
    _SYMBOL,
    _NUMBER,
    _FUNCTION,
};

#define KC_MO_SYM MO(_SYMBOL)
#define KC_MO_NUM MO(_NUMBER)
#define KC_MO_FUN MO(_FUNCTION)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_ESC,     KC_Q,  KC_W,     KC_E,       KC_R,     KC_T,                      KC_Y,    KC_U,     KC_I,       KC_O,    KC_P,     KC_BSPC,
        KC_MO_FUN,  KC_A,  KC_S,     KC_D,       KC_F,     KC_G,    KC_NO,    KC_NO,  KC_H,    KC_J,     KC_K,       KC_L,    KC_SCLN,  KC_ENT,
        KC_LSFT,    KC_Z,  KC_X,     KC_C,       KC_V,     KC_B,    KC_NO,    KC_NO,  KC_N,    KC_M,     KC_COMM,    KC_DOT,  KC_SLSH,  KC_RSFT,
                           KC_LGUI,  KC_MO_NUM,  KC_LCTL,  KC_TAB,                    KC_SPC,  KC_RCTL,  KC_MO_SYM,  KC_RALT
    ),

    [_SYMBOL] = LAYOUT(
        KC_ESC,   KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_NO,    KC_NO,    KC_BSPC,
        KC_NO,    KC_NO,    KC_GRV,   KC_LPRN,  KC_LBRC,  KC_MINS,  KC_NO,    KC_NO,  KC_EQL,   KC_RBRC,  KC_RPRN,  KC_QUOT,  KC_BSLS,  KC_ENT,
        KC_LSFT,  KC_NO,    KC_TILD,  KC_LT,    KC_LCBR,  KC_UNDS,  KC_NO,    KC_NO,  KC_PLUS,  KC_RCBR,  KC_GT,    KC_DQUO,  KC_PIPE,  KC_RSFT,
                            KC_LGUI,  KC_NO,    KC_LCTL,  KC_TAB,                     KC_SPC,   KC_RCTL,  KC_TRNS,  KC_RALT
    ),

    [_NUMBER] = LAYOUT(
        KC_ESC,   KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,                     KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_BSPC,
        KC_NO,    KC_1,   KC_2,     KC_3,     KC_4,     KC_5,    KC_NO,    KC_NO,  KC_6,    KC_7,     KC_8,   KC_9,    KC_0,   KC_ENT,
        KC_LSFT,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,    KC_NO,  KC_NO,   KC_NO,    KC_NO,  KC_NO,   KC_NO,  KC_RSFT,
                          KC_LGUI,  KC_TRNS,  KC_LCTL,  KC_TAB,                    KC_SPC,  KC_RCTL,  KC_NO,  KC_RALT
    ),

    [_FUNCTION] = LAYOUT(
        KC_ESC,   KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,                     KC_NO,   KC_NO,    KC_NO,  KC_NO,    KC_NO,   KC_BSPC,
        KC_TRNS,  KC_F1,  KC_F2,    KC_F3,  KC_F4,    KC_F5,   KC_NO,    KC_NO,  KC_F6,   KC_F7,    KC_F8,  KC_F9,    KC_F10,  KC_ENT,
        KC_LSFT,  KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,   KC_NO,    KC_NO,  KC_NO,   KC_LEFT,  KC_UP,  KC_RGHT,  KC_NO,   KC_RSFT,
                          KC_LGUI,  KC_NO,  KC_LALT,  KC_TAB,                    KC_SPC,  KC_RCTL,  KC_NO,  KC_DOWN
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_NO, KC_NO),     ENCODER_CCW_CW(KC_NO, KC_NO)      },
    [1] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [2] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [3] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  }
};
#endif
