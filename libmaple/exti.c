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
 * @file libmaple/exti.c
 * @brief External interrupt control routines
 */

#include <libmaple/exti.h>
#include <libmaple/libmaple.h>
#include <libmaple/nvic.h>
#include <libmaple/bitband.h>

static inline void dispatch_single_exti(uint32 exti_num);
static inline void dispatch_extis(uint32 start, uint32 stop);

/*
 * Internal state
 */

typedef struct exti_channel {
    void (*handler)(void *);
    void *arg;
} exti_channel;

static exti_channel exti_channels[] = {
    { .handler = NULL, .arg = NULL },  // EXTI0
    { .handler = NULL, .arg = NULL },  // EXTI1
};

/*
 * Portable routines
 */

/**
 * @brief Register a handler to run upon external interrupt.
 *
 * This function assumes that the interrupt request corresponding to
 * the given external interrupt is masked.
 *
 * @param num     External interrupt line number.
 * @param port    Port to use as source input for external interrupt.
 * @param handler Function handler to execute when interrupt is triggered.
 * @param mode    Type of transition to trigger on, one of:
 *                EXTI_RISING, EXTI_FALLING, EXTI_RISING_FALLING.
 * @see exti_num
 * @see exti_cfg
 * @see voidFuncPtr
 * @see exti_trigger_mode
 */
void exti_attach_interrupt(exti_num num,
                           exti_cfg cfg,
                           voidFuncPtr handler,
                           exti_trigger_mode mode) {
    // Call callback version with arg being null
    exti_attach_callback(num, cfg, (voidArgumentFuncPtr)handler, NULL, mode);
}

/**
 * @brief Register a handler with an argument to run upon external interrupt.
 *
 * This function assumes that the interrupt request corresponding to
 * the given external interrupt is masked.
 *
 * @param num     External interrupt line number.
 * @param port    Port to use as source input for external interrupt.
 * @param handler Function handler to execute when interrupt is triggered.
 * @param arg     Argument to pass to the interrupt handler.
 * @param mode    Type of transition to trigger on, one of:
 *                EXTI_RISING, EXTI_FALLING, EXTI_RISING_FALLING.
 * @see exti_num
 * @see exti_cfg
 * @see voidFuncPtr
 * @see exti_trigger_mode
 */
void exti_attach_callback(exti_num num,
                          exti_cfg trig_num,
                          voidArgumentFuncPtr handler,
                          void *arg,
                          exti_trigger_mode mode) {
    uint32 bit_offset, trig_used = 1;
    uint32 control_reg = EXTI_BASE->CONTROL0;
    ASSERT(handler);

    // The trig num starts at one in the Wiring API
    trig_num -= 1;

    // Trigger is used by an EXTI 0?
    if ((control_reg & 0xf) == trig_num && control_reg & BIT(7)) {
        num = 0;
    }
    // Trigger is used by an EXTI 1?
    else if ((control_reg >> 8 & 0xf) == trig_num && control_reg & BIT(15)) {
        num = 1;
    }
    // Trigger is not used
    else {
        trig_used = 0;
        // Exit if both EXTIs are used
        if (control_reg & (BIT(7) | BIT(15)) ==
                (BIT(7) | BIT(15))) {
            return;
        }
        // Choose the unused EXTI
        num = (control_reg & BIT(7)) ? 1 : 0;
    }
    bit_offset = num ? 8 : 0;

    /* Register the handler */
    exti_channels[num].handler = handler;
    exti_channels[num].arg = arg;

    /* Set trigger mode */
    switch (mode) {
    case EXTI_FALLING:
        REG_SET_CLR(EXTI_BASE->CONTROL0, 1, BIT(5 + bit_offset));
        REG_SET_CLR(EXTI_BASE->CONTROL0, 0, BIT(4 + bit_offset));
        break;
    default: // EXTI_RISING
        REG_SET_CLR(EXTI_BASE->CONTROL0, 1, BIT(5 + bit_offset));
        REG_SET_CLR(EXTI_BASE->CONTROL0, 1, BIT(4 + bit_offset));
        break;
    }

    if (trig_used) {
        return;
    }

    /* Set trigger number */
    REG_SET_CLR(EXTI_BASE->CONTROL0,  0, 0xf << (bit_offset));
    REG_SET_CLR(EXTI_BASE->CONTROL0,  1, trig_num << (bit_offset));

    /* Unmask external interrupt request */
    REG_SET_CLR(EXTI_BASE->CONTROL0, 1, BIT(7 + bit_offset));

    /* Enable the interrupt line */
    switch(num)
    {
        case EXTI0:
            nvic_clr_pending_irq(NVIC_PBEXT0);
            nvic_irq_enable(NVIC_PBEXT0);
            break;
        case EXTI1:
            nvic_clr_pending_irq(NVIC_PBEXT1);
            nvic_irq_enable(NVIC_PBEXT1);
            break;
    }
}

/**
 * @brief Unregister an external interrupt handler
 * @param num External interrupt line to disable.
 * @see exti_num
 */
void exti_detach_interrupt(exti_num num) {
    uint32 trig_num;

    trig_num = num - 1;
    /* Determine which exti it is. If not recognized, return  */
    if ((EXTI_BASE->CONTROL0 & 0xf) == trig_num && EXTI_BASE->CONTROL0 & BIT(7)) {
        num = 0;
    }
    else if ((EXTI_BASE->CONTROL0 >> 8 & 0xf) == trig_num && EXTI_BASE->CONTROL0 & BIT(15)) {
        num = 1;
    }
    else {
        return;
    }

    /* Mask the interrupt request */
    REG_SET_CLR(EXTI_BASE->CONTROL0, 0, BIT(7 + num * 8));

    /* Clear pending interrupts */
    switch(num)
    {
        case EXTI0:
            nvic_clr_pending_irq(NVIC_PBEXT0);
            nvic_irq_disable(NVIC_PBEXT0);
            break;
        case EXTI1:
            nvic_clr_pending_irq(NVIC_PBEXT1);
            nvic_irq_disable(NVIC_PBEXT1);
            break;
    }

    /* Unregister the user's handler */
    exti_channels[num].handler = NULL;
    exti_channels[num].arg = NULL;
}

/*
 * Interrupt handlers
 */

void __irq_exti0(void) {
    dispatch_single_exti(EXTI0);
}

void __irq_exti1(void) {
    dispatch_single_exti(EXTI1);
}


/*
 * Auxiliary functions
 */

/* This dispatch routine is for non-multiplexed EXTI lines only; i.e.,
 * it doesn't check EXTI_PR. */
static __always_inline void dispatch_single_exti(uint32 exti) {
    voidArgumentFuncPtr handler = exti_channels[exti].handler;

    if (!handler) {
        return;
    }

    handler(exti_channels[exti].arg);
}
void exti_select(exti_num num, exti_cfg cfg) {

}

