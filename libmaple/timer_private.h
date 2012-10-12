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
#define get_adv_irq_flags(reg) \
            ((EPCA_STATUS_CXCCI_MASK & reg)  >> EPCA_IRQ_CXCCI_SHIFT | \
            (EPCA_STATUS_OVFI_MASK & reg)    >> EPCA_IRQ_OVFI_SHIFT  | \
            (EPCA_STATUS_HALTI_MASK & reg)   >> EPCA_IRQ_HALTI_SHIFT | \
            (EPCA_STATUS_CXIOVFI_MASK & reg) >> EPCA_IRQ_CXIOVFI_SHIFT);

#define adv_chnl_cc_irq_enabled(chnl, dev) \
            (dev->chnl_regs[chnl]->CONTROL & EPCACH_CR_CCIEN_MASK)
#define adv_ovfi_irq_enabled(dev) \
            (dev->regs->CONTROL & EPCA_CR_OVFIEN_MASK)
#define adv_halt_irq_enabled(dev) \
            (dev->regs->CONTROL & EPCA_CR_HALTIEN_MASK)
#define adv_chnl_ovfi_irq_enabled(chnl, dev) \
            (dev->chnl_regs[chnl]->CONTROL & EPCACH_CR_CIOVFDEN_MASK)

#define adv_irq_enabled(bit, dev) \
            ( \
            bit <= TIMER_OVERFLOW_INTERRUPT ? adv_chnl_cc_irq_enabled(bit, dev) : /* chnl cap/cmp interrupt     */ \
            bit <= TIMER_HALT_INTERRUPT  ? adv_ovfi_irq_enabled(dev)         : /* timer overflow interrupt   */ \
            bit <= TIMER_OVFL1_INTERRUPT    ? adv_halt_irq_enabled(dev)         : /* halt interrupt             */ \
            adv_chnl_ovfi_irq_enabled(bit - TIMER_OVFL1_INTERRUPT, dev)           /* chnl overflow interrupt    */ \
            )

#define EPCA_IRQ_FLAGS_MASK     (EPCA_STATUS_CXCCI_MASK | EPCA_STATUS_OVFI_MASK | EPCA_STATUS_HALTI_MASK | EPCA_STATUS_CXIOVFI_MASK)
#define EPCA_IRQ_CXCCI_SHIFT    0
#define EPCA_IRQ_OVFI_SHIFT     (1 + EPCA_IRQ_CXCCI_SHIFT)
#define EPCA_IRQ_HALTI_SHIFT    (1 + EPCA_IRQ_OVFI_SHIFT)
#define EPCA_IRQ_CXIOVFI_SHIFT  (0 + EPCA_IRQ_HALTI_SHIFT)

static __always_inline void dispatch_adv(timer_dev *dev) {
    timer_reg_map *regs = dev->regs;
    uint32 status = regs->STATUS & EPCA_IRQ_FLAGS_MASK;
    uint32 control = regs->CONTROL & EPCA_IRQ_FLAGS_MASK;
    uint32 irq_flags;
    uint32 bit;

    irq_flags = get_adv_irq_flags(status);
    // Service interrupts
    do {
        bit = __builtin_ctz(irq_flags);
        irq_flags ^= 1 << bit;
        if (dev->handlers[bit] && adv_irq_enabled(bit, dev)) {
            dev->handlers[bit]();
        }
    } while (irq_flags);

    // Clear pending flags
    REG_WRITE_SET_CLR(regs->STATUS, 0, status);
}

static __always_inline void dispatch_general(timer_dev *dev) {

}

static __always_inline void dispatch_basic(timer_dev *dev) {

}

#endif
