/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung (from <libmaple/i2c.h>).
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
 * @file libmaple/stm32f1/include/series/i2c.h
 * @brief STM32F1 I2C
 */

#ifndef _LIBMAPLE_SIM3U1_I2C_H_
#define _LIBMAPLE_SIM3U1_I2C_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** I2C register map type */
typedef struct i2c_reg_map {
    volatile uint32_t CR1;            /**< Control register 1 */
    volatile uint32_t CR2;            /**< Control register 2 */
    volatile uint32_t OAR1;           /**< Own address register 1 */
    volatile uint32_t OAR2;           /**< Own address register 2 */
    volatile uint32_t DR;             /**< Data register */
    volatile uint32_t SR1;            /**< Status register 1 */
    volatile uint32_t SR2;            /**< Status register 2 */
    volatile uint32_t CCR;            /**< Clock control register */
    volatile uint32_t TRISE;          /**< TRISE (rise time) register */
} i2c_reg_map;

/*
 * Register maps
 */


/** STM32F1 I2C1 register map base pointer */
#define I2C1_BASE               ((struct i2c_reg_map*)0x40005400)
#define I2C2_BASE               ((struct i2c_reg_map*)0x40005800)

/*
 * Devices
 */


/*
 * For internal use
 */
/*
 * Register bit definitions
 */

/* Control register 1 */

#define I2C_CR1_SWRST           (1U << 15)    // Software reset
#define I2C_CR1_ALERT           (1U << 13)    // SMBus alert
#define I2C_CR1_PEC             (1U << 12)    // Packet error checking
#define I2C_CR1_POS             (1U << 11)    // Acknowledge/PEC position
#define I2C_CR1_ACK             (1U << 10)    // Acknowledge enable
#define I2C_CR1_STOP            (1U << 9)     // Stop generation
#define I2C_CR1_START           (1U << 8)     // Start generation
#define I2C_CR1_NOSTRETCH       (1U << 7)     // Clock stretching disable
#define I2C_CR1_ENGC            (1U << 6)     // General call enable
#define I2C_CR1_ENPEC           (1U << 5)     // PEC enable
#define I2C_CR1_ENARP           (1U << 4)     // ARP enable
#define I2C_CR1_SMBTYPE         (1U << 3)     // SMBus type
#define I2C_CR1_SMBTYPE_DEVICE  (0U << 3)     //     SMBus type: device
#define I2C_CR1_SMBTYPE_HOST    (1U << 3)     //     SMBus type: host
#define I2C_CR1_SMBUS           (1U << 1)     // SMBus mode
#define I2C_CR1_SMBUS_I2C       (0U << 1)     //     SMBus mode: I2C
#define I2C_CR1_SMBUS_SMBUS     (1U << 1)     //     SMBus mode: SMBus
#define I2C_CR1_PE              (1U << 0)     // Peripheral Enable

/* Control register 2 */

#define I2C_CR2_LAST            (1U << 12)    // DMA last transfer
#define I2C_CR2_DMAEN           (1U << 11)    // DMA requests enable
#define I2C_CR2_ITBUFEN         (1U << 10)    // Buffer interrupt enable
#define I2C_CR2_ITEVTEN         (1U << 9)     // Event interupt enable
#define I2C_CR2_ITERREN         (1U << 8)     // Error interupt enable
#define I2C_CR2_FREQ            0x3F          // Peripheral input frequency

/* Own address register 1 */

#define I2C_OAR1_ADDMODE        (1U << 15)    // Addressing mode
#define I2C_OAR1_ADDMODE_7_BIT  (0U << 15)    //     Addressing mode: 7-bit
#define I2C_OAR1_ADDMODE_10_BIT (1U << 15)    //     Addressing mode: 10-bit
#define I2C_OAR1_ADD            0x3FF         // Interface address

/* Own address register 2 */

#define I2C_OAR2_ADD2           0xFE          // Interface address
#define I2C_OAR2_ENDUAL         1U            // Dual addressing mode enable

/* Status register 1 */

#define I2C_SR1_SMBALERT        (1U << 15)    // SMBus alert
#define I2C_SR1_TIMEOUT         (1U << 14)    // Timeout or Tlow error
#define I2C_SR1_PECERR          (1U << 12)    // PEC Error in reception
#define I2C_SR1_OVR             (1U << 11)    // Overrun/underrun
#define I2C_SR1_AF              (1U << 10)    // Acknowledge failure
#define I2C_SR1_ARLO            (1U << 9)     // Arbitration lost
#define I2C_SR1_BERR            (1U << 8)     // Bus error
#define I2C_SR1_TXE             (1U << 7)     // Data register empty
#define I2C_SR1_RXNE            (1U << 6)     // Data register not empty
#define I2C_SR1_STOPF           (1U << 4)     // Stop detection
#define I2C_SR1_ADD10           (1U << 3)     // 10-bit header sent
#define I2C_SR1_BTF             (1U << 2)     // Byte transfer finished
#define I2C_SR1_ADDR            (1U << 1)     // Address sent/matched
#define I2C_SR1_SB              (1U << 0)     // Start bit

/* Status register 2 */

#define I2C_SR2_PEC             0xFF00        // Packet error checking register
#define I2C_SR2_DUALF           (1U << 7)     // Dual flag
#define I2C_SR2_SMBHOST         (1U << 6)     // SMBus host header
#define I2C_SR2_SMBDEFAULT      (1U << 5)     // SMBus device default address
#define I2C_SR2_GENCALL         (1U << 4)     // General call address
#define I2C_SR2_TRA             (1U << 2)     // Transmitter/receiver
#define I2C_SR2_BUSY            (1U << 1)     // Bus busy
#define I2C_SR2_MSL             (1U << 0)     // Master/slave

/* Clock control register */

#define I2C_CCR_FS              (1U << 15)    // Fast mode selection
#define I2C_CCR_DUTY            (1U << 14)    // Fast mode duty cycle
#define I2C_CCR_DUTY_2_1        (0U << 14)    //     Fast mode duty: 2/1
#define I2C_CCR_DUTY_16_9       (1U << 14)    //     Fast mode duty: 16/9
#define I2C_CCR_CCR             0xFFF         // Clock control bits

#ifdef __cplusplus
}
#endif

#endif  /*_LIBMAPLE_SIM3U1_I2C_H_ */
