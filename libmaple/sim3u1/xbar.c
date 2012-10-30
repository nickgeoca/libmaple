/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 Silicon Laboratories.
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

#include <libmaple/gpio.h>

void xbar_init(void) {
    // Enable clock on port banks. All GPIO clk id's reference PBCFG
    clk_enable_dev(CLK_PB);

    // Enable Crossbar 0 signals & set properties
    REG_SET_CLR(PBCFG_BASE->XBAR0H, 1, PBCFG_XBAR0H_XBAR0EN_MASK);

    // Skip list
    GPIOA->regs->std.PBSKIPEN = 0x0000FFFF;
}


void xbar_set_dev(xbar_dev_id xbar_id, uint8 enable) {
    uint32 xbar_mask_bit;
    uint32 xbar_mask = 0;
    __io uint32 *xbar_mask_reg;
    uint32 gpio_skip_mask = 0;
    int32 xbar_cnt = XBAR_MAP[xbar_id].info_cnt;
    uint8 xbar_num = XBAR_MAP[xbar_id].xbar_num;
    // xbar can configure across port banks (e.g. USART tx may be on PB0.15 and USART rx may be on PB1.2), so
    // there is a second port bank skip register.
    // If gpio dev is GPIOA or GPIOC, then figure out the skip2 register.
    gpio_reg_map *gpio1_regs;
    gpio_reg_map *gpio2_regs;

    if (xbar_num == XBAR_NUM_NULL || xbar_num == XBAR_NUM_GPIOE) {
        return;
    }

    if (xbar_num == XBAR_NUM_1) {
        gpio1_regs = GPIOC->regs;
        gpio2_regs = GPIOD->regs;
        xbar_mask_reg = &PBCFG_BASE->XBAR1;
    }
    else {
        gpio1_regs = GPIOA->regs;
        gpio2_regs = GPIOB->regs;
        if (xbar_num == XBAR_NUM_0H) {
            xbar_mask_reg = &PBCFG_BASE->XBAR0H;
        }
        else {
            xbar_mask_reg = &PBCFG_BASE->XBAR0L;
        }
    }


    while((--xbar_cnt) >= 0) {
        gpio_skip_mask |= XBAR_MAP[xbar_id].xbar_info[xbar_cnt].pb_mask;
        xbar_mask |= XBAR_MAP[xbar_id].xbar_info[xbar_cnt].xbar_mask;
    }

    // Set PINLPEN bit. This holds the pin states
    //REG_SET_CLR(*(__io uint32*)0x40048000, 1, 2);

    // Skip pins
    REG_SET_CLR(gpio1_regs->std.PBSKIPEN, !enable, gpio_skip_mask & 0xffff);
    REG_SET_CLR(gpio2_regs->std.PBSKIPEN, !enable, gpio_skip_mask >> 16);

    // Set xbar settings
    REG_SET_CLR(*xbar_mask_reg, enable, xbar_mask);

    // Clear PINLPEN bit. This holds the pin states
    //REG_SET_CLR(*(__io uint32*)0x40048000, 0, 2);
}
