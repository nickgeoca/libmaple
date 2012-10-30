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
#include <series/spi.h>

/*
 * Register maps
 */

/** SPI register map type. */
typedef struct spi_reg_map {
    __io uint32 DATA;       // Base Address + 0x0
    uint32      reserved0;
    uint32      reserved1;
    uint32      reserved2;
    __io uint32 CONTROL;    // Base Address + 0x10
    __io uint32 CONTROL_SET;
    __io uint32 CONTROL_CLR;
    uint32      reserved3;
    __io uint32 CONFIG;     // Base Address + 0x20
    __io uint32 CONFIG_SET;
    __io uint32 CONFIG_CLR;
    uint32      reserved4;
    __io uint32 CLKRATE;    // Base Address + 0x30
    uint32      reserved5;
    uint32      reserved6;
    uint32      reserved7;
    __io uint32 FSTATUS;    // Base Address + 0x40
    uint32      reserved8;
    uint32      reserved9;
    uint32      reserved10;
} spi_reg_map;

#define SPI_DATA_MASK                         0xFFFFFFFF
#define SPI_DATA_BIT                          0  /* DATA<31:0>: Input/Output Data.                 */

#define SPI_CR_RFRQI_MASK                     0x00000001
#define SPI_CR_RFORI_MASK                     0x00000002
#define SPI_CR_TFRQI_MASK                     0x00000004
#define SPI_CR_TFORI_MASK                     0x00000008
#define SPI_CR_SLVSELI_MASK                   0x00000010
#define SPI_CR_MDFI_MASK                      0x00000020
#define SPI_CR_URI_MASK                       0x00000040
#define SPI_CR_SREI_MASK                      0x00000080
#define SPI_CR_RFILI_MASK                     0x00000100
#define SPI_CR_TFILI_MASK                     0x00000200
#define SPI_CR_NSSSTS_MASK                    0x00004000
#define SPI_CR_BUSYF_MASK                     0x00008000
#define SPI_CR_RFCNT_MASK                     0x000F0000
#define SPI_CR_TFCNT_MASK                     0x00F00000
#define SPI_CR_DBGMD_MASK                     0x01000000
#define SPI_CR_RFRQI_BIT                      0  /* RFRQI<0>: Receive FIFO Read Request Interrupt Flag. */
#define SPI_CR_RFORI_BIT                      1  /* RFORI<1>: Receive FIFO Overrun Interrupt Flag. */
#define SPI_CR_TFRQI_BIT                      2  /* TFRQI<2>: Transmit FIFO Write Request Interrupt Flag. */
#define SPI_CR_TFORI_BIT                      3  /* TFORI<3>: Transmit FIFO Overrun Interrupt Flag. */
#define SPI_CR_SLVSELI_BIT                    4  /* SLVSELI<4>: Slave Selected Interrupt Flag.     */
#define SPI_CR_MDFI_BIT                       5  /* MDFI<5>: Mode Fault Interrupt Flag.            */
#define SPI_CR_URI_BIT                        6  /* URI<6>: Underrun Interrupt Flag.               */
#define SPI_CR_SREI_BIT                       7  /* SREI<7>: Shift Register Empty Interrupt Flag.  */
#define SPI_CR_RFILI_BIT                      8  /* RFILI<8>: Illegal Receive FIFO Access Interrupt Flag. */
#define SPI_CR_TFILI_BIT                      9  /* TFILI<9>: Illegal Transmit FIFO Access Interrupt Flag. */
#define SPI_CR_NSSSTS_BIT                     14 /* NSSSTS<14>: NSS Instantaneous Pin Status.      */
#define SPI_CR_BUSYF_BIT                      15 /* BUSYF<15>: SPI Busy.                           */
#define SPI_CR_RFCNT_BIT                      16 /* RFCNT<19:16>: Receive FIFO Counter.            */
#define SPI_CR_TFCNT_BIT                      20 /* TFCNT<23:20>: Transmit FIFO Counter.           */
#define SPI_CR_DBGMD_BIT                      24 /* DBGMD<24>: SPI Debug Mode.                     */
#define SPI_CR_RFRQI_NOT_SET                  (0 << SPI_CR_RFRQI_BIT)
#define SPI_CR_RFRQI_SET                      (1 << SPI_CR_RFRQI_BIT)
#define SPI_CR_RFORI_NOT_SET                  (0 << SPI_CR_RFORI_BIT)
#define SPI_CR_RFORI_SET                      (1 << SPI_CR_RFORI_BIT)
#define SPI_CR_TFRQI_NOT_SET                  (0 << SPI_CR_TFRQI_BIT)
#define SPI_CR_TFRQI_SET                      (1 << SPI_CR_TFRQI_BIT)
#define SPI_CR_TFORI_NOT_SET                  (0 << SPI_CR_TFORI_BIT)
#define SPI_CR_TFORI_SET                      (1 << SPI_CR_TFORI_BIT)
#define SPI_CR_SLVSELI_NOT_SET                (0 << SPI_CR_SLVSELI_BIT)
#define SPI_CR_SLVSELI_SET                    (1 << SPI_CR_SLVSELI_BIT)
#define SPI_CR_MDFI_NOT_SET                   (0 << SPI_CR_MDFI_BIT)
#define SPI_CR_MDFI_SET                       (1 << SPI_CR_MDFI_BIT)
#define SPI_CR_URI_NOT_SET                    (0 << SPI_CR_URI_BIT)
#define SPI_CR_URI_SET                        (1 << SPI_CR_URI_BIT)
#define SPI_CR_SREI_NOT_SET                   (0 << SPI_CR_SREI_BIT)
#define SPI_CR_SREI_SET                       (1 << SPI_CR_SREI_BIT)
#define SPI_CR_RFILI_NOT_SET                  (0 << SPI_CR_RFILI_BIT)
#define SPI_CR_RFILI_SET                      (1 << SPI_CR_RFILI_BIT)
#define SPI_CR_TFILI_NOT_SET                  (0 << SPI_CR_TFILI_BIT)
#define SPI_CR_TFILI_SET                      (1 << SPI_CR_TFILI_BIT)
#define SPI_CR_NSSSTS_LOW                     (0 << SPI_CR_NSSSTS_BIT)
#define SPI_CR_NSSSTS_HIGH                    (1 << SPI_CR_NSSSTS_BIT)
#define SPI_CR_BUSYF_NOT_SET                  (0 << SPI_CR_BUSYF_BIT)
#define SPI_CR_BUSYF_SET                      (1 << SPI_CR_BUSYF_BIT)
#define SPI_CR_DBGMD_RUN                      (0 << SPI_CR_DBGMD_BIT)
#define SPI_CR_DBGMD_HALT                     (1 << SPI_CR_DBGMD_BIT)


