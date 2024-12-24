enum combos {
    ESC_COMBO,
    ALT_TAB_COMBO,
    CAPS_WORD_COMBO,
    QUOT_COMBO,
    COLN_COMBO,
    BG_FG_COMBO,
};


const uint16_t PROGMEM esc_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM cw_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM alt_tab_combo[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM quot_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM coln_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM fg_combo[] = {KC_T, KC_G, COMBO_END};

combo_t key_combos[] = {
    [ESC_COMBO] = COMBO(esc_combo, KC_ESC),
    [ALT_TAB_COMBO] = COMBO(alt_tab_combo, KC_NO),
    [CAPS_WORD_COMBO] = COMBO(cw_combo, CW_TOGG),
    [QUOT_COMBO] = COMBO(quot_combo, KC_QUOT),
    [COLN_COMBO] = COMBO(coln_combo, KC_COLN),
    [BG_FG_COMBO] = COMBO(fg_combo, C(KC_Z)),
};

/** Repress-able combos
  * https://docs.qmk.fm/features/combo#customizable-key-repress
  **/
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case ALT_TAB_COMBO:
            if (pressed) {
                register_mods(MOD_LALT);
                tap_code(KC_TAB);
            } else {
                unregister_mods(MOD_LALT);
            }
            break;
    }
}

bool process_combo_key_repress(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    switch (combo_index) {
        case ALT_TAB_COMBO:
            switch (keycode) {
                case KC_S:
                    tap_code16(S(KC_TAB));
                    return true;
                case KC_T:
                    tap_code(KC_TAB);
                    return true;
            }
    }
    return false;
}
