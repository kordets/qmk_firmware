/* Copyright 2015-2017 Jack Humbert
 * Copyright 2020 Daniel Reibl <janos.daniel.reibl@protonmail.com>
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

enum layer_names {
    _QWERTY,
    _SYMBOL,
    _NAV
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    DVORAK,
    BACKLIT
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_5x12(
    KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  LT(_SYMBOL,KC_ESC),    
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,  KC_U,   KC_I,      KC_O,     KC_P,     KC_LBRC,  
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,  KC_J,    KC_K,      KC_L,     KC_SCLN,  KC_QUOT,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,  KC_M,   KC_COMM,   KC_DOT,   KC_SLSH,  KC_RSFT, 
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BSPC, LCTL_T(KC_SPC),  RALT_T(KC_ENT),  KC_NO,   KC_NO, KC_NO, KC_NO  
),

// [_QWERTY] = LAYOUT_ortho_5x12(
//     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    
//     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    
//     KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, 
//     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, 
//     KC_NO, KC_NO, KC_NO, KC_NO, LOWER,   KC_SPC,  KC_SPC,  KC_NO,   KC_NO, KC_NO, KC_NO  
// ),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOL] = LAYOUT_ortho_5x12(
    KC_F1,    KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,      _______,    
    KC_TAB,   _______,    KC_UP,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, 
    _______,  KC_LEFT,    KC_DOWN,    KC_RIGHT,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    
    _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, 
    _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_CAPS   
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_ortho_5x12(
   KC_F1,    KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,      _______,    
    KC_TAB,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, 
    _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    
    _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, 
    _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_CAPS
)

};

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
// }

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case QWERTY:
//             if (record->event.pressed) {
//                 set_single_persistent_default_layer(_QWERTY);
//             }
//             return false;
//             break;
//         case COLEMAK:
//             if (record->event.pressed) {
//                 set_single_persistent_default_layer(_COLEMAK);
//             }
//             return false;
//             break;
//         case DVORAK:
//             if (record->event.pressed) {
//                 set_single_persistent_default_layer(_DVORAK);
//             }
//             return false;
//             break;
//         case BACKLIT:
//             if (record->event.pressed) {
//                 register_code(keycode_config(KC_LGUI));
//                 #ifdef BACKLIGHT_ENABLE
//                     backlight_step();
//                 #endif
//             } else {
//                 unregister_code(keycode_config(KC_LGUI));
//             }
//             return false;
//             break;
//     }
//     return true;
// };