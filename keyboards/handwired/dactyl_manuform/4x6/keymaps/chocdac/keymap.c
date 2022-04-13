#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

#include "drivers/sensors/pimoroni_trackball.h"
#include "oneshot.h"

#define _BASE 0
#define _RAISE 1
#define _LOWER 2
#define _GAME  3
#define _SSFN  4
#define _SSFNALT 5
#define _SSFNSFT 6
#define _SSFNCTL 7
#define _SSMOUSE 8

enum custom_keycodes {
  OS_FN = SAFE_RANGE,
  OS_MOUSE,
  OS_CTRL,
  OS_ALT,
  OS_GUI,
  OS_SFT,  
};

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN1

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define SSFN  OSL(_SSFN)
#define SSFNALT OSL(_SSFNALT)
#define SSFNSFT OSL(_SSFNSFT)
#define SSFNCTL OSL(_SSFNCTL)
#define KC_COPY   LCTL(KC_C)
#define KC_PASTE  LCTL(KC_V)
#define KC_CUT    LCTL(KC_X)

// debugging triggers
#define SSMOUSE OSL(_SSMOUSE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * +-----------------------------------------+                             +-----------------------------------------+
     * | TAB  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |   +  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | <--  |   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ö  |   ä  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   -  |   /  |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |  <   |   >  |                                                         |   (  |   )  |
     *               +-------------+-------------+------+               +------+-------------+-------------+
     *                             | FUN  | SHFT |  NUM |               | ENT  | SPC  | FUN  |
     *                             |------+------|------+               +------|------+------|
     *                                    | CTRL |  ALT |               | WIN  | CTL  |
     *                                     +-------------+               +-------------+
     */
    [_BASE] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_MINS,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, KC_QUOT,
        KC_ESC, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, SE_SLSH,
        RAISE,   KC_LSFT, SE_LABK, SE_RABK, KC_LCTL, LOWER,             KC_ENT,  KC_RCTL, SE_LPRN, SE_RPRN,  KC_SPC,  RAISE, 
                                            XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
                                            XXXXXXX,  KC_LALT,            KC_LGUI,  XXXXXXX,
                                            XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX
    ),


    /* Function/symbol
     * +-----------------------------------------+                             +-----------------------------------------+
     * | ESC  |      |   7  |   8  |   9  |   ,  |                             |   ,  |   7  |   8  |   9  |      |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | <--  |      |   4  |   5  |   6  |   .  |                             |   .  |   4  |   5  |   6  |      |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |      |   1  |   2  |   3  |   0  |                             |   0  |   1  |   2  |   3  |      |      |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |      |   0  |                                                         |      |      |
     *               +-------------+-------------+------+               +------+-------------+-------------+
     *                             |      |      |      |               |      |      |FN(ss)|
     *                             |------+------|------+               +------|------+------|
     *                                    |      |      |               |      |      |
     *                                    +-------------+               +-------------+
     */
    // [_LOWER] = LAYOUT(
    //     KC_ESC,  _______,    KC_7,      KC_8,    KC_9,      KC_COMM,               _______,    _______,    _______,    _______,    _______,    SSMOUSE,
    //     KC_BSPC,  _______,   KC_4,      KC_5,    KC_6,      KC_DOT,                _______,    _______,    _______,    _______,    _______,    _______,
    //     _______, _______,    KC_1,      KC_2,    KC_3,      KC_0,                  _______,    _______,    _______,    _______,    _______,    _______,
    //     _______, _______,    _______,   KC_0,    _______,    _______,              _______,    _______,    _______,    _______,    _______,    SSFN, 
    //                                         XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,
    //                                         XXXXXXX,  _______,                          _______,  XXXXXXX,
    //                                         XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX
    // ),

    [_LOWER] = LAYOUT(
        KC_ESC,  _______,    KC_7,      KC_8,    KC_9,      KC_COMM,               KC_COMM,   KC_7,    KC_8,    KC_9,    _______,    SSMOUSE,
        KC_BSPC,  _______,   KC_4,      KC_5,    KC_6,      KC_DOT,                KC_DOT,    KC_4,    KC_5,    KC_6,    _______,    _______,
        _______, _______,    KC_1,      KC_2,    KC_3,      KC_0,                  KC_0,      KC_1,    KC_2,    KC_3,    _______,    _______,
        _______, _______,    _______,   KC_0,    _______,    _______,              KC_BTN1,   KC_BTN3,    _______,    _______,    KC_BTN2,    OS_FN, 
                                            XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,
                                            XXXXXXX,  _______,                          _______,  XXXXXXX,
                                            XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX
    ),

    /* Function/symbol
     * +-----------------------------------------+                             +-----------------------------------------+
     * | ESC  |   !  |   "  |   #  |   @  |   %  |                             |   &  | HOME |  UP  | PGUP |   =  |   *  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | <--  |   ~  | CUT  | COPY |PASTE |   |  |                             |  INS | LEFT | DOWN | RGHT |      |   '  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |   ^  |      |      |      |   $  |                             |   €  |  END |      | PGDN |      |   \  |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |  [   |   ]  |                                                         |   {  |   }  |
     *               +-------------+-------------+------+               +------+-------------+-------------+
     *                             |      |      |      |               | MOU1 | MOU2 |      |
     *                             |------+------|------+               +------|------+------|
     *                                    |      |      |               |      | MOU3 |
     *                                    +-------------+               +-------------+
     */
    [_RAISE] = LAYOUT(
        KC_ESC,  SE_EXLM,    SE_DQUO,    SE_HASH,    SE_AT,      SE_PERC,               SE_AMPR,    KC_HOME,   KC_UP,    KC_PGUP,    SE_EQL,     SE_ASTR,
        KC_DEL,  SE_TILD,    KC_CUT,     KC_COPY,    KC_PASTE,    SE_PIPE,               KC_INS,     KC_LEFT,   KC_DOWN,  KC_RIGHT,   _______,    SE_QUOT,
        _______, SE_CIRC,    _______,    _______,    _______,    SE_DLR,                SE_EURO,    KC_END,    _______,  KC_PGDN,    _______,    SE_BSLS,
        _______, _______,    SE_LBRC,    SE_RBRC,    _______,    _______,               KC_BTN1,    KC_BTN3,   SE_LCBR,  SE_RCBR,    KC_BTN2,    _______, 
                                            XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,
                                            XXXXXXX,  _______,                          _______,  XXXXXXX,
                                            XXXXXXX, XXXXXXX,                           XXXXXXX,  XXXXXXX
    ),


    /* Single shot functions
     * +-----------------------------------------+                             +-----------------------------------------+
     * | ESC  |      |  F7  |  F8  |  F9  |  F12 |                             |      |      |      |      | PRNT |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | CAPS |      |  F4  |  F5  |  F6  |  F11 |                             |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |      |  F1  |  F2  |  F3  |  F10 |                             |      |      |      |      |      |      |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |      |      |                                                         |      |      |
     *               +-------------+-------------+------+               +------+-------------+-------------+
     *                             |      |      |      |               | GAME |      |      |
     *                             |------+------|------+               +------|------+------|
     *                                    |      |      |               |      |      |
     *                                    +-------------+               +-------------+
     */
    [_SSFN] = LAYOUT(
        KC_ESC,  _______,    KC_F7,      KC_F8,    KC_F9,      KC_F12,               _______,    _______,    _______,    _______,    KC_PSCR,    _______,
        KC_CAPS, _______,    KC_F4,      KC_F5,    KC_F6,      KC_F11,                _______,    _______,    _______,    _______,    _______,    _______,
        _______, _______,    KC_F1,      KC_F2,    KC_F3,      KC_F10,                  _______,    _______,    _______,    _______,    _______,    _______,
        _______, SSFNSFT,    _______,   _______,    SSFNCTL,    _______,              KC_MS_BTN1,    _______,    _______,    _______,    _______,    _______, 
                                            XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,
                                            XXXXXXX,  SSFNALT,                          TO(_GAME),  XXXXXXX,
                                            XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX
    ),

    [_GAME] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_MINS,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, SE_SLSH,
        KC_RCTL,   KC_RSFT, SE_LABK, SE_RABK, KC_LCTL, KC_RALT,             KC_ENT,  KC_RCTL, SE_LPRN, SE_RPRN,  KC_SPC,  TO(_BASE), 
                                            XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
                                            XXXXXXX,  KC_LALT,            TO(_BASE),  XXXXXXX,
                                            XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX
    ),

    [_SSFNALT] = LAYOUT(
        KC_ESC,  _______,    LALT(KC_F7),      LALT(KC_F8),    LALT(KC_F9),      LALT(KC_F12),               _______,    _______,    _______,    _______,    KC_PSCR,    _______,
        KC_BSPC, _______,    LALT(KC_F4),      LALT(KC_F5),    LALT(KC_F6),      LALT(KC_F11),                _______,    _______,    _______,    _______,    _______,    _______,
        _______, _______,    LALT(KC_F1),      LALT(KC_F2),    LALT(KC_F3),      LALT(KC_F10),                  _______,    _______,    _______,    _______,    _______,    _______,
        _______, _______,    _______,   _______,    _______,    _______,              _______,    _______,    _______,    _______,    _______,    _______, 
                                            XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,
                                            XXXXXXX,  _______,                          _______,  XXXXXXX,
                                            XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX
    ),

    [_SSFNSFT] = LAYOUT(
        KC_ESC,  _______,    LSFT(KC_F7),      LSFT(KC_F8),    LSFT(KC_F9),      LSFT(KC_F12),               _______,    _______,    _______,    _______,    KC_PSCR,    _______,
        KC_BSPC, _______,    LSFT(KC_F4),      LSFT(KC_F5),    LSFT(KC_F6),      LSFT(KC_F11),                _______,    _______,    _______,    _______,    _______,    _______,
        _______, _______,    LSFT(KC_F1),      LSFT(KC_F2),    LSFT(KC_F3),      LSFT(KC_F10),                  _______,    _______,    _______,    _______,    _______,    _______,
        _______, _______,    _______,   _______,    _______,    _______,              _______,    _______,    _______,    _______,    _______,    _______, 
                                            XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,
                                            XXXXXXX,  _______,                          _______,  XXXXXXX,
                                            XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX
    ),

    [_SSFNCTL] = LAYOUT(
        KC_ESC,  _______,    LCTL(KC_F7),      LCTL(KC_F8),    LCTL(KC_F9),      LCTL(KC_F12),               _______,    _______,    _______,    _______,    KC_PSCR,    _______,
        KC_BSPC, _______,    LCTL(KC_F4),      LCTL(KC_F5),    LCTL(KC_F6),      LCTL(KC_F11),                _______,    _______,    _______,    _______,    _______,    _______,
        _______, _______,    LCTL(KC_F1),      LCTL(KC_F2),    LCTL(KC_F3),      LCTL(KC_F10),                  _______,    _______,    _______,    _______,    _______,    _______,
        _______, _______,    _______,   _______,    _______,    _______,              _______,    _______,    _______,    _______,    _______,    _______, 
                                            XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,
                                            XXXXXXX,  _______,                          _______,  XXXXXXX,
                                            XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX
    ),

    [_SSMOUSE] = LAYOUT(
        XXXXXXX,  XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,      XXXXXXX,                XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,      XXXXXXX,                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,      XXXXXXX,                  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        RAISE,    XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,        LOWER,                      KC_BTN1,    KC_BTN3,   XXXXXXX,     XXXXXXX,    KC_BTN2,    XXXXXXX, 
                                            XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,
                                            XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,
                                            XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX
    )

    
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case RAISE: 
    case LOWER:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_layer_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
    case OS_FN:
    case OS_MOUSE:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_mod_key(uint16_t keycode) {
    switch (keycode) {
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
    case OS_SFT:
        return true;
    default:
        return false;
    }
}

