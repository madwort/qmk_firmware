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
#include "raw_hid.h"


// Assume Dvorak layout for any use of SEND_STRING
#include "sendstring_dvorak.h"

enum layers {
    _QWERTY = 0,
    _DVORAK,
    _NAV,
    _NAVSYM,
    _NAVSYMR,
    _FUNCTION,
    _ADJUST,
    _MOUSEKE,
};

enum madwort_keycodes {
  SS_HELLO = SAFE_RANGE,
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define DVORAK   DF(_DVORAK)
#define DF_NAV   DF(_NAV)
#define NAVSYMR  DF(_NAVSYMR)
// TODO: better name for MOUSEKE!!
#define MOUSEKE  DF(_MOUSEKE)

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
 * | M Play |      |      |   ↑  |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | CapsLk |      |  ←   |   ↓  |   →  |      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| M Play |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | QWERTY|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      KC_MPLY, _______, _______, KC_UP  , _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
      KC_CAPS, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_MPLY,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, _______, KC_SCRL, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______,  QWERTY, _______, _______
    ),

/*
 * NavSym Layer: Arrows & Numbers & symbols (just like my Atreus!)
 *
 * NB. THIS IS INTENDED OUTPUT, NOT CHAR CODES!
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  !   |  @   |   ↑  |   $  |  Hi  |                              | PgUp |  7   |  8   |  9   |  Del |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  (   |  ←   |   ↓  |   →  |  )   |                              | PgDn |  4   |  5   |  6   |  Tab |   =    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   NAV  |      |  ?   |   #  |   [  |  ]   |  ^   |      |  |      |   &  |   *  |  1   |  2   |  3   |  +   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |  .   |  0   |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAVSYM] = LAYOUT(
      KC_GRV , KC_EXLM, KC_AT  ,  KC_UP ,   KC_DLR,   SS_HELLO,                                  KC_PGUP,   KC_7 ,  KC_8 , KC_9, KC_DEL, _______,
     KC_TILD , KC_LPRN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_RPRN,                                     KC_PGDN,   KC_4 ,  KC_5 , KC_6, KC_TAB, KC_RBRC,
      DF_NAV , _______, KC_LCBR, KC_HASH, KC_MINS, KC_EQUAL, KC_CIRC, _______, _______, KC_AMPR, KC_ASTR,   KC_1 ,  KC_2 , KC_3, KC_RCBR, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______,  KC_PDOT, KC_0
    ),

/*
 * NavSymR Layer: Arrows on the right hand!
 *
 * NB. THIS IS INTENDED OUTPUT, NOT CHAR CODES!
 * TODO: maybe put the arrow keys on *both* sides?
 * TODO: fix the mousewheel scroll encoder for this layout 
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp |      |   ↑  |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | PgDn |  ←   |   ↓  |   →  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAVSYMR] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PGUP, _______, KC_UP  , _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
 * |        |      |MOUSKE|QWERTY|NAVSYMR|      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |Dvorak|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  NAV   |      |      |  NAV |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, MOUSEKE, QWERTY , NAVSYMR, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, DVORAK , _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
       DF_NAV, _______, _______, DF_NAV , _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),


  [_MOUSEKE] = LAYOUT(
    _______, _______, MOUSEKE, _______ , _______, _______,                                    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______ , _______, _______,                                    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______ , _______, _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,_______, KC_MS_BTN2, KC_MS_BTN1, _______, NAVSYM, _______, _______
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

char hidoutput[16] = "";

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
        // oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

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
            case _NAVSYMR:
                oled_write_P(PSTR("NavSym RHS\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            case _MOUSEKE:
                oled_write_P(PSTR("Mouse\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
        // maybe truncate hidoutput to oled_max_chars()
        oled_write(hidoutput, false);

    } else {
        // clang-format off
        // static const char PROGMEM kyria_logo[] = {
        //     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //     0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //     0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //     0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        //     0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        //     0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //     0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        // };
      // 'mdwrt-logo2', 128x64px
      const char epd_bitmap_mdwrt_logo [] PROGMEM = {
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xe0, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x60, 0x30, 0x18, 0x0c, 0x0c, 
      	0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x06, 0x06, 0x0c, 0x18, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0xf0, 0x18, 0x08, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xff, 0x00, 
      	0x00, 0x80, 0xc0, 0xc0, 0x60, 0x38, 0x1c, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0c, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x38, 0x78, 0xd8, 0xf0, 0xfc, 
      	0xf0, 0xe3, 0xf7, 0xdc, 0xf8, 0xf8, 0xd8, 0x98, 0x18, 0x8c, 0x8c, 0xcc, 0xfe, 0xf6, 0xc7, 0xc7, 
      	0x8f, 0x19, 0xb9, 0xf0, 0xe0, 0xe0, 0xc0, 0xf0, 0xf0, 0xf8, 0x18, 0x2c, 0x06, 0x03, 0x01, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x20, 0x30, 0xf0, 
      	0x20, 0x30, 0xf0, 0xc0, 0x00, 0x00, 0x20, 0x30, 0x30, 0x30, 0xe0, 0xc0, 0x00, 0x00, 0xc0, 0xe0, 
      	0x30, 0x30, 0x30, 0xfe, 0xfe, 0x00, 0x00, 0xf0, 0xe0, 0x00, 0xc0, 0xe0, 0x00, 0x80, 0xf0, 0x00, 
      	0x80, 0xe0, 0x60, 0x30, 0x30, 0x30, 0xe0, 0x80, 0x00, 0x00, 0x20, 0xf0, 0xe0, 0x60, 0x30, 0x30, 
      	0x70, 0x00, 0x00, 0x30, 0xf8, 0xf8, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 
      	0xd3, 0x00, 0x07, 0xfd, 0x27, 0xff, 0xff, 0xff, 0xfe, 0xbf, 0x01, 0x01, 0x01, 0xc1, 0xff, 0xff, 
      	0xff, 0xff, 0x1f, 0x27, 0x63, 0x21, 0x11, 0x03, 0xef, 0xff, 0xff, 0xfe, 0xf0, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x1f, 
      	0x00, 0x00, 0x1f, 0x0f, 0x00, 0x0e, 0x1f, 0x19, 0x19, 0x09, 0x0f, 0x1f, 0x00, 0x00, 0x07, 0x0f, 
      	0x18, 0x18, 0x08, 0x0f, 0x1f, 0x00, 0x00, 0x03, 0x1f, 0x1e, 0x07, 0x03, 0x1f, 0x1f, 0x07, 0x00, 
      	0x03, 0x0f, 0x0c, 0x18, 0x18, 0x08, 0x0f, 0x03, 0x00, 0x00, 0x08, 0x1f, 0x1f, 0x18, 0x08, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x7f, 0xff, 
      	0xff, 0xf0, 0xc0, 0x8b, 0x1f, 0x3c, 0x3f, 0xff, 0xff, 0x60, 0xc0, 0x40, 0x00, 0x0f, 0x1d, 0x7f, 
      	0xff, 0xef, 0x1c, 0x18, 0x1b, 0x8e, 0xe0, 0xf2, 0x7f, 0x3f, 0x3f, 0xff, 0xf3, 0xc6, 0x98, 0x30, 
      	0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x00, 0x00, 0xc0, 0xc0, 
      	0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x00, 0x00, 0x40, 0xc0, 0xc0, 0x80, 0x40, 0xc0, 0xc0, 0x00, 
      	0x00, 0x40, 0x40, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0xc0, 0x80, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x10, 
      	0x1f, 0x03, 0x03, 0x07, 0x0f, 0x0e, 0x1c, 0x1c, 0x1b, 0x3f, 0x3e, 0x70, 0xf0, 0xf0, 0x60, 0x60, 
      	0xc0, 0xc1, 0x83, 0x86, 0xfe, 0x0f, 0x19, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x01, 0x01, 0x1d, 0x27, 
      	0x03, 0x06, 0x06, 0x06, 0x0c, 0x1c, 0xf8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x02, 0x06, 0x0f, 0x18, 0x30, 0x20, 0x00, 0x00, 0x03, 
      	0x9f, 0xf0, 0x78, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x20, 0x3f, 0x3f, 0x20, 0x20, 0x01, 0x00, 0x00, 
      	0x00, 0x20, 0x20, 0x3f, 0x3f, 0x20, 0x20, 0x20, 0x00, 0x00, 0x3c, 0x3c, 0x22, 0x22, 0x1f, 0x3f, 
      	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0e, 0x1c, 
      	0x38, 0x70, 0x61, 0xc1, 0x83, 0x83, 0x06, 0x1c, 0xf8, 0xc0, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
      	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
      	0x06, 0x0c, 0x08, 0x08, 0x09, 0x09, 0x0f, 0x07, 0x07, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x20, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      };

        // clang-format on
        oled_write_raw_P(epd_bitmap_mdwrt_logo, sizeof(epd_bitmap_mdwrt_logo));
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
          case _ADJUST:
              if (clockwise) {
                  tap_code16(LCTL(KC_RIGHT));
              } else {
                  tap_code16(LCTL(KC_LEFT));
              }
              break;
          case _MOUSEKE:
              if (clockwise) {
                  tap_code(KC_MS_RIGHT);
              } else {
                  tap_code(KC_MS_LEFT);
              }
              break;
      }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
            case _FUNCTION:
            case _DVORAK:
            case _NAV:
                // System Volume control
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case _ADJUST:
              // Swinsian Volume control
              // nb. this is buggy
              if (clockwise) {
                  tap_code16(LCAG(KC_I));
              } else {
                  tap_code16(LCAG(KC_D));
              }
              break;
            case _NAVSYM:
            if (clockwise) {
                    tap_code(KC_BRIGHTNESS_UP);
                } else {
                    tap_code(KC_BRIGHTNESS_DOWN);
                }
                break;
            case _MOUSEKE:
                if (clockwise) {
                    tap_code(KC_MS_UP);
                } else {
                    tap_code(KC_MS_DOWN);
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
        case _NAVSYMR:
            // pale red
            rgblight_setrgb_at(0x08, 0x00, 0x00, 0);
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SS_HELLO:
            if (record->event.pressed) {
                SEND_STRING("Hello, world!\n");
            }
            return false;
    }

    return true;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
  // works but flashes off again quickly
  rgblight_setrgb_at(RGB_WHITE, 0);

  // copy data to this var which gets output to the screen
  // this appears to be intermittently unreliable
  // buffer should be 32
  // TODO ensure this doesn't read beyond the end of the buffer?!?!?!
  memcpy(hidoutput, data, 32);

  //  doesn't work - maybe needs some kind of split sync
  // rgblight_setrgb_at(RGB_WHITE, 1);

  // raw_hid_send(data, length);
}
