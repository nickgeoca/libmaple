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
 * @file libmaple/stm32f2/include/series/usart.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief STM32F2 USART support.
 */

#ifndef _LIBMAPLE_STM32F2_USART_H_
#define _LIBMAPLE_STM32F2_USART_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/gpio.h>      /* for gpio_af */

/*
 * Register map base pointers.
 */

struct usart_reg_map;

/** USART1 register map base pointer */
#define USART1_BASE                     ((struct usart_reg_map*)0x40002000)


/*
 * F2-only register bit definitions.
 */

/* Control register 1 */

/**
 * @brief Oversampling mode bit.
 * Availability: STM32F2. */
#define USART_CR1_OVER8_BIT             15

/**
 * @brief Oversampling mode.
 * Availability: STM32F2. */
#define USART_CR1_OVER8                 (1U << USART_CR1_OVER8_BIT)

/* Control register 3 */

/** One sample bit method enable bit. */
#define USART_CR3_ONEBIT_BIT            11

/** One bit sample method enable. */
#define USART_CR3_ONEBIT                (1 << USART_CR3_ONEBIT_BIT)
/** Sample method: Three sample bit method. */
#define USART_CR3_ONEBIT_3SAMPLE        (0 << USART_CR3_ONEBIT_BIT)
/** Sample method: One sample bit method. */
#define USART_CR3_ONEBIT_1SAMPLE        (1 << USART_CR3_ONEBIT_BIT)

/*
 * Devices
 */

struct usart_dev;
extern struct usart_dev *USART1;

/*
 * Routines
 */

gpio_af usart_get_af(struct usart_dev *dev);

typedef struct usart_reg_map
{
    __io uint32  CONFIG; // Base Address + 0x0
    __io uint32  CONFIG_SET;
    __io uint32  CONFIG_CLR;
    uint32       reserved0;
    __io uint32  MODE; // Base Address + 0x10
    __io uint32  MODE_SET;
    __io uint32  MODE_CLR;
    uint32       reserved1;
    __io uint32  FLOWCN; // Base Address + 0x20
    __io uint32  FLOWCN_SET;
    __io uint32  FLOWCN_CLR;
    uint32       reserved2;
    __io uint32  CONTROL; // Base Address + 0x30
    __io uint32  CONTROL_SET;
    __io uint32  CONTROL_CLR;
    uint32       reserved3;
    __io uint32  IPDELAY; // Base Address + 0x40
    uint32       reserved4;
    uint32       reserved5;
    uint32       reserved6;
    __io uint32  BAUDRATE; // Base Address + 0x50
    uint32       reserved7;
    uint32       reserved8;
    uint32       reserved9;
    __io uint32  FIFOCN; // Base Address + 0x60
    __io uint32  FIFOCN_SET;
    __io uint32  FIFOCN_CLR;
    uint32       reserved10;
    __io uint32  DATA; // Base Address + 0x70
    uint32       reserved11;
    uint32       reserved12;
    uint32       reserved13;
} usart_reg_map;

/** USART device type */
typedef struct usart_dev {
    usart_reg_map *regs;             /**< Register map */
    ring_buffer *rb;                 /**< RX ring buffer */
    uint32 max_baud;                 /**< @brief Deprecated.
                                      * Maximum baud rate. */
    uint8 rx_buf[64];               /**< @brief Deprecated.
                                      * Actual RX buffer used by rb.
                                      * This field will be removed in
                                      * a future release. */ // todo silabs: rx_buf size
    clk_dev_id clk_id;               /**< RCC clock information */
    nvic_irq_num irq_num;            /**< USART NVIC interrupt */
} usart_dev;

