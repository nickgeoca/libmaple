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
#include <libmaple/libmaple.h>
#include <libmaple/rcc.h>




volatile uint32 ADC_SCAN_FINISHED;

static void hndlr2(const adc_dev *dev)
{
    adc_reg_map *regs = ADC1->regs;
    // Clear interrupt: 1) single conversion complete
    REG_WRITE_SET_CLR(regs->STATUS, 0, SARADC_STATUS_SCCI_MASK);
    // Enable burst mode and start conversion
    REG_WRITE_SET_CLR(regs->CONTROL, 1, SARADC_CR_BURSTEN_MASK);
    REG_WRITE_SET_CLR(regs->CONTROL, 1, SARADC_CR_ADBUSY_MASK);
}

static void hndlr1(const adc_dev *dev)
{
    adc_reg_map *regs = ADC1->regs;
    // Clear interrupts: 1) scan done; 2) single conversion complete
    REG_WRITE_SET_CLR(regs->STATUS, 0, SARADC_STATUS_SDI_MASK);
    REG_WRITE_SET_CLR(regs->STATUS, 0, SARADC_STATUS_SCCI_MASK);
    // Disable autoscan
    REG_WRITE_SET_CLR(regs->CONFIG, 0, SARADC_CFGR_SCANEN_MASK);
    // Disable accumulator
    REG_WRITE_SET_CLR(regs->CONTROL, 1, SARADC_CR_ACCMD_MASK);
    ADC_SCAN_FINISHED = 1;
}

void  __irq_adc1(void) {
    adc_reg_map *regs = ADC1->regs;

    // Scan complete interrupt handler
    if (regs->STATUS & SARADC_STATUS_SDI_MASK &&
            regs->CONFIG & SARADC_CFGR_SDIEN_MASK) {
        hndlr1(ADC1);
    }

    // Conversion complete interrupt handler
    else if (regs->STATUS & SARADC_STATUS_SCCI_MASK &&
            regs->CONFIG & SARADC_CFGR_SCCIEN_MASK) {
        hndlr2(ADC1);
    }

    return;
}


static inline void adc_set_tslot_chnl(const adc_dev *dev, uint32 tslot, adc_tslot_chnl chnl)
{
    volatile uint32 *reg = SARADC_SQ_REG(dev->regs, tslot);
    uint32 sq_reg = *reg;
    sq_reg &= ~SARADC_SQ_TSMUX_MASK(tslot);
    sq_reg |= chnl << SARADC_SQ_TSMUX_BIT(tslot);
    *reg = sq_reg;
    return;
}

static inline void adc_set_tslot_grp(const adc_dev *dev, uint32 tslot, adc_grp_num grp)
{
    volatile uint32 *reg = SARADC_SQ_REG(dev->regs, tslot);
    uint32 sq_reg = *reg;
    sq_reg &= ~SARADC_SQ_TSCHR_MASK(tslot);
    sq_reg |= grp << SARADC_SQ_TSCHR_BIT(tslot);
    *reg = sq_reg;
    return;
}

static inline void adc_set_grp_res(const adc_dev *dev, uint32 grp, adc_bit_res res)
{
    volatile uint32 *reg = SARADC_CHAR_REG(dev->regs, grp);
    REG_WRITE_SET_CLR(*reg, 0, SARADC_CHAR_RSEL_MASK(grp));
    REG_WRITE_SET_CLR(*reg, 1, res << SARADC_CHAR_RSEL_BIT(grp));
}

static inline void adc_set_grp_brst_cnt(const adc_dev *dev, uint32 grp, adc_smp_cnt cnt)
{
    volatile uint32 *reg = SARADC_CHAR_REG(dev->regs, grp);
    REG_WRITE_SET_CLR(*reg, 0, SARADC_CHAR_RPT_MASK(grp));
    REG_WRITE_SET_CLR(*reg, 1, cnt << SARADC_CHAR_RPT_BIT(grp));
}

