
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"

// in the future, should use (1U<<_LAYER_NAME) instead, but needs to be moved to keymap,c
#define L_DEFAULT 0
#define L_SYMBOL (1<<_SYMBOL)
#define L_NUMBER (1<<_NUMBER)
#define L_FUNCTION (1<<_FUNCTION)

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
