# QMK Keymap for the Keebio Iris CE

This is a valid [QMK userspace](https://docs.qmk.fm/newbs_external_userspace) repository, containing my keymap for the Iris CE.

## Features

-   Favors comfort over speed
-   Home Row Modifiers enhanced via [Chordal Hold](https://github.com/qmk/qmk_firmware/pull/24560/)
-   Utilizes [combos](https://docs.qmk.fm/features/combo) to output hard to reach keys, e.g., `:`, `'`, `Ctrl-Z`, `Alt-Tab`, `Escape` and more.
-   Utilizes [key overrides](https://docs.qmk.fm/features/key_overrides) to change what actions shifted keys perform. For example:
    -   `Shift + :` outputs `;`.
    -   `Shift + Bspc` outputs `Delete`.
-   Utilizes [Caps Word](https://docs.qmk.fm/features/caps_word), [Sentence Case](https://getreuer.info/posts/keyboards/sentence-case/index.html) and a Shift key on the thumb cluster to reduce finger stretches when capitalizing words/letters.
-   Symbol layer that favors Vim navigation, inspired by [sunaku's awesome symbol layer](https://sunaku.github.io/moergo-glove80-keyboard.html#symbol-layer).
-   Navigation layer inspired by the awesome [Extend layer](https://dreymar.colemak.org/layers-extend.html), which contains stuff like:
    -   Home/End,
    -   PageUp/PageDown,
    -   Vim-like arrows,
    -   Shortcuts for navigating workspaces,
    -   Shortcuts for Copy/Paste/Undo,
    -   One-shot modifiers,
    -   and more..

## Setup

1. You need a properly setup QMK environment:

    ```bash
    git clone https://github.com/qmk/qmk_firmware --recurse-submodules --shallow-submodules
    cd qmk_firmware
    qmk setup
    ```

2. Switch to the `develop` branch so [Chordal Hold](https://github.com/qmk/qmk_firmware/pull/24560) is available:

    ```bash
    cd qmk_firmware
    git chechout develop && git pull
    ```

3. Clone this repository and set it as an overlay:

    ```bash
    git clone https://github.com/chzerv/qmk_userspace

    qmk config user.overlay_dir="$(realpath qmk_userspace)"
    ```

4. Compile and flash the firmware:

    ```bash
    cd qmk_userspace
    qmk compile
    qmk flash
    ```

# Acknowledgments

-   [sunaku's configuration](https://sunaku.github.io/moergo-glove80-keyboard.html)
-   [Pascal Getreuer's keymap](https://github.com/getreuer/qmk-keymap)
-   [Jonas Hietala's T-34 layout](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/)
