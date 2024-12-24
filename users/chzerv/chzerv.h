#pragma once

#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY,
    _COLEMAK,
    _NAV,
    _SYM,
    _NUM,
    _FUN,
};
/**
 * Custom keys
 */
enum custom_keycodes {
    UPDIR = SAFE_RANGE,
    USRNAME,
    LITERAL,
    SRCHSEL,
    SW_WIN,
    SW_LANG,
    QWERTY,
    COLEMAK,
    OSM_G,
    OSM_A,
    OSM_S,
    OSM_C,
};


/**
 * Aliases for complex keys, mainly for improving readability.
 **/

// One Shot Modifiers.
#define OSM_LS OSM(MOD_LSFT)

#define TAB_NAV LT(_NAV, KC_TAB) // 'Tab' when tapped, 'MO(_NAV)' when held
#define ENT_NUM LT(_NUM, KC_ENT) // 'Enter' when tapped, 'MO(_NUM)' when held
#define BSP_CTL LCTL_T(KC_BSPC)  // 'Backspace' when tapped, 'Control' when held

#define REDO C(S(KC_Z))

// Navigating browser tabs
#define TAB_PR C(S(KC_TAB))
#define TAB_NX C(KC_TAB)
#define TAB_CL C(KC_W)
