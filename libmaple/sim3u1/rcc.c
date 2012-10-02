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

#include "rcc_private.h"

volatile uint32 clk_sys_freq = 0;
volatile uint32 clk_apb_freq = 0;
volatile uint32 clk_ahb_freq = 0;

void clk_init(uint32 sys_clk, uint32 ahb_div, uint32 apb_div)
{
    uint32 tmp;
    // Set clock dividers
    tmp = CLK_BASE->CONTROL;
    tmp &= ~(CLK_CR_AHBDIV_MASK | CLK_CR_APBDIV_MASK);
    CLK_CR_AHBDIV_DIVn(ahb_div, tmp);
    CLK_CR_APBDIV_DIVn(apb_div, tmp);
    CLK_BASE->CONTROL = tmp;

    // TODO [silabs]: pll
    clk_sys_freq = sys_clk;
    clk_ahb_freq = sys_clk / ahb_div;
    clk_apb_freq = clk_ahb_freq / apb_div;
}

static clk_domain clk_dev_get_bus(clk_dev_id id) {
    if (id < CLK_LAST_AHB_ENTRY_) {
        return CLK_AHB;
    }
    else if (id < CLK_LAST_APB0_ENTRY_) {
        return CLK_APB0;
    }
    return CLK_APB1;
}
#define CLK_GET_DEV_BIT(id_in, bus_in, bit_out) do { \
                                                    if (bus_in == CLK_AHB) { \
                                                        bit_out = 1 << id_in; \
                                                    } \
                                                    else if (bus_in == CLK_APB0) { \
                                                        bit_out = 1 << (id_in - CLK_LAST_AHB_ENTRY_ - 1); \
                                                    } \
                                                    else { \
                                                        bit_out = 1 << (id_in - CLK_LAST_APB0_ENTRY_ - 1); \
                                                    } \
                                                } while(0)

uint32 clk_get_bus_speed(clk_dev_id id) {
    return (clk_dev_get_bus(id) == CLK_AHB) ? clk_ahb_freq : clk_apb_freq;
}

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

