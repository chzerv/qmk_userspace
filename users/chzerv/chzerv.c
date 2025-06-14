#include "features/swapper.h"
#include "chzerv.h"

// Holding the `_NAV` and `_SYM` keys simultaneously activates the `_FUN` layer.
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _FUN);
}

// Increase the TAPPING_TERM for pinky keys.
// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
//   switch (keycode) {
//     case HOME_A:
//     case HOME_O:
//     case HOME_I:
//       return TAPPING_TERM + 50;
//     default:
//       return TAPPING_TERM;
//   }
// }

// When a dual function thumb key + another key is pressed, use the hold action.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TAB_NAV:
        case ENT_NUM:
        case LT_AREP:
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TAB_NAV:
        case ENT_NUM:
        case LT_AREP:
            return false;
        default:
            return true;
    }
}

// Disable key repeating unless its for Vim navigation.
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case HOME_N:
            return QUICK_TAP_TERM;
        default:
            return 0;
    }
}

// bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
//         uint16_t other_keycode, keyrecord_t* other_record) {
//     // Allow one handed chords when Layer Taps are involved.
//     switch (tap_hold_keycode) {
//         case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
//             return true;
//     }
//
//     // Otherwise defer to the opposite hands rule.
//     return get_chordal_hold_default(tap_hold_record, other_record);
// }

/**
 * Caps word (https://docs.qmk.fm/features/caps_word)
 **/
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

            // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_LPRN:
            return true;

        default:
            return false;
    }
}

/*
 * Repeat (https://docs.qmk.fm/features/repeat_key)
 **/
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
        uint8_t* remembered_mods) {
    if (keycode == LT_AREP) { return false; }
    return true;
}

// "Magic key", inspired by https://github.com/getreuer/qmk-keymap
// Also see: https://getreuer.info/posts/keyboards/alt-layouts/index.html#magic-sturdy
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if ((mods & MOD_MASK_CTRL)) {
        switch (keycode) {
            case HOME_A: return C(KC_E); // Ctrl+A -> Ctrl+E (shell navigation)
            case KC_E: return C(KC_A);   // Ctrl+E -> Ctrl+A (shell navigation)
            case KC_C: return C(KC_V);   // Ctrl+C -> Ctrl+V
        }
    } else if ((mods & ~MOD_MASK_SHIFT) == 0) {
        switch (keycode) {
            case HOME_N:
                if ((mods & MOD_MASK_SHIFT) == 0) {
                    return S(KC_N);
                }
            case KC_N: return KC_N;
            case KC_Y: return M_OU;
            case KC_L: return M_LK;
            case KC_M: return M_MENT;
            case KC_C: return M_ON;
            case TAB_NX: return TAB_PR;
            case TAB_PR: return TAB_NX;
            case HOME_I:
                if ((mods & MOD_MASK_SHIFT) == 0) {
                    return M_ION;
                } else {
                    return KC_QUOT;
                }
        }
    }

    return KC_TRNS;
}

/////////////////////////////////////////////////////////////////////////////

// Needed for swapper
bool sw_win_active = false;
bool sw_lang_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

    // Switch windows.
    update_swapper(
            &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
            keycode, record
            );

    // Switch input language.
    update_swapper(
            &sw_lang_active, KC_LGUI, KC_SPC, SW_LANG,
            keycode, record
            );

    // Dual function alt-repeat key.
    switch (keycode) {
        case LT_AREP:
            if (record->tap.count) {
                alt_repeat_key_invoke(&record->event);
                return false;
            }
            break;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case QWERTY:
                set_single_persistent_default_layer(_QWERTY);
                return false;

            case COLEMAK:
                set_single_persistent_default_layer(_COLEMAK);
                return false;

            case UPDIR:
                SEND_STRING("../");
                return false;

            case USRNAME:
                SEND_STRING("chzerv");
                return false;

            case LITERAL:
                SEND_STRING("\"${}\""SS_TAP(X_LEFT)SS_TAP(X_LEFT));
                return false;

            case SRCHSEL:
                SEND_STRING(SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER));
                return false;

            case M_ION:
                SEND_STRING(/*i*/"on");
                return false;

            case M_OU:
                SEND_STRING(/*y*/"ou");
                return false;

            case M_LK:
                SEND_STRING(/*l*/"k");
                return false;

            case M_MENT:
                SEND_STRING(/*m*/"ent");
                return false;

            case M_ON:
                SEND_STRING(/*c*/"on");
                return false;
        }
    }

    return true;
}
