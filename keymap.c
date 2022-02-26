/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Andre Brait <andrebrait@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE
    #ifndef RGB_CONFIRMATION_BLINKING_TIME
        #define RGB_CONFIRMATION_BLINKING_TIME 1000 // 2 seconds
    #endif
#endif // RGB_MATRIX_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     PrtScr      Rotary(Play/Pause)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Ins
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 Del
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgUp
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       PgDn
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_INS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_CALC,          _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),


};
// clang-format on

//custom keycodes for encoder
#define MODS_ALT_MASK (MOD_BIT(KC_LALT)) // Make ALT layer for encoder use 
#define MODS_CTRL_MASK (MOD_BIT(KC_LCTL)) // Make CTRL layer for encoder use

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_mods() & MODS_ALT_MASK) {
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
        }
    } else if (get_mods() & MODS_CTRL_MASK) {
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
        }
	} else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
#endif // ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE

/*
#if RGB_CONFIRMATION_BLINKING_TIME > 0
static uint16_t effect_started_time = 0;
static uint8_t r_effect = 0x0, g_effect = 0x0, b_effect = 0x0;
#define effect_red() r_effect = 0xFF, g_effect = 0x0, b_effect = 0x0
#define effect_green() r_effect = 0x0, g_effect = 0xFF, b_effect = 0x0
static void start_effects(void);
#endif // RGB_CONFIRMATION_BLINKING_TIME > 0
*/

static void set_rgb_default_leds(void);
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state)) {
    // special handling per layer
        case 0:  //layer one
            if (host_keyboard_led_state().caps_lock)
                rgb_matrix_set_color_all(0xFF, 0x00, 0x7F);  // TODO
            else
                set_rgb_default_leds();  // sets all to preset colors
            break;
        case 1:
            for (uint8_t i = led_min; i < led_max; i++) {
                 RGB_MATRIX_INDICATOR_SET_COLOR(i,0,0,0);
            }
            RGB_MATRIX_INDICATOR_SET_COLOR(7, 0, 0, 255) //1 for RGB toggle
            RGB_MATRIX_INDICATOR_SET_COLOR(14, 0, 0, 255) //w for RGB increase brightness
            RGB_MATRIX_INDICATOR_SET_COLOR(15, 0, 0, 255) //s for RGB decrease brightness
            RGB_MATRIX_INDICATOR_SET_COLOR(16, 0, 0, 255) //x for RGB hue increase (shift for decrease)
            RGB_MATRIX_INDICATOR_SET_COLOR(38, 255, 0, 0) //n for N key Roll Over
            RGB_MATRIX_INDICATOR_SET_COLOR(69, 0, 0, 255) //PrtScn for CALC
            RGB_MATRIX_INDICATOR_SET_COLOR(93, 255, 0, 0) //slash/vertical line for RESET
			break;
		default:
            break;
    }
}

/* Renaming those to make the purpose on this keymap clearer */
#define LED_FLAG_CAPS LED_FLAG_NONE
#define LED_FLAG_EFFECTS LED_FLAG_INDICATOR


/*
#if RGB_CONFIRMATION_BLINKING_TIME > 0
static void start_effects() {
    effect_started_time = sync_timer_read();
    if (!rgb_matrix_is_enabled()) {
        // Turn it ON, signal the cause (EFFECTS) 
        rgb_matrix_set_flags(LED_FLAG_EFFECTS);
        rgb_matrix_enable_noeeprom();
    } else if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
        // It's already ON, promote the cause from CAPS to EFFECTS 
        rgb_matrix_set_flags(LED_FLAG_EFFECTS);
    }
}
#endif // RGB_CONFIRMATION_BLINKING_TIME > 0
*/


