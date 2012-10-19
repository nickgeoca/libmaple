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
#define NR_ADV_HANDLERS                 14
/*
 * Devices
 *
 * Defer to the timer_private API for declaring these.
 */

static const nvic_irq_num timer1_irqs[1] = {NVIC_EPCA1};
static const timer_chnl_reg_map *t1_chnl_regs[6] = {TIMER1_CH0, TIMER1_CH1, TIMER1_CH2,
                                               TIMER1_CH3, TIMER1_CH4, TIMER1_CH5};
static timer_dev timer1 = {
    .regs = TIMER1_BASE,
    .clk_id = CLK_EPCA1,
    .type = TIMER_ADVANCED,
    .nvic_irqs.irq_count = 1,
    .nvic_irqs.irq_array = timer1_irqs,
    .chnl_regs = t1_chnl_regs,
    .handlers = { [NR_ADV_HANDLERS - 1] = 0 }
};
timer_dev *TIMER1 = &timer1;

static const nvic_irq_num timer2_irqs[1] = {NVIC_PCA1};
static const timer_chnl_reg_map *t2_chnl_regs[2] = {TIMER2_CH0, TIMER2_CH1};
static timer_dev timer2 = {
    .regs = TIMER2_BASE,
    .clk_id = CLK_PCA1,
    .type = TIMER_GENERAL,
    .nvic_irqs.irq_count = 1,
    .nvic_irqs.irq_array = timer2_irqs,
    .chnl_regs = t2_chnl_regs,
    .handlers = { [0] = 0 }
};
timer_dev *TIMER2 = &timer2;

static const nvic_irq_num timer3_irqs[1] = {NVIC_PCA2};
static const timer_chnl_reg_map *t3_chnl_regs[2] = {TIMER3_CH0, TIMER3_CH1};
static timer_dev timer3 = {
    .regs = TIMER3_BASE,
    .clk_id = CLK_PCA2,
    .type = TIMER_GENERAL,
    .nvic_irqs.irq_count = 1,
    .nvic_irqs.irq_array = timer3_irqs,
    .chnl_regs = t3_chnl_regs,
    .handlers = { [0] = 0 }
};
timer_dev *TIMER3 = &timer3;

static const nvic_irq_num timer4_irqs[2] = {NVIC_TIMER0L, NVIC_TIMER0H};
static timer_dev timer4 = {
    .regs = TIMER4_BASE,
    .clk_id = CLK_TIMER1,
    .type = TIMER_BASIC,
    .nvic_irqs.irq_count = 2,
    .nvic_irqs.irq_array = timer4_irqs,
    .chnl_regs = 0,
    .handlers = { [0] = 0 }
};
timer_dev *TIMER4 = &timer4;

static const nvic_irq_num timer5_irqs[2] = {NVIC_TIMER1L, NVIC_TIMER1H};
static timer_dev timer5 = {
    .regs = TIMER5_BASE,
    .clk_id = CLK_TIMER2,
    .type = TIMER_BASIC,
    .nvic_irqs.irq_count = 2,
    .nvic_irqs.irq_array = timer5_irqs,
    .chnl_regs = 0,
    .handlers = { [0] = 0 }
};
timer_dev *TIMER5 = &timer5;

/*
 * Routines
 */

/**
 * @brief Call a function on timer devices.
 * @param fn Function to call on each timer device.
 */
void timer_foreach(void (*fn)(timer_dev*)) {
    fn(TIMER1);
    fn(TIMER2);
    fn(TIMER3);
    fn(TIMER4);
    fn(TIMER5);
}

/**
 * Initialize a timer, and reset its register map.
 * @param dev Timer to initialize
 */
