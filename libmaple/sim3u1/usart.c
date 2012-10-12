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
 * @file libmaple/stm32f2/usart.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief STM32F2 USART.
 */

#include <libmaple/usart.h>
#include <libmaple/gpio.h>
#include "usart_private.h"

/*
 * Devices
 */

static ring_buffer usart1_rb;
static usart_dev usart1 = {
    .regs     = USART1_BASE,
    .rb       = &usart1_rb,
    .max_baud = 4500000UL,
    .clk_id   = CLK_UART1,
    .irq_num  = NVIC_UART1,
};
/** USART1 device */
usart_dev *USART1 = &usart1;

static ring_buffer usart2_rb;
static usart_dev usart2 = {
    .regs     = USART2_BASE,
    .rb       = &usart2_rb,
    .max_baud = 4500000UL,
    .clk_id   = CLK_UART2,
    .irq_num  = NVIC_UART2,
};
/** USART2 device */
usart_dev *USART2 = &usart2;

static ring_buffer usart3_rb;
static usart_dev usart3 = {
    .regs     = USART3_BASE,
    .rb       = &usart3_rb,
    .max_baud = 4500000UL,
    .clk_id   = CLK_USART1,
    .irq_num  = NVIC_USART1,
};
/** USART3 device */
usart_dev *USART3 = &usart3;

static ring_buffer usart4_rb;
static usart_dev usart4 = {
    .regs     = USART4_BASE,
    .rb       = &usart4_rb,
    .max_baud = 4500000UL,
    .clk_id   = CLK_USART2,
    .irq_num  = NVIC_USART2,
};
/** USART4 device */
usart_dev *USART4 = &usart4;

/*
 * Routines
 */

void usart_config_gpios_async(usart_dev *udev,
                              gpio_dev *rx_dev, uint8 rx,
                              gpio_dev *tx_dev, uint8 tx,
                              unsigned flags) {
    gpio_set_mode(rx_dev, rx, GPIO_DIGITAL_INPUT_PULLUP);
    gpio_set_mode(tx_dev, tx, GPIO_DIGITAL_PP);
}

void usart_set_baud_rate(usart_dev *dev, uint32 clock_speed, uint32 baud) {
    uint32 tmp;

    /* Figure out the clock speed, if the user doesn't give one. */
    if (clock_speed == 0) {
        clock_speed = clk_get_bus_freq(dev->clk_id);
    }
    ASSERT(clock_speed);
    // Full duplex mode
    REG_WRITE_SET_CLR(dev->regs->MODE, 0, 0x08000000);
    /* Convert desired baud rate to baud rate register setting. */
    tmp = clock_speed / (2 * baud) - 1;
    dev->regs->BAUDRATE = tmp | (tmp << 16);
}

/**
 * @brief Call a function on each USART.
 * @param fn Function to call.
 */
void usart_foreach(void (*fn)(usart_dev*)) {
    fn(USART1);
}

/**
 * @brief Get GPIO alternate function mode for a USART.
 * @param dev USART whose gpio_af to get.
 * @return gpio_af corresponding to dev.
 */
gpio_af usart_get_af(usart_dev *dev) {
    return (gpio_af)0; // TODO [silabs]: finish usart get alternate-fnct
}

/*
 * Interrupt handlers.
 */

void __irq_uart1(void) {
    usart_irq(&usart1_rb, USART1_BASE);
}
void __irq_uart2(void) {
    usart_irq(&usart2_rb, USART2_BASE);
}
void __irq_usart1(void) {
    usart_irq(&usart3_rb, USART3_BASE);
}
void __irq_usart2(void) {
    usart_irq(&usart4_rb, USART4_BASE);
}

/**
 * @brief Initialize a serial port.
 * @param dev         Serial port to be initialized
 */
