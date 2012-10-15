/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 LeafLabs, LLC.
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
 * @file libmaple/include/libmaple/adc.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>,
 *         Perry Hung <perry@leaflabs.com>
 * @brief Analog-to-Digital Conversion (ADC) header.
 */

#ifndef _LIBMAPLE_ADC_H_
#define _LIBMAPLE_ADC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple.h>
#include <libmaple/bitband.h>
#include <libmaple/rcc.h>
#include <libmaple/nvic.h>
/* We include the series header below, after defining the register map
 * and device structs. */

/*
 * Register map
 */






/* Pull in the series header (which may need the above struct
 * definitions).
 *
 * IMPORTANT: The series header must define the following:
 *
 * - enum adc_extsel_event (and typedef to adc_extsel_event): One per
 *   external event used to trigger start of conversion of a regular
 *   group. If two different series support the same event as a
 *   trigger, they must use the same token for the enumerator for that
 *   event. (The value of the enumerator is of course allowed to be
 *   different).
 *
 * - enum adc_smp_rate (and typedef to adc_smp_rate): One per
 *   available sampling time.  These must be in the form ADC_SMPR_X_Y
 *   for X.Y cycles (e.g. ADC_SMPR_1_5 means 1.5 cycles), or
 *   ADC_SMPR_X for X cycles (e.g. ADC_SMPR_3 means 3 cycles).
 *
 * - enum adc_prescaler (and typedef): One per available prescaler,
 *   suitable for adc_set_prescaler. Series which have the same
 *   prescaler dividers (e.g. STM32F1 and STM32F2 both divide PCLK2 by
 *   2, 4, 6, or 8) must provide the same tokens as enumerators, for
 *   portability.
 */
#include <series/adc.h>

/*
 * Register bit definitions
 */



/*
 * Routines
 */

void adc_init(const adc_dev *dev);
void adc_set_extsel(const adc_dev *dev, adc_extsel_event event);
void adc_set_sample_rate(const adc_dev *dev, adc_smp_rate smp_rate);
uint16 adc_read(const adc_dev *dev, uint8 channel);

/**
 * @brief Set the ADC prescaler.
 *
 * This determines the ADC clock for all devices.
 */
extern void adc_set_prescaler(adc_prescaler pre);

/**
 * @brief Call a function on all ADC devices.
 * @param fn Function to call on each ADC device.
 */
extern void adc_foreach(void (*fn)(const adc_dev*));

struct gpio_dev;
/**
 * @brief Configure a GPIO pin for ADC conversion.
 * @param dev ADC device to use for conversion (currently ignored on
 *            all targets).
 * @param gdev GPIO device to configure.
 * @param bit Bit on gdev to configure for ADC conversion.
 */
extern void adc_config_gpio(const struct adc_dev *dev,
                            struct gpio_dev *gdev,
                            uint8 bit);

/**
 * @brief Enable an ADC and configure it for single conversion mode.
 *
 * This function performs any initialization necessary to allow the
 * ADC device to perform a single synchronous regular software
 * triggered conversion, using adc_read().
 *
 * @param dev Device to enable.
 * @see adc_read()
 */
extern void adc_enable_single_swstart(const adc_dev* dev);

/**
 * @brief Set the regular channel sequence length.
 *
 * Defines the total number of conversions in the regular channel
 * conversion sequence.
 *
 * @param dev ADC device.
 * @param length Regular channel sequence length, from 1 to 16.
 */
static inline void adc_set_reg_seqlen(const adc_dev *dev, uint8 length) {
#if 0
    uint32 tmp = dev->regs->SQR1;
    tmp &= ~ADC_SQR1_L;
    tmp |= (length - 1) << 20;
    dev->regs->SQR1 = tmp;
#endif
}

/**
 * @brief Enable an adc peripheral
 * @param dev ADC device to enable
 */
static inline void adc_enable(const adc_dev *dev) {
    // Enable ADC
    REG_SET_CLR(dev->regs->CONTROL, SARADC_CR_ADCEN_EN, BIT(SARADC_CR_ADCEN_BIT));

}

/**
 * @brief Disable an ADC peripheral
 * @param dev ADC device to disable
 */
extern void adc_disable(const adc_dev *dev);

/**
 * @brief Disable all ADC peripherals.
 */
static inline void adc_disable_all(void) {
    adc_foreach(adc_disable);
}

// Note: Only set one tslot at a time
static inline void adc_set_tslot_grp(const adc_dev *dev, uint32 tslot, adc_grp_num grp)
{
    volatile uint32 *reg = SARADC_SQ_REG(dev->regs, tslot);
    uint32 sq_reg = *reg;
    sq_reg &= ~SARADC_SQ_TSCHR_MASK(tslot);
    sq_reg |= grp << SARADC_SQ_TSCHR_BIT(tslot);
    *reg = sq_reg;
    return;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