void timer_init(timer_dev *dev) {
    timer_reg_map *regs = dev->regs;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;

    clk_enable_dev(dev->clk_id);

    switch (dev->type) {
    case TIMER_BASIC:
        // Initialize registers
        regs_b->CONFIG = 0;
        regs_b->CLKDIV = 0;
        regs_b->COUNT = 0;
        regs_b->CAPTURE = 0;
        // Split timer mode
        REG_SET_CLR(regs_b->CONFIG, 1, TIMER_CFGR_SPLITEN_EN);
        // Select high timer clock source
        REG_SET_CLR(regs_b->CONFIG, 1, TIMER_CFGR_HCLK_TIMER_CLKDIV);
        // High pwm mode
        REG_SET_CLR(regs_b->CONFIG, 1, TIMER_CFGR_HMD_PWM);
        // Set clock divider. Run at APB rate.
        regs_b->CLKDIV = 255;

        break;
    default:

        // Set clock speed
        regs->MODE &= ~EPCA_MODE_CLKSEL_MASK & ~EPCA_MODE_CLKDIV_MASK;
        regs->MODE |= EPCA_MODE_CLKSEL_APB | (0 << EPCA_MODE_CLKDIV_BIT);

        // Set PWM frequency
        regs->LIMIT = 0;
        regs->MODE &= ~EPCACH_MODE_COSEL_MASK & ~EPCA_MODE_HDOSEL_MASK;
        regs->MODE |= EPCACH_MODE_COSEL_TOGGLE_OUTPUT | EPCA_MODE_HDOSEL_NO_DIFF;

        // Disable all interrupts
        regs->STATUS = 0;
        break;
    }
    // Enable IRQ on NVIC
    nvic_clr_pending_dev(&dev->nvic_irqs);
    nvic_irq_enable_dev(&dev->nvic_irqs);
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
    nvic_clr_pending_dev(&dev->nvic_irqs);
    nvic_irq_disable_dev(&dev->nvic_irqs);
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
    ASSERT_FAULT(channel > 0 && channel <= 4);

    /* TODO decide about the basic timers */
    ASSERT(dev->type != TIMER_BASIC);
    if (dev->type == TIMER_BASIC)
        return;

    switch (mode) {
    case TIMER_DISABLED:
        disable_channel(dev, channel);
        break;
    case TIMER_PWM:
        pwm_mode(dev, channel);
        break;
    case TIMER_OUTPUT_COMPARE:
        output_compare_mode(dev, channel);
        break;
    }
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
    dev->handlers[interrupt] = handler;
    timer_enable_irq(dev, interrupt);
    enable_irq(dev, interrupt);
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
    timer_disable_irq(dev, interrupt);
    dev->handlers[interrupt] = NULL;
}

/*
 * Utilities
 */

static void disable_channel(timer_dev *dev, uint8 channel) {
    timer_detach_interrupt(dev, channel);
    timer_cc_disable(dev, channel);
}

static void pwm_mode(timer_dev *dev, uint8 channel) {
    timer_disable_irq(dev, channel);
    timer_oc_set_mode(dev, channel, TIMER_OC_MODE_PWM_1, TIMER_OC_PE);
    timer_cc_enable(dev, channel);
}

static void output_compare_mode(timer_dev *dev, uint8 channel) {

}

static void enable_adv_irq(timer_dev *dev, timer_interrupt_id id);
static void enable_bas_gen_irq(timer_dev *dev);

static inline void enable_irq(timer_dev *dev, timer_interrupt_id iid) {
    if (dev->type == TIMER_BASIC) {
        enable_bas_gen_irq(dev);
    } else {
        enable_adv_irq(dev, iid);
    }
}

/* Advanced control timers have several IRQ lines corresponding to
 * different timer interrupts.
 *
 * Note: This function assumes that the only advanced timers are TIM1
 * and TIM8, and needs the obvious changes if that assumption is
 * violated by a later STM32 series. */
static void enable_adv_irq(timer_dev *dev, timer_interrupt_id id) {
    if (dev->type == TIMER_ADVANCED) {
        nvic_irq_enable(NVIC_EPCA1);
    }
    else {
        if (dev == TIMER2) {
            nvic_irq_enable(NVIC_PCA1);
        }
        else {
            nvic_irq_enable(NVIC_PCA2);
        }
    }
}

/* Basic and general purpose timers have a single IRQ line, which is
 * shared by all interrupts supported by a particular timer. */
static void enable_bas_gen_irq(timer_dev *dev) {
    if (dev == TIMER4) {
        // nvic_irq_enable(NVIC_TIMER0L);
        // nvic_irq_enable(NVIC_TIMER0H);
    }
    else {
        // nvic_irq_enable(NVIC_TIMER1L);
        // nvic_irq_enable(NVIC_TIMER1H);
    }

    // FIXME: enable bas gen irq
}
