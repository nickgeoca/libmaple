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
 * @file libmaple/include/libmaple/rcc.h
 * @brief Reset and Clock Control (RCC) interface.
 */

#ifndef _LIBMAPLE_RCC_H_
#define _LIBMAPLE_RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple_types.h>
#include <series/rcc.h>

extern volatile uint32 g_clk_sys_freq;

#define CLK_GET_AHB_PRESCALER    (1 << ((CLK_BASE->CONTROL & CLK_CR_AHBDIV_MASK) >> CLK_CR_AHBDIV_BIT))
#define CLK_GET_APB_PRESCALER    (1 << ((CLK_BASE->CONTROL & CLK_CR_APBDIV_MASK) >> CLK_CR_APBDIV_BIT))
/*
 * Returns the actual frequency output by the PLL
 */
static inline uint32 pll_get_actl_freq(uint32 src_freq, uint32 targ_freq)
{
    return src_freq * (uint32)(targ_freq / src_freq);
}
static inline clk_domain clk_dev_get_bus(clk_dev_id id) {
    if (id < CLK_LAST_AHB_ENTRY_) {
        return CLK_AHB;
    }
    else if (id < CLK_LAST_APB0_ENTRY_) {
        return CLK_APB0;
    }
    return CLK_APB1;
}

static inline uint32 clk_get_sys_freq(void) {
    return g_clk_sys_freq;
}

static inline uint32 clk_get_bus_freq(clk_dev_id id) {
    return clk_get_sys_freq() / ((clk_dev_get_bus(id) == CLK_AHB) ? (CLK_GET_AHB_PRESCALER) : (CLK_GET_AHB_PRESCALER * CLK_GET_APB_PRESCALER));
}

void pll_set_freq(uint32 freq);
void clk_switch_sysclk(clk_sysclk_src sysclk_src);
void clk_rcfg_devices(void);
void pll_set_ref(uint32 ref);
void clk_set_prescalers(clk_prescaler prescaler, uint32 divider);



#ifdef __cplusplus
} // extern "C"
#endif

#endif