/* Config reg */
#define UART_CFGR_RSTRTEN_MASK          0x00000001
#define UART_CFGR_RPAREN_MASK           0x00000002
#define UART_CFGR_RSTPEN_MASK           0x00000004
#define UART_CFGR_RSTPMD_MASK           0x00000018
#define UART_CFGR_RPARMD_MASK           0x00000060
#define UART_CFGR_RDATLN_MASK           0x00000700
#define UART_CFGR_RSCEN_MASK            0x00001000
#define UART_CFGR_RIRDAEN_MASK          0x00002000
#define UART_CFGR_RINVEN_MASK           0x00004000
#define UART_CFGR_TSTRTEN_MASK          0x00010000
#define UART_CFGR_TPAREN_MASK           0x00020000
#define UART_CFGR_TSTPEN_MASK           0x00040000
#define UART_CFGR_TSTPMD_MASK           0x00180000
#define UART_CFGR_TPARMD_MASK           0x00600000
#define UART_CFGR_TDATLN_MASK           0x07000000
#define UART_CFGR_TSCEN_MASK            0x10000000
#define UART_CFGR_TIRDAEN_MASK          0x20000000
#define UART_CFGR_TINVEN_MASK           0x40000000

#define UART_CFGR_RSTRTEN_BIT           0  /* RSTRTEN<0>: Receiver Start Enable.             */
#define UART_CFGR_RPAREN_BIT            1  /* RPAREN<1>: Receiver Parity Enable.             */
#define UART_CFGR_RSTPEN_BIT            2  /* RSTPEN<2>: Receiver Stop Enable.               */
#define UART_CFGR_RSTPMD_BIT            3  /* RSTPMD<4:3>: Receiver Stop Mode.               */
#define UART_CFGR_RPARMD_BIT            5  /* RPARMD<6:5>: Receiver Parity Mode.             */
#define UART_CFGR_RDATLN_BIT            8  /* RDATLN<10:8>: Receiver Data Length.            */
#define UART_CFGR_RSCEN_BIT             12 /* RSCEN<12>: Receiver Smartcard Parity Response Enable. */
#define UART_CFGR_RIRDAEN_BIT           13 /* RIRDAEN<13>: Receiver IrDA Enable.             */
#define UART_CFGR_RINVEN_BIT            14 /* RINVEN<14>: Receiver Invert Enable.            */
#define UART_CFGR_TSTRTEN_BIT           16 /* TSTRTEN<16>: Transmitter Start Enable.         */
#define UART_CFGR_TPAREN_BIT            17 /* TPAREN<17>: Transmitter Parity Enable.         */
#define UART_CFGR_TSTPEN_BIT            18 /* TSTPEN<18>: Transmitter Stop Enable.           */
#define UART_CFGR_TSTPMD_BIT            19 /* TSTPMD<20:19>: Transmitter Stop Mode.          */
#define UART_CFGR_TPARMD_BIT            21 /* TPARMD<22:21>: Transmitter Parity Mode.        */
#define UART_CFGR_TDATLN_BIT            24 /* TDATLN<26:24>: Transmitter Data Length.        */
#define UART_CFGR_TSCEN_BIT             28 /* TSCEN<28>: Transmitter Smartcard Parity Response Enable. */
#define UART_CFGR_TIRDAEN_BIT           29 /* TIRDAEN<29>: Transmitter IrDA Enable.          */
#define UART_CFGR_TINVEN_BIT            30 /* TINVEN<30>: Transmitter Invert Enable.         */

