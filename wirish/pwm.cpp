/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file wirish/pwm.cpp
 * @brief Wiring-style pwmWrite().
 */

#include <wirish/pwm.h>

#include <libmaple/libmaple_types.h>
#include <libmaple/timer.h>

#include <wirish/boards.h>

void pwmWrite(uint8 pin, uint16 duty_cycle) {
    const stm32_pin_info *gpio_pin = &PIN_MAP[pin];
    if (pin >= BOARD_NR_GPIO_PINS) {
        return;
    }
    uint32 short_num = board_get_short_num(gpio_pin->gpio_device, gpio_pin->gpio_bit);
    if (short_num) {
        short_num -= 1;
        gpio_pin = &PIN_MAP_SHORTS[short_num];
    }

    timer_dev *dev = gpio_pin->timer_device;
    uint8 cc_channel = gpio_pin->timer_channel;
    ASSERT(dev && cc_channel);
    timer_set_compare(dev, cc_channel, ((uint32)duty_cycle * (uint32)timer_get_reload(dev)) / ((1<<16)-1));
}
