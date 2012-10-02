/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
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
 * @file   libmaple/timer.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Portable timer routines.
 */

#include <libmaple/timer.h>
#include <libmaple/stm32.h>
#include "timer_private.h"

static void disable_channel(timer_dev *dev, uint8 channel);
static void pwm_mode(timer_dev *dev, uint8 channel);
static void output_compare_mode(timer_dev *dev, uint8 channel);

static inline void enable_irq(timer_dev *dev, uint8 interrupt);

/*
 * Devices
 *
 * Defer to the timer_private API for declaring these.
 */
static timer_dev timer1 = ADVANCED_TIMER(1);
timer_dev *TIMER1 = &timer1;



/*
 * Routines
 */

/**
 * @brief Call a function on timer devices.
 * @param fn Function to call on each timer device.
 */
void timer_foreach(void (*fn)(timer_dev*)) {
    fn(TIMER1);
}

/**
 * Initialize a timer, and reset its register map.
 * @param dev Timer to initialize
 */
void timer_init(timer_dev *dev) {
    timer_reg_map *regs = dev->regs;
    clk_enable_dev(dev->clk_id);
    regs->MODE &= ~EPCA_MODE_CLKSEL_MASK & ~EPCA_MODE_CLKDIV_MASK;
    regs->MODE |= EPCA_MODE_CLKSEL_APB | (19 << EPCA_MODE_CLKDIV_BIT);
    regs->LIMIT = 0x7CF;
    regs->MODE &= ~EPCACH_MODE_COSEL_MASK & ~EPCA_MODE_HDOSEL_MASK;
    regs->MODE |= EPCACH_MODE_COSEL_TOGGLE_OUTPUT | EPCA_MODE_HDOSEL_NO_DIFF;

    // Setup channel 0

    REG_WRITE_SET_CLR(TIMER1_CH0->CONTROL, 0, 1);
    TIMER1_CH0->CCAPV = 0x003E8;

    REG_WRITE_SET_CLR(regs->STATUS, 0, EPCA_STATUS_C0IOVFI_MASK | 1);

}

/**
 * @brief Disable a timer.
 *
 * The timer will stop counting, all DMA requests and interrupts will
 * be disabled, and no state changes will be output.
 *
 * @param dev Timer to disable.
 */
void timer_disable(timer_dev *dev) {

}

/**
 * Sets the mode of an individual timer channel.
 *
 * Note that not all timers can be configured in every mode.  For
 * example, basic timers cannot be configured to output compare mode.
 * Be sure to use a timer which is appropriate for the mode you want.
 *
 * @param dev Timer whose channel mode to set
 * @param channel Relevant channel
 * @param mode New timer mode for channel
 */
void timer_set_mode(timer_dev *dev, uint8 channel, timer_mode mode) {

}

/**
 * @brief Determine whether a timer has a particular capture/compare channel.
 *
 * Different timers have different numbers of capture/compare channels
 * (and some have none at all). Use this function to test whether a
 * given timer/channel combination will work.
 *
 * @param dev Timer device
 * @param channel Capture/compare channel, from 1 to 4
 * @return Nonzero if dev has channel, zero otherwise.
 */
int timer_has_cc_channel(timer_dev *dev, uint8 channel) {
    return 0;
}

/**
 * @brief Attach a timer interrupt.
 * @param dev Timer device
 * @param interrupt Interrupt number to attach to; this may be any
 *                  timer_interrupt_id or timer_channel value appropriate
 *                  for the timer.
 * @param handler Handler to attach to the given interrupt.
 * @see timer_interrupt_id
 * @see timer_channel
 */
void timer_attach_interrupt(timer_dev *dev,
                            uint8 interrupt,
                            voidFuncPtr handler) {

}

/**
 * @brief Detach a timer interrupt.
 * @param dev Timer device
 * @param interrupt Interrupt number to detach; this may be any
 *                  timer_interrupt_id or timer_channel value appropriate
 *                  for the timer.
 * @see timer_interrupt_id
 * @see timer_channel
 */
void timer_detach_interrupt(timer_dev *dev, uint8 interrupt) {

}

/*
 * Utilities
 */

static void disable_channel(timer_dev *dev, uint8 channel) {

}

static void pwm_mode(timer_dev *dev, uint8 channel) {

}

static void output_compare_mode(timer_dev *dev, uint8 channel) {

}

static void enable_adv_irq(timer_dev *dev, timer_interrupt_id id);
static void enable_bas_gen_irq(timer_dev *dev);

static inline void enable_irq(timer_dev *dev, timer_interrupt_id iid) {

}

/* Advanced control timers have several IRQ lines corresponding to
 * different timer interrupts.
 *
 * Note: This function assumes that the only advanced timers are TIM1
 * and TIM8, and needs the obvious changes if that assumption is
 * violated by a later STM32 series. */
static void enable_adv_irq(timer_dev *dev, timer_interrupt_id id) {

}

/* Basic and general purpose timers have a single IRQ line, which is
 * shared by all interrupts supported by a particular timer. */
static void enable_bas_gen_irq(timer_dev *dev) {

}
