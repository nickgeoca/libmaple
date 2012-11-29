/******************************************************************************
 * The MIT License
 *
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
 * @file   libmaple/include/libmaple/timer.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Timer interface.
 */

#ifndef _LIBMAPLE_TIMER_H_
#define _LIBMAPLE_TIMER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <series/timer.h>
#include <libmaple/libmaple.h>
#include <libmaple/rcc.h>
#include <libmaple/nvic.h>
#include <libmaple/bitband.h>
#include <libmaple/gpio.h>

/** Timer device type */
typedef struct timer_dev {
    timer_reg_map *regs;         /**< Register map */
    clk_dev_id clk_id;          /**< RCC clock information */
    timer_type type;            /**< Timer's type */
    nvic_irqs_t nvic_irqs;            /**<  */
    xbar_dev_id xbar_id;
    timer_chnl_reg_map **chnl_regs;
    voidFuncPtr handlers[];
} timer_dev;

extern timer_dev *TIMER1;
extern timer_dev *TIMER2;
extern timer_dev *TIMER3;
extern timer_dev *TIMER4;
extern timer_dev *TIMER5;

/*
 * Convenience routines
 */






/*
 * Note: Don't require timer_channel arguments! We want to be able to say
 *
 * for (int channel = 1; channel <= 4; channel++) {
 *    ...
 * }
 *
 * without the compiler yelling at us.
 */
gpio_af timer_get_af(struct timer_dev *dev);
void timer_init(timer_dev *dev);
void timer_disable(timer_dev *dev);
void timer_set_mode(timer_dev *dev, uint8 channel, timer_mode mode);
void timer_foreach(void (*fn)(timer_dev*));
int timer_has_cc_channel(timer_dev *dev, uint8 channel);



void timer_attach_interrupt(timer_dev *dev,
                            uint8 interrupt,
                            voidFuncPtr handler);
void timer_detach_interrupt(timer_dev *dev, uint8 interrupt);

/**
 * Initialize all timer devices on the chip.
 */
static inline void timer_init_all(void) {

}

/**
 * Disables all timers on the device.
 */
static inline void timer_disable_all(void) {

}

/**
 * @brief Stop a timer's counter from changing.
 *
 * Does not affect the timer's mode or other settings.
 *
 * @param dev Device whose counter to pause.
 */
static inline void timer_pause(timer_dev *dev) {
    timer_basic_reg_map *regs_b;
    switch (dev->type) {
    case TIMER_BASIC:
        regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
        REG_SET_CLR(regs_b->CONFIG, 0, 0x20000000);
        break;
    default:
        REG_SET_CLR(dev->regs->STATUS, EPCA_STATUS_RUN_STOP, EPCA_STATUS_RUN_START);
        break;
    }

}

/**
 * @brief Start a timer's counter.
 *
 * Does not affect the timer's mode or other settings.
 *
 * @param dev Device whose counter to resume
 */
static inline void timer_resume(timer_dev *dev) {
    timer_basic_reg_map *regs_b;
    switch (dev->type) {
    case TIMER_BASIC:
        regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
        REG_SET_CLR(regs_b->CONFIG, 1, 0x20000000);
        break;
    default:
        REG_SET_CLR(dev->regs->STATUS, EPCA_STATUS_RUN_START, EPCA_STATUS_RUN_START);
        break;
    }
}

static inline uint32 timer_actl_freq(timer_dev *dev, uint32 tmr_clk) {
    uint32 bus_clk = clk_get_bus_freq(dev->clk_id);
    // PCA modules
    // 1) tmr_clk = bus_clk / (clk_div + 1)
    // 2) clk_div = bus_clk / tmr_clk - 1
    // => tmr_clk = bus_clk / ((bus_clk / tmr_clk - 1)  + 1)
    // Timer modules
    // 1) tmr_clk = bus_clk / (256 - clk_div)
    // 2) clk_div = 256 - bus_clk / tmr_clk
    // => tmr_clk = bus_clk / (256 - (256 - bus_clk / tmr_clk))
    return dev->type == TIMER_BASIC ? bus_clk / (256 - (256 - bus_clk / tmr_clk)) :
            bus_clk / ((bus_clk / tmr_clk - 1) + 1);
}

