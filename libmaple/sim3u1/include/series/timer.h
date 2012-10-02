/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011,2012 LeafLabs, LLC.
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
 * @file   libmaple/stm32f2/include/series/timer.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  STM32F2 timer support.
 */

#ifndef _LIBMAPLE_STM32F2_TIMER_H_
#define _LIBMAPLE_STM32F2_TIMER_H_

#include <libmaple/libmaple_types.h>
#include <libmaple/gpio.h>      /* for gpio_af */

/*
 * Register maps and base pointers
 */

/**
 * @brief STM32F2 general purpose timer register map type
 *
 * Note that not all general purpose timers have all of these
 * registers. Consult your chip's reference manual for the details.

struct timer_adv_reg_map;
struct timer_bas_reg_map;


/*
 * Register bit definitions
 */
#define TIMER1_BASE     ((timer_reg_map*)0x4000E180)
#define TIMER2_BASE     ((timer_reg_map*)0x4000F180)
#define TIMER3_BASE     ((timer_reg_map*)0x40010180)
/* TIM2 option register */

/** Timer 2 option register internal trigger 1 remap */
#define TIMER2_OR_ITR1_RMP              (0x3 << 10)
/** Timer 2 OR internal trigger 1: TIM8_TRGOUT */
#define TIMER2_OR_ITR1_RMP_TIM8_TRGOUT  (0x0 << 10)
/** Timer 2 OR internal trigger 1: Ethernet PTP trigger output */
#define TIMER2_OR_ITR1_RMP_PTP_TRGOUT   (0x1 << 10)
/** Timer 2 OR internal trigger 1: USB OTG full speed start of frame */
#define TIMER2_OR_ITR1_RMP_OTG_FS_SOF   (0x2 << 10)
/** Timer 2 OR internal trigger 1: USB OTG high speed start of frame */
#define TIMER2_OR_ITR1_RMP_OTG_HS_SOF   (0x3 << 10)

/* TIM5 option register */

/**
 * Timer 5 option register input 4 remap.
 *
 * These bits control whether TIM5_CH4 is connected to a GPIO or a
 * clock. Connecting to a GPIO is the normal mode, useful for e.g. PWM
 * generation or input pulse duration measurement. Connecting to a
 * clock is useful for calibrating that clock.
 */
#define TIMER5_OR_TI4_RMP               (0x3 << 6)
/**
 * Timer 5 OR input 4: Timer 5 channel 4 connected to GPIO. */
#define TIMER5_OR_TI4_RMP_GPIO          (0x0 << 6)
/**
 * Timer 5 OR input 4: low speed internal clock (LSI) is connected to
 * TIM5_CH4. */
#define TIMER5_OR_TI4_RMP_LSI           (0x1 << 6)
/**
 * Timer 5 OR input 4: low speed external clock (LSE) is connected to
 * TIM5_CH4. */
#define TIMER5_OR_TI4_RMP_LSE           (0x2 << 6)
/**
 * Timer 5 OR input 4: real time clock (RTC) output is connected to
 * TIM5_CH4. */
#define TIMER5_OR_TI4_RMP_RTC           (0x3 << 6)

/*
 * Device pointers
 */

struct timer_dev;

extern struct timer_dev *TIMER1;

/*
 * Routines
 */

gpio_af timer_get_af(struct timer_dev *dev);

#endif