oneshot_state os_fn_state = os_up_unqueued;
oneshot_state os_mouse_state = os_up_unqueued;
oneshot_state* current_oneshot = NULL;
uint16_t current_oneshot_layer = _BASE;

#define ONESHOT_ENABLE_TIME 2000
static uint32_t oneshot_timer_start;
//static uint32_t oneshot_timer_target;
static bool oneshot_timer_running;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool handled = true;
  handled = update_oneshot_layer(
      &os_fn_state, _SSFN, OS_FN,
      keycode, record
  ) & handled;

  // If oneshot layer was activated, start the autodisable timer
  if (os_fn_state == os_up_queued) {
    oneshot_timer_start = timer_read32(); 
    oneshot_timer_running = true;
    current_oneshot = &os_fn_state;
    current_oneshot_layer = _SSFN;
    return true;
  } else if (os_fn_state == os_up_unqueued) {
    current_oneshot = NULL;
    current_oneshot_layer = _BASE;
  }

  handled = update_oneshot_layer(
      &os_mouse_state, _SSMOUSE, OS_MOUSE,
      keycode, record
  ) & handled;

  // If oneshot layer was activated, start the autodisable timer
  if (os_mouse_state == os_up_queued) {
    // oneshot_timer_start = timer_read32(); 
    // oneshot_timer_running = true;
    // current_oneshot = &os_mouse_state;
    // current_oneshot_layer = _SSMOUSE;
    return true;
  } else if (os_mouse_state == os_up_unqueued) {
    current_oneshot = NULL;
    current_oneshot_layer = _BASE;
  }

  return true;
}