/**
 * @brief Returns the timer's counter value.
 *
 * This value is likely to be inaccurate if the counter is running
 * with a low prescaler.
 *
 * @param dev Timer whose counter to return
 */
static inline uint16 timer_get_count(timer_dev *dev) {
    return 0;
}

/**
 * @brief Sets the counter value for the given timer.
 * @param dev Timer whose counter to set
 * @param value New counter value
 */
static inline void timer_set_count(timer_dev *dev, uint16 value) {

}

/**
 * @brief Returns the given timer's prescaler.
 *
 * Note that if the timer's prescaler is set (e.g. via
 * timer_set_prescaler() or accessing a TIMx_PSC register), the value
 * returned by this function will reflect the new setting, but the
 * timer's counter will only reflect the new prescaler at the next
 * update event.
 *
 * @param dev Timer whose prescaler to return
 * @see timer_generate_update()
 */
static inline uint16 timer_get_prescaler(timer_dev *dev) {
    timer_reg_map *regs = dev->regs;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        return 255 - (regs_b->CLKDIV & 255);
    default:
        // psc = clk_in / Fepca - 1
        return ((regs->MODE & EPCA_MODE_CLKDIV_MASK) >> EPCA_MODE_CLKDIV_BIT);
    }
}

/**
 * @brief Set a timer's prescale value.
 *
 * Divides the input clock by (PSC+1).  The new value will not take
 * effect until the next update event.
 *
 * @param dev Timer whose prescaler to set
 * @param psc New prescaler value
 * @see timer_generate_update()
 */
static inline void timer_set_prescaler(timer_dev *dev, uint16 psc) {
    timer_reg_map *regs = dev->regs;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        // limit psc
        if (psc > 255) {
            psc = 255;
        }
        regs_b->CLKDIV = 255 - psc;
        break;
    default:
        // limit psc
        if (psc > 1023) {
            psc = 1023;
        }
        regs->MODE &= ~EPCA_MODE_CLKDIV_MASK;
        regs->MODE |= psc << EPCA_MODE_CLKDIV_BIT;
        break;
    }
}

/**
 * @brief Returns a timer's reload value.
 * @param dev Timer whose reload value to return
 */
static inline uint16 timer_get_reload(timer_dev *dev) {
    timer_reg_map *regs = dev->regs;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        return 65535;
    default:
        return regs->LIMIT & EPCA_LIMIT_MASK;
    }

    return 0;
}

/**
 * @brief Set a timer's reload value.
 * @param dev Timer whose reload value to set
 * @param arr New reload value to use.  Takes effect at next update event.
 * @see timer_generate_update()
 */
static inline void timer_set_reload(timer_dev *dev, uint16 arr) {
    timer_reg_map *regs = dev->regs;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        break;
    case TIMER_ADVANCED:
        regs->adv.LIMITUPD = arr;
        break;
    default:
        regs->LIMIT = arr;
        break;
    }
}

/**
 * @brief Get the compare value for the given timer channel.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose compare value to get.
 */
static inline uint16 timer_get_compare(timer_dev *dev, uint8 channel) {
    timer_chnl_reg_map *reg;
    timer_basic_reg_map *regs_b;
    uint32 limit;
    channel -= 1;
    switch (dev->type) {
    case TIMER_BASIC:
        regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
        return (uint16)(regs_b->CAPTURE >> 16);
    default:
        reg = dev->chnl_regs[channel];
        // Divide 2 because DC = (overflow - .5 * compare) / overflow
        return (uint16)reg->CCAPVUPD / 2;
    }
}

/**
 * @brief Set the compare value for the given timer channel.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose compare value to set.
 * @param value   New compare value.
 */
static inline void timer_set_compare(timer_dev *dev,
                                     uint8 channel,
                                     uint16 value) {
    timer_chnl_reg_map *reg;
    timer_basic_reg_map *regs_b;
    channel -= 1;
    switch (dev->type) {
    case TIMER_BASIC:
        regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
        regs_b->CAPTURE &= 0xFFFF;
        regs_b->CAPTURE |= value << 16;
        break;
    default:
        reg = dev->chnl_regs[channel];
        // Times 2 because DC = (overflow - .5 * compare) / overflow
        reg->CCAPVUPD = value * 2;
        break;
    }
}

