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