void usart_init(usart_dev *dev) {
    usart_reg_map *regs = dev->regs;
    rb_init(dev->rb, USART_RX_BUF_SIZE, dev->rx_buf);

    nvic_clr_pending_irq(dev->irq_num);
    nvic_irq_enable(dev->irq_num);

    // 8-bit, 1stop, no-parity

    // tx configuration
    REG_WRITE_SET_CLR(regs->CONFIG, 0,
            UART_CFGR_TDATLN_MASK | UART_CFGR_TPAREN_MASK | UART_CFGR_TSTPMD_MASK | UART_CFGR_TINVEN_MASK);
    REG_WRITE_SET_CLR(regs->CONFIG, 1,
            UART_CFGR_TDATLN_8_BITS | UART_CFGR_TSTRTEN_EN | UART_CFGR_TSTPEN_EN | (1 << UART_CFGR_TSTPMD_BIT));

    // rx configuration
    REG_WRITE_SET_CLR(regs->CONFIG, 0,
            UART_CFGR_RDATLN_MASK | UART_CFGR_RSTPMD_MASK | UART_CFGR_RINVEN_MASK);
    REG_WRITE_SET_CLR(regs->CONFIG, 1,
            UART_CFGR_RDATLN_8_BITS | UART_CFGR_RSTRTEN_EN | UART_CFGR_RSTPEN_EN | (1 << UART_CFGR_RSTPMD_BIT));

    // Interrupt when a single byte is in rx buffer
    REG_WRITE_SET_CLR(regs->FIFOCN, 0 , 0x00000030);
}

/**
 * @brief Enable a serial port.
 *
 * USART is enabled in single buffer transmission mode, multibuffer
 * receiver mode, 8n1.
 *
 * Serial port must have a baud rate configured to work properly.
 *
 * @param dev Serial port to enable.
 * @see usart_set_baud_rate()
 */
typedef enum SI32_UART_STOP_BITS_Enum
{
   SI32_UART_A_STOP_BITS_0P5_BIT  = 0,
   SI32_UART_A_STOP_BITS_1_BIT    = 1,
   SI32_UART_A_STOP_BITS_1P5_BITS = 2,
   SI32_UART_A_STOP_BITS_2_BITS   = 3
} SI32_UART_A_STOP_BITS_Enum_Type;

void usart_enable(usart_dev *dev) {;
    usart_reg_map *regs = dev->regs;

    clk_enable_dev(dev->clk_id);

    // Enable tx/rx
    REG_WRITE_SET_CLR(regs->CONTROL, 1 , UART_CR_REN_EN | UART_CR_TEN_EN);

    // Enable Interupts
    REG_WRITE_SET_CLR(regs->CONTROL, 1, UART_CR_RDREQIEN_EN);

}

/**
 * @brief Turn off a serial port.
 * @param dev Serial port to be disabled
 */
void usart_disable(usart_dev *dev) {
    usart_reg_map *regs = dev->regs;

    // DISABLE INTERRUPTS
    REG_WRITE_SET_CLR(regs->CONTROL, 0, UART_CR_RDREQIEN_EN);
    nvic_clr_pending_irq(dev->irq_num);

    // DISABLE UART0 CLOCK
    clk_disable_dev(dev->clk_id);

    /* Clean up buffer */
    usart_reset_rx(dev);
}

/**
 * @brief Nonblocking USART transmit
 * @param dev Serial port to transmit over
 * @param buf Buffer to transmit
 * @param len Maximum number of bytes to transmit
 * @return Number of bytes transmitted
 */
uint32 usart_tx(usart_dev *dev, const uint8 *buf, uint32 len) {
    usart_reg_map *regs = dev->regs;
    uint32 txed = 0;

    while (((regs->FIFOCN >> 16) & 7) < 4 && (txed < len)) {
        REG_CAST_BYTE(regs->DATA) = buf[txed++];
    }
    return txed;
}

/**
 * @brief Nonblocking USART receive.
 * @param dev Serial port to receive bytes from
 * @param buf Buffer to store received bytes into
 * @param len Maximum number of bytes to store
 * @return Number of bytes received
 */
uint32 usart_rx(usart_dev *dev, uint8 *buf, uint32 len) {
    uint32 rxed = 0;

    while (usart_data_available(dev) && rxed < len) {
        *buf++ = usart_getc(dev);
        rxed++;
    }
    return rxed;
}

/**
 * @brief Transmit an unsigned integer to the specified serial port in
 *        decimal format.
 *
 * This function blocks until the integer's digits have been
 * completely transmitted.
 *
 * @param dev Serial port to send on
 * @param val Number to print
 */
void usart_putudec(usart_dev *dev, uint32 val) {
    char digits[12];

    int i = 0;
    do {
        digits[i++] = val % 10 + '0';
        val /= 10;
    } while (val > 0);

    while (--i >= 0) {
        usart_putc(dev, digits[i]);
    }
}