// void persistent_default_layer_set(uint16_t default_layer) {
//     eeconfig_update_default_layer(default_layer);
//     default_layer_set(default_layer);
// }

bool capslock_led_on = false;

// bool led_user_update(led_t led_state) {
//   static uint8_t caps_state = 0;
//   if (caps_state != led_state.caps_lock) {
//     caps_state = led_state.caps_lock;
//     if (led_state.caps_lock) {
//       capslock_led_on = true;
//     } else {
//       capslock_led_on = false;
//     }
//   }
//   return true;
// }

// changes underglow based on current layer
#define RBG_VAL 120
layer_state_t layer_state_set_user(layer_state_t state) {
  switch(biton32(state)) {
  case _LOWER:
    // green-ish
    //dprintf("Layer: _LOWER\n");
    pimoroni_trackball_set_rgbw(241,66,141,128);
    //rgblight_sethsv_noeeprom(72, 221, RBG_VAL);
    break;
  case _RAISE:
    // Red
    //dprintf("Layer: _RAISE\n");
    pimoroni_trackball_set_rgbw(0,0,255,0);
    break;
  case _GAME:
    // COLOR
    pimoroni_trackball_set_rgbw(0,255,255,0);
    break;
  case _SSFN:
  case _SSFNALT:
  case _SSFNSFT:
  case _SSFNCTL:
    // Dark Blue
    //dprintf("Layer: _FN\n");
    pimoroni_trackball_set_rgbw(0,255,0,0);
    break;

  case _SSMOUSE:
    //dprintf("Layer: _MOUSE\n");
    pimoroni_trackball_set_rgbw(255, 255, 0, 0);
    break;
  default:
    // Default colors
    if (capslock_led_on == false) {
      pimoroni_trackball_set_rgbw(0,0,0,0);
    } else {
      pimoroni_trackball_set_rgbw(255,0,0,0);
    }
    
    break;
  }
  return state;
}

