/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)
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
#include "pimoroni_trackball.h"
#include "i2c_master.h"
#include "print.h"
#include "debug.h"
#include "timer.h"

// clang-format off
#define PIMORONI_TRACKBALL_REG_LED_RED 0x00
#define PIMORONI_TRACKBALL_REG_LED_GRN 0x01
#define PIMORONI_TRACKBALL_REG_LED_BLU 0x02
#define PIMORONI_TRACKBALL_REG_LED_WHT 0x03
#define PIMORONI_TRACKBALL_REG_LEFT    0x04
#define PIMORONI_TRACKBALL_REG_RIGHT   0x05
#define PIMORONI_TRACKBALL_REG_UP      0x06
#define PIMORONI_TRACKBALL_REG_DOWN    0x07
// clang-format on

static uint16_t precision = 64;

uint16_t pimoroni_trackball_get_cpi(void) {
    return (precision * 125);
}
/**
 * @brief Sets the scaling value for pimoroni trackball
 *
 * Sets a scaling value for pimoroni trackball to allow runtime adjustment. This isn't used by the sensor and is an
 * approximation so the functions are consistent across drivers.
 *
 * NOTE: This rounds down to the nearest number divisable by 125 that's a positive integer, values below 125 are clamped to 125.
 *
 * @param cpi uint16_t
 */
void pimoroni_trackball_set_cpi(uint16_t cpi) {
    if (cpi < 249) {
        precision = 1;
    } else {
        precision = (cpi - (cpi % 125)) / 125;
    }
}

void pimoroni_trackball_set_rgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    uint8_t                              data[4] = {r, g, b, w};
    __attribute__((unused)) i2c_status_t status  = i2c_writeReg(PIMORONI_TRACKBALL_ADDRESS << 1, PIMORONI_TRACKBALL_REG_LED_RED, data, sizeof(data), PIMORONI_TRACKBALL_TIMEOUT);

#ifdef CONSOLE_ENABLE
    if (debug_mouse) dprintf("Trackball RGBW i2c_status_t: %d\n", status);
#endif
}

i2c_status_t read_pimoroni_trackball(pimoroni_data_t* data) {
    i2c_status_t status = i2c_readReg(PIMORONI_TRACKBALL_ADDRESS << 1, PIMORONI_TRACKBALL_REG_LEFT, (uint8_t*)data, sizeof(*data), PIMORONI_TRACKBALL_TIMEOUT);
#ifdef CONSOLE_ENABLE
    if (debug_mouse) {
        static uint16_t d_timer;
        if (timer_elapsed(d_timer) > PIMORONI_TRACKBALL_DEBUG_INTERVAL) {
            //dprintf("Trackball READ i2c_status_t: %d L: %d R: %d Up: %d D: %d SW: %d\n", status, data->left, data->right, data->up, data->down, data->click);
            d_timer = timer_read();
        }
    }
#endif

    return status;
}

__attribute__((weak)) void pimoroni_trackball_device_init(void) {
    i2c_init();
    pimoroni_trackball_set_rgbw(0x00, 0x00, 0x00, 0x00);
}

#include "math.h"
int16_t pimoroni_trackball_get_offsets(uint8_t negative_dir, uint8_t positive_dir, uint8_t scale) {
    uint8_t offset     = 0;
    bool    isnegative = false;
    if (negative_dir > positive_dir) {
        offset     = negative_dir - positive_dir;
        isnegative = true;
    } else {
        offset = positive_dir - negative_dir;
    }
    uint16_t magnitude = (scale * offset * offset * offset * precision) >> 7;
    return isnegative ? -(int16_t)(magnitude) : (int16_t)(magnitude);
}

int16_t pimoroni_trackball_get_offsets2(int16_t *offsetX, int16_t *offsetY, uint8_t negative_dirX, uint8_t positive_dirX, uint8_t negative_dirY, uint8_t positive_dirY, uint8_t scale) {

    // X
    uint8_t _offsetX     = 0;
    bool    isnegativeX = false;
    if (negative_dirX > positive_dirX) {
        _offsetX     = negative_dirX - positive_dirX;
        isnegativeX = true;
    } else {
        _offsetX = positive_dirX - negative_dirX;
    }

    uint8_t _offsetY     = 0;
    bool    isnegativeY = false;
    if (negative_dirY > positive_dirY) {
        _offsetY     = negative_dirY - positive_dirY;
        isnegativeY = true;
    } else {
        _offsetY = positive_dirY - negative_dirY;
    }

    // calculate angle and vector length
    double angle_rad = atan2(_offsetY, _offsetX);
    double len = sqrt(pow(_offsetX, 6) + pow(_offsetY, 6));

    // bit shift magic to use a larger calculation result buffer to mitigate overflow, then shift back to fit into int16
    uint16_t magX = (((uint16_t)(len*cos(angle_rad))*scale*precision)) >> 7;
    uint16_t magY = ((uint16_t)(len*sin(angle_rad)*scale*precision)) >> 7;
    
    if (magX > 0 || magY > 0) {
      dprintf("magX: %d, magY: %d\n", magX, magY);
    }
    

    // Apply sign and calculate actual value
    if (isnegativeX) {
      *offsetX -= (int16_t)magX;
    } else {
      *offsetX += (int16_t)magX;
    }

    if (isnegativeY) {
      *offsetY -= (int16_t)magY;
    } else {
      *offsetY += (int16_t)magY;
    }

    return 1;

    //uint16_t magnitude = (scale * offset * offset * offset * precision) >> 7;
    //return isnegative ? -(int16_t)(magnitude) : (int16_t)(magnitude);
}