/**
 * @brief Generate an update event for the given timer.
 *
 * Normally, this will cause the prescaler and auto-reload values in
 * the PSC and ARR registers to take immediate effect.  However, this
 * function will do nothing if the UDIS bit is set in the timer's CR1
 * register (UDIS is cleared by default).
 *
 * @param dev Timer device to generate an update for.
 */
static inline void timer_generate_update(timer_dev *dev) {
    return;
}

/**
 * @brief Enable a timer's trigger DMA request
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL
 */
static inline void timer_dma_enable_trg_req(timer_dev *dev) {

}

/**
 * @brief Disable a timer's trigger DMA request
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL
 */
static inline void timer_dma_disable_trg_req(timer_dev *dev) {

}

/**
 * @brief Enable a timer channel's DMA request.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL
 * @param channel Channel whose DMA request to enable.
 */
static inline void timer_dma_enable_req(timer_dev *dev, uint8 channel) {

}

/**
 * @brief Disable a timer channel's DMA request.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose DMA request to disable.
 */
static inline void timer_dma_disable_req(timer_dev *dev, uint8 channel) {

}

static inline void timer_irq_set_clr(timer_dev *dev, uint8 interrupt, uint8 set) {
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    interrupt -= 1;
    switch (dev->type) {
    case TIMER_ADVANCED:

        if (interrupt <= TIMER_CC6_INTERRUPT) {
            REG_SET_CLR(dev->chnl_regs[interrupt]->CONTROL, set, EPCACH_CR_CCIEN_MASK);
        }
        else if (interrupt == TIMER_OVERFLOW_INTERRUPT) {
            REG_SET_CLR(dev->regs->CONTROL, set, EPCA_CR_OVFIEN_MASK);
        }
        else if (interrupt == TIMER_HALT_INTERRUPT) {
            REG_SET_CLR(dev->regs->CONTROL, set, EPCA_CR_HALTIEN_MASK);
        }
        else if (interrupt >= TIMER_OVFL1_INTERRUPT) {
            REG_SET_CLR(dev->chnl_regs[interrupt - TIMER_OVFL1_INTERRUPT]->CONTROL, set, EPCACH_CR_CIOVFIEN_MASK);
        }
        break;
    case TIMER_GENERAL:
        if (interrupt <= TIMER_GEN_CC2_IRQ) {
            REG_SET_CLR(dev->chnl_regs[interrupt]->CONTROL, set, EPCACH_CR_CCIEN_MASK);
        }
        else if (interrupt == TIMER_GEN_OVERFLOW_IRQ) {
            REG_SET_CLR(dev->regs->CONTROL, set, EPCACH_CR_CCIEN_MASK);
        }
        else if (interrupt <= TIMER_GEN_OVFL2_IRQ) {
            REG_SET_CLR(dev->chnl_regs[interrupt - TIMER_GEN_OVFL1_IRQ]->CONTROL, set, EPCACH_CR_CIOVFIEN_MASK);
        }
        break;
    case TIMER_BASIC:
        if (interrupt == TIMER_BASIC_HIGH_OVFI_IRQ) {
            REG_SET_CLR(regs_b->CONFIG, set, TIMER_CFGR_HOVFIEN_MASK);
        }
        else if (interrupt == TIMER_BASIC_HIGH_EXTRA_IRQ) {
            REG_SET_CLR(regs_b->CONFIG, set, TIMER_CFGR_HEXIEN_MASK);
        }
        break;
    }
}

/**
 * @brief Enable a timer interrupt.
 * @param dev Timer device.
 * @param interrupt Interrupt number to enable; this may be any
 *                  timer_interrupt_id value appropriate for the timer.
 * @see timer_interrupt_id
 * @see timer_channel
 */
static inline void timer_enable_irq(timer_dev *dev, uint8 interrupt) {
    timer_irq_set_clr(dev, interrupt, 1);
}

/**
 * @brief Disable a timer interrupt.
 * @param dev Timer device.
 * @param interrupt Interrupt number to disable; this may be any
 *                  timer_interrupt_id value appropriate for the timer.
 * @see timer_interrupt_id
 * @see timer_channel
 */
static inline void timer_disable_irq(timer_dev *dev, uint8 interrupt) {
    timer_irq_set_clr(dev, interrupt, 0);
}



