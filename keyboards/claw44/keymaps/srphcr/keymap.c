#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef SSD1306OLED
#include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

extern uint8_t is_master;

#define KC_SYM MO(_SYMBOL)
#define KC_NUM MO(_NUMBER)
#define KC_FUN TT(_FUNCTION)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_ESC,   KC_Q,  KC_W,     KC_E,    KC_R,     KC_T,      KC_Y,    KC_U,     KC_I,     KC_O,    KC_P,     KC_BSPC,
        KC_FUN,   KC_A,  KC_S,     KC_D,    KC_F,     KC_G,      KC_H,    KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_ENT,
        KC_LSFT,  KC_Z,  KC_X,     KC_C,    KC_V,     KC_B,      KC_N,    KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,
                         KC_LGUI,  KC_NUM,  KC_LCTL,  KC_TAB,    KC_SPC,  KC_RCTL,  KC_SYM,   KC_RALT
        ),

    [_SYMBOL] = LAYOUT(
        KC_TRNS,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_NO,    KC_NO,    KC_TRNS,
        KC_NO,    KC_NO,    KC_GRV,   KC_LPRN,  KC_LBRC,  KC_MINS,    KC_EQL,   KC_RBRC,  KC_RPRN,  KC_QUOT,  KC_BSLS,  KC_TRNS,
        KC_TRNS,  KC_NO,    KC_TILD,  KC_LT,    KC_LCBR,  KC_UNDS,    KC_PLUS,  KC_RCBR,  KC_GT,    KC_DQUO,  KC_PIPE,  KC_TRNS,
                            KC_TRNS,  KC_NO,    KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
        ),

    [_NUMBER] = LAYOUT(
        KC_TRNS,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,  KC_NO,   KC_NO,  KC_TRNS,
        KC_NO,    KC_1,   KC_2,     KC_3,     KC_4,     KC_5,       KC_6,     KC_7,     KC_8,   KC_9,    KC_0,   KC_TRNS,
        KC_TRNS,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,  KC_NO,   KC_NO,  KC_TRNS,
                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_NO,  KC_TRNS
        ),

    [_FUNCTION] = LAYOUT(
        KC_TRNS,  KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,   KC_TRNS,
        KC_TRNS,  KC_F1,  KC_F2,    KC_F3,  KC_F4,    KC_F5,      KC_F6,    KC_F7,    KC_F8,  KC_F9,    KC_F10,  KC_TRNS,
        KC_TRNS,  KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,      KC_NO,    KC_LEFT,  KC_UP,  KC_RGHT,  KC_NO,   KC_TRNS,
                          KC_TRNS,  KC_NO,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_NO,  KC_DOWN
        ),
};

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
#endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

char blank_line[24];

const char *read_blank_line(void);

const char *read_blank_line(void) {
    snprintf(blank_line, sizeof(blank_line), " ");

    return blank_line;
}

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);

void matrix_scan_user(void) {
    iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        // If you want to change the display of OLED, you need to change here
        matrix_write_ln(matrix, read_blank_line());
        matrix_write_ln(matrix, read_blank_line());
        matrix_write_ln(matrix, read_layer_state());
        /* matrix_write_ln(matrix, read_keylog()); */
        /* matrix_write_ln(matrix, read_keylogs()); */
        //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
        //matrix_write_ln(matrix, read_host_led_state());
        //matrix_write_ln(matrix, read_timelog());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
