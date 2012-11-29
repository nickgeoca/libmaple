/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 LeafLabs, LLC.
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
 * @file libmaple/stm32f2/include/series/spi.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief STM32F2 SPI/I2S series header.
 */

#ifndef _LIBMAPLE_SIM3U1_SPI_H_
#define _LIBMAPLE_SIM3U1_SPI_H_

#include <stdint.h>      /* for gpio_af */

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Register maps
 */

/** SPI register map type. */
typedef struct spi_reg_map {
    volatile uint32_t DATA;       // Base Address + 0x0
    uint32_t          reserved0;
    uint32_t          reserved1;
    uint32_t          reserved2;
    volatile uint32_t CONTROL;    // Base Address + 0x10
    volatile uint32_t CONTROL_SET;
    volatile uint32_t CONTROL_CLR;
    uint32_t          reserved3;
    volatile uint32_t CONFIG;     // Base Address + 0x20
    volatile uint32_t CONFIG_SET;
    volatile uint32_t CONFIG_CLR;
    uint32_t          reserved4;
    volatile uint32_t CLKRATE;    // Base Address + 0x30
    uint32_t          reserved5;
    uint32_t          reserved6;
    uint32_t          reserved7;
    volatile uint32_t FSTATUS;    // Base Address + 0x40
    uint32_t          reserved8;
    uint32_t          reserved9;
    uint32_t          reserved10;
} spi_reg_map;

#define SPI1_BASE                       ((spi_reg_map*)0x40004000)
#define SPI2_BASE                       ((spi_reg_map*)0x40005000)
#define SPI3_BASE                       ((spi_reg_map*)0x40006000)

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


/**
 * @brief SPI initialization flags.
 * @see spi_master_enable()
 * @see spi_slave_enable()
 */
typedef enum spi_cfg_flag {
    SPI_MASTER = SPI_CFGR_MSTEN_EN,
    SPI_SLAVE = 0,
    SPI_CLKPOLAR_HIGH = SPI_CFGR_CLKPOL_HIGH,                   /**< High/low clock polarity */
    SPI_CLKPHASE_EDGE = SPI_CFGR_CLKPHA_EDGE,                   /**< Edge/Center clock phase */
    SPI_SLVNSS_HIGH = SPI_CFGR_NSSPOL_HIGH,                   /**< High/low active NSS.    */
    SPI_SLVNSS_LOW  = 0,
    SPI_FRAME_LSB = SPI_CFGR_DDIRSEL_LSB_FIRST,                 /**< MSB/LSB First.          */
    SPI_FRAME_MSB = 0,

    // Choose one of these
    SPI_MODE_MST_SLV_3WIRE = SPI_CFGR_NSSMD_3_WIRE_MASTER_SLAVE,
    SPI_MODE_SLV_4WIRE = SPI_CFGR_NSSMD_4_WIRE_SLAVE,
    SPI_MODE_MST_4WIRE_NSS_LOW = SPI_CFGR_NSSMD_4_WIRE_MASTER_NSS_LOW,
    SPI_MODE_MST_4WIRE_NSS_HIGH = SPI_CFGR_NSSMD_4_WIRE_MASTER_NSS_HIGH,

    // Choose one of these
    SPI_DFF_8_BIT = (7 << SPI_CFGR_DSIZE_BIT),       /**< 8 bit frame buffer */
    SPI_DFF_16_BIT = (15 << SPI_CFGR_DSIZE_BIT),     /**< 16 bit frame buffer */

} spi_cfg_flag;


typedef enum spi_mode {
    SPI_MODE_0 = 0 | 0,                                 /**< Clock polarity low. Rising edge capture.   */
    SPI_MODE_1 = 0 | SPI_CLKPHASE_EDGE,                 /**< Clock polarity low. Falling edge capture.  */
    SPI_MODE_2 = SPI_CLKPOLAR_HIGH | 0,                 /**< Clock polarity high. Falling edge capture. */
    SPI_MODE_3 = SPI_CLKPOLAR_HIGH | SPI_CLKPHASE_EDGE, /**< Clock polarity high. Rising edge capture.  */
}spi_mode;






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


#define SPI_INTERRUPTS_ALL  (SPI_CFGR_RFRQIEN_MASK | SPI_CFGR_RFORIEN_MASK  |  \
                            SPI_CFGR_TFRQIEN_MASK | SPI_CFGR_TFORIEN_MASK   |  \
                            SPI_CFGR_SLVSELIEN_MASK | SPI_CFGR_MDFIEN_MASK  |  \
                            SPI_CFGR_URIEN_MASK | SPI_CFGR_SREIEN_MASK)


#ifdef __cplusplus
}
#endif

#endif