#define SPI_CFGR_RFRQIEN_MASK                 0x00000001
#define SPI_CFGR_RFORIEN_MASK                 0x00000002
#define SPI_CFGR_TFRQIEN_MASK                 0x00000004
#define SPI_CFGR_TFORIEN_MASK                 0x00000008
#define SPI_CFGR_SLVSELIEN_MASK               0x00000010
#define SPI_CFGR_MDFIEN_MASK                  0x00000020
#define SPI_CFGR_URIEN_MASK                   0x00000040
#define SPI_CFGR_SREIEN_MASK                  0x00000080
#define SPI_CFGR_SPIEN_MASK                   0x00000100
#define SPI_CFGR_MSTEN_MASK                   0x00000200
#define SPI_CFGR_CLKPOL_MASK                  0x00000400
#define SPI_CFGR_CLKPHA_MASK                  0x00000800
#define SPI_CFGR_NSSPOL_MASK                  0x00001000
#define SPI_CFGR_DDIRSEL_MASK                 0x00002000
#define SPI_CFGR_NSSMD_MASK                   0x0000C000
#define SPI_CFGR_RFTH_MASK                    0x00030000
#define SPI_CFGR_TFTH_MASK                    0x000C0000
#define SPI_CFGR_DSIZE_MASK                   0x00F00000
#define SPI_CFGR_DMAEN_MASK                   0x01000000
#define SPI_CFGR_RFIFOFL_MASK                 0x20000000
#define SPI_CFGR_TFIFOFL_MASK                 0x40000000
#define SPI_CFGR_RESET_MASK                   0x80000000
#define SPI_CFGR_RFRQIEN_BIT                  0  /* RFRQIEN<0>: Receive FIFO Read Request Interrupt Enable. */
#define SPI_CFGR_RFORIEN_BIT                  1  /* RFORIEN<1>: Receive FIFO Overrun Interrupt Enable. */
#define SPI_CFGR_TFRQIEN_BIT                  2  /* TFRQIEN<2>: Transmit FIFO Write Request Interrupt Enable. */
#define SPI_CFGR_TFORIEN_BIT                  3  /* TFORIEN<3>: Transmit FIFO Overrun Interrupt Enable. */
#define SPI_CFGR_SLVSELIEN_BIT                4  /* SLVSELIEN<4>: Slave Selected Interrupt Enable. */
#define SPI_CFGR_MDFIEN_BIT                   5  /* MDFIEN<5>: Mode Fault Interrupt Enable.        */
#define SPI_CFGR_URIEN_BIT                    6  /* URIEN<6>: Underrun Interrupt Enable.           */
#define SPI_CFGR_SREIEN_BIT                   7  /* SREIEN<7>: Shift Register Empty Interrupt Enable. */
#define SPI_CFGR_SPIEN_BIT                    8  /* SPIEN<8>: SPI Enable.                          */
#define SPI_CFGR_MSTEN_BIT                    9  /* MSTEN<9>: Master Mode Enable.                  */
#define SPI_CFGR_CLKPOL_BIT                   10 /* CLKPOL<10>: SPI Clock Polarity.                */
#define SPI_CFGR_CLKPHA_BIT                   11 /* CLKPHA<11>: SPI Clock Phase.                   */
#define SPI_CFGR_NSSPOL_BIT                   12 /* NSSPOL<12>: Slave Select Polarity Select.      */
#define SPI_CFGR_DDIRSEL_BIT                  13 /* DDIRSEL<13>: Data Direction Select.            */
#define SPI_CFGR_NSSMD_BIT                    14 /* NSSMD<15:14>: Slave Select Mode.               */
#define SPI_CFGR_RFTH_BIT                     16 /* RFTH<17:16>: Receive FIFO Threshold.           */
#define SPI_CFGR_TFTH_BIT                     18 /* TFTH<19:18>: Transmit FIFO Threshold.          */
#define SPI_CFGR_DSIZE_BIT                    20 /* DSIZE<23:20>: Data Size.                       */
#define SPI_CFGR_DMAEN_BIT                    24 /* DMAEN<24>: DMA Enable.                         */
#define SPI_CFGR_RFIFOFL_BIT                  29 /* RFIFOFL<29>: Receive FIFO Flush.               */
#define SPI_CFGR_TFIFOFL_BIT                  30 /* TFIFOFL<30>: Transmit FIFO Flush.              */
#define SPI_CFGR_RESET_BIT                    31 /* RESET<31>: Module Soft Reset.                  */
#define SPI_CFGR_RFRQIEN_DS                   (0 << SPI_CFGR_RFRQIEN_BIT)
#define SPI_CFGR_RFRQIEN_EN                   (1 << SPI_CFGR_RFRQIEN_BIT)
#define SPI_CFGR_RFORIEN_DS                   (0 << SPI_CFGR_RFORIEN_BIT)
#define SPI_CFGR_RFORIEN_EN                   (1 << SPI_CFGR_RFORIEN_BIT)
#define SPI_CFGR_TFRQIEN_DS                   (0 << SPI_CFGR_TFRQIEN_BIT)
#define SPI_CFGR_TFRQIEN_EN                   (1 << SPI_CFGR_TFRQIEN_BIT)
#define SPI_CFGR_TFORIEN_DS                   (0 << SPI_CFGR_TFORIEN_BIT)
#define SPI_CFGR_TFORIEN_EN                   (1 << SPI_CFGR_TFORIEN_BIT)
#define SPI_CFGR_SLVSELIEN_DS                 (0 << SPI_CFGR_SLVSELIEN_BIT)
#define SPI_CFGR_SLVSELIEN_EN                 (1 << SPI_CFGR_SLVSELIEN_BIT)
#define SPI_CFGR_MDFIEN_DS                    (0 << SPI_CFGR_MDFIEN_BIT)
#define SPI_CFGR_MDFIEN_EN                    (1 << SPI_CFGR_MDFIEN_BIT)
#define SPI_CFGR_URIEN_DS                     (0 << SPI_CFGR_URIEN_BIT)
#define SPI_CFGR_URIEN_EN                     (1 << SPI_CFGR_URIEN_BIT)
#define SPI_CFGR_SREIEN_DS                    (0 << SPI_CFGR_SREIEN_BIT)
#define SPI_CFGR_SREIEN_EN                    (1 << SPI_CFGR_SREIEN_BIT)
#define SPI_CFGR_SPIEN_DS                     (0 << SPI_CFGR_SPIEN_BIT)
#define SPI_CFGR_SPIEN_EN                     (1 << SPI_CFGR_SPIEN_BIT)
#define SPI_CFGR_MSTEN_DS                     (0 << SPI_CFGR_MSTEN_BIT)
#define SPI_CFGR_MSTEN_EN                     (1 << SPI_CFGR_MSTEN_BIT)
#define SPI_CFGR_CLKPOL_LOW                   (0 << SPI_CFGR_CLKPOL_BIT)
#define SPI_CFGR_CLKPOL_HIGH                  (1 << SPI_CFGR_CLKPOL_BIT)
#define SPI_CFGR_CLKPHA_CENTER                (0 << SPI_CFGR_CLKPHA_BIT)
#define SPI_CFGR_CLKPHA_EDGE                  (1 << SPI_CFGR_CLKPHA_BIT)
#define SPI_CFGR_NSSPOL_LOW                   (0 << SPI_CFGR_NSSPOL_BIT)
#define SPI_CFGR_NSSPOL_HIGH                  (1 << SPI_CFGR_NSSPOL_BIT)
#define SPI_CFGR_DDIRSEL_MSB_FIRST            (0 << SPI_CFGR_DDIRSEL_BIT)
#define SPI_CFGR_DDIRSEL_LSB_FIRST            (1 << SPI_CFGR_DDIRSEL_BIT)
#define SPI_CFGR_NSSMD_3_WIRE_MASTER_SLAVE    (0 << SPI_CFGR_NSSMD_BIT)
#define SPI_CFGR_NSSMD_4_WIRE_SLAVE           (1 << SPI_CFGR_NSSMD_BIT)
#define SPI_CFGR_NSSMD_4_WIRE_MASTER_NSS_LOW  (2 << SPI_CFGR_NSSMD_BIT)
#define SPI_CFGR_NSSMD_4_WIRE_MASTER_NSS_HIGH (3 << SPI_CFGR_NSSMD_BIT)
#define SPI_CFGR_RFTH_ONE                     (0 << SPI_CFGR_RFTH_BIT)
#define SPI_CFGR_RFTH_TWO                     (1 << SPI_CFGR_RFTH_BIT)
#define SPI_CFGR_RFTH_FOUR                    (2 << SPI_CFGR_RFTH_BIT)
#define SPI_CFGR_RFTH_FULL                    (3 << SPI_CFGR_RFTH_BIT)
#define SPI_CFGR_TFTH_ONE                     (0 << SPI_CFGR_TFTH_BIT)
#define SPI_CFGR_TFTH_TWO                     (1 << SPI_CFGR_TFTH_BIT)
#define SPI_CFGR_TFTH_FOUR                    (2 << SPI_CFGR_TFTH_BIT)
#define SPI_CFGR_TFTH_EMPTY                   (3 << SPI_CFGR_TFTH_BIT)
#define SPI_CFGR_DMAEN_DS                     (0 << SPI_CFGR_DMAEN_BIT)
#define SPI_CFGR_DMAEN_EN                     (1 << SPI_CFGR_DMAEN_BIT)
#define SPI_CFGR_RFIFOFL_SET                  (1 << SPI_CFGR_RFIFOFL_BIT)
#define SPI_CFGR_TFIFOFL_SET                  (1 << SPI_CFGR_TFIFOFL_BIT)
#define SPI_CFGR_RESET_INACTV                 (0U << SPI_CFGR_RESET_BIT)
#define SPI_CFGR_RESET_ACTV                   (1U << SPI_CFGR_RESET_BIT)