static void set_rgb_default_leds() {
	rgb_matrix_set_color_all(0, 0, 0xFF); // set all to blue
    rgb_matrix_set_color(0, 0xFF, 0x00, 0x7F);  // pink escape
    rgb_matrix_set_color(33, 0xFF, 0x00, 0x7F); // pink spacebar
    rgb_matrix_set_color(96, 0xFF, 0x00, 0x7F); // pink enter 
    /*rgb_matrix_set_color(28, 0x33, 0x99, 0xFF); // blue f5
    rgb_matrix_set_color(34, 0x33, 0x99, 0xFF); // blue f6
    rgb_matrix_set_color(39, 0x33, 0x99, 0xFF); // blue f7
    rgb_matrix_set_color(44, 0x33, 0x99, 0xFF); // blue f8
    rgb_matrix_set_color(2, 0x33, 0x99, 0xFF);  // blue tab
    rgb_matrix_set_color(3, 0x33, 0x99, 0xFF);  // blue caps
    rgb_matrix_set_color(4, 0x33, 0x99, 0xFF);  // blue Lshift
    rgb_matrix_set_color(5, 0x33, 0x99, 0xFF);  // blue Lctrl
    rgb_matrix_set_color(11, 0x33, 0x99, 0xFF); // blue Lwindows
    rgb_matrix_set_color(17, 0x33, 0x99, 0xFF); // blue Lalt
	rgb_matrix_set_color(49, 0x33, 0x99, 0xFF); // blue Ralt
    rgb_matrix_set_color(55, 0x33, 0x99, 0xFF); // blue Rfn
    rgb_matrix_set_color(65, 0x33, 0x99, 0xFF); // blue Rctrl
    rgb_matrix_set_color(90, 0x33, 0x99, 0xFF); // blue Rshift
    rgb_matrix_set_color(94, 0x33, 0x99, 0xFF); // blue up
    rgb_matrix_set_color(97, 0x33, 0x99, 0xFF); // blue down
    rgb_matrix_set_color(95, 0x33, 0x99, 0xFF); // blue left
    rgb_matrix_set_color(79, 0x33, 0x99, 0xFF); // blue right
    rgb_matrix_set_color(85, 0x33, 0x99, 0xFF); // blue backspace
	rgb_matrix_set_color(72, 0x33, 0x99, 0xFF); // blue ins
    rgb_matrix_set_color(75, 0x33, 0x99, 0xFF); // blue del
    rgb_matrix_set_color(86, 0x33, 0x99, 0xFF); // blue pgup
    rgb_matrix_set_color(82, 0x33, 0x99, 0xFF); // blue pgdn
	
	*/
	
	rgb_matrix_set_color(67, 0x33, 0x99, 0xFF); // Left side LED 1
    rgb_matrix_set_color(68, 0x33, 0x99, 0xFF); // Right side LED 1
    rgb_matrix_set_color(70, 0x33, 0x99, 0xFF); // Left side LED 2
    rgb_matrix_set_color(71, 0x33, 0x99, 0xFF); // Right side LED 2
    rgb_matrix_set_color(73, 0x33, 0x99, 0xFF); // Left side LED 3
    rgb_matrix_set_color(74, 0x33, 0x99, 0xFF); // Right side LED 3
    rgb_matrix_set_color(76, 0x33, 0x99, 0xFF); // Left side LED 4
    rgb_matrix_set_color(77, 0x33, 0x99, 0xFF); // Right side LED 4
    rgb_matrix_set_color(80, 0x33, 0x99, 0xFF); // Left side LED 5
    rgb_matrix_set_color(81, 0x33, 0x99, 0xFF); // Right side LED 5
    rgb_matrix_set_color(83, 0x33, 0x99, 0xFF); // Left side LED 6
    rgb_matrix_set_color(84, 0x33, 0x99, 0xFF); // Right side LED 6
    rgb_matrix_set_color(87, 0x33, 0x99, 0xFF); // Left side LED 7
    rgb_matrix_set_color(88, 0x33, 0x99, 0xFF); // Right side LED 7
    rgb_matrix_set_color(91, 0x33, 0x99, 0xFF); // Left side LED 8
    rgb_matrix_set_color(92, 0x33, 0x99, 0xFF); // Right side LED 8
	
}

#endif // RGB_MATRIX_ENABLE
