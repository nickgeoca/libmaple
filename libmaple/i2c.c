/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * @file libmaple/i2c.c
 * @author Perry Hung <perry@leaflabs.com>
 * @brief Inter-Integrated Circuit (I2C) support.
 *
 * Currently, only master mode is supported.
 */

#include "i2c_private.h"

#include <libmaple/libmaple.h>
#include <libmaple/rcc.h>
#include <libmaple/gpio.h>
#include <libmaple/nvic.h>
#include <libmaple/i2c.h>
#include <libmaple/systick.h>

#include <string.h>

static inline int32 wait_for_state_change(i2c_dev *dev,
                                          i2c_state state,
                                          uint32 timeout);
static void set_ccr_trise(i2c_dev *dev, uint32 flags);

/**
 * @brief Fill data register with slave address
 * @param dev I2C device
 * @param addr Slave address
 * @param rw Read/write bit
 */
static inline void i2c_send_slave_addr(i2c_dev *dev, uint32 addr, uint32 rw) {

}

/*
 * Simple debugging trail. Define I2C_DEBUG to turn on.
 */
#ifdef I2C_DEBUG

#define NR_CRUMBS       128
static struct crumb crumbs[NR_CRUMBS];
static uint32 cur_crumb = 0;

static inline void i2c_drop_crumb(uint32 event, uint32 arg0, uint32 arg1) {

}
#define I2C_CRUMB(event, arg0, arg1) i2c_drop_crumb(event, arg0, arg1)

#else
#define I2C_CRUMB(event, arg0, arg1)
#endif

struct crumb {
    uint32 event;
    uint32 arg0;
    uint32 arg1;
};

enum {
    IRQ_ENTRY           = 1,
    TXE_ONLY            = 2,
    TXE_BTF             = 3,
    STOP_SENT           = 4,
    TEST                = 5,
    RX_ADDR_START       = 6,
    RX_ADDR_STOP        = 7,
    RXNE_ONLY           = 8,
    RXNE_SENDING        = 9,
    RXNE_START_SENT     = 10,
    RXNE_STOP_SENT      = 11,
    RXNE_DONE           = 12,
    ERROR_ENTRY         = 13,
};

/**
 * @brief Reset an I2C bus.
 *
 * Reset is accomplished by clocking out pulses until any hung slaves
 * release SDA and SCL, then generating a START condition, then a STOP
 * condition.
 *
 * @param dev I2C device
 */
void i2c_bus_reset(const i2c_dev *dev) {

}

/**
 * @brief Initialize an I2C device and reset its registers to their
 *        default values.
 * @param dev Device to initialize.
 */
void i2c_init(i2c_dev *dev) {

}

/* Hack for deprecated bit of STM32F1 functionality */
#ifndef _I2C_HAVE_DEPRECATED_I2C_REMAP
#define _i2c_handle_remap(dev, flags) ((void)0)
#endif

/**
 * @brief Initialize an I2C device as bus master
 * @param dev Device to enable
 * @param flags Bitwise or of the following I2C options:
 *              I2C_FAST_MODE: 400 khz operation,
 *              I2C_DUTY_16_9: 16/9 Tlow/Thigh duty cycle (only applicable for
 *                             fast mode),
 *              I2C_BUS_RESET: Reset the bus and clock out any hung slaves on
 *                             initialization,
 *              I2C_10BIT_ADDRESSING: Enable 10-bit addressing,
 *              I2C_REMAP: (deprecated, STM32F1 only) Remap I2C1 to SCL/PB8
 *                         SDA/PB9.
 */
void i2c_master_enable(i2c_dev *dev, uint32 flags) {

}

/**
 * @brief Process an i2c transaction.
 *
 * Transactions are composed of one or more i2c_msg's, and may be read
 * or write tranfers.  Multiple i2c_msg's will generate a repeated
 * start in between messages.
 *
 * @param dev I2C device
 * @param msgs Messages to send/receive
 * @param num Number of messages to send/receive
 * @param timeout Bus idle timeout in milliseconds before aborting the
 *                transfer.  0 denotes no timeout.
 * @return 0 on success,
 *         I2C_ERROR_PROTOCOL if there was a protocol error,
 *         I2C_ERROR_TIMEOUT if the transfer timed out.
 */
int32 i2c_master_xfer(i2c_dev *dev,
                      i2c_msg *msgs,
                      uint16 num,
                      uint32 timeout) {
    return 0;
}

/**
 * @brief Wait for an I2C event, or time out in case of error.
 * @param dev I2C device
 * @param state I2C_state state to wait for
 * @param timeout Timeout, in milliseconds
 * @return 0 if target state is reached, a negative value on error.
 */
static inline int32 wait_for_state_change(i2c_dev *dev,
                                          i2c_state state,
                                          uint32 timeout) {
    return 0;
}

/*
 * Private API
 */

/*
 * IRQ handler for I2C master. Handles transmission/reception.
 */
void _i2c_irq_handler(i2c_dev *dev) {
    return;
}

/*
 * Interrupt handler for I2C error conditions. Aborts any pending I2C
 * transactions.
 */
void _i2c_irq_error_handler(i2c_dev *dev) {

}

/*
 * CCR/TRISE configuration helper
 */
static void set_ccr_trise(i2c_dev *dev, uint32 flags) {

}