#define SPI_CLKRATE_CLKDIV_MASK               0x0000FFFF
#define SPI_CLKRATE_CLKDIV_BIT                0  /* CLKDIV<2>: 1 ? ? ? +                           */

#define SPI_FSTATUS_RFRPTR_MASK               0x0000000F
#define SPI_FSTATUS_RFWPTR_MASK               0x000000F0
#define SPI_FSTATUS_TFRPTR_MASK               0x00000F00
#define SPI_FSTATUS_TFWPTR_MASK               0x0000F000
#define SPI_FSTATUS_RFRPTR_BIT                0  /* RFRPTR<3:0>: Receive FIFO Read Pointer.        */
#define SPI_FSTATUS_RFWPTR_BIT                4  /* RFWPTR<7:4>: Receive FIFO Write Pointer.       */
#define SPI_FSTATUS_TFRPTR_BIT                8  /* TFRPTR<11:8>: Transmit FIFO Read Pointer.      */
#define SPI_FSTATUS_TFWPTR_BIT                12 /* TFWPTR<15:12>: Transmit FIFO Write Pointer.    */

/*
 * Devices
 */

/** SPI device type */
typedef struct spi_dev {
    spi_reg_map *regs;          /**< Register map */
    clk_dev_id clk_id;          /**< RCC clock information */
    nvic_irq_num irq_num;       /**< NVIC interrupt number */
    xbar_dev_id xbar_id;
} spi_dev;

