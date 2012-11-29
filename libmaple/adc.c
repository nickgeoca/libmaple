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
 * @file libmaple/adc.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>,
 *         Perry Hung <perry@leaflabs.com>
 * @brief Analog to digital converter routines
 */

#include <libmaple/adc.h>
#include <libmaple/rcc.h>
#include <libmaple/gpio.h>

/*
 * Devices
 */

static adc_dev adc1 = {
    .regs   = ADC1_BASE,
    .clk_id = CLK_SARADC1,
    .irq_num = NVIC_SARADC1
};
/** ADC1 device. */
const adc_dev *ADC1 = &adc1;

static adc_dev adc2 = {
    .regs   = ADC2_BASE,
    .clk_id = CLK_SARADC2,
    .irq_num = NVIC_SARADC2
};
/** ADC1 device. */
const adc_dev *ADC2 = &adc2;

/*
 * Common routines
 */

void adc_set_prescaler(adc_prescaler pre) {

}

void adc_foreach(void (*fn)(const adc_dev*)) {
    fn(ADC1);
    fn(ADC2);
}

void adc_config_gpio(const adc_dev *ignored, gpio_dev *gdev, uint8 bit) {
}

void adc_enable_single_swstart(const adc_dev *dev) {
    adc_init(dev);
    //adc_set_extsel(dev, ADC_SWSTART);
    //adc_set_exttrig(dev, 1);
    adc_enable(dev);

}

void  __irq_adc1(void) {
    adc_reg_map *regs = ADC1->regs;
    // Interrupt: single conversion complete
    if (regs->STATUS & SARADC_STATUS_SCCI_MASK &&
                regs->CONFIG & SARADC_CFGR_SCCIEN_MASK) {
        // Clear interrupt
        REG_SET_CLR(regs->STATUS, 0, SARADC_STATUS_SCCI_MASK);
    }
    return;
}

void  __irq_adc2(void) {
    adc_reg_map *regs = ADC2->regs;
    // Interrupt: single conversion complete
    if (regs->STATUS & SARADC_STATUS_SCCI_MASK &&
                regs->CONFIG & SARADC_CFGR_SCCIEN_MASK) {
        // Clear interrupt
        REG_SET_CLR(regs->STATUS, 0, SARADC_STATUS_SCCI_MASK);
    }
    return;
}

// Note: Only set one tslot at a time
static inline void adc_set_tslot_chnl(const adc_dev *dev, uint32 tslot, adc_tslot_chnl chnl)
{
    volatile uint32 *reg = SARADC_SQ_REG(dev->regs, tslot);
    uint32 sq_reg = *reg;
    sq_reg &= ~SARADC_SQ_TSMUX_MASK(tslot);
    sq_reg |= chnl << SARADC_SQ_TSMUX_BIT(tslot);
    *reg = sq_reg;
    return;
}

// Note: Only set one group characteristic at a time
static inline void adc_set_grp_res(const adc_dev *dev, uint32 grp, adc_bit_res res)
{
    volatile uint32 *reg = SARADC_CHAR_REG(dev->regs, grp);
    REG_SET_CLR(*reg, res, 1 << SARADC_CHAR_RSEL_BIT(grp));
}

// Note: Only set one group characteristic at a time
static inline void adc_set_grp_seqlen(const adc_dev *dev, uint32 grp, adc_smp_cnt cnt)
{
    volatile uint32 *reg = SARADC_CHAR_REG(dev->regs, grp);
    REG_SET_CLR(*reg, 0, SARADC_CHAR_RPT_MASK(grp));
    REG_SET_CLR(*reg, 1, cnt << SARADC_CHAR_RPT_BIT(grp));
}

// Note: Only set one group characteristic at a time
static inline void adc_set_grp_gain(const adc_dev *dev, uint32 grp, adc_grp_gain gn)
{
    volatile uint32 *reg = SARADC_CHAR_REG(dev->regs, grp);
    REG_SET_CLR(*reg, gn, 1 << SARADC_CHAR_GN_BIT(grp));
}

/**
 * @brief Initialize an ADC peripheral.
 *
 * Initializes the RCC clock line for the given peripheral.  Resets
 * ADC device registers.
 *
 * @param dev ADC peripheral to initialize
 */
