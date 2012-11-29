/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
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
 * @file libmaple/include/libmaple/spi.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief Serial Peripheral Interface (SPI) and Integrated
 *        Interchip Sound (I2S) peripheral support.
 *
 * I2S support is currently limited to register maps and bit definitions.
 */

#ifndef _LIBMAPLE_SPI_H_
#define _LIBMAPLE_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <libmaple/libmaple_types.h>
#include <libmaple/rcc.h>
#include <libmaple/nvic.h>
#include <libmaple/gpio.h>
#include <libmaple/xbar.h>

#include <series/spi.h>


/*
 * Register map base pointers
 */
/** SPI device type */
typedef struct spi_dev {
    spi_reg_map *regs;          /**< Register map */
    clk_dev_id clk_id;          /**< RCC clock information */
    nvic_irq_num irq_num;       /**< NVIC interrupt number */
    xbar_dev_id xbar_id;
} spi_dev;




/*
 * Register bit definitions
 */

/* Control register 2 */

#define SPI_CR2_FRF_BIT                 4

#define SPI_CR2_FRF                     (1U << SPI_CR2_FRF_BIT)

/* Status register */

#define SPI_SR_TIFRFE_BIT               8

#define SPI_SR_TIFRFE                   (1U << SPI_SR_TIFRFE_BIT)

/*
 * Device pointers
 */

extern struct spi_dev *SPI1;
extern struct spi_dev *SPI2;
extern struct spi_dev *SPI3;

/*
 * Routines
 */

gpio_af spi_get_af(struct spi_dev *dev);
void spi_master_enable(spi_dev *dev,
                       uint32 baud,
                       spi_mode mode,
                       uint32 flags);

void spi_slave_enable(spi_dev *dev,
                      spi_mode mode,
                      uint32 flags);

uint32 spi_tx(spi_dev *dev, const void *buf, uint32 len);

/**
 * @brief Call a function on each SPI port
 * @param fn Function to call.
 */
extern void spi_foreach(void (*fn)(spi_dev*));

void spi_peripheral_enable(spi_dev *dev);
void spi_peripheral_disable(spi_dev *dev);

void spi_tx_dma_enable(spi_dev *dev);
void spi_tx_dma_disable(spi_dev *dev);

void spi_rx_dma_enable(spi_dev *dev);
void spi_rx_dma_disable(spi_dev *dev);
void spi_init(spi_dev *dev);
/**
 * @brief Configure GPIO bit modes for use as a SPI port's pins.
 *
 * @param dev SPI device
 * @param as_master If true, configure as bus master; otherwise, as slave.
 * @param nss_dev NSS pin's GPIO device
 * @param nss_bit NSS pin's GPIO bit on nss_dev
 * @param comm_dev SCK, MISO, MOSI pins' GPIO device
 * @param sck_bit SCK pin's GPIO bit on comm_dev
 * @param miso_bit MISO pin's GPIO bit on comm_dev
 * @param mosi_bit MOSI pin's GPIO bit on comm_dev
 */
extern void spi_config_gpios(spi_dev *dev,
                             uint8 as_master,
                             struct gpio_dev *nss_dev,
                             uint8 nss_bit,
                             struct gpio_dev *comm_dev,
                             uint8 sck_bit,
                             uint8 miso_bit,
                             uint8 mosi_bit);
/**
 * @brief Determine if a SPI peripheral is enabled.
 * @param dev SPI device
 * @return True, if and only if dev's peripheral is enabled.
 */
static inline uint8 spi_is_enabled(spi_dev *dev) {
    return 0;
}

/**
 * @brief Disable all SPI peripherals
 */
static inline void spi_peripheral_disable_all(void) {

}

/**
 * @brief Enable SPI interrupt requests
 * @param dev SPI device
 * @param interrupt_flags Bitwise OR of spi_interrupt values to enable
 * @see spi_interrupt
 */
static inline void spi_irq_enable(spi_dev *dev, uint32 interrupt_flags) {
    nvic_irq_enable(dev->irq_num);
    REG_SET_CLR(dev->regs->CONFIG, 1, interrupt_flags);
}

/**
 * @brief Disable SPI interrupt requests
 * @param dev SPI device
 * @param interrupt_flags Bitwise OR of spi_interrupt values to disable
 * @see spi_interrupt
 */
static inline void spi_irq_disable(spi_dev *dev, uint32 interrupt_flags) {
    REG_SET_CLR(dev->regs->CONFIG, 0, interrupt_flags);
}

/**
 * @brief Get the data frame format flags with which a SPI port is
 *        configured.
 * @param dev SPI device whose data frame format to get.
 * @return SPI_DFF_8_BIT, if dev has an 8-bit data frame format.
 *         Otherwise, SPI_DFF_16_BIT.
 */
static inline spi_cfg_flag spi_dff(spi_dev *dev) {
    return (spi_cfg_flag)(dev->regs->CONFIG & SPI_CFGR_DSIZE_MASK);
}

/**
 * @brief Determine whether the device's peripheral receive (RX)
 *        register is empty.
 * @param dev SPI device
 * @return true, iff dev's RX register is NOT empty.
 */
static inline uint8 spi_is_rx_nonempty(spi_dev *dev) {
    return (dev->regs->CONTROL & SPI_CR_RFCNT_MASK) >> SPI_CR_RFCNT_BIT;
}

/**
 * @brief Retrieve the contents of the device's peripheral receive
 *        (RX) register.
 *
 * You may only call this function when the RX register is nonempty.
 * Calling this function clears the contents of the RX register.
 *
 * @param dev SPI device
 * @return Contents of dev's peripheral RX register
 * @see spi_is_rx_reg_nonempty()
 */
static inline uint16 spi_rx_reg(spi_dev *dev) {
    return *(__io uint8*)&dev->regs->DATA;
}

/**
 * @brief Determine whether the device's peripheral transmit (TX)
 *        register is empty.
 * @param dev SPI device
 * @return true, iff dev's TX register is empty.
 */
static inline uint8 spi_is_tx_empty(spi_dev *dev) {
    if (dev->regs->CONTROL & SPI_CR_TFCNT_MASK) {
        return 0;
    }
    return 1;
}

/**
 * @brief Load a value into the device's peripheral transmit (TX) register.
 *
 * You may only call this function when the TX register is empty.
 * Calling this function loads val into the peripheral's TX register.
 * If the device is properly configured, this will initiate a
 * transmission, the completion of which will cause the TX register to
 * be empty again.
 *
 * @param dev SPI device
 * @param val Value to load into the TX register.  If the SPI data
 *            frame format is 8 bit, the value must be right-aligned.
 * @see spi_is_tx_reg_empty()
 * @see spi_init()
 * @see spi_master_enable()
 * @see spi_slave_enable()
 */
static inline void spi_tx_reg(spi_dev *dev, uint16 val) {
    (*(__io uint16 *)&dev->regs->DATA) = (uint16)val;
}

/**
 * @brief Determine whether the device's peripheral busy (SPI_SR_BSY)
 *        flag is set.
 * @param dev SPI device
 * @return true, iff dev's BSY flag is set.
 */
static inline uint8 spi_is_busy(spi_dev *dev) {
    return (dev->regs->CONTROL & SPI_CR_BUSYF_MASK) != 0;
}

static inline void spi_blk_nss_inactv(spi_dev *dev) {
    while (!(dev->regs->CONTROL & SPI_CR_SLVSELI_MASK));
}




#ifdef __cplusplus
}
#endif

#endif