#define UART_CFGR_TDATLN_5_BITS         (0 << UART_CFGR_TDATLN_BIT)
#define UART_CFGR_TDATLN_6_BITS         (1 << UART_CFGR_TDATLN_BIT)
#define UART_CFGR_TDATLN_7_BITS         (2 << UART_CFGR_TDATLN_BIT)
#define UART_CFGR_TDATLN_8_BITS         (3 << UART_CFGR_TDATLN_BIT)
#define UART_CFGR_TDATLN_9_BITS_FIFO    (4 << UART_CFGR_TDATLN_BIT)
#define UART_CFGR_TDATLN_9_BITS_TBIT    (5 << UART_CFGR_TDATLN_BIT)
#define UART_CFGR_RDATLN_5_BITS         (0 << UART_CFGR_RDATLN_BIT)
#define UART_CFGR_RDATLN_6_BITS         (1 << UART_CFGR_RDATLN_BIT)
#define UART_CFGR_RDATLN_7_BITS         (2 << UART_CFGR_RDATLN_BIT)
#define UART_CFGR_RDATLN_8_BITS         (3 << UART_CFGR_RDATLN_BIT)
#define UART_CFGR_RDATLN_9_BITS_STORED  (4 << UART_CFGR_RDATLN_BIT)
#define UART_CFGR_RDATLN_9_BITS_MATCH   (5 << UART_CFGR_RDATLN_BIT)
#define UART_CFGR_RSTRTEN_DS            (0 << UART_CFGR_RSTRTEN_BIT)
#define UART_CFGR_RSTRTEN_EN            (1 << UART_CFGR_RSTRTEN_BIT)
#define UART_CFGR_RPAREN_DS             (0 << UART_CFGR_RPAREN_BIT)
#define UART_CFGR_RPAREN_EN             (1 << UART_CFGR_RPAREN_BIT)
#define UART_CFGR_RSTPEN_DS             (0 << UART_CFGR_RSTPEN_BIT)
#define UART_CFGR_RSTPEN_EN             (1 << UART_CFGR_RSTPEN_BIT)
#define UART_CFGR_RSTPMD_0P5_STOP       (0 << UART_CFGR_RSTPMD_BIT)
#define UART_CFGR_RSTPMD_1_STOP         (1 << UART_CFGR_RSTPMD_BIT)
#define UART_CFGR_RSTPMD_1P5_STOP       (2 << UART_CFGR_RSTPMD_BIT)
#define UART_CFGR_RSTPMD_2_STOP         (3 << UART_CFGR_RSTPMD_BIT)
#define UART_CFGR_RPARMD_ODD            (0 << UART_CFGR_RPARMD_BIT)
#define UART_CFGR_RPARMD_EVEN           (1 << UART_CFGR_RPARMD_BIT)
#define UART_CFGR_RPARMD_MARK           (2 << UART_CFGR_RPARMD_BIT)
#define UART_CFGR_RPARMD_SPACE          (3 << UART_CFGR_RPARMD_BIT)
#define UART_CFGR_RSCEN_DS              (0 << UART_CFGR_RSCEN_BIT)
#define UART_CFGR_RSCEN_EN              (1 << UART_CFGR_RSCEN_BIT)
#define UART_CFGR_RIRDAEN_DS            (0 << UART_CFGR_RIRDAEN_BIT)
#define UART_CFGR_RIRDAEN_EN            (1 << UART_CFGR_RIRDAEN_BIT)
#define UART_CFGR_RINVEN_DS             (0 << UART_CFGR_RINVEN_BIT)
#define UART_CFGR_RINVEN_EN             (1 << UART_CFGR_RINVEN_BIT)
#define UART_CFGR_TSTRTEN_DS            (0 << UART_CFGR_TSTRTEN_BIT)
#define UART_CFGR_TSTRTEN_EN            (1 << UART_CFGR_TSTRTEN_BIT)
#define UART_CFGR_TPAREN_DS             (0 << UART_CFGR_TPAREN_BIT)
#define UART_CFGR_TPAREN_EN             (1 << UART_CFGR_TPAREN_BIT)
#define UART_CFGR_TSTPEN_DS             (0 << UART_CFGR_TSTPEN_BIT)
#define UART_CFGR_TSTPEN_EN             (1 << UART_CFGR_TSTPEN_BIT)
#define UART_CFGR_TSTPMD_0P5_STOP       (0 << UART_CFGR_TSTPMD_BIT)
#define UART_CFGR_TSTPMD_1_STOP         (1 << UART_CFGR_TSTPMD_BIT)
#define UART_CFGR_TSTPMD_1P5_STOP       (2 << UART_CFGR_TSTPMD_BIT)
#define UART_CFGR_TSTPMD_2_STOP         (3 << UART_CFGR_TSTPMD_BIT)
#define UART_CFGR_TPARMD_ODD            (0 << UART_CFGR_TPARMD_BIT)
#define UART_CFGR_TPARMD_EVEN           (1 << UART_CFGR_TPARMD_BIT)
#define UART_CFGR_TPARMD_MARK           (2 << UART_CFGR_TPARMD_BIT)
#define UART_CFGR_TPARMD_SPACE          (3 << UART_CFGR_TPARMD_BIT)
#define UART_CFGR_TSCEN_DS              (0 << UART_CFGR_TSCEN_BIT)
#define UART_CFGR_TSCEN_EN              (1 << UART_CFGR_TSCEN_BIT)
#define UART_CFGR_TIRDAEN_DS            (0 << UART_CFGR_TIRDAEN_BIT)
#define UART_CFGR_TIRDAEN_EN            (1 << UART_CFGR_TIRDAEN_BIT)
#define UART_CFGR_TINVEN_DS             (0 << UART_CFGR_TINVEN_BIT)
#define UART_CFGR_TINVEN_EN             (1 << UART_CFGR_TINVEN_BIT)

