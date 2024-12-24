/**
  This is a custom one shot implementation, provided by Exidex (https://github.com/Exidex/qmk_firmware/tree/custom/keyboards/beekeeb/piantor_pro).
  I've made some tweaks to it so that
    1. it doesn't use a separate layer for modifier keys, but instead, it uses my existing navigation layer
    2. it works better when the key that switches to the layer that contains the modifiers is an LT key

  More information can be found on Exidex' repository, linked above.
  **/
#pragma once

#include QMK_KEYBOARD_H

typedef enum {
    osl_up_unqueued, // default, waiting for layer to be pressed
    osl_up_queued, // layer pressed and released without pressing mod key, next modifier press will have layer enabled, on all mod release layer will be disabled
    osl_up_pending_used, // layer was pressed but released when some mods were still held, on all mod release layer will be disabled
    osl_down_unused, // layer pressed and held, all mod presses will have layer enabled, until all mods are released
    osl_down_pending_used, // layer pressed and held, some mods are still pressed
    osl_down_used, // mods were pressed but layer is still held, on layer release layer will be disabled
} oneshot_layer_state;

typedef enum {
    osm_up_unqueued, // default, waiting for mod to be pressed
    osm_down_unused, // mod pressed and held, all other presses will be with this modifier enabled, until mod released
    osm_down_used, // other key pressed while mod is held, on mod release modifier will be disabled
    osm_up_queued, // mod pressed and released without pressing other key, next press will have modifier enabled
    osm_up_queued_with_layer, // other key pressed abd released while layer and mod are active, next presses will have modifier enabled until layer is released
} oneshot_mod_state;

void update_oneshot_mod(
    oneshot_layer_state *layer_state,
    oneshot_mod_state *mod_state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
);

void update_oneshot_layer(
    oneshot_layer_state *layer_state,
    oneshot_mod_state *shift_state,
    oneshot_mod_state *ctrl_state,
    oneshot_mod_state *alt_state,
    oneshot_mod_state *gui_state,
    uint16_t trigger,
    uint16_t layer,
    uint16_t keycode,
    keyrecord_t *record
);

// Defines keys to cancel oneshot mods.
bool is_oneshot_cancel_key(uint16_t keycode);

//  Defines keys to ignore when determining whether a oneshot mod has been used.
// Setting this to modifiers and layer change keys allows stacking multiple
// oneshot modifiers, and carrying them between layers.
bool is_oneshot_ignored_key(uint16_t keycode);

bool is_oneshot_mod_key(uint16_t keycode);

#define CUSTOM_ONE_SHOT_MOD_GET_MODS(kc) ((kc)&0x1F)
