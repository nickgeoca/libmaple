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
 * @file libmaple/stm32f2/rcc.c
 * @brief STM32F2 RCC.
 */

#include <libmaple/rcc.h>
#include <libmaple/libmaple.h>
#include <series/flash.h>
#include "rcc_private.h"

volatile uint32 g_clk_sys_freq = 0;

void clk_rcfg_devices(void)
{
    flash_set_latency(clk_get_bus_freq(CLK_FLASH));
    return;
}

#define PLL_LOCKED_TRUE         (PLL_BASE->CONTROL & PLL_CR_LCKI_MASK)
void pll_freqency_lock(uint32 freq)
{
    // Guess initial mode
    uint8 mode = 4;
    uint32 tmp;
    if (freq < 35000000) {
      mode = 0;
    }
    else if (freq < 45000000) {
      mode = 1;
    }
    else if (freq < 55000000) {
      mode = 2;
    }
    else if (freq < 70000000) {
      mode = 3;
    }

    // set freqency adjuster value
    PLL_BASE->CALCONFIG &= ~PLL_CALCONFIG_CAL_MASK;
    PLL_BASE->CALCONFIG |= 0xFFF << PLL_CALCONFIG_CAL_BIT;

    // set freqency range
    PLL_BASE->CALCONFIG &= ~PLL_CALCONFIG_RANGE_MASK;
    PLL_BASE->CALCONFIG |= mode << PLL_CALCONFIG_RANGE_BIT;

    // Set to freqency lock mode
    REG_WRITE_SET_CLR(PLL_BASE->CONTROL, 0, PLL_CR_OUTMD_MASK);
    REG_WRITE_SET_CLR(PLL_BASE->CONTROL, 1, PLL_CR_OUTMD_FLL);

    // wait until pll is locked
    while (1) {
        while (!(PLL_LOCKED_TRUE || PLL_BASE->CONTROL & (PLL_CR_LLMTF_MASK | PLL_CR_HLMTF_MASK)));
        if (PLL_LOCKED_TRUE) {
            return;
        }
        // disable dco output
        REG_WRITE_SET_CLR(PLL_BASE->CONTROL, 0, PLL_CR_OUTMD_MASK);

        // Adjust range
        if ((PLL_BASE->CONTROL & PLL_CR_LLMTF_MASK) && (mode < 4)) {
            mode += 1;
        }
        else if (mode < 4) {
            mode -= 1;
        }
        // set freqency range
        PLL_BASE->CALCONFIG &= ~PLL_CALCONFIG_RANGE_MASK;
        PLL_BASE->CALCONFIG |= mode << PLL_CALCONFIG_RANGE_BIT;

        // set to freqency lock mode
        REG_WRITE_SET_CLR(PLL_BASE->CONTROL, 1, PLL_CR_OUTMD_FLL);
    }
}

void pll_set_freq(uint32 freq)
{
    // Switch clocks while pll is getting setup
    clk_set_clk_variable(20000000);
    clk_switch_sysclk(CLK_SRC_LP);
    // Disable digitally controlled oscillator
    REG_WRITE_SET_CLR(PLL_BASE->CONTROL, 0, PLL_CR_OUTMD_MASK);
    pll_set_prescaler(freq / 32768, 1);
    pll_freqency_lock(freq);
}
void pll_set_ref(uint32 ref)
{
    REG_WRITE_SET_CLR(PLL_BASE->CONTROL, 0, PLL_CR_REFSEL_MASK);
    REG_WRITE_SET_CLR(PLL_BASE->CONTROL, 1, ref << PLL_CR_REFSEL_BIT);
}

void pll_set_prescaler(uint32 num, uint32 denom)
{
    PLL_BASE->DIVIDER = (num - 1) << PLL_DIVIDER_N_BIT | (denom - 1) << PLL_DIVIDER_M_BIT;
}

void clk_switch_sysclk(clk_sysclk_src sysclk_src)
{
    uint32 control = CLK_BASE->CONTROL & ~CLKCTRL_CR_AHBSEL_MASK;
    control |= sysclk_src;
    // Wait until the oscillators are not busy
    while (CLK_BASE->CONTROL & CLKCTRL_CR_OBUSYF_MASK);
    CLK_BASE->CONTROL = control;
    // Update TPIU_ACPR
    *((__io uint32 *) 0xE0040010) = ((50 * clk_get_sys_freq()) / 20000000) - 1;
}

void clk_set_prescalers(clk_prescaler prescaler, uint32 divider)
{
    uint32 control = CLK_BASE->CONTROL;
    if (prescaler == CLK_PRESCALE_AHB) {
        control &= ~CLKCTRL_CR_AHBDIV_MASK;
        control |= divider << CLKCTRL_CR_AHBDIV_BIT;
    }
    else {
        control &= ~CLKCTRL_CR_APBDIV_MASK;
        control |= divider << CLKCTRL_CR_APBDIV_BIT;
    }
    // Wait until the oscillators are not busy
    while (CLK_BASE->CONTROL & CLKCTRL_CR_OBUSYF_MASK);
    CLK_BASE->CONTROL = control;
}

void clk_set_clk_variable(uint32 sys_clk)
{
    g_clk_sys_freq = sys_clk;
}


#define CLK_GET_DEV_BIT(id_in, bus_in, bit_out)                 \
    do {                                                        \
        if (bus_in == CLK_AHB) {                                \
            bit_out = 1 << id_in;                               \
        }                                                       \
        else if (bus_in == CLK_APB0) {                          \
            bit_out = 1 << (id_in - CLK_LAST_AHB_ENTRY_ - 1);   \
        }                                                       \
        else {                                                  \
            bit_out = 1 << (id_in - CLK_LAST_APB0_ENTRY_ - 1);  \
        }                                                       \
    } while(0)




