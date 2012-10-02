/******************************************************************************
 * The MIT License
 *
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
 * @file libmaple/include/libmaple/usart.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>,
 *         Perry Hung <perry@leaflabs.com>
 * @brief USART definitions and prototypes
 */

#ifndef _LIBMAPLE_USART_H_
#define _LIBMAPLE_USART_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple_types.h>
#include <libmaple/util.h>
#include <libmaple/rcc.h>
#include <libmaple/nvic.h>
#include <libmaple/ring_buffer.h>
#include <series/usart.h>


/*
 * Register bit definitions
 */

/* Status register */


#ifndef USART_RX_BUF_SIZE
#define USART_RX_BUF_SIZE               64
#endif
/*
 * Devices
 */

void usart_init(usart_dev *dev);

struct gpio_dev;                /* forward declaration */
/* FIXME [PRE 0.0.13] decide if flags are necessary */
/**
 * @brief Configure GPIOs for use as USART TX/RX.
 * @param udev USART device to use
 * @param rx_dev RX pin gpio_dev
 * @param rx     RX pin bit on rx_dev
 * @param tx_dev TX pin gpio_dev
 * @param tx     TX pin bit on tx_dev
 * @param flags  Currently ignored
 */
extern void usart_config_gpios_async(usart_dev *udev,
                                     struct gpio_dev *rx_dev, uint8 rx,
                                     struct gpio_dev *tx_dev, uint8 tx,
                                     unsigned flags);

#define USART_USE_PCLK 0
void usart_set_baud_rate(usart_dev *dev, uint32 clock_speed, uint32 baud);

void usart_enable(usart_dev *dev);
void usart_disable(usart_dev *dev);
void usart_foreach(void (*fn)(usart_dev *dev));
uint32 usart_tx(usart_dev *dev, const uint8 *buf, uint32 len);
uint32 usart_rx(usart_dev *dev, uint8 *buf, uint32 len);
void usart_putudec(usart_dev *dev, uint32 val);

/**
 * @brief Disable all serial ports.
 */
static inline void usart_disable_all(void) {
    usart_foreach(usart_disable);
}

/**
 * @brief Transmit one character on a serial port.
 *
 * This function blocks until the character has been successfully
 * transmitted.
 *
 * @param dev Serial port to send on.
 * @param byte Byte to transmit.
 */
static inline void usart_putc(usart_dev* dev, uint8 byte) {
    while (!usart_tx(dev, &byte, 1))
        ;
}

/**
 * @brief Transmit a character string on a serial port.
 *
 * This function blocks until str is completely transmitted.
 *
 * @param dev Serial port to send on
 * @param str String to send
 */
static inline void usart_putstr(usart_dev *dev, const char* str) {
    uint32 i = 0;
    while (str[i] != '\0') {
        usart_putc(dev, str[i++]);
    }
}

/**
 * @brief Read one character from a serial port.
 *
 * It's not safe to call this function if the serial port has no data
 * available.
 *
 * @param dev Serial port to read from
 * @return byte read
 * @see usart_data_available()
 */
static inline uint8 usart_getc(usart_dev *dev) {
    return rb_remove(dev->rb);
}

/**
 * @brief Return the amount of data available in a serial port's RX buffer.
 * @param dev Serial port to check
 * @return Number of bytes in dev's RX buffer.
 */
static inline uint32 usart_data_available(usart_dev *dev) {
    return rb_full_count(dev->rb);
}

/**
 * @brief Discard the contents of a serial port's RX buffer.
 * @param dev Serial port whose buffer to empty.
 */
static inline void usart_reset_rx(usart_dev *dev) {
    rb_reset(dev->rb);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