#   ifndef TRACKBALL_ANGLE_OFFSET
#   define TRACKBALL_ANGLE_OFFSET 0
#   endif

uint8_t TRACKBALL_ORIENTATION_CUSTOM = 0;

void pimoroni_trackball_adapt_values(int8_t* mouseX, int8_t* mouseY, int16_t* offsetX, int16_t* offsetY, pimoroni_data_t* data) {

// #if TRACKBALL_ORIENTATION_CUSTOM == 0
//   // Pimoroni text is up
//   *offsetY = data->left-data->right;
//   *offsetX = data->down-data->up;
// #elif TRACKBALL_ORIENTATION_CUSTOM == 1
//   // Pimoroni text is right
//   offsetY = data->down-data->up;
//   offsetX = data->right-data->left;
// #elif TRACKBALL_ORIENTATION_CUSTOM == 2
//   // Pimoroni text is down
//   offsetY = data->right-data->left;
//   offsetX = data->up-data->down;
// #else
//   // Pimoroni text is left
//   offsetY = data->up-data->down;
//   offsetX = data->left-data->right;
// #endif
    bool printDebugNow = false;
    if (*offsetX != 0 || *offsetY != 0 || data->left != 0 || data->right != 0 || data->up != 0 || data->down != 0) {
      //dprintf("tb2: inX: %d inY: %d left: %d right: %d up: %d down: %d\n", *offsetX, *offsetY, data->left, data->right, data->up, data->down);
      printDebugNow=true;
    }
    

    // Acceleration implementation from github/sevanteri
    // data->angle_rad = atan2(*offsetY, *offsetX) + TRACKBALL_ANGLE_OFFSET;
    // data->vector_length = sqrt(pow(*offsetX, 3) + pow(*offsetY, 3));
    // data->raw_x = *offsetX;
    // data->raw_y = *offsetY;

    //*offsetX
    //int16_t newX = (int16_t)(data->vector_length * cos(data->angle_rad));
    //*offsetY
    //int16_t newY = (int16_t)(data->vector_length * sin(data->angle_rad));

    if (printDebugNow) {
      //dprintf("tb3: a: %d L: %d newX: %d newY: %d\n", data->angle_rad, data->vector_length, newX, newY);
      //dprintf("a: %d\n", data->angle_rad);
      //dprintf("newX: %d, newY: %d\n",newX,newY);
    }

    // //re-apply original signs
    // if (*offsetY > 0){
    //   if (data->raw_y < 0) {
    //     *offsetY *= -1;
    //   }
    // } else if (*offsetY < 0) {
    //   if (data->raw_y > 0) {
    //     *offsetY *= -1;
    //   }
    // //} else {
    //    // case 0, do nothing
    // }

    // if (*offsetX > 0){
    //   if (data->raw_x < 0) {
    //     *offsetX *= -1;
    //   }
    // } else if (*offsetX < 0) {
    //   if (data->raw_x > 0) {
    //     *offsetX *= -1;
    //   }
    // //} else {
    //    // case 0, do nothing
    // }

    // mousereport clamping to int8 range
    if (*offsetX > 127) {
        *mouseX = 127;
        *offsetX -= 127;
    } else if (*offsetX < -127) {
        *mouseX = -127;
        *offsetX += 127;
    } else {
        *mouseX  = *offsetX;
        *offsetX = 0;
    }

    if (*offsetY > 127) {
        *mouseY = 127;
        *offsetY -= 127;
    } else if (*offsetY < -127) {
        *mouseY = -127;
        *offsetY += 127;
    } else {
        //*mouseY  = -1 * (*offsetY);
        *mouseY  = (*offsetY);
        *offsetY = 0;
    }
    
    if (printDebugNow) {
      //dprintf("mouseX: %d, mouseY: %d\n", *mouseX, *mouseY);
    }
    
}
