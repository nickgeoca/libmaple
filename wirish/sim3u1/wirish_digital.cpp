/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 * Copyright (c) 2012 LeafLabs, LLC.
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

/*
 * STM32F1 implementations for basic GPIO functionality.
 */

#include <wirish/io.h>

#include <libmaple/gpio.h>
#include <libmaple/timer.h>

#include <wirish/boards.h>

void pinMode(uint8 pin_num, WiringPinMode mode) {
    gpio_pin_mode outputMode;
    bool pwm = false;
    stm32_pin_info *gpio_pin = &PIN_MAP[pin_num];
    stm32_pin_info *shorted_pin = board_get_short_num(gpio_pin->gpio_device, gpio_bit) ?
            &PIN_MAP_SHORTS[board_get_short_num(gpio_pin->gpio_device, gpio_bit) - 1] : 0;

    if (pin_num >= BOARD_NR_GPIO_PINS) {
        return;
    }

    switch(mode) {
        case OUTPUT:
            outputMode = GPIO_DIGITAL_PP;
            break;
        case OUTPUT_OPEN_DRAIN:
            outputMode = GPIO_DIGITAL_OD;
            break;
        case INPUT:
        case INPUT_FLOATING:
        case INPUT_PULLDOWN:
        case INPUT_PULLUP:
            outputMode = GPIO_DIGITAL_INPUT_PULLUP;
            break;
        case INPUT_ANALOG:
            outputMode = GPIO_ANALOG;
            break;
        case PWM:
            outputMode = GPIO_DIGITAL_PP;
            pwm = true;
            break;
        case PWM_OPEN_DRAIN:
            outputMode = GPIO_DIGITAL_OD;
            pwm = true;
            break;
        default:
            ASSERT(0);
            return;
    }

    // Shorted pin case
    if (shorted_pin) {
        if (pwm == false) {
            // turn off secondary shorted pin
            gpio_set_af(shorted_pin->gpio_device, shorted_pin->gpio_bit, GPIOHD_FNCT_GPIO);
            gpio_set_mode(shorted_pin->gpio_device, shorted_pin->gpio_bit, GPIO_DIGITAL_INPUT_PULLUP);
        }
        else {
            // turn off primary shorted pin
            xbar_dis_device(gpio_pin->gpio_device, gpio_pin->gpio_bit);
            gpio_set_mode(gpio_pin->gpio_device, gpio_pin->gpio_bit, GPIO_DIGITAL_INPUT_PULLUP);
            gpio_pin = shorted_pin;
        }
    }

    // Set pin mode
    gpio_set_mode(gpio_pin->gpio_device, gpio_pin->gpio_bit, outputMode);

    //
    if (gpio_pin->timer_device != NULL) {
        /* Enable/disable timer channels if we're switching into or
         * out of PWM. */
        timer_set_mode(gpio_pin->timer_device,
                       gpio_pin->timer_channel,
                       pwm ? TIMER_PWM : TIMER_DISABLED);
    }

    // This only applies to PB4 pins
    if (gpio_get_type(gpio_pin->gpio_device) == GPIO_HIGHDRIVE) {
        gpio_set_af(gpio_pin->gpio_device, gpio_pin->gpio_bit, pwm ? GPIOHD_FNCT_EPCA0 : GPIOHD_FNCT_GPIO);
    }
}
