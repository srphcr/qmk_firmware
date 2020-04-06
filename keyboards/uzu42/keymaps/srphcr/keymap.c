#include QMK_KEYBOARD_H
#include "uzu42.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef SSD1306OLED
#include "ssd1306.h"
#endif


#ifdef RGBLIGHT_ENABLE
#include <stdio.h>
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

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

enum custom_keycodes {
    RGB_RST = SAFE_RANGE,
};

#define KC_SYM TT(_SYMBOL)
#define KC_NUM TT(_NUMBER)
#define KC_F_ESC LT(_FUNCTION, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_Q,      KC_W,     KC_E,    KC_R,     KC_T,                         KC_Y,     KC_U,    KC_I,     KC_O,    KC_P,
        KC_A,      KC_S,     KC_D,    KC_F,     KC_G,                         KC_H,     KC_J,    KC_K,     KC_L,    KC_SCLN,
        KC_Z,      KC_X,     KC_C,    KC_V,     KC_B,                         KC_N,     KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,
        KC_F_ESC,  KC_LGUI,  KC_NUM,  KC_LSFT,  KC_LCTL,  KC_TAB,    KC_SPC,  KC_RALT,  KC_SYM,  KC_RSFT,  KC_ENT,  KC_BSPC
        ),

    [_SYMBOL] = LAYOUT(
        KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                        KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_NO,    KC_NO,
        KC_NO,    KC_GRV,   KC_LPRN,  KC_LBRC,  KC_MINS,                        KC_EQL,   KC_RBRC,  KC_RPRN,  KC_QUOT,  KC_BSLS,
        KC_NO,    KC_TILD,  KC_LT,    KC_LCBR,  KC_UNDS,                        KC_PLUS,  KC_RCBR,  KC_GT,    KC_DQUO,  KC_PIPE,
        KC_ESC,   KC_TRNS,  KC_NO,    KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
        ),

    [_NUMBER] = LAYOUT(
        KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,
        KC_P1,   KC_P2,    KC_P3,    KC_P4,    KC_P5,                          KC_P6,    KC_P7,  KC_P8,    KC_P9,    KC_P0,
        KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,
        KC_ESC,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_NO,  KC_TRNS,  KC_TRNS,  KC_TRNS
        ),

    [_FUNCTION] = LAYOUT(
        RESET,    RGB_RST,  KC_NO,    KC_NO,    KC_F5,                          KC_F6,    KC_F7,    KC_F8,    KC_NO,    KC_NO,
        RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
        RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  KC_NO,                          KC_NO,    KC_LEFT,  KC_UP,    KC_RGHT,  KC_NO,
        KC_TRNS,  KC_TRNS,  KC_NO,    KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_DOWN,  KC_TRNS,  KC_TRNS,  KC_TRNS
        )
};

int RGB_current_mode;

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

#define L_DEFAULT 0
#define L_SYMBOL (1 << 1)
#define L_NUMBER (1 << 2)
#define L_FUNCTION (1 << 3)

char layer_state_str[24];

const char *read_layer_state(void) {
    switch (layer_state)
    {
    case L_DEFAULT:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
        break;
    case L_SYMBOL:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Symbol");
        break;
    case L_NUMBER:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Number");
        break;
    case L_FUNCTION:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Function");
        break;
    default:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
    }

    return layer_state_str;
}

const char *read_logo(void) {
    static char logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    return logo;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master())
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_state(), false);
    } else {
        oled_write(read_logo(), false);
    }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGB_MOD:
#ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
        }
#endif
        return false;
        break;
    case RGB_RST:
#ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
        }
#endif
        break;
    }
    return true;
}

#ifdef RGBLIGHT_ENABLE

char rbf_info_str[24];
const char *read_rgb_info(void) {

    snprintf(rbf_info_str, sizeof(rbf_info_str), "%s %2d h%3d s%3d v%3d",
             rgblight_config.enable ? "on" : "- ", rgblight_config.mode,
             rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
    return rbf_info_str;
}
#endif