/*
 * SPI Convenience functions
 */

void spi_init(spi_dev *dev);

struct gpio_dev;
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
 * @brief SPI initialization flags.
 * @see spi_master_enable()
 * @see spi_slave_enable()
 */
typedef enum spi_cfg_flag {
    SPI_MASTER = SPI_CFGR_MSTEN_EN,
    SPI_CLKPOLAR_HIGH = SPI_CFGR_CLKPOL_HIGH,                   /**< High/low clock polarity */
    SPI_CLKPHASE_EDGE = SPI_CFGR_CLKPHA_EDGE,                   /**< Edge/Center clock phase */
    SPI_SLVPOLAR_HIGH = SPI_CFGR_NSSPOL_HIGH,                   /**< High/low active NSS    */
    SPI_FRAME_LSB = SPI_CFGR_DDIRSEL_LSB_FIRST,                 /**< MSB/LSB First. (big/little-endiann) */

    // Choose one of these
    SPI_MODE_SLV_3WIRE = SPI_CFGR_NSSMD_3_WIRE_MASTER_SLAVE,
    SPI_MODE_SLV_4WIRE = SPI_CFGR_NSSMD_4_WIRE_SLAVE,
    SPI_MODE_MST_4WIRE_NSS_LOW = SPI_CFGR_NSSMD_4_WIRE_MASTER_NSS_LOW,
    SPI_MODE_MST_4WIRE_NSS_HIGH = SPI_CFGR_NSSMD_4_WIRE_MASTER_NSS_HIGH,

    // Choose one of these
    SPI_DFF_8_BIT = (7 << SPI_CFGR_DSIZE_BIT),       /**< 8 bit frame buffer */
    SPI_DFF_16_BIT = (15 << SPI_CFGR_DSIZE_BIT),     /**< 16 bit frame buffer */

    // Not needed, just here for compatibility.
    SPI_FRAME_MSB = 0,
} spi_cfg_flag;