/* reg */
#define UART_MODE_DBGMD_MASK            0x00010000
#define UART_MODE_LBMD_MASK             0x000C0000
#define UART_MODE_DUPLEXMD_MASK         0x08000000
#define UART_MODE_ITSEN_MASK            0x40000000

#define UART_MODE_DBGMD_BIT             16 /* DBGMD<16>: UART Debug Mode.                    */
#define UART_MODE_LBMD_BIT              18 /* LBMD<19:18>: Loop Back Mode.                   */
#define UART_MODE_DUPLEXMD_BIT          27 /* DUPLEXMD<27>: Duplex Mode.                     */
#define UART_MODE_ITSEN_BIT             30 /* ITSEN<30>: Idle TX Tristate Enable.            */

#define UART_MODE_DBGMD_RUN             (0 << UART_MODE_DBGMD_BIT)
#define UART_MODE_DBGMD_HALT            (1 << UART_MODE_DBGMD_BIT)
#define UART_MODE_LBMD_DS               (0 << UART_MODE_LBMD_BIT)
#define UART_MODE_LBMD_RX_ONLY          (1 << UART_MODE_LBMD_BIT)
#define UART_MODE_LBMD_TX_ONLY          (2 << UART_MODE_LBMD_BIT)
#define UART_MODE_LBMD_BOTH             (3 << UART_MODE_LBMD_BIT)
#define UART_MODE_DUPLEXMD_FULL_DUPLEX  (0 << UART_MODE_DUPLEXMD_BIT)
#define UART_MODE_DUPLEXMD_HALF_DUPLEX  (1 << UART_MODE_DUPLEXMD_BIT)
#define UART_MODE_ITSEN_DS              (0 << UART_MODE_ITSEN_BIT)
#define UART_MODE_ITSEN_EN              (1 << UART_MODE_ITSEN_BIT)

/* reg */
#define UART_FLOWCN_RTS_MASK            0x00000001
#define UART_FLOWCN_RX_MASK             0x00000002
#define UART_FLOWCN_RTSINVEN_MASK       0x00000020
#define UART_FLOWCN_RTSTH_MASK          0x00000040
#define UART_FLOWCN_RTSEN_MASK          0x00000080
#define UART_FLOWCN_CTS_MASK            0x00010000
#define UART_FLOWCN_TX_MASK             0x00020000
#define UART_FLOWCN_CTSINVEN_MASK       0x00200000
#define UART_FLOWCN_CTSEN_MASK          0x00800000
#define UART_FLOWCN_TIRDAPW_MASK        0x30000000

#define UART_FLOWCN_RTS_BIT             0  /* RTS<0>: RTS State.                             */
#define UART_FLOWCN_RX_BIT              1  /* RX<1>: RX Pin Status.                          */
#define UART_FLOWCN_RTSINVEN_BIT        5  /* RTSINVEN<5>: RTS Invert Enable.                */
#define UART_FLOWCN_RTSTH_BIT           6  /* RTSTH<6>: RTS Threshold Control.               */
#define UART_FLOWCN_RTSEN_BIT           7  /* RTSEN<7>: RTS Enable.                          */
#define UART_FLOWCN_CTS_BIT             16 /* CTS<16>: CTS State.                            */
#define UART_FLOWCN_TX_BIT              17 /* TX<17>: TX State.                              */
#define UART_FLOWCN_CTSINVEN_BIT        21 /* CTSINVEN<21>: CTS Invert Enable.               */
#define UART_FLOWCN_CTSEN_BIT           23 /* CTSEN<23>: CTS Enable.                         */
#define UART_FLOWCN_TIRDAPW_BIT         28 /* TIRDAPW<29:28>: Transmit IrDA Pulse Width.     */

