/******************************************************************************
 * The MIT License
 *
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

/**
 * @file   libmaple/stm32f2/timer.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  STM32F2 timers.
 */

#include <libmaple/timer.h>
#include "timer_private.h"

/*
 * Routines
 */

/**
 * @brief Get the GPIO alternate function corresponding to a timer.
 *
 * For example, if dev is TIMER1, this function returns
 * GPIO_AF_TIM_1_2. This is useful for e.g. using gpio_set_af() to set
 * a pin's alternate function to a timer.
 *
 * @param dev Timer device, must not be TIMER6 or TIMER7.
 * @return gpio_af corresponding to dev
 * @see gpio_set_af
 * @see gpio_af
 */
//gpio_af timer_get_af(timer_dev *dev) {

//s}

/*
 * IRQ handlers
 *
 * Defer to the timer_private dispatch API.
 */

void __irq_epca1(void) {
    dispatch_adv(TIMER1);
    return;
}

void __irq_pca1(void) {
    dispatch_general(TIMER2);
    return;
}

void __irq_pca2(void) {
    dispatch_general(TIMER3);
    return;
}

void __irq_tim1_low(void) {
    //dispatch_basic_low(TIMER4);
    return;
}

void __irq_tim1_high(void) {
    dispatch_basic_high(TIMER4);
    return;
}

void __irq_tim2_low(void) {
    //dispatch_basic_low(TIMER5);
    return;
}

void __irq_tim2_high(void) {
    dispatch_basic_high(TIMER5);
    return;
}

