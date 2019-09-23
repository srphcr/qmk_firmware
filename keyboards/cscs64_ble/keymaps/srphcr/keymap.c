/*
Copyright 2018 Sekigon
Copyright 2019 hatano.h

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
#include "app_ble_func.h"

/**
 * Layers
 */
enum layer_number {
    _DEFAULT = 0,
    _SYMBOL,
    _NUMBER,
    _CONFIG,
};

/*
 * Custom keycodes
 */
enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    SEL_BLE,              /* Select BLE HID Sending               */
    SEL_USB,              /* Select USB HID Sending               */
    TOG_HID,              /* Toggle BLE/USB HID Sending           */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    ADV_ID5,              /* Start advertising to PeerID 5        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    DEL_ID5,              /* Delete bonding of PeerID 5           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
};

/*
 * Keymaps
 */
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Default
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  BS  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |   Q  |   W  |   E  |   R  |   T  |   -  |   =  |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Config|   A  |   S  |   D  |   F  |   G  |   [  |   ]  |   H  |   J  |   K  |   L  |   ;  | Enter|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |   `  |   '  |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Number|      |  Alt |  GUI | Ctrl |  TAB |             | Space| Ctrl |  GUI |  Alt |      |Symbol|
   * `------+      +---------------------------+             +---------------------------+      +------'
   */
  [_DEFAULT] = LAYOUT(
    KC_ESC,       KC_1,  KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,    KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
    KC_NO,        KC_Q,  KC_W,     KC_E,     KC_R,     KC_T,    KC_MINS,   KC_EQL,   KC_Y,    KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
    TT(_CONFIG),  KC_A,  KC_S,     KC_D,     KC_F,     KC_G,    KC_LBRC,   KC_RBRC,  KC_H,    KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_ENT,
    KC_LSFT,      KC_Z,  KC_X,     KC_C,     KC_V,     KC_B,    KC_GRV,    KC_QUOT,  KC_N,    KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    TT(_NUMBER),         KC_LALT,  KC_LGUI,  KC_LCTL,  KC_TAB,                       KC_SPC,  KC_RCTL,  KC_RGUI,  KC_RALT,            TT(_SYMBOL)
    ),

  /*
   * Symbol
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |   !  |   @  |   #  |   $  |   %  |      |      |   ^  |   &  |   *  |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |   `  |   (  |   [  |   -  |      |      |   =  |   ]  |   )  |   '  |   \  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |   ~  |   <  |   {  |   _  |      |      |   +  |   }  |   >  |   "  |   |  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  Alt |  GUI | Ctrl |  TAB |             | Space| Ctrl |  GUI |  Alt |      |Symbol|
   * `------+      +---------------------------+             +---------------------------+      +------'
   */
  [_SYMBOL] = LAYOUT(
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_NO,   KC_NO,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_NO,    KC_NO,    KC_NO,
    KC_NO,  KC_NO,    KC_GRV,   KC_LPRN,  KC_LBRC,  KC_MINS,  KC_NO,   KC_NO,  KC_EQL,   KC_RBRC,  KC_RPRN,  KC_QUOT,  KC_BSLS,  KC_NO,
    KC_NO,  KC_NO,    KC_TILD,  KC_LT,    KC_LCBR,  KC_UNDS,  KC_NO,   KC_NO,  KC_PLUS,  KC_RCBR,  KC_GT,    KC_DQT,   KC_PIPE,  KC_NO,
    KC_NO,            KC_TRNS,  KC_DOWN,  KC_TRNS,  KC_TRNS,                   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS
    ),

  /*
   * Number
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  1   |  2   |  3   |  4   |  5   |      |      |  6   |  7   |  8   |  9   |  0   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Number|      |  Alt |  GUI | Ctrl |  TAB |             | Space| Ctrl |  GUI |  Alt |      |      |
   * `------+      +---------------------------+             +---------------------------+      +------'
   */
  [_NUMBER] = LAYOUT(
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_P1,    KC_P2,    KC_P3,    KC_P4,    KC_P5,    KC_NO,   KC_NO,  KC_P6,    KC_P7,    KC_P8,    KC_P9,    KC_P0,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_NO
    ),

  /*
   * Config
   * |------+------+------+------+------+------.             ,------+------+------+------+------+------|
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * ,-----------------------------------------+------+------+-----------------------------------------.
   * |RESET | ADV1 | ADV2 | ADV3 | ADV4 | ADV5 |      |      | DEL1 | DEL2 | DEL3 | DEL4 | DEL5 |  SLP |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Config|      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |SELBLE|SELUSB|  DFU | BATT |AU_ON |AU_OFF|      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |  ADV |             |      |      |      |      |      |      |
   * `------+      +---------------------------+             +---------------------------+      +------'
   */
  [_CONFIG] =  LAYOUT(
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                         KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
    RESET,    ADV_ID1,  ADV_ID2,  ADV_ID3,  ADV_ID4,  ADV_ID5,  KC_NO,     KC_NO,    DEL_ID1,  DEL_ID2,  DEL_ID3,  DEL_ID4,  DEL_ID5,  ENT_SLP,
    KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    SEL_BLE,  SEL_USB,  ENT_DFU,   BATT_LV,  AU_ON,    AU_OFF,   KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_LEFT,  KC_UP,    KC_RGHT,  KC_NO,    KC_NO,
    KC_NO,              KC_NO,    KC_NO,    KC_NO,    AD_WO_L,                       KC_NO,    KC_NO,    KC_DOWN,  KC_NO,              KC_NO
    ),
};

/*
 * Custom process
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case DELBNDS:
    if (record->event.pressed)
      delete_bonds();
    break;
  case AD_WO_L:
    if (record->event.pressed)
      restart_advertising_wo_whitelist();
    break;
  case SEL_BLE:
    if (record->event.pressed) {
      set_ble_enabled(true);
      set_usb_enabled(false);
    }
    break;
  case SEL_USB:
    if (record->event.pressed) {
      set_ble_enabled(false);
      set_usb_enabled(true);
    }
    break;
  case TOG_HID:
#ifndef NRF_SEPARATE_KEYBOARD_SLAVE
    // workaround:
    // get_ble_enabled() macro(in app_ble_func.h) is incorrect.
    if (record->event.pressed) {
      bool ble = get_ble_enabled();

      set_ble_enabled(!ble);
      set_usb_enabled(ble);
    }
#endif
    break;
  case ADV_ID0:
  case ADV_ID1:
  case ADV_ID2:
  case ADV_ID3:
  case ADV_ID4:
  case ADV_ID5:
    if (record->event.pressed)
      restart_advertising_id(keycode-ADV_ID0);
    break;
  case DEL_ID0:
  case DEL_ID1:
  case DEL_ID2:
  case DEL_ID3:
  case DEL_ID4:
  case DEL_ID5:
    if (record->event.pressed)
      delete_bond_id(keycode-DEL_ID0);
    break;
  case BATT_LV:
    if (record->event.pressed) {
      char str[16];

      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
    }
    break;
  case ENT_DFU:
    if (record->event.pressed)
      bootloader_jump();
    break;
  case ENT_SLP:
    if (!record->event.pressed)
      sleep_mode_enter();
    break;

  default:
    return true;
  }

  return false;
}