#define UART_FLOWCN_RTS_LOW             (0 << UART_FLOWCN_RTS_BIT)
#define UART_FLOWCN_RTS_HIGH            (1 << UART_FLOWCN_RTS_BIT)
#define UART_FLOWCN_RX_LOW              (0 << UART_FLOWCN_RX_BIT)
#define UART_FLOWCN_RX_HIGH             (1 << UART_FLOWCN_RX_BIT)
#define UART_FLOWCN_RTSINVEN_DS         (0 << UART_FLOWCN_RTSINVEN_BIT)
#define UART_FLOWCN_RTSINVEN_EN         (1 << UART_FLOWCN_RTSINVEN_BIT)
#define UART_FLOWCN_RTSTH_FULL          (0 << UART_FLOWCN_RTSTH_BIT)
#define UART_FLOWCN_RTSTH_ONE_BYTE_FREE (1 << UART_FLOWCN_RTSTH_BIT)
#define UART_FLOWCN_RTSEN_DS            (0 << UART_FLOWCN_RTSEN_BIT)
#define UART_FLOWCN_RTSEN_EN            (1 << UART_FLOWCN_RTSEN_BIT)
#define UART_FLOWCN_CTS_LOW             (0 << UART_FLOWCN_CTS_BIT)
#define UART_FLOWCN_CTS_HIGH            (1 << UART_FLOWCN_CTS_BIT)
#define UART_FLOWCN_TX_LOW              (0 << UART_FLOWCN_TX_BIT)
#define UART_FLOWCN_TX_HIGH             (1 << UART_FLOWCN_TX_BIT)
#define UART_FLOWCN_CTSINVEN_DS         (0 << UART_FLOWCN_CTSINVEN_BIT)
#define UART_FLOWCN_CTSINVEN_EN         (1 << UART_FLOWCN_CTSINVEN_BIT)
#define UART_FLOWCN_CTSEN_DS            (0 << UART_FLOWCN_CTSEN_BIT)
#define UART_FLOWCN_CTSEN_EN            (1 << UART_FLOWCN_CTSEN_BIT)
#define UART_FLOWCN_TIRDAPW_1_16TH      (0 << UART_FLOWCN_TIRDAPW_BIT)
#define UART_FLOWCN_TIRDAPW_1_8TH       (1 << UART_FLOWCN_TIRDAPW_BIT)
#define UART_FLOWCN_TIRDAPW_3_16TH      (2 << UART_FLOWCN_TIRDAPW_BIT)
#define UART_FLOWCN_TIRDAPW_1_4TH       (3 << UART_FLOWCN_TIRDAPW_BIT)

/* reg */
#define UART_CR_RFRMERI_MASK            0x00000001
#define UART_CR_RPARERI_MASK            0x00000002
#define UART_CR_ROREI_MASK              0x00000004
#define UART_CR_RDREQI_MASK             0x00000008
#define UART_CR_RERIEN_MASK             0x00000020
#define UART_CR_RDREQIEN_MASK           0x00000040
#define UART_CR_MATMD_MASK              0x00000300
#define UART_CR_RABDEN_MASK             0x00000400
#define UART_CR_RBUSYF_MASK             0x00000800
#define UART_CR_RBIT_MASK               0x00001000
#define UART_CR_ROSEN_MASK              0x00002000
#define UART_CR_RINH_MASK               0x00004000
#define UART_CR_REN_MASK                0x00008000
#define UART_CR_TSCERI_MASK             0x00010000
#define UART_CR_TDREQI_MASK             0x00040000
#define UART_CR_TCPTI_MASK              0x00080000
#define UART_CR_TCPTTH_MASK             0x00100000
#define UART_CR_TERIEN_MASK             0x00200000
#define UART_CR_TDREQIEN_MASK           0x00400000
#define UART_CR_TCPTIEN_MASK            0x00800000
#define UART_CR_TBUSYF_MASK             0x08000000
#define UART_CR_TBIT_MASK               0x10000000
#define UART_CR_TINH_MASK               0x40000000
#define UART_CR_TEN_MASK                0x80000000

