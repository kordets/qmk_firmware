#include "print.h"
#include "oneshot.h"

#undef DEBUG_ONESHOT

void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
            #ifdef DEGUG_ONESHOT
            dprintf("trigger down (on?), mod: %d, ? -> os_down_unused\n", mod);
            #endif
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                #ifdef DEGUG_ONESHOT
                dprintf("trigger up, mod: %d, os_down_unused -> os_up_queued\n", mod);
                #endif
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                #ifdef DEGUG_ONESHOT
                dprintf("trigger up (off), mod: %d, os_down_used -> os_up_unqueued\n", mod);
                #endif
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
                #ifdef DEGUG_ONESHOT
                dprintf("cancel (off), mod: %d, ? -> os_up_unqueued\n", mod);
                #endif
            }
            if (!is_oneshot_ignored_key(keycode)) {
                switch (*state) {
                case os_up_queued:
                    *state = os_up_queued_used;
                    #ifdef DEGUG_ONESHOT
                    dprintf("key up (off), mod: %d, os_up_queued -> os_up_queued_used\n", mod);
                    #endif
                    break;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    #ifdef DEGUG_ONESHOT
                    dprintf("key up (off), mod: %d, os_up_queued_used -> os_up_unqueued\n", mod);
                    #endif
                    break;
                default:
                    break;
                }
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    #ifdef DEGUG_ONESHOT
                    dprintf("key up, mod: %d, os_down_unused -> os_down_used\n", mod);
                    #endif
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    #ifdef DEGUG_ONESHOT
                    dprintf("key up (off), mod: %d, os_up_queued -> os_up_unqueued\n", mod);
                    #endif
                    break;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    #ifdef DEGUG_ONESHOT
                    dprintf("key up (off), mod: %d, os_up_queued_used -> os_up_unqueued\n", mod);
                    #endif
                    break;
                default:
                    break;
                }
            }
        }
    }
}

bool update_oneshot_layer(
    oneshot_state *state,
    uint16_t layer,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                layer_on(layer);
            }
            *state = os_down_unused;
            #ifdef DEGUG_ONESHOT
            dprintf("trigger down (on?), layer: %d, ? -> os_down_unused\n", layer);
            #endif
            return false;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the layer while trigger was held, queue it.
                *state = os_up_queued;
                #ifdef DEGUG_ONESHOT
                dprintf("trigger up, layer: %d, os_down_unused -> os_up_queued\n", layer);
                #endif
                return false;
            case os_down_used:
                // If we did use the layer while trigger was held, turn off it.
                *state = os_up_unqueued;
                layer_off(layer);
                #ifdef DEGUG_ONESHOT
                dprintf("trigger up (off), layer: %d, os_down_used -> os_up_unqueued\n", layer);
                #endif
                return false;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_layer_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot layer on designated cancel keydown.
                *state = os_up_unqueued;
                layer_off(layer);
                #ifdef DEGUG_ONESHOT
                dprintf("cancel (off), layer: %d, ? -> os_up_unqueued\n", layer);
                #endif
                return false;
            }
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    #ifdef DEGUG_ONESHOT
                    dprintf("key down, layer: %d, os_down_unused -> os_down_used\n", layer);
                    #endif
                    return true;
                case os_up_queued:
                    if (is_oneshot_mod_key(keycode)) {
                        *state = os_up_unqueued;
                        layer_off(layer);
                        #ifdef DEGUG_ONESHOT
                        dprintf("key down, layer: %d, os_up_queued -> os_up_unqueued\n", layer);
                        #endif
                        return false;
                    } else {
                        *state = os_up_queued_used;
                        #ifdef DEGUG_ONESHOT
                        dprintf("key down, layer: %d, os_up_queued -> os_up_queued_used\n", layer);
                        #endif
                    }
                    return true;
               case os_up_queued_used:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    #ifdef DEGUG_ONESHOT
                    dprintf("key down (off), layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                    #endif
                    return false;
                default:
                    break;
                }
            }
        } else {
            // Ignore key ups from other layers
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_up_queued:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    #ifdef DEBUG_ONESHOT
                    dprintf("key up (off), layer: %d, os_up_queued -> os_up_unqueued\n", layer);
                    #endif
                    return true;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    #ifdef DEBUG_ONESHOT
                    dprintf("key up (off), layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                    #endif
                    return true;
                default:
                    break;
                }
            }
        }
    }
    return true;
}

void cancel_oneshot_layer(oneshot_state *state, uint16_t layer) {
  // TODO: write me
  *state = os_up_unqueued;
  layer_off(layer);
}