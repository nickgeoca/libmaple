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
 * @file wirish/stm32f1/boards_setup.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief STM32F1 chip setup.
 *
 * This file controls how init() behaves on the STM32F1. Be very
 * careful when changing anything here. Many of these values depend
 * upon each other.
 */

#include "boards_private.h"

#include <libmaple/gpio.h>
#include <libmaple/timer.h>

#include <wirish/boards.h>
#include <wirish/usb_serial.h>

// Allow boards to provide a PLL multiplier. This is useful for
// e.g. STM32F100 value line MCUs, which use slower multipliers.
// (We're leaving the default to RCC_PLLMUL_9 for now, since that
// works for F103 performance line MCUs, which is all that LeafLabs
// currently officially supports).
#ifndef BOARD_RCC_PLLMUL
#define BOARD_RCC_PLLMUL RCC_PLLMUL_9
#endif

namespace wirish {
    namespace priv {

        __weak adc_prescaler w_adc_pre = (adc_prescaler)0;
        // Default Group Configuration:
        //  Grp 0: 10Bit, Seq Len 1;    Grp 1: 10Bit, Seq Len 16
        //  Grp 2: 12Bit, Seq Len 1;    Grp 3: 12Bit, Seq Len 16
        __weak adc_grp_num w_adc_grp = (adc_grp_num)2;

        __weak void board_reset_pll(void) {
            // TODO
        }

        __weak void board_setup_clock_prescalers(uint32 sys_freq) {
            uint32 apb_div = CLK_APB_HCLK_DIV_1;
            uint32 ahb_div = CLK_AHB_SYSCLK_DIV_1;

            // Set limit on apb bus to 50 MHz
            apb_div = (sys_freq / (1 << ahb_div)) > 50000000 ? CLK_APB_HCLK_DIV_2 : CLK_APB_HCLK_DIV_1;
            clk_set_prescalers(CLK_PRESCALE_APB, apb_div);
            clk_set_prescalers(CLK_PRESCALE_AHB, ahb_div);
        }

        __weak void board_setup_gpio(void) {
            gpio_init_all();

        }

        __weak void board_setup_xbar(void) {
            gpio_init_xbar();

        }

        __weak void board_setup_usb(void) {

        }

        __weak void series_init(void) {
            // Turn off watchdog
            *((volatile uint32*)0x4002D020) = 0;
            clk_enable_dev(CLK_MISC1);
            *((volatile uint32*)0x40030030) = 0xA5;
            *((volatile uint32*)0x40030030) = 0xDD;
        }
        __weak void board_setup_rtc(void) {
            __io uint32 *rtc_base = (__io uint32 *)0x40029000;

            // Set RTC pins as analog
            gpio_set_modef(GPIOA, 9, GPIO_ANALOG, GPIO_DRIVE_WEAK);
            gpio_set_modef(GPIOA, 10, GPIO_ANALOG, GPIO_DRIVE_WEAK);

            // Enable clock
            clk_enable_dev(CLK_MISC0);

            // Clear interrupts
            nvic_clr_pending_irq(NVIC_RTC0ALRM);
            nvic_irq_enable(NVIC_RTC0ALRM);

            // enable high speed mode
            REG_SET_CLR(*(__io uint32 *)((uint32)rtc_base + 0x10), 1, 1 << 7);

            // disable auto gain control
            REG_SET_CLR(*rtc_base, 0, 0x00040000);
            // enable bias doubler
            REG_SET_CLR(*rtc_base, 1, 1 << 16);
            // enable auto load cap stepping
            REG_SET_CLR(*rtc_base, 1, 1 << 3);
            // set clk source as rtc
            REG_SET_CLR(*rtc_base, 0, 1 << 30);
            // set as crystal oscillator
            REG_SET_CLR(*rtc_base, 1, 0x00020000);
            // enable module
            REG_SET_CLR(*rtc_base, 1, 1 << 31);

            // Wait at least 20 ms
            delay(20);

            // Poll clock until stable
            while (!((*(__io uint32 *)((uint32)rtc_base + 0x10)) & 0x20));

            // Poll load capacitance ready
            while (!((*(__io uint32 *)((uint32)rtc_base + 0x10)) & 0x100));

            // Wait at least 2 ms
            delay(2);
        }
    }
}
