#pragma once

// Tap-hold settings
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Leader Key
#ifdef LEADER_ENABLE
#define LEADER_TIMEOUT 300
#endif

// Caps Word
#ifdef CAPS_WORD_ENABLE
// Activate Caps Word by double tapping Shift
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
// Holding Shift while Caps Word is active inverts the shift state.
#define CAPS_WORD_INVERT_ON_SHIFT
// Turn Caps Word off after 5s of idle
#define CAPS_WORD_IDLE_TIMEOUT 5000
#endif

// Combos
#ifdef COMBO_ENABLE
#   undef COMBO_TERM
#   define COMBO_TERM 35
#   define COMBO_PROCESS_KEY_REPRESS
#endif