/**
 * @brief Get a channel's capture/compare output polarity
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose capture/compare output polarity to get.
 * @return Polarity, either 0 or 1.
 * @see timer_cc_set_polarity()
 */
static inline uint8 timer_cc_get_pol(timer_dev *dev, uint8 channel) {
    uint32 shift;
    uint32 pol;
    channel -= 1;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        return regs_b->CONFIG & TIMER_CFGR_HMD_MASK;
    default:
        pol = dev->chnl_regs[channel]->CONTROL & EPCACH_CR_COUTST_MASK;
        // Errata: Channels 4&5 (Wiring 5&6) polarities are reversed.
        if (channel >= 4) {
            pol = !pol;
        }
        return pol;
    }
    return 0;
}

/**
 * @brief Set a timer channel's capture/compare output polarity.
 *
 * If the timer channel is configured as output: polarity == 0 means
 * the output channel will be active high; polarity == 1 means active
 * low.
 *
 * If the timer channel is configured as input: polarity == 0 means
 * capture is done on the rising edge of ICn; when used as an external
 * trigger, ICn is non-inverted.  polarity == 1 means capture is done
 * on the falling edge of ICn; when used as an external trigger, ICn
 * is inverted.
 *
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose capture/compare output polarity to set.
 * @param pol New polarity, 0 or 1.
 */
static inline void timer_cc_set_pol(timer_dev *dev, uint8 channel, uint8 pol) {
    uint32 shift;
    channel -= 1;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        REG_SET_CLR(regs_b->CONFIG, pol, TIMER_CFGR_HMD_MASK);
        break;
    default:
        // Errata: Channels 4&5 (Wiring 5&6) polarities are reversed.
        if (channel >= 4) {
            pol = !pol;
        }
        REG_SET_CLR(dev->chnl_regs[channel]->CONTROL, pol,  EPCACH_CR_COUTST_MASK);
        break;
    }
}

/**
 * @brief Get a timer's DMA burst length.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @return Number of transfers per read or write to timer DMA register,
 *         from 1 to 18.
 */
static inline uint8 timer_dma_get_burst_len(timer_dev *dev) {
    return 0;
}

/**
 * @brief Set a timer's DMA burst length.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param length DMA burst length; i.e., number of DMA transfers per
 *               read/write to timer DMA register, from 1 to 18.
 */
static inline void timer_dma_set_burst_len(timer_dev *dev, uint8 length) {

}

/**
 * @brief Timer DMA base address.
 *
 * Defines the base address for DMA transfers.
 */
typedef enum timer_dma_base_addr {
    /** Base is control register 1 */
    TIMER_DMA_BASE_CR1 = 1
} timer_dma_base_addr;

/**
 * @brief Get the timer's DMA base address.
 *
 * Some restrictions apply; see the reference manual for your chip.
 *
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @return DMA base address
 */
static inline timer_dma_base_addr timer_dma_get_base_addr(timer_dev *dev) {
    static timer_dma_base_addr tmp;
    return tmp;
}

/**
 * @brief Set the timer's DMA base address.
 *
 * Some restrictions apply; see the reference manual for your chip.
 *
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param dma_base DMA base address.
 */
static inline void timer_dma_set_base_addr(timer_dev *dev,
                                           timer_dma_base_addr dma_base) {

}


/**
 * @brief Configure a channel's output compare mode.
 *
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel to configure in output compare mode.
 * @param mode Timer mode to set.
 * @param flags OR of timer_oc_mode_flags.
 * @see timer_oc_mode
 * @see timer_oc_mode_flags
 */
static inline void timer_mode_select(timer_dev *dev,
                                     uint8 channel,
                                     timer_mode_arch mode) {
    uint32 shift;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    channel -= 1;
    switch (dev->type) {
    case TIMER_BASIC:
        REG_SET_CLR(regs_b->CONFIG, 0, TIMER_CFGR_HMD_MASK);
        REG_SET_CLR(regs_b->CONFIG, 1, mode << TIMER_CFGR_HMD_BIT);
        break;
    default:
        dev->chnl_regs[channel]->MODE &= EPCACH_MODE_CMD_MASK | EPCACH_MODE_COSEL_MASK;
        dev->chnl_regs[channel]->MODE |= mode;
        break;
    }
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
