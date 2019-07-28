
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "claw44.h"

#define L_DEFAULT 0
#define L_SYMBOL (1<<_SYMBOL)
#define L_NUMBER (1<<_NUMBER)
#define L_FUNCTION (1<<_FUNCTION)

char layer_state_str[24];

const char *read_layer_state(void) {
    switch (layer_state)
    {
    case L_DEFAULT:
        snprintf(layer_state_str, sizeof(layer_state_str), "       Default");
        break;
    case L_SYMBOL:
        snprintf(layer_state_str, sizeof(layer_state_str), "       Symbol");
        break;
    case L_NUMBER:
        snprintf(layer_state_str, sizeof(layer_state_str), "       Number");
        break;
    case L_FUNCTION:
        snprintf(layer_state_str, sizeof(layer_state_str), "       Function");
        break;
    default:
        snprintf(layer_state_str, sizeof(layer_state_str), "    Undef-%ld", layer_state);
    }

    return layer_state_str;
}
