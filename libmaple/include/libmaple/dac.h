/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
 * Copyright (c) 2010 Bryan Newbold.
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
 * @file libmaple/include/libmaple/dac.h
 * @brief Digital to analog converter support.
 */

/* See notes/dac.txt for more info */

#ifndef _LIBMAPLE_DAC_H_
#define _LIBMAPLE_DAC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <series/dac.h>
#include <libmaple/libmaple_types.h>
#include <libmaple/rcc.h>
#include <libmaple/stm32.h>
#include <libmaple/xbar.h>

/*
 * Register map base and device pointers.
 *
 * The DACs are the same on all supported targets, so it's not worth
 * repeating these in the series headers.
 */

/** DAC device type. */
typedef struct dac_dev {
    void *tmp;
    //dac_reg_map *regs; /**< Register map */
} dac_dev;


extern const dac_dev *DAC;



#define DAC_CH1 0x1
#define DAC_CH2 0x2
void dac_init(const dac_dev *dev, uint32 flags);

void dac_write_channel(const dac_dev *dev, uint8 channel, uint16 val);
void dac_enable_channel(const dac_dev *dev, uint8 channel);
void dac_disable_channel(const dac_dev *dev, uint8 channel);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