#if 0

void clk_set_prescaler(rcc_prescaler prescaler, uint32 divider) {

}

/* pll_cfg->data must point to a struct stm32f2_rcc_pll_data. */
void clk_configure_pll(rcc_pll_cfg *pll_cfg) {

}

/**
 * @brief Get a peripheral's clock domain
 * @param id Clock ID of the peripheral whose clock domain to return
 * @return Clock source for the given clock ID
 */
rcc_clk_domain clk_dev_domain(clk_dev_id id) {
    return NULL;
}

/**
 * @brief Switch the clock used as the source of the system clock.
 *
 * After switching the source, this function blocks until the new
 * clock source is in use.
 *
 * @param sysclk_src New system clock source.
 * @see rcc_sysclk_src
 */
void clk_switch_sysclk(rcc_sysclk_src sysclk_src) {

}

/*
 * Turning clocks off and on, querying their status.
 */

/* IMPORTANT NOTE FOR IMPLEMENTORS:
 *
 * libmaple assumes that enum rcc_clk enumerators are two-byte
 * values, stored in a uint16, in the following way:
 *
 *  - The high-order byte is the byte offset (from RCC_BASE) of the register
 *    to touch when turning on or off the given clock.
 *
 *  - The low-order byte is the bit in that register that turns the
 *    clock on or off.
 *
 * Example for STM32F1: Turning on the high-speed external clock (HSE)
 * involves setting HSEON, bit 16, of RCC_CR. The high-order byte is
 * then offsetof(struct rcc_reg_map, CR) = 0, and the low-order byte
 * is 16.
 *
 * The corresponding value of RCC_CLK_HSE is thus (0 << 8) | 16 = 16.
 *
 * On all known STM32 series, this encoding has the property that
 * adding one to the low byte also gives the bit to check to determine
 * if the clock is ready. For example, on STM32F1, RCC_CR_HSERDY is
 * bit 17. If that's not the case on your series, rcc_is_clk_ready()
 * won't work for you. */

/* Returns the RCC register which controls the clock source. */
static inline __io uint32* clk_dev_reg(rcc_clk clock) {
    return NULL;
}

/* Returns a mask in rcc_clk_reg(clock) to be used for turning the
 * clock on and off */
static inline uint32 clk_dev_on_mask(rcc_clk clock) {
    return 0;
}

/* Returns a mask in rcc_clk_reg(clock) to be used when checking the
 * readiness of the clock. */
static inline uint32 clk_dev_ready_mask(rcc_clk clock) {
    return 0;
}
#endif
/**
 * @brief Turn on a clock source.
 *
 * After this routine exits, callers should ensure that the clock
 * source is ready by waiting until rcc_is_clk_ready(clock) returns
 * true.
 *
 * @param clock Clock to turn on.
 * @see rcc_turn_off_clk()
 * @see rcc_is_clk_ready()
 */
void clk_enable_dev(clk_dev_id clock) {
    uint32 bit;
    clk_domain bus = clk_dev_get_bus(clock);
    CLK_GET_DEV_BIT(clock, bus, bit);


    switch (bus) {
    case CLK_AHB:
        REG_WRITE_SET_CLR(CLK_BASE->AHBCLKG, 1, bit);
        break;
    case CLK_APB0:
        REG_WRITE_SET_CLR(CLK_BASE->APBCLKG0, 1, bit);
        break;
    case CLK_APB1:
        REG_WRITE_SET_CLR(CLK_BASE->APBCLKG1, 1, bit);
        break;
    }
}

/**
 * @brief Turn off a clock source.
 *
 * In certain configurations, certain clock sources cannot be safely
 * turned off. (For example, the main PLL on STM32F1 devices cannot be
 * turned off if it has been selected as the SYSCLK source). Consult
 * the reference material for your MCU to ensure it is safe to call
 * this function.
 *
 * @param clock Clock to turn off.
 * @see rcc_turn_on_clk()
 * @see rcc_is_clk_ready()
 */
void clk_disable_dev(clk_dev_id clock) {
    uint32 bit;
    clk_domain bus = clk_dev_get_bus(clock);
    CLK_GET_DEV_BIT(clock, bus, bit);

    switch (bus) {
    case CLK_AHB:
        REG_WRITE_SET_CLR(CLK_BASE->AHBCLKG, 0, bit);
        break;
    case CLK_APB0:
        REG_WRITE_SET_CLR(CLK_BASE->APBCLKG0, 0, bit);
        break;
    case CLK_APB1:
        REG_WRITE_SET_CLR(CLK_BASE->APBCLKG1, 0, bit);
        break;
    }
}



/**
 * @brief Check if a clock is on.
 * @param clock Clock to check.
 * @return 1 if the clock is on, 0 if the clock is off.
 */
int clk_is_dev_on(clk_dev_id clock) {
    return 0;
}

/**
 * @brief Check if a clock source is ready.
 *
 * In general, it is not safe to rely on a clock source unless this
 * function returns nonzero. Also note that this function may return
 * nonzero for a short period of time after a clock has been turned
 * off. Consult the reference material for your MCU for more details.
 *
 * @param clock Clock whose readiness to check for.
 * @return Nonzero if the clock is ready, zero otherwise.
 * @see rcc_turn_on_clk()
 * @see rcc_turn_off_clk()
 */
int clk_is_dev_rdy(clk_dev_id clock) {
    return 0;
}

