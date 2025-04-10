# Disable features we don't use to reduce firmeware size.
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
BLUETOOTH_ENABLE = no

# Compile with `flto` for smaller firmware size
LTO_ENABLE = yes

# DEBOUNCE_TYPE = sym_eager_pk
DEBOUNCE_TYPE = asym_eager_defer_pk

# QMK features
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
NKRO_ENABLE = yes
LAYER_LOCK_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
REPEAT_KEY_ENABLE = yes

SRC += $(USER_PATH)/features/swapper.c
SRC += $(USER_PATH)/chzerv.c

INTROSPECTION_KEYMAP_C = $(USER_PATH)/combos.c
