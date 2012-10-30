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

/* Changing a shorted pin to unshorted
 *   1) Comment out "#define PIN_Dx_SHORTED and change the sequence order
 *   2) Change BOARD_NR_SHORTED_PINS
 *   3) Add pin to both enums
 */
#define PIN_D30_SHORTED 0
#define PIN_D31_SHORTED 1
#define PIN_D32_SHORTED 2
#define PIN_D33_SHORTED 3
#define PIN_D34_SHORTED 4
#define PIN_D35_SHORTED 5
#define BOARD_NR_SHORTED_PINS  6

/* Pin aliases: these give the GPIO port/bit for each pin as an
 * enum. These are optional, but recommended. They make it easier to
 * write code using low-level GPIO functionality. */
enum {
    PD5, PD4, PD7, PD6, PC9, PD8, PD9, PC10, PD10,
    PD11,PD3, PD2, PD1, PD0, PA0, PA1, PA2, PA3,
    PA4, PA5, PA6, PA7, PA13, PA14, PA15, PB0, PB2,
    /* Shorted Pins */ //PE5, PE4, PE3, PE2, PE1, PE0,
    PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8,
    PC11, PC12, PC13, PC14,PA8, PA11, PB1, PB3,
    PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12,
    PB13, PB14, PB15, PA12
};

/* Board pins */
enum {
    D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10,
    D11, D12, D13, D14, D15, D16, D17, D18, D19,
    D20, D21, D22, D23, D24, D25, D26,
    /* Shorted pins */ //D30, D31, D32, D33, D34, D35,
    D36, D37, D38, D39, D40, D41, D42, D45, D46,
    D49, D50, D51, D52, A0, A1, A2, A3, A4, A5,
    A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, AREF
};

/* System clock options:
 * 1) 2.5 MHz - This speed is not well supported by the peripherals. ex: baud rate must be lowered to ~56k
 * 2) 20 MHz
 * 3) 23-80MHz
 *
 * Note: Bus speeds are configurable in boards_setup.cpp.
 *       They are configured to work as fast as possible,
 *       so modification isn't necessary.
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
#define BOARD_USART1_TX_PIN     0xFF
#define BOARD_USART1_RX_PIN     0xFF
#define BOARD_USART2_TX_PIN     D0
#define BOARD_USART2_RX_PIN     D1
#define BOARD_USART3_TX_PIN     D14
#define BOARD_USART3_RX_PIN     D15
#define BOARD_USART4_TX_PIN     D20
#define BOARD_USART4_RX_PIN     D21

/* Number of SPI ports broken out to headers. */
#define BOARD_NR_SPI            3

/* SPI pin numbers. */
#define BOARD_SPI1_NSS_PIN      D19
#define BOARD_SPI1_MOSI_PIN     D18
#define BOARD_SPI1_MISO_PIN     D17
#define BOARD_SPI1_SCK_PIN      D16
#define BOARD_SPI2_NSS_PIN      D4
#define BOARD_SPI2_MOSI_PIN     D46
#define BOARD_SPI2_MISO_PIN     D45
#define BOARD_SPI2_SCK_PIN      D42
#define BOARD_SPI3_NSS_PIN      D10
#define BOARD_SPI3_MOSI_PIN     D11
#define BOARD_SPI3_MISO_PIN     D12
#define BOARD_SPI3_SCK_PIN      D13



/* Timer pin numbers. */
#define BOARD_TIMER1C1_PIN      0xFF
#define BOARD_TIMER1C2_PIN      0xFF
#define BOARD_TIMER1C3_PIN      0xFF
#define BOARD_TIMER1C4_PIN      0xFF
#define BOARD_TIMER1C5_PIN      0xFF
#define BOARD_TIMER1C6_PIN      0xFF
#define BOARD_TIMER2C1_PIN      A1
#define BOARD_TIMER2C2_PIN      D22
#define BOARD_TIMER3C1_PIN      D23
#define BOARD_TIMER3C2_PIN      D24
#define BOARD_TIMER4CX_PIN      A8
#define BOARD_TIMER4EX_PIN      A9
#define BOARD_TIMER5CX_PIN      A10
#define BOARD_TIMER5EX_PIN      A11

/* I2C pin numbers */
#define BOARD_I2C1_SDA_PIN      0xFF
#define BOARD_I2C1_SCL_PIN      0xFF
#define BOARD_I2C2_SDA_PIN      0xFF
#define BOARD_I2C2_SCL_PIN      0xFF

/* I2S pin numbers */
#define BOARD_I2S1TX_WS_PIN      0xFF
#define BOARD_I2S1TX_SCK_PIN     0xFF
#define BOARD_I2S1TX_SD_PIN      0xFF
#define BOARD_I2S1RX_WS_PIN      0xFF
#define BOARD_I2S1RX_SCK_PIN     0xFF
#define BOARD_I2S1RX_SD_PIN      0xFF

/* AHB (divided by 16) out pin number */
#define BOARD_AHB_OUT_PIN      0xFF


/* Total number of GPIO pins that are broken out to headers and
 * intended for use. This includes pins like the LED, button, and
 * debug port (JTAG/SWD) pins. */
#define BOARD_NR_GPIO_PINS      (63 - BOARD_NR_SHORTED_PINS)

/* Number of pins capable of PWM output. */
#define BOARD_NR_PWM_PINS       12

/* Number of pins capable of ADC conversion. */
#define BOARD_NR_ADC_PINS       11

/* Number of pins already connected to external hardware.  For Maple,
 * these are just BOARD_LED_PIN, BOARD_BUTTON_PIN, and the debug port
 * pins (see below). */
#define BOARD_NR_USED_PINS       0


#endif