#define UART_CR_RFRMERI_BIT             0  /* RFRMERI<0>: Receive Frame Error Interrupt Flag. */
#define UART_CR_RPARERI_BIT             1  /* RPARERI<1>: Receive Parity Error Interrupt Flag. */
#define UART_CR_ROREI_BIT               2  /* ROREI<2>: Receive Overrun Error Interrupt Flag. */
#define UART_CR_RDREQI_BIT              3  /* RDREQI<3>: Receive Data Request Interrupt Flag. */
#define UART_CR_RERIEN_BIT              5  /* RERIEN<5>: Receive Error Interrupt Enable.     */
#define UART_CR_RDREQIEN_BIT            6  /* RDREQIEN<6>: Receive Data Request Interrupt Enable. */
#define UART_CR_MATMD_BIT               8  /* MATMD<9:8>: Match Mode.                        */
#define UART_CR_RABDEN_BIT              10 /* RABDEN<10>: Receiver Auto-Baud Enable.         */
#define UART_CR_RBUSYF_BIT              11 /* RBUSYF<11>: Receiver Busy Flag.                */
#define UART_CR_RBIT_BIT                12 /* RBIT<12>: Last Receive Bit.                    */
#define UART_CR_ROSEN_BIT               13 /* ROSEN<13>: Receiver One-Shot Enable.           */
#define UART_CR_RINH_BIT                14 /* RINH<14>: Receiver Inhibit.                    */
#define UART_CR_REN_BIT                 15 /* REN<15>: Receiver Enable.                      */
#define UART_CR_TSCERI_BIT              16 /* TSCERI<16>: Smartcard Parity Error Interrupt Flag. */
#define UART_CR_TDREQI_BIT              18 /* TDREQI<18>: Transmit Data Request Interrupt Flag. */
#define UART_CR_TCPTI_BIT               19 /* TCPTI<19>: Transmit Complete Interrupt Flag.   */
#define UART_CR_TCPTTH_BIT              20 /* TCPTTH<20>: Transmit Complete Threshold.       */
#define UART_CR_TERIEN_BIT              21 /* TERIEN<21>: Transmit Error Interrupt Enable.   */
#define UART_CR_TDREQIEN_BIT            22 /* TDREQIEN<22>: Transmit Data Request Interrupt Enable. */
#define UART_CR_TCPTIEN_BIT             23 /* TCPTIEN<23>: Transmit Complete Interrupt Enable. */
#define UART_CR_TBUSYF_BIT              27 /* TBUSYF<27>: Transmitter Busy Flag.             */
#define UART_CR_TBIT_BIT                28 /* TBIT<28>: Last Transmit Bit.                   */
#define UART_CR_TINH_BIT                30 /* TINH<30>: Transmit Inhibit.                    */
#define UART_CR_TEN_BIT                 31 /* TEN<31>: Transmitter Enable.                   */