// void oneshot_layer_changed_user(uint8_t layer) {
//   if (layer == _SSFN) {
//     println("Oneshot layer _FN on");
//   }
//   if (!layer) {
//     println("Oneshot layer off");
//   }
// }

void suspend_power_down_user(void) {
    // code will run multiple times while keyboard is suspended
    pimoroni_trackball_set_rgbw(0,0,0,0);
}

void suspend_wakeup_init_user(void) {
    // code will run on keyboard wakeup
    pimoroni_trackball_set_rgbw(0,0,0,0);
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {


    static int8_t prevX = 0;
    static int8_t prevY = 0;

    // Use _NUM layer to toggle scrolling
    if (IS_LAYER_ON(_LOWER)) {
      mouse_report.h = 0;
      mouse_report.v = (-1) * (mouse_report.y / 2);
      mouse_report.x = 0;
      mouse_report.y = 0;
      return mouse_report;
    }

    // Entering mouse layer
    if ((prevX != mouse_report.x || prevY != mouse_report.y) && !IS_LAYER_ON(_SSMOUSE) && !IS_LAYER_ON(_SSFN) && !IS_LAYER_ON(_GAME)) {
      layer_on(_SSMOUSE);
      os_mouse_state = os_up_queued;
      
      oneshot_timer_start = timer_read32(); 
      oneshot_timer_running = true;
      current_oneshot = &os_mouse_state;
      current_oneshot_layer = _SSMOUSE;

    // Only refresh mouse layer timer if we saw movement and mouse layer is active
    // Assumes that the timer is set to running...
    } else if ((prevX != mouse_report.x || prevY != mouse_report.y) && IS_LAYER_ON(_SSMOUSE)) {
      oneshot_timer_start = timer_read32();
    }
    
    prevX = mouse_report.x;
    prevY = mouse_report.y;

    return mouse_report;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

void matrix_scan_user(void) {
  if (oneshot_timer_running && timer_elapsed32(oneshot_timer_start) > ONESHOT_ENABLE_TIME) {
    oneshot_timer_running = false;
    if (current_oneshot != NULL) {
      if (*current_oneshot == os_up_queued || *current_oneshot == os_up_queued_used) {
        cancel_oneshot_layer(current_oneshot, current_oneshot_layer);
        current_oneshot = NULL;
        current_oneshot_layer = _BASE;
      }
    }
    
    
  }
}