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
    GAMING,
    M_ION,
    M_OU,
};


/**
 * Aliases for complex keys, mainly for improving readability.
 **/

// One Shot Modifiers.
#define OSM_LS OSM(MOD_LSFT)
#define OSM_S OSM(MOD_LSFT)
#define OSM_C OSM(MOD_LCTL)
#define OSM_A OSM(MOD_LALT)
#define OSM_G OSM(MOD_LGUI)

#define TAB_NAV LT(_NAV, KC_TAB) // 'Tab' when tapped, 'MO(_NAV)' when held
#define ENT_NUM LT(_NUM, KC_ENT) // 'Enter' when tapped, 'MO(_NUM)' when held
#define BSP_CTL LCTL_T(KC_BSPC)  // 'Backspace' when tapped, 'Control' when held
#define LT_REP LT(_SYM, KC_0)  // 'Backspace' when tapped, 'Control' when held

#define REDO C(S(KC_Z))

// Navigating browser tabs
#define TAB_PR C(S(KC_TAB))
#define TAB_NX C(KC_TAB)
#define TAB_CL C(KC_W)

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LSFT_T(KC_S)
#define HOME_T LCTL_T(KC_T)

// Right-hand home row mods
#define HOME_N RCTL_T(KC_N)
#define HOME_E RSFT_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)
