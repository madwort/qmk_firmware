/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _DVORAK,
    _NAV,
    _NAVSYM,
    _FUNCTION,
    _ADJUST,
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define DVORAK   DF(_DVORAK)
#define DF_NAV   DF(_NAV)

#define NAV      MO(_NAV)
#define NAVSYM   MO(_NAVSYM)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY (for OS Dvorak)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  Enter |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   Esc  |LShift|   X  |   C  |   V  |   B  |  ` ~ |      |  |VolMut|  \ | |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |   Z  |Adjust| LGUI | Bksp | Ctrl |  | Alt  | Space|NavSym|   [  |  '   |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
     CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN, KC_ENTER,
     KC_ESCAPE , KC_LSFT , KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_GRAVE,  _______,   KC_MUTE  , KC_BACKSLASH, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                KC_Z , ADJUST, KC_LGUI, KC_BSPC , KC_LEFT_CTRL,     KC_LALT    , KC_SPC , NAVSYM, KC_LEFT_BRACKET, KC_QUOTE
    ),

/*
 * Base Layer: Dvorak (for OS QWERTY)
 * TODO: check this for bugs!
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   | ' "  | , <  | . >  |   P  |   Y  |                              |   F  |   G  |   C  |   R  |   L  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   O  |   E  |   U  |   I  |                              |   D  |   H  |   T  |   N  |   S  |  Enter |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  Esc   |LShift|   Q  |   J  |   K  |   X  |  ` ~ |      |  |VolMut|  \ | |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  ; : |Adjust| LGUI | Bksp | Ctrl |  | Alt  | Space|NavSym| / ?  | - _  |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_DVORAK] = LAYOUT(
     KC_TAB  ,KC_QUOTE,KC_COMM,  KC_DOT,   KC_P ,   KC_Y ,                                        KC_F,   KC_G ,  KC_C ,   KC_R ,  KC_L , KC_BSPC,
     CTL_ESC , KC_A ,  KC_O   ,  KC_E  ,   KC_U ,   KC_I ,                                        KC_D,   KC_H ,  KC_T ,   KC_N ,  KC_S , KC_ENTER,
     KC_ESCAPE ,KC_LSFT, KC_Q   ,  KC_J  ,   KC_K ,   KC_X , KC_GRAVE,_______,     KC_MUTE , KC_BACKSLASH, KC_B,   KC_M ,  KC_W ,   KC_V ,  KC_Z , KC_RSFT,
                                 KC_SCLN, ADJUST, KC_LGUI, KC_BSPC , KC_LEFT_CTRL,     KC_LALT  , KC_SPC , NAVSYM, KC_SLSH, KC_MINS
    ),

/*
 * Nav Layer: Media, navigation
 * TODO: not sure about the QWERTY move here!
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| M Play |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | QWERTY|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_MPLY,
      _______, _______, _______, _______, _______, _______, _______, KC_SCRL, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______,  QWERTY, _______, _______
    ),

/*
 * NavSym Layer: Arrows & Numbers & symbols (just like my Atreus!)
 *
 * NB. THIS IS INTENDED OUTPUT, NOT CHAR CODES!
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  !   |  @   |   ↑  |   $  |      |                              | PgUp |  7   |  8   |  9   |  Del |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  (   |  ←   |   ↓  |   →  |  )   |                              | PgDn |  4   |  5   |  6   |  Tab |   =    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   NAV  |      |  ?   |   #  |   [  |  ]   |  ^   |      |  |      |   &  |   *  |  1   |  2   |  3   |  +   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |  .   |  0   |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAVSYM] = LAYOUT(
      KC_GRV , KC_EXLM, KC_AT  ,  KC_UP ,   KC_DLR,   _______,                                     KC_PGUP,   KC_7 ,  KC_8 , KC_9, KC_DEL, _______,
     KC_TILD , KC_LPRN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_RPRN,                                     KC_PGDN,   KC_4 ,  KC_5 , KC_6, KC_TAB, KC_RBRC,
      DF_NAV , _______, KC_LCBR, KC_HASH, KC_MINS, KC_EQUAL, KC_CIRC, _______, _______, KC_AMPR, KC_ASTR,   KC_1 ,  KC_2 , KC_3, KC_RCBR, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______,  KC_PDOT, KC_0
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |Dvorak|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |  NAV |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, QWERTY , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, DVORAK , _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, DF_NAV , _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("OS Dvorak\n"), false);
                break;
            case _DVORAK:
                oled_write_P(PSTR("OS QWERTY\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _NAVSYM:
                oled_write_P(PSTR("NavSym\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // static const char PROGMEM epd_bitmap_mdwrt_logo [] = {
        //   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3c, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xf9, 0xff, 0xe7, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xfd, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xfd, 0xff, 0x9f, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xfd, 0xff, 0x3f, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xfd, 0xfe, 0x7f, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xf3, 0xfd, 0xfc, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xc3, 0xf9, 0xf9, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0x9f, 0xf9, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xbf, 0xf9, 0xf3, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xbf, 0xf9, 0xc7, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xbf, 0xf9, 0x8f, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0x9f, 0xf4, 0x1f, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xfd, 0x9f, 0xf0, 0x7f, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xfc, 0x1e, 0xcf, 0x80, 0x7f, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xfb, 0xfe,
        //   0xf0, 0x02, 0xe0, 0x07, 0x1f, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xf3, 0xfe,
        //   0xff, 0xe0, 0x40, 0x73, 0x8e, 0x1f, 0xff, 0xf4, 0x9c, 0x3f, 0x06, 0xfd, 0xe3, 0xec, 0x60, 0x7e,
        //   0xff, 0xc4, 0x13, 0xf1, 0xc2, 0x27, 0xff, 0xf0, 0x0c, 0x1e, 0x06, 0x6d, 0x81, 0xc0, 0x60, 0x7e,
        //   0xff, 0xf0, 0x01, 0xc0, 0xe0, 0x3f, 0xff, 0xf6, 0xcf, 0xcc, 0xe6, 0x4d, 0x99, 0xe2, 0x73, 0xfe,
        //   0xff, 0xf8, 0x00, 0x80, 0x40, 0x1f, 0xff, 0xf6, 0xcf, 0xcc, 0xe6, 0x49, 0x3c, 0xe7, 0xf3, 0xfe,
        //   0xff, 0xf8, 0x40, 0x80, 0x00, 0x1f, 0xff, 0xf6, 0xcc, 0x0c, 0xe6, 0x41, 0x3c, 0xe7, 0xf3, 0xfe,
        //   0xff, 0xf8, 0x50, 0x3c, 0x04, 0x0f, 0xff, 0xf6, 0xc9, 0xcc, 0xe6, 0x01, 0x3c, 0xe7, 0xf3, 0xfe,
        //   0xff, 0xf0, 0x40, 0x3c, 0x0f, 0x0f, 0xff, 0xf6, 0xc9, 0xcc, 0xe7, 0x11, 0x99, 0xe7, 0xfb, 0xfe,
        //   0xff, 0xf0, 0x68, 0x3c, 0x1f, 0x0f, 0xff, 0xf6, 0xc8, 0x0e, 0x07, 0x33, 0x81, 0xc1, 0xf8, 0x3e,
        //   0xff, 0xf0, 0x60, 0x3c, 0x1d, 0x87, 0xff, 0xf6, 0xdc, 0x6f, 0x37, 0x33, 0xc3, 0xe3, 0xfc, 0x7e,
        //   0xff, 0xf0, 0xe0, 0x38, 0x23, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xf0, 0x68, 0x38, 0x37, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xf0, 0x60, 0x38, 0x3f, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xf0, 0x64, 0x78, 0x37, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xf0, 0x64, 0x7a, 0x32, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xf0, 0x70, 0x78, 0x1a, 0x0b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xfe,
        //   0xff, 0xf8, 0x60, 0x78, 0x03, 0x0d, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xfe,
        //   0xff, 0xf8, 0x30, 0x3c, 0x46, 0x04, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xfc, 0x38, 0x3e, 0x3c, 0x06, 0x7f, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xfc, 0x1e, 0x0e, 0x3c, 0x63, 0x3f, 0xff, 0xfd, 0xcc, 0xf3, 0x11, 0x87, 0xc0, 0xff, 0xfe,
        //   0xff, 0xfe, 0x0e, 0x4f, 0x38, 0xe1, 0x3f, 0xff, 0xfd, 0x9c, 0xe7, 0x89, 0xe7, 0xfc, 0xff, 0xfe,
        //   0xff, 0xff, 0x07, 0x3f, 0x99, 0xf0, 0x7f, 0xff, 0xfd, 0x3e, 0x67, 0x9b, 0xe7, 0xfc, 0xff, 0xfe,
        //   0xff, 0xff, 0x03, 0x1f, 0xc3, 0xfe, 0x0f, 0xff, 0xfc, 0x3e, 0x67, 0x9f, 0xe7, 0xe0, 0xff, 0xfe,
        //   0xff, 0xfd, 0x60, 0x9f, 0xe3, 0xfc, 0x83, 0xff, 0xfd, 0x3e, 0x4f, 0x9f, 0xe7, 0xcc, 0xff, 0xfe,
        //   0xff, 0xf9, 0x70, 0x1f, 0xf0, 0xfd, 0xf1, 0xff, 0xfd, 0x9f, 0x0f, 0x9f, 0xe7, 0xcc, 0xff, 0xfe,
        //   0xff, 0xfc, 0x7c, 0x03, 0xf4, 0x7d, 0xf9, 0xff, 0xfd, 0xcf, 0x1f, 0x9f, 0xe3, 0xcc, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0x00, 0xf7, 0x3e, 0xf9, 0xff, 0xfd, 0xc7, 0x1f, 0x07, 0x80, 0xc0, 0x7f, 0xfe,
        //   0xff, 0xff, 0xff, 0xe0, 0x37, 0x9f, 0xfd, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xf3, 0x07, 0xcf, 0xfc, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xf3, 0xc3, 0xef, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xf9, 0xf1, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xfc, 0xf8, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xfc, 0x7e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xfe, 0x3e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0x8f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0xe3, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xfe, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xfe, 0x7c, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0x38, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0x81, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        //   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe
        // };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
      switch (get_highest_layer(layer_state|default_layer_state)) {
          case _QWERTY:
          case _FUNCTION:
          case _ADJUST:
          case _DVORAK:
          case _NAV:
              // // Page up/Page down
              // if (clockwise) {
              //     tap_code(KC_PGDN);
              // } else {
              //     tap_code(KC_PGUP);
              // }
              // Mouse wheel up/down
              if (clockwise) {
                  tap_code(KC_MS_WH_DOWN);
              } else {
                  tap_code(KC_MS_WH_UP);
              }
              break;
          case _NAVSYM:
          if (clockwise) {
                  tap_code16(LALT(KC_RIGHT));
              } else {
                  tap_code16(LALT(KC_LEFT));
              }
              break;
      }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
            case _FUNCTION:
            case _ADJUST:
            case _DVORAK:
            case _NAV:
                // Volume control
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case _NAVSYM:
            if (clockwise) {
                    tap_code(KC_BRIGHTNESS_UP);
                } else {
                    tap_code(KC_BRIGHTNESS_DOWN);
                }
                break;
        }
    }
    return false;
}
#endif

void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}

void keyboard_post_init_user(void) {
    // Initialize RGB to static black
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_BLACK);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

void housekeeping_task_user(void) {
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _QWERTY:
            rgblight_setrgb_at(RGB_OFF, 0);
            break;
        case _DVORAK:
            // pale orange
            rgblight_setrgb_at(0x10, 0x08, 0x00, 0);
            break;
        case _NAV:
            // pale yellow
            rgblight_setrgb_at(0x10, 0x10, 0x00, 0);
            break;
        case _NAVSYM:
            // pale green
            rgblight_setrgb_at(0x00, 0x10, 0x00, 0);
            break;
        case _FUNCTION:
            rgblight_setrgb_at(RGB_WHITE, 0);
            break;
        case _ADJUST:
            // pale purple
            rgblight_setrgb_at(0x08, 0x00, 0x10, 0);
            break;
    }
}
