# Madwort's Kyria Keymap

## Concept

I want to use a Kyria for home & a Keyboardio Atreus for travel, as I've been using the Atreus for a while & I'm generally very happy with it, I just get a little finger pain after extended sessions. I already have a [layout for Atreus](https://github.com/madwort/atreus-layout/) that I'm happy with, so this layout attempts to port that layout to the Kyria and then extend it with the extra features (LEDs, encoders, etc).

## Typing layer(s)

We have two typing layers, both of which are intended for typing using the Dvorak layout:

* "QWERTY" or "OS Dvorak" - a QWERTY-based layout intended for typing Dvorak with the operating system set to the Dvorak layout. 
* "Dvorak" or "OS QWERTY" - a Dvorak-based layout intended for typing Dvorak with the operating system set to the QWERTY layout. This is useful for things like Japanese Hiragana input using the Dvorak layout. 

Therefore both layouts are intended to ultimately produce the following characters in your editing software:

```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   | ' "  | , <  | . >  |   P  |   Y  |                              |   F  |   G  |   C  |   R  |   L  |  Bksp  |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|Ctrl/Esc|   A  |   O  |   E  |   U  |   I  |                              |   D  |   H  |   T  |   N  |   S  |  Enter |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|  Esc   |LShift|   Q  |   J  |   K  |   X  |  ` ~ |      |  |VolMut|  \ | |   B  |   M  |   W  |   V  |   Z  | RShift |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |  ; : |Adjust| LGUI | Bksp | Ctrl |  | Alt  | Space|NavSym| / ?  | - _  |
                       `----------------------------------'  `----------------------------------'
```

In the "QWERTY" or "OS Dvorak" layout, this is produced by the following layout (which doesn't make much sense for actual QWERTY use):

```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  Enter |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|   Esc  |LShift|   X  |   C  |   V  |   B  |  ` ~ |      |  |VolMut|  \ | |   N  |   M  | ,  < | . >  | /  ? | RShift |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |   Z  |Adjust| LGUI | Bksp | Ctrl |  | Alt  | Space|NavSym|   [  |  '   |
                       `----------------------------------'  `----------------------------------'
```

## NavSym layer

This layer replaces the Navigation & Symbol layers on the default kyria keymap, with a layout again based on my Atreus layout. 

This only works as intended with the Operating System set to Dvorak mode. This diagram shows the layout in terms of the characters that are intended to be produced:

```
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  !   |  @   |   ↑  |   $  |      |                              | PgUp |  7   |  8   |  9   |  Del |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  (   |  ←   |   ↓  |   →  |  )   |                              | PgDn |  4   |  5   |  6   |  Tab |   =    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   NAV  |      |  ?   |   #  |   [  |  ]   |  ^   |      |  |      |   &  |   *  |  1   |  2   |  3   |  +   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |  .   |  0   |
 *                        `----------------------------------'  `----------------------------------'
```


## Navigation layer

WIP!

```
Nav Layer: Media, navigation
                                                                                                                         
,-------------------------------------------.                              ,-------------------------------------------.
|        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |  GUI |  Alt | Ctrl | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

This is where you'll find all the keys that are generally between the main block of a classic keyboard and the numpad in addition to media controls and modifiers on easy access on the home row for fast and comfortable chording with navigation keys.

Useful mnemonics:
- “GACS” to remember the order of the modifiers on the left-hand home row
- <kbd>Scroll Lock</kbd> is on the same key as <kbd>Caps Lock</kbd> because they're both locks
- <kbd>Delete</kbd> is on the same key as <kbd>Backspace</kbd> because they both erase characters
- <kbd>Home</kbd> is the leftmost position on the current line so it is above <kbd>←</kbd>. Same logic applies for <kbd>End</kbd>.
- <kbd>Media Previous</kbd> = ⏮, <kbd>Media Next</kbd> = ⏭
- <kbd>Page Up</kbd>, <kbd>Page Down</kbd> and <kbd>Volume Up</kbd>, <kbd>Volume Down</kbd> are positioned like the main <kbd>Up</kbd> and <kbd>Down</kbd> keys.

## Sym layer
```
Sym Layer: Numbers, symbols
                                                                                                                         
,-------------------------------------------.                              ,-------------------------------------------.
|    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```
The top row is the unshifted num row, the home row of the layer is the shifted num row and the bottom row contains the hyphen `-` and the underscore `_` on the best lower row spot because of how frequent they are as well as redundant symbols that are already present on the base layer but are reproduced here to avoid juggling back and forth between base, shift, and sym when typing a string of symbols.

The layout of the first two rows needs no introduction, you're already used to them but it's worth looking into the structure of the bottom row.

The two halves are mirrored in a sense. On the right, you can find <kbd>,</kbd> <kbd>.</kbd> <kbd>/</kbd> at their usual spots with the addition of <kbd>Shift</kbd>+<kbd>/</kbd>=<kbd>?</kbd> to the right of the <kbd>/</kbd> key to remove the need to press simultaneously <kbd>Sym</kbd> and a <kbd>Shift</kbd> key to access `?`. 

Now, if you look at the left side, you'll notice that the mirror of <kbd>,</kbd> is <kbd>;</kbd>, the mirror of <kbd>.</kbd> is <kbd>:</kbd> and the mirror of <kbd>/</kbd> is <kbd>\\</kbd>. The same logic used for <kbd>Shift</kbd>+<kbd>/</kbd>=<kbd>?</kbd> also applies to <kbd>Shift</kbd>+<kbd>\\</kbd>=<kbd>|</kbd>.

In case you wish to combine <kbd>Shift</kbd> with a symbol key anyways, you can hold down <kbd>Shift</kbd> on the base layer with your pinky, activate <kbd>Sym</kbd> with your right thumb and while still holding down the <kbd>Shift</kbd> key, tap your desired symbol key. Same thing if you need <kbd>Ctrl</kbd>+<kbd>Digit</kbd>.

## Function layer
```
Function Layer: Function keys
                                                                                                                         
,-------------------------------------------.                              ,-------------------------------------------.
|        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```
In a similar fashion to the nav layer, pressing down `FKEYS` with the right thumb enables a numpad of function keys on the opposite hand and modifiers on the right-hand home row. Once again, mirror symmetry is leveraged in this keymap for the order of the right-hand modifiers.

The <kbd>Alt</kbd> modifier, despite being situated on the right half of the keyboard is *not* `KC_RALT`, it is `KC_LALT`. `KC_RALT` is actually the <kbd>AltGr</kbd> key which generally acts very differently to the left <kbd>Alt</kbd> key. Keyboard shortcuts involving <kbd>AltGr</kbd>+<kbd>F#</kbd> are rare and infrequent as opposed to the much more common <kbd>Alt</kbd>+<kbd>F#</kbd> shortcuts. Consequently, `KC_LALT` was chosen for the function layer.

Since there are more than 10 function keys, the cluster of F-keys does not follow the usual 3×3+1 numpad arrangement.


## Adjust layer
```
Adjust Layer: Default layer settings, RGB
                                                                                                                         
,-------------------------------------------.                              ,-------------------------------------------.
|        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |      |      |Dvorak|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |      |      |      |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

Default layer settings on the left and various RGB underglow controls on the right.

The default layer settings are lined up on the middle finger column because the home middle finger key is <kbd>D</kbd> on QWERTY (like the “D” in “Dvorak”) and the lower middle finger key is <kbd>C</kbd> on QWERTY (like the “C” in “Colemak”). I can hear you say that “QWERTY” doesn't start with “E” but Dvorak and Colemak were already aligned in a column so the QWERTY may as well join the formation.

NOTE: The default layer settings set by those keys are *NOT* stored in EEPROM and thus do not persist through boots. If you wish to change the default layer in a non-volatile manner, either change the order of the layers in the firmware, for example like so if you want to set Dvorak as the new default:
```c
enum layers {
    _DVORAK = 0,
    _QWERTY,
    _NAV,
    _SYM,
    _NAVSYM,
    _FUNCTION,
    _ADJUST
};
```
or re-define the `QWERTY` and `DVORAK` keys to point to custom keycodes starting on `SAFE_RANGE` and calling the `set_single_persistent_default_layer` function inside of `process_record_user`.

## Hardware Features

### Rotary Encoder
The right rotary encoder is programmed to control the volume whereas the left encoder sends <kbd>PgUp</kbd> or <kbd>PgDn</kbd> on every turn.

TODO: more stuff on the left rotary

* display brightness
* pgup/pgdn
* word right/left
* ...?

Can we use the button press to rotate through these?

### OLEDs
The OLEDs display the current layer at the top of the active layers stack, the Kyria logo and lock status (caps lock, num lock, scroll lock).

The config parameters are tweaked to better suit the particular OLED displays that I have.

## Compiling

Note to self:

```bash
qmk compile -e CONVERT_TO=promicro_rp2040 -kb splitkb/kyria/rev3 -km madwort
```
