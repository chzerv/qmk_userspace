#include "features/sentence_case.h"
#include "features/swapper.h"
#include "features/oneshot.h"
#include "chzerv.h"

// Holding the `_NAV` and `_SYM` keys simultaneously activates the `_FUN` layer.
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _FUN);
}

// When a dual function thumb key + another key is pressed, use the hold action.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TAB_NAV:
        case MO(_SYM):
        case ENT_NUM:
            return true;
        default:
            return false;
    }
}

// Custom One Shot Modifiers
oneshot_mod_state osm_shift_state = osm_up_unqueued;
oneshot_mod_state osm_ctrl_state = osm_up_unqueued;
oneshot_mod_state osm_alt_state = osm_up_unqueued;
oneshot_mod_state osm_gui_state = osm_up_unqueued;
oneshot_layer_state osl_mod_state = osl_up_unqueued;

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case MO(_SYM):
        case KC_ESC:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case TAB_NAV:
        case OSM_S:
        case OSM_C:
        case OSM_A:
        case OSM_G:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_mod_key(uint16_t keycode) {
    switch (keycode) {
        case OSM_S:
        case OSM_C:
        case OSM_A:
        case OSM_G:
            return true;
        default:
            return false;
    }
}
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

/**
 * Leader Key (https://docs.qmk.fm/features/leader_key)
 **/
void leader_end_user(void) {
    if (leader_sequence_one_key(KC_V)) { // Vim vertical split
        tap_code16(C(KC_W));
        tap_code(KC_V);
    } else if (leader_sequence_one_key(KC_S)) { // Vim horizontal split
        tap_code16(C(KC_W));
        tap_code(KC_S);
    } else if (leader_sequence_one_key(KC_Q)) { // Quit Vim
        tap_code(KC_ESC);
        tap_code16(KC_COLN);
        tap_code(KC_Q);
        tap_code(KC_ENT);
    } else if (leader_sequence_two_keys(KC_Q, KC_Q)) { // Force quit Vim
        tap_code(KC_ESC);
        tap_code16(KC_COLN);
        tap_code(KC_Q);
        tap_code16(KC_EXLM);
        tap_code(KC_ENT);
    } else if (leader_sequence_one_key(KC_W)) { // Save buffer in Vim
        tap_code(KC_ESC);
        tap_code16(KC_COLN);
        tap_code(KC_W);
        tap_code(KC_ENT);
    } else if (leader_sequence_one_key(KC_X)) { // Save buffer and exit Vim
        tap_code(KC_ESC);
        tap_code16(KC_COLN);
        tap_code(KC_X);
        tap_code(KC_ENT);
    } else if (leader_sequence_one_key(KC_C)) { // Toggle Caps Lock
        tap_code(KC_CAPS);
    }
}

/////////////////////////////////////////////////////////////////////////////

// Needed for swapper
bool sw_win_active = false;
bool sw_lang_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

    update_oneshot_mod(
            &osl_mod_state,
            &osm_shift_state,
            KC_LSFT,
            OSM_S,
            keycode,
            record
            );

    update_oneshot_mod(
            &osl_mod_state,
            &osm_ctrl_state,
            KC_LCTL,
            OSM_C,
            keycode,
            record
            );

    update_oneshot_mod(
            &osl_mod_state,
            &osm_alt_state,
            KC_LALT,
            OSM_A,
            keycode,
            record
            );

    update_oneshot_mod(
            &osl_mod_state,
            &osm_gui_state,
            KC_LGUI,
            OSM_G,
            keycode,
            record
            );

    update_oneshot_mod(
            &osl_mod_state,
            &osm_gui_state,
            KC_LSFT | KC_LCTL,
            OSM_G,
            keycode,
            record
            );


    update_oneshot_layer(
            &osl_mod_state,
            &osm_shift_state,
            &osm_ctrl_state,
            &osm_alt_state,
            &osm_gui_state,
            TAB_NAV,
            _NAV,
            keycode,
            record
            );
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

    if (!process_sentence_case(keycode, record)) { return false; }

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
        }
    }

    return true;
}
