/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
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
 * @file libmaple/dac.c
 * @brief Digital to analog converter support.
 */

#include <libmaple/dac.h>
#include <libmaple/libmaple.h>
#include <libmaple/gpio.h>

#if STM32_HAVE_DAC
dac_dev dac = {
    .tmp = 0,
};
const dac_dev *DAC = &dac;
#endif

/**
 * @brief Initialize the digital to analog converter
 * @param dev DAC device
 * @param flags Flags:
 *      DAC_CH1: Enable channel 1
 *      DAC_CH2: Enable channel 2
 * @sideeffect May set PA4 or PA5 to INPUT_ANALOG
 */
void dac_init(const dac_dev *dev, uint32 flags) {

}

/**
 * @brief Write a 12-bit value to the DAC to output
 * @param dev DAC device
 * @param channel channel to select (1 or 2)
 * @param val value to write
 */
void dac_write_channel(const dac_dev *dev, uint8 channel, uint16 val) {

}

/**
 * @brief Enable a DAC channel
 * @param dev DAC device
 * @param channel channel to enable, either 1 or 2
 * @sideeffect May change pin mode of PA4 or PA5
 */
void dac_enable_channel(const dac_dev *dev, uint8 channel) {

}

/**
 * @brief Disable a DAC channel
 * @param dev DAC device
 * @param channel channel to disable, either 1 or 2
 */
void dac_disable_channel(const dac_dev *dev, uint8 channel) {

}