void adc_init(const adc_dev *dev) {
    adc_reg_map *regs = dev->regs;
    uint32 clk, i;
    uint32 sar_clk = 16240000; // slowed down for 2.5MHz clk; max: 16240000

    // Enable clock
    clk_enable_dev(dev->clk_id);

    // Setup Peripheral
    // SAR clk to operate at 10 MHZ
    REG_SET_CLR(regs->CONFIG, 0, SARADC_CFGR_CLKDIV_MASK);
    clk = (2 * clk_get_bus_freq(dev->clk_id)) / sar_clk - 1;
    REG_SET_CLR(regs->CONFIG, 1, clk << SARADC_CFGR_CLKDIV_BIT);
    REG_SET_CLR(regs->CONFIG, 0, SARADC_CFGR_PACKMD_MASK);
    REG_SET_CLR(regs->CONFIG, 1, SARADC_CFGR_PACKMD_LOWER_ONLY);

    // set conversion start to software only
    REG_SET_CLR(regs->CONTROL, 0, SARADC_CR_SCSEL_MASK);
    REG_SET_CLR(regs->CONTROL, 1, SARADC_CR_SCSEL_ADCNT0);
    // Use burst mode for 12 bit resolution
    REG_SET_CLR(regs->CONFIG, 1, SARADC_CFGR_BCLKSEL_MASK); /**< Burst mode uses apb clk */

    // adc will run through one scan of all enabled time sequences
    REG_SET_CLR(regs->CONFIG, 0, SARADC_CFGR_SCANMD_MASK); /**< Autoscan mode once */
    REG_SET_CLR(regs->CONTROL, 1, SARADC_CR_VCMEN_MASK); /**< Enable vcm buffer */
    REG_SET_CLR(regs->CONTROL, 0, SARADC_CR_VREFSEL_MASK); /**< Select vref internal */
    REG_SET_CLR(regs->CONTROL, 1, SARADC_CR_TRKMD_DELAYED); /**< Delay tracking by 3 SAR clk cylces */
    REG_SET_CLR(regs->CONTROL, 1, SARADC_CR_BMTK_MASK); /**< Minimize burst mode delay (4/apb frequency), since trkmd delay is already set. */
    REG_SET_CLR(regs->CONTROL, 1, SARADC_CR_AD12BSSEL_ONE); /**< Sample once convert 4 times for 12-bit mode. */

    // Setup group 0
    adc_set_grp_res(dev, ADC_GRP_0, ADC_10_bit);
    adc_set_grp_gain(dev, ADC_GRP_0, ADC_GN_HALF);
    adc_set_grp_seqlen(dev, ADC_GRP_0, ADC_SMPCNT_1);
    // Setup group 1
    adc_set_grp_res(dev, ADC_GRP_1, ADC_10_bit);
    adc_set_grp_gain(dev, ADC_GRP_1, ADC_GN_HALF);
    adc_set_grp_seqlen(dev, ADC_GRP_1, ADC_SMPCNT_16);
    // Setup group 2
    adc_set_grp_res(dev, ADC_GRP_2, ADC_12_bit);
    adc_set_grp_gain(dev, ADC_GRP_2, ADC_GN_HALF);
    adc_set_grp_seqlen(dev, ADC_GRP_2, ADC_SMPCNT_1);
    // Setup group 3
    adc_set_grp_res(dev, ADC_GRP_3, ADC_12_bit);
    adc_set_grp_gain(dev, ADC_GRP_3, ADC_GN_HALF);
    adc_set_grp_seqlen(dev, ADC_GRP_3, ADC_SMPCNT_16);

    // Enable interrupt: Single conversion complete
    nvic_clr_pending_irq(dev->irq_num);
    nvic_irq_enable(dev->irq_num);
    //REG_SET_CLR(regs->CONFIG, 1, SARADC_CFGR_SCCIEN_MASK);
}

void adc_disable(const adc_dev *dev) {
    adc_reg_map *regs = dev->regs;
    // DISAABLE INTERRUPTS
    REG_SET_CLR(regs->CONFIG, 0, SARADC_CFGR_FURIEN_MASK |
            SARADC_CFGR_FORIEN_MASK | SARADC_CFGR_SDIEN_MASK | SARADC_CFGR_SCCIEN_MASK);

    nvic_clr_pending_irq(dev->irq_num);

    // DISABLE MODULE
    REG_SET_CLR(regs->CONTROL, SARADC_CR_ADCEN_DS, BIT(SARADC_CR_ADCEN_BIT));

    // DISABLE CLOCK
    //clk_dev_disable(dev->clk_id);
}

/**
 * @brief Set external event select for regular group
 * @param dev ADC device
 * @param event Event used to trigger the start of conversion.
 * @see adc_extsel_event
 */
void adc_set_extsel(const adc_dev *dev, adc_extsel_event event) {
#if 0
    uint32 cr2 = dev->regs->CR2;
    cr2 &= ~ADC_CR2_EXTSEL;
    cr2 |= event;
    dev->regs->CR2 = cr2;
#endif
}

/**
 * @brief Set the sample rate for all channels on an ADC device.
 *
 * Don't call this during conversion.
 *
 * @param dev adc device
 * @param smp_rate sample rate to set
 * @see adc_smp_rate
 */
void adc_set_sample_rate(const adc_dev *dev, adc_smp_rate smp_rate) {
    return;
}

/**
 * @brief Perform a single synchronous software triggered conversion on a
 *        channel.
 * @param dev ADC device to use for reading.
 * @param channel channel to convert
 * @return conversion result
 */
uint16 adc_read(const adc_dev *dev, uint8 channel) {

    adc_reg_map *regs = dev->regs;
    uint32 val;
    uint32 prev_chnl = (regs->SQ3210 & SARADC_SQ3210_TS0MUX_MASK) >> SARADC_SQ3210_TS0MUX_BIT;

    // Clear the FIFO
    while (regs->FIFOSTATUS & SARADC_FIFOSTATUS_FIFOLVL_MASK) {
        val = regs->DATA;
    }

    // Single read only uses timeslot 0
    adc_set_tslot_chnl(dev, 0, channel);

    REG_SET_CLR(regs->CONTROL, 1, SARADC_CR_BURSTEN_EN);

    // a 1-to-0 transition on ACCMD bit will enable the accumulator for the next conversion
    REG_SET_CLR(regs->CONTROL, 0, SARADC_CR_ACCMD_MASK);
    regs->ACC = 0;

    // Start conversion
    REG_SET_CLR(regs->CONTROL, 1, SARADC_CR_ADBUSY_MASK);

    while (!(regs->FIFOSTATUS & SARADC_FIFOSTATUS_FIFOLVL_MASK));
    val = regs->DATA * 3300 / 4095;

    // Set previous channel
    adc_set_tslot_chnl(dev, 0, prev_chnl);

    return val;
}
