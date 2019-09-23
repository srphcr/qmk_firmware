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

/* enum custom_keycodes { */
/*     DEFAULT = SAFE_RANGE, */
/*     SYMBOL, */
/*     NUMBER, */
/*     FUNCTION */
/* }; */

// Tap Dance
/* enum { */
/*     TAP_SYMBOL_SPC = 0, */
/*     TAP_NUMBER_TAB */
/* }; */

/* #define KC_S_SPC TD(TAP_SYMBOL_SPC) */
/* #define KC_N_TAB TD(TAP_NUMBER_TAB) */
#define KC_S_SPC LT(_SYMBOL, KC_SPC)
#define KC_N_TAB LT(_NUMBER, KC_TAB)
#define KC_FUNC TT(_FUNCTION)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_ESC,   KC_Q,  KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,      KC_U,     KC_I,     KC_O,    KC_P,     KC_BSPC,
        KC_FUNC,  KC_A,  KC_S,     KC_D,     KC_F,     KC_G,        KC_H,      KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_ENT,
        KC_LSFT,  KC_Z,  KC_X,     KC_C,     KC_V,     KC_B,        KC_N,      KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,
                         KC_LALT,  KC_LGUI,  KC_LCTL,  KC_N_TAB,    KC_S_SPC,  KC_RCTL,  KC_RGUI,  KC_RALT
        ),

    [_SYMBOL] = LAYOUT(
        KC_TRNS,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_NO,    KC_NO,    KC_TRNS,
        KC_TRNS,  KC_NO,    KC_GRV,   KC_LPRN,  KC_LBRC,  KC_MINS,    KC_EQL,   KC_RBRC,  KC_RPRN,  KC_QUOT,  KC_BSLS,  KC_TRNS,
        KC_TRNS,  KC_NO,    KC_TILD,  KC_LT,    KC_LCBR,  KC_UNDS,    KC_PLUS,  KC_RCBR,  KC_GT,    KC_DQUO,  KC_PIPE,  KC_TRNS,
                            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
        ),

    [_NUMBER] = LAYOUT(
        KC_TRNS,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_TRNS,
        KC_TRNS,  KC_P1,  KC_P2,    KC_P3,    KC_P4,    KC_P5,      KC_P6,    KC_P7,    KC_P8,    KC_P9,   KC_P0,  KC_TRNS,
        KC_TRNS,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_TRNS,
                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
        ),

    [_FUNCTION] = LAYOUT(
        KC_TRNS,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_F5,      KC_F6,   KC_F7,    KC_F8,    KC_NO,    KC_NO,  KC_TRNS,
        KC_TRNS,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_TRNS,
        KC_TRNS,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,   KC_LEFT,  KC_UP,    KC_RGHT,  KC_NO,  KC_TRNS,
                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_SPC,  KC_TRNS,  KC_TRNS,  KC_DOWN
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
/* void set_keylog(uint16_t keycode, keyrecord_t *record); */
/* const char *read_keylog(void); */
/* const char *read_keylogs(void); */

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

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
/*     if (record->event.pressed) { */
/* #ifdef SSD1306OLED */
/*         /\* set_keylog(keycode, record); *\/ */
/* #endif */
/*         // set_timelog(); */
/*     } */

    /* switch (keycode) { */
    /* case DEFAULT: */
    /*     if (record->event.pressed) { */
    /*         set_single_persistent_default_layer(_DEFAULT); */
    /*     } */
    /*     return false; */
    /*     break; */

    /* case SYMBOL: */
    /*     if (record->event.pressed) { */
    /*         layer_on(_SYMBOL); */
    /*     } else { */
    /*         layer_off(_SYMBOL); */
    /*     } */
    /*     return false; */
    /*     break; */

    /* case NUMBER: */
    /*     if (record->event.pressed) { */
    /*         layer_on(_NUMBER); */
    /*     } else { */
    /*         layer_off(_NUMBER); */
    /*     } */
    /*     return false; */
    /*     break; */

    /* case FUNCTION: */
    /*     if (record->event.pressed) { */
    /*         layer_on(_FUNCTION); */
    /*     } else { */
    /*         layer_off(_FUNCTION); */
    /*     } */
    /*     return false; */
    /*     break; */
    /* } */
    return true;
}

// Tap Dances
/* enum { */
/*   SINGLE_TAP = 1, */
/*   SINGLE_HOLD = 2, */
/*   DOUBLE_TAP = 3, */
/* }; */

/* typedef struct { */
/*   bool is_press_action; */
/*   int state; */
/* } tap; */

/* int cur_dance (qk_tap_dance_state_t *state) { */
/*   if (state->count == 1) { */
/*       if (!state->pressed) { */
/*           return SINGLE_TAP; */

/*       } else { */
/*           return SINGLE_HOLD; */
/*       } */

/*   } else if (state->count == 2) { */
/*     return DOUBLE_TAP; */

/*   } else { */
/*       return 6; */
/*   } */
/* } */

/* static tap tap_state = { */
/*   .is_press_action = true, */
/*   .state = 0 */
/* }; */

/* void tap_symbol_space (qk_tap_dance_state_t *state, void *user_data) { */
/*     tap_state.state = cur_dance(state); */

/*     switch (tap_state.state) { */
/*     case SINGLE_TAP: */
/*         if (IS_LAYER_ON(_SYMBOL)){ */
/*             layer_off(_SYMBOL); */

/*         } else { */
/*             register_code(KC_SPC); */
/*         } */
/*         break; */

/*     case SINGLE_HOLD: */
/*         layer_on(_SYMBOL); */
/*         break; */

/*     case DOUBLE_TAP: */
/*         layer_invert(_SYMBOL); */
/*         break; */
/*     } */
/* } */

/* void reset_tap_symbol_space (qk_tap_dance_state_t *state, void *user_data) { */
/*     switch (tap_state.state) { */
/*     case SINGLE_TAP: */
/*         unregister_code(KC_SPC); */
/*         break; */

/*     case SINGLE_HOLD: */
/*         layer_off(_SYMBOL); */
/*         break; */

/*     case DOUBLE_TAP: */
/*         break; */
/*     } */

/*     tap_state.state = 0; */
/* } */

/* void tap_number_tab (qk_tap_dance_state_t *state, void *user_data) { */
/*     tap_state.state = cur_dance(state); */

/*     switch (tap_state.state) { */
/*     case SINGLE_TAP: */
/*         if (IS_LAYER_ON(_NUMBER)){ */
/*             layer_off(_NUMBER); */

/*         } else { */
/*             register_code(KC_TAB); */
/*         } */
/*         break; */

/*     case SINGLE_HOLD: */
/*         layer_on(_NUMBER); */
/*         break; */

/*     case DOUBLE_TAP: */
/*         layer_invert(_NUMBER); */
/*         break; */
/*     } */
/* } */

/* void reset_tap_number_tab (qk_tap_dance_state_t *state, void *user_data) { */
/*     switch (tap_state.state) { */
/*     case SINGLE_TAP: */
/*         unregister_code(KC_TAB); */
/*         break; */

/*     case SINGLE_HOLD: */
/*         layer_off(_NUMBER); */
/*         break; */

/*     case DOUBLE_TAP: */
/*         break; */
/*     } */

/*     tap_state.state = 0; */
/* } */

/* qk_tap_dance_action_t tap_dance_actions[] = { */
/*     [TAP_SYMBOL_SPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_symbol_space, reset_tap_symbol_space), */
/*     [TAP_NUMBER_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_number_tab, reset_tap_number_tab) */
/* }; */
