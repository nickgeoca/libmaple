/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
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
 * @file   wirish/boards/maple/include/board/board.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Maple board header.
 */

#ifndef _BOARD_MAPLE_H_
#define _BOARD_MAPLE_H_

/* Pin aliases: these give the GPIO port/bit for each pin as an
 * enum. These are optional, but recommended. They make it easier to
 * write code using low-level GPIO functionality. */
enum {
    PD5, PD4, PD7, PD6, PC9, PD8, PD9, PC10, PD10,
    PD11,PD3, PD2, PD1, PD0, PA0, PA1, PA2, PA3,
    PA4, PA5, PA6, PA7, PA13, PA14, PA15, PB0, PB2,
    PE5, PE4, PE3, PE2, PE1, PE0, PC0, PC1, PC2,
    PC3, PC4, PC5, PC6, PC7, PC8, PC11, PC12, PC13,
    PC14,PA8, PA11, PB1, PB3, PB4, PB5, PB6, PB7,
    PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15, PA12
};

/* Set of all possible pin names; not all boards have all these (note
 * that we use the Dx convention since all of the Maple's pins are
 * "digital" pins (e.g. can be used with digitalRead() and
 * digitalWrite()), but not all of them are connected to ADCs. */
enum {
    D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10,
    D11, D12, D13, D14, D15, D16, D17, D18, D19,
    D20, D21, D22, D23, D24, D25, D26, D30, D31,
    D32, D33, D34, D35, D36, D37, D38, D39, D40,
    D41, D42, D45, D46, D49, D50, D51, D52, A0,
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11,
    A12, A13, A14, A15, AREF
};

/* System clock options:
 * 1) 2.5 MHz
 * 2) 20 MHz
 * 3) 23-80MHz
 */
#define CYCLES_PER_MICROSECOND  80
#define RTC_XTAL_HZ             32768


/* Pin number for the built-in button. */
#define BOARD_BUTTON_PIN        0

/* Pin number for the built-in LED. */
#define BOARD_LED_PIN           D13

/* Number of USARTs/UARTs whose pins are broken out to headers. */
#define BOARD_NR_USARTS         4

/* USART pin numbers. */
#define BOARD_USART1_TX_PIN     PB12
#define BOARD_USART1_RX_PIN     PB13
#define BOARD_USART2_TX_PIN     PD4
#define BOARD_USART2_RX_PIN     PD5
#define BOARD_USART3_TX_PIN     PA0
#define BOARD_USART3_RX_PIN     PA1
#define BOARD_USART4_TX_PIN     PA6
#define BOARD_USART4_RX_PIN     PA7

/* Number of SPI ports broken out to headers. */
#define BOARD_NR_SPI            2

/* SPI pin numbers. */
#define BOARD_SPI1_NSS_PIN      PA5
#define BOARD_SPI1_MOSI_PIN     PA4
#define BOARD_SPI1_MISO_PIN     PA3
#define BOARD_SPI1_SCK_PIN      PA2
#define BOARD_SPI2_NSS_PIN      PC9
#define BOARD_SPI2_MOSI_PIN     PC8
#define BOARD_SPI2_MISO_PIN     PC7
#define BOARD_SPI2_SCK_PIN      PC6

/* Total number of GPIO pins that are broken out to headers and
 * intended for use. This includes pins like the LED, button, and
 * debug port (JTAG/SWD) pins. */
#define BOARD_NR_GPIO_PINS      63

/* Number of pins capable of PWM output. */
#define BOARD_NR_PWM_PINS       12

/* Number of pins capable of ADC conversion. */
#define BOARD_NR_ADC_PINS       11

/* Number of pins already connected to external hardware.  For Maple,
 * these are just BOARD_LED_PIN, BOARD_BUTTON_PIN, and the debug port
 * pins (see below). */
#define BOARD_NR_USED_PINS       0

#endif