#define UART_CR_RFRMERI_NOT_SET         (0 << UART_CR_RFRMERI_BIT)
#define UART_CR_RFRMERI_SET             (1 << UART_CR_RFRMERI_BIT)
#define UART_CR_RPARERI_NOT_SET         (0 << UART_CR_RPARERI_BIT)
#define UART_CR_RPARERI_SET             (1 << UART_CR_RPARERI_BIT)
#define UART_CR_ROREI_NOT_SET           (0 << UART_CR_ROREI_BIT)
#define UART_CR_ROREI_SET               (1 << UART_CR_ROREI_BIT)
#define UART_CR_RDREQI_NOT_SET          (0 << UART_CR_RDREQI_BIT)
#define UART_CR_RDREQI_SET              (1 << UART_CR_RDREQI_BIT)
#define UART_CR_RERIEN_DS               (0 << UART_CR_RERIEN_BIT)
#define UART_CR_RERIEN_EN               (1 << UART_CR_RERIEN_BIT)
#define UART_CR_RDREQIEN_DS             (0 << UART_CR_RDREQIEN_BIT)
#define UART_CR_RDREQIEN_EN             (1 << UART_CR_RDREQIEN_BIT)
#define UART_CR_MATMD_OFF               (0 << UART_CR_MATMD_BIT)
#define UART_CR_MATMD_MCE               (1 << UART_CR_MATMD_BIT)
#define UART_CR_MATMD_FRAME             (2 << UART_CR_MATMD_BIT)
#define UART_CR_MATMD_STORE             (3 << UART_CR_MATMD_BIT)
#define UART_CR_RABDEN_DS               (0 << UART_CR_RABDEN_BIT)
#define UART_CR_RABDEN_EN               (1 << UART_CR_RABDEN_BIT)
#define UART_CR_RBUSYF_NOT_SET          (0 << UART_CR_RBUSYF_BIT)
#define UART_CR_RBUSYF_SET              (1 << UART_CR_RBUSYF_BIT)
#define UART_CR_RBIT_NOT_SET            (0 << UART_CR_RBIT_BIT)
#define UART_CR_RBIT_SET                (1 << UART_CR_RBIT_BIT)
#define UART_CR_ROSEN_DS                (0 << UART_CR_ROSEN_BIT)
#define UART_CR_ROSEN_EN                (1 << UART_CR_ROSEN_BIT)
#define UART_CR_RINH_INACTV             (0 << UART_CR_RINH_BIT)
#define UART_CR_RINH_ACTV               (1 << UART_CR_RINH_BIT)
#define UART_CR_REN_DS                  (0 << UART_CR_REN_BIT)
#define UART_CR_REN_EN                  (1 << UART_CR_REN_BIT)
#define UART_CR_TSCERI_NOT_SET          (0 << UART_CR_TSCERI_BIT)
#define UART_CR_TSCERI_SET              (1 << UART_CR_TSCERI_BIT)
#define UART_CR_TDREQI_NOT_SET          (0 << UART_CR_TDREQI_BIT)
#define UART_CR_TDREQI_SET              (1 << UART_CR_TDREQI_BIT)
#define UART_CR_TCPTI_NOT_SET           (0 << UART_CR_TCPTI_BIT)
#define UART_CR_TCPTI_SET               (1 << UART_CR_TCPTI_BIT)
#define UART_CR_TCPTTH_SET_ON_TX        (0 << UART_CR_TCPTTH_BIT)
#define UART_CR_TCPTTH_SET_ON_EMPTY     (1 << UART_CR_TCPTTH_BIT)
#define UART_CR_TERIEN_DS               (0 << UART_CR_TERIEN_BIT)
#define UART_CR_TERIEN_EN               (1 << UART_CR_TERIEN_BIT)
#define UART_CR_TDREQIEN_DS             (0 << UART_CR_TDREQIEN_BIT)
#define UART_CR_TDREQIEN_EN             (1 << UART_CR_TDREQIEN_BIT)
#define UART_CR_TCPTIEN_DS              (0 << UART_CR_TCPTIEN_BIT)
#define UART_CR_TCPTIEN_EN              (1 << UART_CR_TCPTIEN_BIT)
#define UART_CR_TBUSYF_NOT_SET          (0 << UART_CR_TBUSYF_BIT)
#define UART_CR_TBUSYF_SET              (1 << UART_CR_TBUSYF_BIT)
#define UART_CR_TBIT_NOT_SET            (0 << UART_CR_TBIT_BIT)
#define UART_CR_TBIT_SET                (1 << UART_CR_TBIT_BIT)
#define UART_CR_TINH_INACTV             (0 << UART_CR_TINH_BIT)
#define UART_CR_TINH_ACTV               (1 << UART_CR_TINH_BIT)
#define UART_CR_TEN_DS                  (0U << UART_CR_TEN_BIT)
#define UART_CR_TEN_EN                  (1U << UART_CR_TEN_BIT)

/* reg */
#define UART_IPDELAY_MASK               0x00FF0000

#define UART_IPDELAY_BIT                16 /* IPDELAY<23:16>: Inter-Packet Delay.            */

/* reg */
#define UART_BAUDRATE_RBAUD_MASK        0x0000FFFF
#define UART_BAUDRATE_TBAUD_MASK        0xFFFF0000

#define UART_BAUDRATE_RBAUD_BIT         0  /* RBAUD<15:0>: Receiver Baud Rate Control.       */
#define UART_BAUDRATE_TBAUD_BIT         16 /* TBAUD<31:16>: Transmitter Baud Rate Control.   */

