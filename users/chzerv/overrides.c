/**
  * Key Overrides (https://docs.qmk.fm/features/key_overrides)
  **/
const key_override_t coln_override = ko_make_basic(MOD_MASK_SHIFT, KC_COLN, KC_SCLN);
const key_override_t delete_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&coln_override,
    &delete_override
};

