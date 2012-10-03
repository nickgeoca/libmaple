/******************************************************************************
 * The MIT License
 *
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
 * @file   libmaple/timer_private.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Private, internal timer APIs.
 */

#ifndef _LIBMAPLE_TIMER_PRIVATE_H_
#define _LIBMAPLE_TIMER_PRIVATE_H_

/*
 * Helper macros for declaring timer_devs of various timer_types
 */

/* The indexes of user handlers in a timer_dev.handlers are just like
 * the corresponding DIER bits, as follows: */



/* For declaring advanced timers. */
#define ADVANCED_TIMER(num)                                             \
    {                                                                   \
        .regs = TIMER##num##_BASE,                           \
        .clk_id = CLK_EPCA##num,                                       \
        .type = TIMER_ADVANCED,                                         \
        .chnl_base = TIMER##num##_CH0,                     \
    }


/*
 * IRQ handlers
 *
 * These decode TIMx_DIER and TIMx_SR, then dispatch to the user-level
 * IRQ handlers. They also clean up TIMx_SR afterwards, so the user
 * doesn't have to deal with register details.
 *
 * Notes:
 *
 * - These dispatch routines make use of the fact that DIER interrupt
 *   enable bits and SR interrupt flags have common bit positions.
 *   Thus, ANDing DIER and SR lets us check if an interrupt is enabled
 *   and if it has occurred simultaneously.
 *
 * - We force these routines to inline to avoid call overhead, but
 *   there aren't any measurements to prove that this is actually a
 *   good idea.  Profile-directed optimizations are definitely wanted. */

/* A special-case dispatch routine for timers which only serve a
 * single interrupt on a given IRQ line.
 *
 * This function still checks DIER & SR, as in some cases, a timer may
 * only serve a single interrupt on a particular NVIC line, but that
 * line may be shared with another timer. For example, the timer 1
 * update interrupt shares an IRQ line with the timer 10 interrupt on
 * STM32F1 (XL-density), STM32F2, and STM32F4. */
static __always_inline void dispatch_single_irq(timer_dev *dev,
                                                timer_interrupt_id iid,
                                                uint32 irq_mask) {

}

/* Helper macro for dispatch routines which service multiple interrupts. */
#define handle_irq(dier_sr, irq_mask, handlers, iid, handled_irq) do {  \
        if ((dier_sr) & (irq_mask)) { ;}                                  \
                                                              \
    } while (0)

static __always_inline void dispatch_adv_brk(timer_dev *dev) {

}

static __always_inline void dispatch_adv_up(timer_dev *dev) {

}

static __always_inline void dispatch_adv_trg_com(timer_dev *dev) {

}

static __always_inline void dispatch_adv_cc(timer_dev *dev) {

}

static __always_inline void dispatch_general(timer_dev *dev) {

}

/* On F1 (XL-density), F2, and F4, TIM9 and TIM12 are restricted
 * general-purpose timers with update, CC1, CC2, and TRG interrupts. */
static __always_inline void dispatch_tim_9_12(timer_dev *dev) {

}

/* On F1 (XL-density), F2, and F4, timers 10, 11, 13, and 14 are
 * restricted general-purpose timers with update and CC1 interrupts. */
static __always_inline void dispatch_tim_10_11_13_14(timer_dev *dev) {

}

static __always_inline void dispatch_basic(timer_dev *dev) {

}

#endif
