#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define KC_S_SPC LT(_SYMBOL, KC_SPC)
#define KC_N_TAB LT(_NUMBER, KC_TAB)
#define KC_FUNC TT(_FUNCTION)

enum custom_keycodes {
    RGB_RST = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT(
      KC_ESC,   KC_Q,  KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,      KC_U,     KC_I,     KC_O,    KC_P,     KC_BSPC,
      KC_FUNC,  KC_A,  KC_S,     KC_D,     KC_F,     KC_G,        KC_H,      KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_ENT,
      KC_LSFT,  KC_Z,  KC_X,     KC_C,     KC_V,     KC_B,        KC_N,      KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,
                                 KC_LGUI,  KC_LCTL,  KC_N_TAB,    KC_S_SPC,  KC_RCTL,  KC_RALT
      ),

  [_SYMBOL] = LAYOUT(
      KC_TRNS,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_NO,    KC_NO,    KC_TRNS,
      KC_TRNS,  KC_NO,    KC_GRV,   KC_LPRN,  KC_LBRC,  KC_MINS,    KC_EQL,   KC_RBRC,  KC_RPRN,  KC_QUOT,  KC_BSLS,  KC_TRNS,
      KC_TRNS,  KC_NO,    KC_TILD,  KC_LT,    KC_LCBR,  KC_UNDS,    KC_PLUS,  KC_RCBR,  KC_GT,    KC_DQUO,  KC_PIPE,  KC_TRNS,
                                    KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS
    ),

  [_NUMBER] = LAYOUT(
      KC_TRNS,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_TRNS,
      KC_TRNS,  KC_P1,  KC_P2,    KC_P3,    KC_P4,    KC_P5,      KC_P6,    KC_P7,    KC_P8,    KC_P9,   KC_P0,  KC_TRNS,
      KC_TRNS,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_TRNS,
                                  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [_FUNCTION] = LAYOUT(
      KC_TRNS,  RESET,    RGB_RST,   KC_NO,    KC_NO,    KC_F5,      KC_F6,   KC_F7,    KC_F8,    KC_NO,    KC_NO,  KC_TRNS,
      KC_TRNS,  RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  KC_NO,      KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_TRNS,
      KC_TRNS,  RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  KC_NO,      KC_NO,   KC_LEFT,  KC_UP,    KC_RGHT,  KC_NO,  KC_TRNS,
                                    KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_SPC,  KC_TRNS,  KC_DOWN
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
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