static inline void adc_set_grp_gain(const adc_dev *dev, uint32 grp, adc_grp_gain gn)
{
    volatile uint32 *reg = SARADC_CHAR_REG(dev->regs, grp);
    REG_WRITE_SET_CLR(*reg, 0, SARADC_CHAR_GN_MASK(grp));
    REG_WRITE_SET_CLR(*reg, 1, gn << SARADC_CHAR_GN_BIT(grp));
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
    uint32 clk;
    uint32 group = 0;
    uint32 tslot = 0;
    uint32 sar_clk = 10000000; // 16240000

    // Enable clock
    clk_enable_dev(dev->clk_id);

    // Setup Peripheral
    // SAR clk to operate at 10 MHZ
    REG_WRITE_SET_CLR(regs->CONFIG, 0, SARADC_CFGR_CLKDIV_MASK);
    clk = (2 * clk_get_bus_speed(dev->clk_id)) / sar_clk - 1;
    REG_WRITE_SET_CLR(regs->CONFIG, 1, 3 << SARADC_CFGR_CLKDIV_BIT);
    REG_WRITE_SET_CLR(regs->CONFIG, 0, SARADC_CFGR_PACKMD_MASK);
    REG_WRITE_SET_CLR(regs->CONFIG, 1, SARADC_CFGR_PACKMD_LOWER_ONLY);

    // set conversion start to software only
    REG_WRITE_SET_CLR(regs->CONTROL, 0, SARADC_CR_SCSEL_MASK);
    REG_WRITE_SET_CLR(regs->CONTROL, 1, SARADC_CR_SCSEL_ADCNT0);
    REG_WRITE_SET_CLR(regs->CONFIG, 1, SARADC_CFGR_BCLKSEL_MASK); /**< Burst mode uses apb clk */

    // adc will run through one scan of all enabled time sequences
    REG_WRITE_SET_CLR(regs->CONFIG, 0, SARADC_CFGR_SCANMD_MASK); /**< Autoscan mode once */
    REG_WRITE_SET_CLR(regs->CONTROL, 1, SARADC_CR_VCMEN_MASK); /**< Enable vcm buffer */
    REG_WRITE_SET_CLR(regs->CONTROL, 0, SARADC_CR_VREFSEL_MASK); /**< Select vref internal */

    // Setup group 0
    adc_set_grp_res(dev, ADC_GRP_0, ADC_10_bit);
    adc_set_grp_brst_cnt(dev, ADC_GRP_0, ADC_SMPCNT_64);
    adc_set_grp_gain(dev, ADC_GRP_0, ADC_GN_HALF);

    // Set timeslot0 group number
    adc_set_tslot_grp(dev, 0, ADC_GRP_0); /**< Associate a timeslot with a group characteristic */

    // Set tslot 1 to end of scan
    adc_set_tslot_chnl(dev, 1, ADC_CHN_END);

    // Enable ADC
    REG_WRITE_SET_CLR(regs->CONTROL, SARADC_CR_ADCEN_EN, BIT(SARADC_CR_ADCEN_BIT));

    // Enable interrupts: 1) Single conversion complete; 2) scan done
    nvic_clr_pending_irq(dev->irq_num);
    nvic_irq_enable(dev->irq_num);
    REG_WRITE_SET_CLR(regs->CONFIG, 1, SARADC_CFGR_SCCIEN_MASK);
    REG_WRITE_SET_CLR(regs->CONFIG, 1, SARADC_CFGR_SDIEN_MASK);
}


void adc_disable(const adc_dev *dev) {
    adc_reg_map *regs = dev->regs;
    // DISAABLE INTERRUPTS
    REG_WRITE_SET_CLR(regs->CONFIG, 0, SARADC_CFGR_FURIEN_MASK |
            SARADC_CFGR_FORIEN_MASK | SARADC_CFGR_SDIEN_MASK | SARADC_CFGR_SCCIEN_MASK);

    nvic_clr_pending_irq(dev->irq_num);
    nvic_irq_enable(dev->irq_num);

    // DISABLE MODULE
    REG_WRITE_SET_CLR(regs->CONTROL, SARADC_CR_ADCEN_DS, BIT(SARADC_CR_ADCEN_BIT));

    // DISABLE CLOCK
    clk_dev_disable(dev->clk_id);
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
#if 0
    uint32 adc_smpr1_val = 0, adc_smpr2_val = 0;
    int i;

    for (i = 0; i < 10; i++) {
        if (i < 8) {
            /* ADC_SMPR1 determines sample time for channels [10,17] */
            adc_smpr1_val |= smp_rate << (i * 3);
        }
        /* ADC_SMPR2 determines sample time for channels [0,9] */
        adc_smpr2_val |= smp_rate << (i * 3);
    }

    dev->regs->SMPR1 = adc_smpr1_val;
    dev->regs->SMPR2 = adc_smpr2_val;
#endif
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
    ADC_SCAN_FINISHED = 0;

    // Set to timeslot 0 to channel
    adc_set_tslot_chnl(dev, 0, channel);

    // burst mode must be enabled before each conversion start
    // it is cleared by hardware after the burst mode conversion completes
    REG_WRITE_SET_CLR(regs->CONTROL, 1, SARADC_CR_BURSTEN_EN);

    // a 0-to-1 transition on the SCANEN bit is required to arm the scan.
    // the scan will not start until a conversion start occurs.
    REG_WRITE_SET_CLR(regs->CONFIG, 1, SARADC_CFGR_SCANEN_EN);

    // a 1-to-0 transition on ACCMD bit will enable the accumulator for the next conversion
    REG_WRITE_SET_CLR(regs->CONTROL, 0, SARADC_CR_ACCMD_MASK);
    regs->ACC = 0;

    // Start conversion
    REG_WRITE_SET_CLR(regs->CONTROL, 1, SARADC_CR_ADBUSY_MASK);

    while (!ADC_SCAN_FINISHED);
    val = regs->DATA;
    val /= 64;
    val = 2 * (val * 1650 / 1023);
    return val;
}