/* reg */
#define UART_FIFOCN_RCNT_MASK           0x00000007
#define UART_FIFOCN_RFTH_MASK           0x00000030
#define UART_FIFOCN_RFIFOFL_MASK        0x00000100
#define UART_FIFOCN_RFERI_MASK          0x00000200
#define UART_FIFOCN_RSRFULLF_MASK       0x00000400
#define UART_FIFOCN_TCNT_MASK           0x00070000
#define UART_FIFOCN_TFTH_MASK           0x00300000
#define UART_FIFOCN_TFIFOFL_MASK        0x01000000
#define UART_FIFOCN_TFERI_MASK          0x02000000
#define UART_FIFOCN_TSRFULLF_MASK       0x04000000

#define UART_FIFOCN_RCNT_BIT            0  /* RCNT<2:0>: Receive FIFO Count.                 */
#define UART_FIFOCN_RFTH_BIT            4  /* RFTH<5:4>: Receive FIFO Threshold.             */
#define UART_FIFOCN_RFIFOFL_BIT         8  /* RFIFOFL<8>: Receive FIFO Flush.                */
#define UART_FIFOCN_RFERI_BIT           9  /* RFERI<9>: Receive FIFO Error Interrupt Flag.   */
#define UART_FIFOCN_RSRFULLF_BIT        10 /* RSRFULLF<10>: Receive Shift Register Full .    */
#define UART_FIFOCN_TCNT_BIT            16 /* TCNT<18:16>: Transmit FIFO Count.              */
#define UART_FIFOCN_TFTH_BIT            20 /* TFTH<21:20>: Transmit FIFO Threshold.          */
#define UART_FIFOCN_TFIFOFL_BIT         24 /* TFIFOFL<24>: Transmit FIFO Flush.              */
#define UART_FIFOCN_TFERI_BIT           25 /* TFERI<25>: Transmit FIFO Error Interrupt Flag. */
#define UART_FIFOCN_TSRFULLF_BIT        26 /* TSRFULLF<26>: Transmit Shift Register Full Flag. */

#define UART_FIFOCN_RFTH_ONE            (0 << UART_FIFOCN_RFTH_BIT)
#define UART_FIFOCN_RFTH_TWO            (1 << UART_FIFOCN_RFTH_BIT)
#define UART_FIFOCN_RFTH_FOUR           (2 << UART_FIFOCN_RFTH_BIT)
#define UART_FIFOCN_RFIFOFL_SET         (1 << UART_FIFOCN_RFIFOFL_BIT)
#define UART_FIFOCN_RFERI_NOT_SET       (0 << UART_FIFOCN_RFERI_BIT)
#define UART_FIFOCN_RFERI_SET           (1 << UART_FIFOCN_RFERI_BIT)
#define UART_FIFOCN_RSRFULLF_NOT_SET    (0 << UART_FIFOCN_RSRFULLF_BIT)
#define UART_FIFOCN_RSRFULLF_SET        (1 << UART_FIFOCN_RSRFULLF_BIT)
#define UART_FIFOCN_TFTH_ONE            (0 << UART_FIFOCN_TFTH_BIT)
#define UART_FIFOCN_TFTH_TWO            (1 << UART_FIFOCN_TFTH_BIT)
#define UART_FIFOCN_TFTH_FOUR           (2 << UART_FIFOCN_TFTH_BIT)
#define UART_FIFOCN_TFIFOFL_SET         (1 << UART_FIFOCN_TFIFOFL_BIT)
#define UART_FIFOCN_TFERI_NOT_SET       (0 << UART_FIFOCN_TFERI_BIT)
#define UART_FIFOCN_TFERI_SET           (1 << UART_FIFOCN_TFERI_BIT)
#define UART_FIFOCN_TSRFULLF_NOT_SET    (0 << UART_FIFOCN_TSRFULLF_BIT)
#define UART_FIFOCN_TSRFULLF_SET        (1 << UART_FIFOCN_TSRFULLF_BIT)

/* reg */
#define UART_DATA_MASK                  0xFFFFFFFF

#define UART_DATA_BIT                   0  /* DATA<31:0>: FIFO Data.                         */

#define REG_CAST_BYTE(n) (((volatile uint8 *)&(n))[0])

#ifdef __cplusplus
}
#endif

#endif