typedef enum spi_mode {
    SPI_MODE_ENUM_
}spi_mode;


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

/** Available SPI interrupts */
typedef enum spi_interrupt {
    SPI_RX_INTERRUPT  = SPI_CFGR_RFRQIEN_MASK,       /**< RX buffer has data. Can set threshold */
    SPI_RXOVF_INTERRUPT = SPI_CFGR_RFORIEN_MASK,     /**< RX buffer overflow  */
    SPI_TX_INTERRUPT  = SPI_CFGR_TFRQIEN_MASK,       /**< Interrupt occurs when a threshold
                                                          of empty slots in FIFO is exceeded  */
    SPI_TXOVF_INTERRUPT = SPI_CFGR_TFORIEN_MASK,     /**< TX buffer overflow  */
    SPI_SLV_SEL_INTERRUPT = SPI_CFGR_SLVSELIEN_MASK, /**< Occurs when NSS is deglitched and active */
    SPI_MODE_FAULT_INTERRUPT = SPI_CFGR_MDFIEN_MASK, /**< Master mode collision on bus  */
    SPI_UNDERRUN_INTERRUPT = SPI_CFGR_URIEN_MASK,    /**< End of transmission (empty shift reg and empty Tx FIFO_  */
    SPI_SHIFT_REG_EMPTY = SPI_CFGR_SREIEN_MASK,      /**< Shift register empty  */
} spi_interrupt;

/**
 * @brief Mask for all spi_interrupt values
 * @see spi_interrupt
 */
#define SPI_INTERRUPTS_ALL  (SPI_CFGR_RFRQIEN_MASK | SPI_CFGR_RFORIEN_MASK  |  \
                            SPI_CFGR_TFRQIEN_MASK | SPI_CFGR_TFORIEN_MASK   |  \
                            SPI_CFGR_SLVSELIEN_MASK | SPI_CFGR_MDFIEN_MASK  |  \
                            SPI_CFGR_URIEN_MASK | SPI_CFGR_SREIEN_MASK)


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
 * @return true, iff dev's RX register is empty.
 */
static inline uint8 spi_is_rx_nonempty(spi_dev *dev) {
    if (dev->regs->CONTROL & SPI_CR_RFCNT_MASK) {
        return 0;
    }
    return 1;
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
    return dev->regs->DATA;
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
    dev->regs->DATA = (uint32)val;
}

/**
 * @brief Determine whether the device's peripheral busy (SPI_SR_BSY)
 *        flag is set.
 * @param dev SPI device
 * @return true, iff dev's BSY flag is set.
 */
static inline uint8 spi_is_busy(spi_dev *dev) {
    return dev->regs->CONTROL & SPI_CR_BUSYF_MASK;
}

/*
 * I2S convenience functions (TODO)
 */

#ifdef __cplusplus
}
#endif

#endif
