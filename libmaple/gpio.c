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
 * @file libmaple/gpio.c
 * @brief Generic STM32 GPIO support.
 */

#include <libmaple/gpio.h>
#include <libmaple/rcc.h>

/*
 * GPIO routines
 */

/**
 * Initialize a GPIO device.
 *
 * Enables the clock for and resets the given device.
 *
 * @param dev GPIO device to initialize.
 */
void gpio_init(gpio_dev *dev) {
    clk_enable_dev(dev->clk_id);
}


/*
 * GPIO devices
 */

gpio_dev gpioa = {
    .regs      = GPIOA_BASE,
    .clk_id    = CLK_PB,
};
/** GPIO port A device. */
gpio_dev* const GPIOA = &gpioa;

gpio_dev gpiob = {
    .regs      = GPIOB_BASE,
    .clk_id    = CLK_PB,
};
/** GPIO port B device. */
gpio_dev* const GPIOB = &gpiob;

gpio_dev gpioc = {
    .regs      = GPIOC_BASE,
    .clk_id    = CLK_PB,
};
/** GPIO port C device. */
gpio_dev* const GPIOC = &gpioc;

gpio_dev gpiod = {
    .regs      = GPIOD_BASE,
    .clk_id    = CLK_PB,
};
/** GPIO port D device. */
gpio_dev* const GPIOD = &gpiod;

gpio_dev gpioe = {
    .regs      = GPIOE_BASE,
    .clk_id    = CLK_PB,
};
/** GPIO port E device. */
gpio_dev* const GPIOE = &gpioe;

/*
 * GPIO routines
 */



/**
 * Initialize and reset all available GPIO devices.
 */
void gpio_init_all(void) {
    // Enable clock on port banks. All GPIO clk id's reference PBCFG
    clk_enable_dev(CLK_PB);

    // Enable Crossbars
    REG_SET_CLR(PBCFG_BASE->XBAR0H, 1, PBCFG_XBAR0H_XBAR0EN_MASK);
    REG_SET_CLR(PBCFG_BASE->XBAR1, 1, PBCFG_XBAR0H_XBAR0EN_MASK);

    // Enable Crossbar 1 signals & set properties
    REG_SET_CLR(PBCFG_BASE->XBAR1, 1, PBCFG_XBAR1_XBAR1EN_MASK);
    GPIOA->regs->std.PBSKIPEN = 0x0000FFFF;
    GPIOB->regs->std.PBSKIPEN = 0x0000FFFF; // 0xf00-timers
    GPIOC->regs->std.PBSKIPEN = 0x0000FFFF;
    GPIOD->regs->std.PBSKIPEN = 0x00007FFF;

    // Setup Port Bank 4
    if (PBCFG_BASE->PBKEY == PBCFG_PBKEY_KEY_INTERMEDIATE) {
        PBCFG_BASE->PBKEY = 0xF1;
    }
    else if (PBCFG_BASE->PBKEY == PBCFG_PBKEY_KEY_LOCKED) {
        PBCFG_BASE->PBKEY = 0xA5;
        PBCFG_BASE->PBKEY = 0xF1;
    }
    GPIOE->regs->hd.PBLOCK = 0;
    // Set high impedance as the PB HD safe state
    REG_SET_CLR(GPIOE->regs->hd.PBSS, 0, PBHD_PBSS_PB0SSSEL_MASK | PBHD_PBSS_PB1SSSEL_MASK | PBHD_PBSS_PB2SSSEL_MASK |
    PBHD_PBSS_PB3SSSEL_MASK | PBHD_PBSS_PB4SSSEL_MASK | PBHD_PBSS_PB5SSSEL_MASK);
    // Enable bias
    REG_SET_CLR(GPIOE->regs->hd.PBDRV, 1, 1 << PBHD_PBDRV_PBBIASEN_BIT);
    // Power level
    REG_SET_CLR(GPIOE->regs->hd.PBDRV, 0, 1 << PBHD_PBDRV_PBLVMD_BIT);
    // Enable drivers
    REG_SET_CLR(GPIOE->regs->hd.PBDRV, 1, PBHD_PBDRV_PBDRVEN_MASK);
    // Slew rate fastest
    REG_SET_CLR(GPIOE->regs->hd.PBDRV, 0, PBHD_PBDRV_PBSLEW_MASK);
    REG_SET_CLR(GPIOE->regs->hd.PBDRV, 1, 0 << PBHD_PBDRV_PBSLEW_BIT);
    // Disable current limit
    REG_SET_CLR(GPIOE->regs->hd.PBILIMIT, 0, 0x1F);
}

/**
 * @brief Set the mode of a GPIO pin.
 * @param dev GPIO device.
 * @param bit Bit on dev whose mode to set, 0--15.
 * @param mode Mode to set the pin to.
 * @param flags Flags to modify basic mode configuration
 */
void gpio_set_modef(gpio_dev *dev,
                    uint8 bit,
                    gpio_pin_mode mode,
                    unsigned flags) {
    gpio_reg_map *regs = dev->regs;
    unsigned shift = bit;
    unsigned mask = 1 << bit;


    /* Mode */
    REG_SET_CLR(regs->PBMDSEL, mode & (1 << GPIO_PBMDSEL_BIT), mask);

    /* High Drive GPIO */
    if (gpio_get_type(dev) == GPIO_HIGHDRIVE) {
        /* Drive strength */
        REG_SET_CLR(regs->hd.PBDRV, flags & (1 << GPIO_PBDRV_BIT), mask);

        /* Analog Pin */
        if (!(mode & (1 << GPIO_PBMDSEL_BIT))) {
            REG_SET_CLR(regs->PB, mode & (1 << GPIO_PB_BIT), mask);
            return;
        }

        // Use PBOUTMD bit for the PBDEN register. Both define PP/OD
        REG_SET_CLR(regs->hd.PBDEN, (1 << GPIO_PBOUTMD_BIT) & mode,
                (mask << PBHD_PBDEN_PBPDEN_BIT));

        // Always write N-Channel (low side)
        REG_SET_CLR(regs->hd.PBDEN, 1,
                (mask << PBHD_PBDEN_PBNDEN_BIT));

    }
    else {
        /* Input type */
        REG_SET_CLR(regs->std.PBOUTMD, mode & (1 << GPIO_PBOUTMD_BIT), mask);

        /* Analog Pin */
        if (!(mode & (1 << GPIO_PBMDSEL_BIT))) {
            REG_SET_CLR(regs->PB, mode & (1 << GPIO_PB_BIT), mask);
            return;
        }

        /* Drive strength */
        REG_SET_CLR(regs->std.PBDRV, flags & (1 << GPIO_PBDRV_BIT), mask);

    }
    /* Output value */
    REG_SET_CLR(regs->PB, mode & (1 << GPIO_PB_BIT), mask);


}

/**
 * @brief Set a pin's alternate function.
 *
 * The pin must have its mode set to GPIO_MODE_AF for this to take
 * effect.
 *
 * @param dev Device whose pin to configure.
 * @param bit Pin whose alternate function to set.
 * @param af  Alternate function to use for pin.
 * @see gpio_set_modef()
 */
void gpio_set_af(gpio_dev *dev, uint8 bit, gpio_af af) {
    uint32 tmp;
    uint32 mask = (bit == 5) ? 7 : 3;
    uint32 shift = bit * 2;

    tmp = ~(mask << shift);
    tmp &= dev->regs->hd.PBFSEL;
    tmp |= (mask & af) << shift;
    dev->regs->hd.PBFSEL = tmp;
}

