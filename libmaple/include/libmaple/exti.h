/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * @file libmaple/include/libmaple/exti.h
 * @brief External interrupt control
 */

/* See notes/exti.txt for more info */

#ifndef _LIBMAPLE_EXTI_H_
#define _LIBMAPLE_EXTI_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <series/exti.h>        /* provides EXTI_BASE */
#include <libmaple/libmaple_types.h>

/*
 * Register map and base pointer.
 */

/** EXTI register map type */
typedef struct exti_reg_map {
    __io uint32 CONTROL0; // Base Address + 0x0
    __io uint32 CONTROL0_SET;
    __io uint32 CONTROL0_CLR;
} exti_reg_map;

/*
 * Types: exti_num, exti_cfg, exti_trigger_mode.
 *
 * A combination of these three specifies an external interrupt
 * configuration (see exti_attach_interrupt()).
 */

/** EXTI line. */
typedef enum exti_num {
    EXTI0,    /**< EXTI line 0 */
    EXTI1,    /**< EXTI line 1 */
} exti_num;

/**
 * @brief EXTI port configuration
 *
 * These specify which GPIO pin an external interrupt trigger should be
 * connected to.
 */
typedef enum exti_cfg {
    EXTIx_TRIG0,  /**< Pin: PC0  */
    EXTIx_TRIG1,  /**< Pin: PC1  */
    EXTIx_TRIG2,  /**< Pin: PC2  */
    EXTIx_TRIG3,  /**< Pin: PC3  */
    EXTIx_TRIG4,  /**< Pin: PC4  */
    EXTIx_TRIG5,  /**< Pin: PC5  */
    EXTIx_TRIG6,  /**< Pin: PC6  */
    EXTIx_TRIG7,  /**< Pin: PC7  */
    EXTIx_TRIG8,  /**< Pin: PD3  */
    EXTIx_TRIG9,  /**< Pin: PD4  */
    EXTIx_TRIG10, /**< Pin: PD5  */
    EXTIx_TRIG11, /**< Pin: PD6  */
    EXTIx_TRIG12, /**< Pin: PD7  */
    EXTIx_TRIG13, /**< Pin: PD8  */
    EXTIx_TRIG14, /**< Pin: PD9  */
    EXTIx_TRIG15, /**< Pin: PD10 */
} exti_cfg;

/** External interrupt trigger mode */
typedef enum exti_trigger_mode {
    EXTI_RISING,         /**< Trigger on the rising edge */
    EXTI_FALLING,        /**< Trigger on the falling edge */
    EXTI_RISING_FALLING  /**< Trigger on both the rising and falling edges */
} exti_trigger_mode;

/*
 * Routines
 */

void exti_attach_interrupt(exti_num num,
                           exti_cfg cfg,
                           voidFuncPtr handler,
                           exti_trigger_mode mode);
void exti_attach_callback(exti_num num,
                          exti_cfg port,
                          voidArgumentFuncPtr handler,
                          void *arg,
                          exti_trigger_mode mode);
void exti_detach_interrupt(exti_num num);

/**
 * @brief Set the GPIO port for an EXTI line.
 *
 * This is a low-level routine that most users will not
 * need. exti_attach_interrupt() handles calling this function
 * appropriately.
 *
 * @param num EXTI line
 * @param port EXTI configuration for GPIO port to connect to num.
 * @see exti_num
 * @see exti_cfg
 */
extern void exti_select(exti_num num, exti_cfg port);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
