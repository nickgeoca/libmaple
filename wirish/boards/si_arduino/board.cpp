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
 * @file   wirish/boards/maple/board.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Maple board file.
 */

#include <board/board.h>         // For this board's header file

#include <wirish/wirish_types.h> // For stm32_pin_info and its contents
                                 // (these go into PIN_MAP).

#include "boards_private.h"      // For PMAP_ROW(), which makes
                                 // PIN_MAP easier to read.

// boardInit(): nothing special to do for Maple.
//
// When defining your own board.cpp, you can put extra code in this
// function if you have anything you want done on reset, before main()
// or setup() are called.
//
// If there's nothing special you need done, feel free to leave this
// function out, as we do here.

void boardInit(void) {

}

<<<<<<< HEAD



=======
>>>>>>> remotes/NG_Repo/silabs
#define PIN_ROW_D30_NOT_SHORTED PMAP_ROW(GPIOE,   5, TIMER1,  6,  NULL,  ADCx,   0),
#define PIN_ROW_D30_SHORTED
#if defined(PIN_D30_SHORTED)
#define PIN_ROW_D30_SHORTED PIN_ROW_D30_NOT_SHORTED
#define PIN_ROW_D30_NOT_SHORTED
#define D30 D3
#endif

#define PIN_ROW_D31_NOT_SHORTED PMAP_ROW(GPIOE,   4, TIMER1,  5,  NULL,  ADCx,   0),
#define PIN_ROW_D31_SHORTED
#if defined(PIN_D31_SHORTED)
#define PIN_ROW_D31_SHORTED PIN_ROW_D30_NOT_SHORTED
#define PIN_ROW_D31_NOT_SHORTED
#define D31 D5
#endif

#define PIN_ROW_D32_NOT_SHORTED PMAP_ROW(GPIOE,   3, TIMER1,  4,  NULL,  ADCx,   0),
#define PIN_ROW_D32_SHORTED
#if defined(PIN_D32_SHORTED)
#define PIN_ROW_D32_SHORTED PIN_ROW_D30_NOT_SHORTED
#define PIN_ROW_D32_NOT_SHORTED
#define D32 D6
#endif

#define PIN_ROW_D33_NOT_SHORTED PMAP_ROW(GPIOE,   2, TIMER1,  3,  NULL,  ADCx,   0),
#define PIN_ROW_D33_SHORTED
#if defined(PIN_D33_SHORTED)
#define PIN_ROW_D33_SHORTED PIN_ROW_D30_NOT_SHORTED
#define PIN_ROW_D33_NOT_SHORTED
#define D33 D9
#endif

#define PIN_ROW_D34_NOT_SHORTED PMAP_ROW(GPIOE,   1, TIMER1,  2,  NULL,  ADCx,   0),
#define PIN_ROW_D34_SHORTED
#if defined(PIN_D34_SHORTED)
#define PIN_ROW_D34_SHORTED PIN_ROW_D30_NOT_SHORTED
#define PIN_ROW_D34_NOT_SHORTED
#define D34 D10
#endif

#define PIN_ROW_D35_NOT_SHORTED PMAP_ROW(GPIOE,   0, TIMER1,  1,  NULL,  ADCx,   0),
#define PIN_ROW_D35_SHORTED
#if defined(PIN_D35_SHORTED)
#define PIN_ROW_D35_SHORTED PIN_ROW_D30_NOT_SHORTED
#define PIN_ROW_D35_NOT_SHORTED
#define D35 D11
#endif



<<<<<<< HEAD
=======


>>>>>>> remotes/NG_Repo/silabs
// Pin map: this lets the basic I/O functions (digitalWrite(),
// analogRead(), pwmWrite()) translate from pin numbers to STM32
// peripherals.
//
// PMAP_ROW() lets us specify a row (really a struct stm32_pin_info)
// in the pin map. Its arguments are:
//
// - GPIO:    Port Bank (PB) and PB pin number
// - Timer:   Timer device and timer channel, Null/0 if none
// - ADC:     ADC device and ADC channel, Null/ADCx if none
// - EXTI:    External Interrupt (EXTI) trigger number, 0 if none
//
// Sections:
//      1) Digital
//      2) Analog
// Comments:
//      Function: Arduino compatible function (non compatible ones not listed).
//      Periph:  Default SiM3U1 peripheral used.
//      Shorted:
//      Alternate: Supported alternate SiM3U1 peripheral.
extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {
    /*       GPIO     -    Timer  -   ADC    -    EXTI      Pin        Function      Periph     Shorted Alternate */

    PMAP_ROW(GPIOD,   5,   NULL,  0,  NULL,  ADCx,  11), /* D0/PD5     UART_RX       UART1_RX           I2C0_SCL   */
    PMAP_ROW(GPIOD,   4,   NULL,  0,  NULL,  ADCx,  10), /* D1/PD4     UART_TX       UART1_TX           I2C0_SDA   */
    PMAP_ROW(GPIOD,   7,   NULL,  0,  NULL,  ADCx,  13), /* D2/PD7     EXT_INT       INT0.12            I2S_RS_SCK */
    PMAP_ROW(GPIOD,   6,   NULL,  0,  NULL,  ADCx,  12), /* D3/PD6     EXT_INT(PWM)  INT0.11    D30     I2S_RX_WS  */
    PMAP_ROW(GPIOC,   9,   NULL,  0,  NULL,  ADCx,   0), /* D4/PC9                   SPI1_NSS                      */
    PMAP_ROW(GPIOD,   8,   NULL,  0,  NULL,  ADCx,  14), /* D5/PD8     (PWM)                    D31                */
    PMAP_ROW(GPIOD,   9,   NULL,  0,  NULL,  ADCx,  15), /* D6/PD9     (PWM)                    D32                */
    PMAP_ROW(GPIOC,  10,   NULL,  0,  NULL,  ADCx,  16), /* D7/PC10                                                */
    PMAP_ROW(GPIOD,  10,   NULL,  0,  NULL,  ADCx,   0), /* D8/PD10                  I2C1_SDA                      */
    PMAP_ROW(GPIOD,  11,   NULL,  0,  NULL,  ADCx,   0), /* D9/PD11    (PWM)                    D33                */
    PMAP_ROW(GPIOD,   3,   NULL,  0,  NULL,  ADCx,   0), /* D10/PD3    SPI_SS(PWM)   SPI2_NSS   D34                */
    PMAP_ROW(GPIOD,   2,   NULL,  0,  NULL,  ADCx,   0), /* D11/PD2    SPI_MOSI(PWM) SPI2_MOSI  D35                */
    PMAP_ROW(GPIOD,   1,   NULL,  0,  NULL,  ADCx,   0), /* D12/PD1    SPI_MISO      SPI2_MISO                     */
    PMAP_ROW(GPIOD,   0,   NULL,  0,  NULL,  ADCx,   0), /* D13/PD0    SPI_SCK/LED   SPI2_SCK                      */
    PMAP_ROW(GPIOA,   0,   NULL,  0,  ADC1,     0,   0), /* D14/PA0    UART_TX       USART0_TX          ADC0.0     */
    PMAP_ROW(GPIOA,   1,   NULL,  0,  ADC1,     1,   0), /* D15/PA1    UART_RX       USART0_RX          ADC0.1     */
    PMAP_ROW(GPIOA,   2,   NULL,  0,  ADC1,     2,   0), /* D16/PA2    UART_TX       SPI0_SCK           ADC0.2     */
    PMAP_ROW(GPIOA,   3,   NULL,  0,  ADC1,     3,   0), /* D17/PA3    UART_RX       SPI0_MISO          ADC0.3     */
    PMAP_ROW(GPIOA,   4,   NULL,  0,  ADC1,     4,   0), /* D18/PA4    UART_TX       SPI0_MOSI          ADC0.4     */
    PMAP_ROW(GPIOA,   5,   NULL,  0,  ADC1,     5,   0), /* D19/PA5    UART_RX       SPI0_NSS           ADC0.5     */
    PMAP_ROW(GPIOA,   6,   NULL,  0,  NULL,  ADCx,   0), /* D20/PA6    I2C_SDA       USART1_TX                     */
    PMAP_ROW(GPIOA,   7,   NULL,  0,  ADC1,     6,   0), /* D21/PA7    I2C_SCL       USART1_RX          ADC0.6     */
    PMAP_ROW(GPIOA,  13, TIMER2,  2,  NULL,  ADCx,   0), /* D22/PA13                 PCA0_CEX1                     */
    PMAP_ROW(GPIOA,  14, TIMER3,  1,  NULL,  ADCx,   0), /* D23/PA14                 PCA1_CEX0                     */
    PMAP_ROW(GPIOA,  15, TIMER3,  2,  NULL,  ADCx,  12), /* D24/PA15                 PCA1_CEX1                     */
    PMAP_ROW(GPIOB,   0,   NULL,  0,  NULL,  ADCx,   0), /* D25/PB0                                                */
    PMAP_ROW(GPIOB,   2,   NULL,  0,  NULL,  ADCx,   0), /* D26/PB2                                                */
    PIN_ROW_D30_NOT_SHORTED                              /* D30/PE5    PWM           EPCA_CEX5  D3                 */
    PIN_ROW_D31_NOT_SHORTED                              /* D31/PE4    PWM           EPCA_CEX4  D5                 */
    PIN_ROW_D32_NOT_SHORTED                              /* D32/PE3    PWM           EPCA_CEX3  D6                 */
    PIN_ROW_D33_NOT_SHORTED                              /* D33/PE2    PWM           EPCA_CEX2  D9                 */
    PIN_ROW_D34_NOT_SHORTED                              /* D34/PE1    PWM           EPCA_CEX1  D10                */
    PIN_ROW_D35_NOT_SHORTED                              /* D35/PE0    PWM           EPCA_CEX0  D11                */
    PMAP_ROW(GPIOC,   0,   NULL,  0,  ADC2,     2,   1), /* D36/PC0                                                */
    PMAP_ROW(GPIOC,   1,   NULL,  0,  ADC2,     1,   2), /* D37/PC1                                                */
    PMAP_ROW(GPIOC,   2,   NULL,  0,  ADC2,     0,   3), /* D38/PC2                                                */
    PMAP_ROW(GPIOC,   3,   NULL,  0,  NULL,  ADCx,   4), /* D39/PC3                                                */
    PMAP_ROW(GPIOC,   4,   NULL,  0,  NULL,  ADCx,   5), /* D40/PC4                                                */
    PMAP_ROW(GPIOC,   5,   NULL,  0,  NULL,  ADCx,   6), /* D41/PC5                                                */
    PMAP_ROW(GPIOC,   6,   NULL,  0,  NULL,  ADCx,   7), /* D42/PC6    SPI_SCK      SPI1_SCK                       */
    PMAP_ROW(GPIOC,   7,   NULL,  0,  NULL,  ADCx,   8), /* D45/PC7    SPI_MISO     SPI1_MISO                      */
    PMAP_ROW(GPIOC,   8,   NULL,  0,  NULL,  ADCx,   0), /* D46/PC8    SPI_MOSI     SPI1_MOSI                      */
    PMAP_ROW(GPIOC,  11,   NULL,  0,  NULL,  ADCx,   0), /* D49/PC11                                               */
    PMAP_ROW(GPIOC,  12,   NULL,  0,  NULL,  ADCx,   0), /* D50/PC12                                               */
    PMAP_ROW(GPIOC,  13,   NULL,  0,  NULL,  ADCx,   0), /* D51/PC13                                               */
    PMAP_ROW(GPIOC,  14,   NULL,  0,  NULL,  ADCx,   0), /* D52/PC14                                               */

    PMAP_ROW(GPIOA,   8,   NULL,  0,  ADC1,     7,   0), /* A0/PA8     ADC0          ADC0.7                        */
    PMAP_ROW(GPIOA,  11, TIMER2,  1,  ADC1,     9,   0), /* A1/PA11    ADC1          ADC0.9             PCA0_CEX0  */
    PMAP_ROW(GPIOB,   1,   NULL,  0,  ADC1,    11,   0), /* A2/PB1     ADC2          ADC0.11                       */
    PMAP_ROW(GPIOB,   3,   NULL,  0,  ADC1,    12,   0), /* A3/PB3     ADC3          ADC0.12                       */
    PMAP_ROW(GPIOB,   4,   NULL,  0,  ADC1,    13,   0), /* A4/PB4     ADC4/SDA      ADC0.13            I2C0_SDA   */
    PMAP_ROW(GPIOB,   5,   NULL,  0,  ADC1,    14,   0), /* A5/PB5     ADC5/SCL      ADC0.14            I2C0_SCL   */
    PMAP_ROW(GPIOB,   6,   NULL,  0,  ADC1,    15,   0), /* A6/PB6     ADC6          ADC0.15                       */
    PMAP_ROW(GPIOB,   7,   NULL,  0,  ADC2,    11,   0), /* A7/PB7     ADC7          ADC1.11                       */
    PMAP_ROW(GPIOB,   8, TIMER4,  1,  ADC2,    10,   0), /* A8/PB8     ADC8          ADC1.10            TIMER0_CT  */
    PMAP_ROW(GPIOB,   9, TIMER4,  2,  ADC2,     9,   0), /* A9/PB9     ADC9          ADC1.9             TIMER0_EX  */
    PMAP_ROW(GPIOB,  10, TIMER5,  1,  ADC2,     8,   0), /* A10/PB10   ADC10         ADC1.8             TIMER1_CT  */
    PMAP_ROW(GPIOB,  11, TIMER5,  2,  ADC2,     7,   0), /* A11/PB11   ADC11         ADC1.7             TIMER1_EX  */
    PMAP_ROW(GPIOB,  12,   NULL,  0,  ADC2,     6,   0), /* A12/PB12   ADC12         ADC1.6             UART0_TX   */
    PMAP_ROW(GPIOB,  13,   NULL,  0,  ADC2,     5,   0), /* A13/PB13   ADC13         ADC1.5             UART0_RX   */
    PMAP_ROW(GPIOB,  14,   NULL,  0,  ADC2,     4,   0), /* A14/PB14   ADC14         ADC1.4                        */
    PMAP_ROW(GPIOB,  15,   NULL,  0,  ADC2,     3,   0), /* A15/PB15   ADC15         ADC1.3                        */
    PMAP_ROW(GPIOA,  12,   NULL,  0,  NULL,  ADCx,   0), /* AREF/PA12  AREF          VREF                          */
};

// Array of pins you can use for pwmWrite(). Keep it in Flash because
// it doesn't change, and so we don't waste RAM.
extern const uint8 boardPWMPins[] __FLASH__ = {
    D30, D31, D32, D33, D34, D35, A1, D22, D23, D24, A9, A11
};

// Array of pins you can use for analogRead().
extern const uint8 boardADCPins[] __FLASH__ = {
    A0, A2, A3, A4, A5, A6, A7, A12, A13, A14, A15
};

// Array of pins that the board uses for something special. Other than
// the button and the LED, it's usually best to leave these pins alone
// unless you know what you're doing.
extern const uint8 boardUsedPins[] __FLASH__ = {

};

<<<<<<< HEAD
#define PIN_TO_PB_MASK(pin)                                 (pin == 0xff ? 0 : PIN_MAP[pin].gpio_device == GPIOA || PIN_MAP[pin].gpio_device == GPIOC ? \
                                                                (uint32)1 << PIN_MAP[pin].gpio_bit : (uint32)1 << (PIN_MAP[pin].gpio_bit + 16))
#define PIN_TO_PB_MASK2(pin1, pin2)                         (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK(pin2))
#define PIN_TO_PB_MASK3(pin1, pin2, pin3)                   (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK2(pin2, pin3))
#define PIN_TO_PB_MASK4(pin1, pin2, pin3, pin4)             (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK3(pin2, pin3, pin4))
#define PIN_TO_PB_MASK5(pin1, pin2, pin3, pin4, pin5)       (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK4(pin2, pin3, pin4, pin5))
#define PIN_TO_PB_MASK6(pin1, pin2, pin3, pin4, pin5, pin6) (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK5(pin2, pin3, pin4, pin5, pin6))
#define XBAR_NUM(pin, xlow_offset) (pin == 0xff ? XBAR_NUM_NULL : pin == 0xfe ? XBAR_NUM_GPIOE : \
                        PIN_MAP[pin].gpio_device == GPIOC || PIN_MAP[pin].gpio_device == GPIOD ? XBAR_NUM_1 : \
                                xlow_offset + XBAR_NUM_0L)
#define XBAR_ROW(array, xbar_num) {(sizeof(array) / sizeof(si_xbar_info)), xbar_num, (si_xbar_info *) &array}
static const si_xbar_info xbar_usart1[] = {XBAR_UART0_ROW(PIN_TO_PB_MASK2(BOARD_USART1_TX_PIN, BOARD_USART1_RX_PIN), XBAR_NUM(BOARD_USART1_TX_PIN, 1))};
static const si_xbar_info xbar_usart2[] = {XBAR_UART1_ROW(PIN_TO_PB_MASK2(BOARD_USART2_TX_PIN, BOARD_USART2_RX_PIN), XBAR_NUM(BOARD_USART2_TX_PIN, 1))};
static const si_xbar_info xbar_usart3[] = {XBAR_USART0_ROW(PIN_TO_PB_MASK2(BOARD_USART3_TX_PIN, BOARD_USART3_RX_PIN), XBAR_NUM(BOARD_USART3_TX_PIN, 0))};
static const si_xbar_info xbar_usart4[] = {XBAR_USART1_ROW(PIN_TO_PB_MASK2(BOARD_USART4_TX_PIN, BOARD_USART4_RX_PIN), XBAR_NUM(BOARD_USART4_TX_PIN, 0))};
static const si_xbar_info xbar_spi1[] = {XBAR_SPI0_ROW(PIN_TO_PB_MASK3(BOARD_SPI1_SCK_PIN, BOARD_SPI1_MISO_PIN, BOARD_SPI1_MOSI_PIN), XBAR_NUM(BOARD_SPI1_MISO_PIN, 0)),
                                        XBAR_SPI0NSS_ROW(PIN_TO_PB_MASK(BOARD_SPI1_NSS_PIN), XBAR_NUM(BOARD_SPI1_NSS_PIN, 0))};
static const si_xbar_info xbar_spi2[] = {XBAR_SPI1_ROW(PIN_TO_PB_MASK3(BOARD_SPI2_SCK_PIN, BOARD_SPI2_MISO_PIN, BOARD_SPI2_MOSI_PIN), XBAR_NUM(BOARD_SPI2_MISO_PIN, 1)),
                                        XBAR_SPI1NSS_ROW(PIN_TO_PB_MASK(BOARD_SPI2_NSS_PIN), XBAR_NUM(BOARD_SPI2_NSS_PIN, 1))};
static const si_xbar_info xbar_spi3[] = {XBAR_SPI2_ROW(PIN_TO_PB_MASK3(BOARD_SPI3_SCK_PIN, BOARD_SPI3_MISO_PIN, BOARD_SPI3_MOSI_PIN), XBAR_NUM(BOARD_SPI3_MISO_PIN, 1)),
                                        XBAR_SPI2NSS_ROW(PIN_TO_PB_MASK(BOARD_SPI3_NSS_PIN), XBAR_NUM(BOARD_SPI3_NSS_PIN, 1))};
static const si_xbar_info xbar_timer1[] = {XBAR_EPCA0_ROW(PIN_TO_PB_MASK6(BOARD_TIMER1C1_PIN, BOARD_TIMER1C2_PIN, BOARD_TIMER1C3_PIN, BOARD_TIMER1C4_PIN, BOARD_TIMER1C5_PIN, BOARD_TIMER1C6_PIN), XBAR_NUM(BOARD_USART1_TX_PIN, 0))};
static const si_xbar_info xbar_timer2[] = {XBAR_PCA0_ROW(PIN_TO_PB_MASK2(BOARD_TIMER2C1_PIN, BOARD_TIMER2C2_PIN), XBAR_NUM(BOARD_TIMER2C1_PIN, 0))};
static const si_xbar_info xbar_timer3[] = {XBAR_PCA1_ROW(PIN_TO_PB_MASK2(BOARD_TIMER3C1_PIN, BOARD_TIMER3C2_PIN), XBAR_NUM(BOARD_TIMER3C1_PIN, 0))};
static const si_xbar_info xbar_timer4[] = {XBAR_TIMER0CT_ROW(PIN_TO_PB_MASK(BOARD_TIMER4CX_PIN), XBAR_NUM(BOARD_TIMER4CX_PIN, 0)),
                                            XBAR_TIMER0EX_ROW(PIN_TO_PB_MASK(BOARD_TIMER4EX_PIN), XBAR_NUM(BOARD_TIMER4EX_PIN, 0))};
static const si_xbar_info xbar_timer5[] = {XBAR_TIMER1CT_ROW(PIN_TO_PB_MASK(BOARD_TIMER5CX_PIN), XBAR_NUM(BOARD_TIMER5CX_PIN, 0)),
                                            XBAR_TIMER1EX_ROW(PIN_TO_PB_MASK(BOARD_TIMER5EX_PIN), XBAR_NUM(BOARD_TIMER5EX_PIN, 0))};
static const si_xbar_info xbar_i2s1[] = {XBAR_I2S0TX_ROW(PIN_TO_PB_MASK3(BOARD_I2S1TX_WS_PIN, BOARD_I2S1TX_SCK_PIN, BOARD_I2S1TX_SD_PIN), XBAR_NUM(BOARD_I2S1TX_WS_PIN, 0)),
                                         XBAR_I2S0RX_ROW(PIN_TO_PB_MASK3(BOARD_I2S1RX_WS_PIN, BOARD_I2S1RX_SCK_PIN, BOARD_I2S1RX_SD_PIN), XBAR_NUM(BOARD_I2S1RX_WS_PIN, 0))};
static const si_xbar_info xbar_i2c1[] = {XBAR_I2C0_ROW(PIN_TO_PB_MASK2(BOARD_I2C1_SDA_PIN, BOARD_I2C1_SCL_PIN), XBAR_NUM(BOARD_I2C1_SDA_PIN, 0))};
static const si_xbar_info xbar_i2c2[] = {XBAR_I2C1_ROW(PIN_TO_PB_MASK2(BOARD_I2C2_SDA_PIN, BOARD_I2C2_SCL_PIN), XBAR_NUM(BOARD_I2C2_SDA_PIN, 0))};
static const si_xbar_info xbar_ahb_out[] = {XBAR_AHB_OUT_ROW(PIN_TO_PB_MASK(BOARD_AHB_OUT_PIN), XBAR_NUM(BOARD_AHB_OUT_PIN, 1))};

extern const xbar_dev_info XBAR_MAP[XBAR_NULL] = {
    // USART
    XBAR_ROW(xbar_usart1, XBAR_NUM(BOARD_USART1_TX_PIN, 1)),
    XBAR_ROW(xbar_usart2, XBAR_NUM(BOARD_USART2_TX_PIN, 1)),
    XBAR_ROW(xbar_usart3, XBAR_NUM(BOARD_USART3_TX_PIN, 0)),
    XBAR_ROW(xbar_usart4, XBAR_NUM(BOARD_USART4_TX_PIN, 0)),

    // SPI
    XBAR_ROW(xbar_spi1, XBAR_NUM(BOARD_SPI1_MISO_PIN, 0)),
    XBAR_ROW(xbar_spi2, XBAR_NUM(BOARD_SPI2_MISO_PIN, 1)),
    XBAR_ROW(xbar_spi3, XBAR_NUM(BOARD_SPI3_MISO_PIN, 1)),

    // Timers
    XBAR_ROW(xbar_timer1, XBAR_NUM(BOARD_TIMER1C1_PIN, 0)),
    XBAR_ROW(xbar_timer2, XBAR_NUM(BOARD_TIMER2C1_PIN, 0)),
    XBAR_ROW(xbar_timer3, XBAR_NUM(BOARD_TIMER3C1_PIN, 0)),
    XBAR_ROW(xbar_timer4, XBAR_NUM(BOARD_TIMER4CX_PIN, 0)),
    XBAR_ROW(xbar_timer5, XBAR_NUM(BOARD_TIMER5CX_PIN, 0)),

    // I2S
    XBAR_ROW(xbar_i2s1, XBAR_NUM(BOARD_I2S1TX_WS_PIN, 0)),

    // I2C
    XBAR_ROW(xbar_i2c1, XBAR_NUM(BOARD_I2C1_SDA_PIN, 0)),
    XBAR_ROW(xbar_i2c2, XBAR_NUM(BOARD_I2C2_SDA_PIN, 0)),

    // AHB out
    XBAR_ROW(xbar_ahb_out, XBAR_NUM(BOARD_AHB_OUT_PIN, 1)),
};

extern const stm32_pin_info PIN_MAP_SHORTS[BOARD_NR_SHORTED_PINS] = {
        PIN_ROW_D30_SHORTED
        PIN_ROW_D31_SHORTED
        PIN_ROW_D32_SHORTED
        PIN_ROW_D33_SHORTED
        PIN_ROW_D34_SHORTED
        PIN_ROW_D35_SHORTED
};

/* Return 0 if not shorted */
uint8 board_get_short_num(gpio_dev *dev, uint8 pin)
{
#if BOARD_NR_SHORTED_PINS == 0
    return 0;
#endif // BOARD_NR_SHORTED_PINS == 0
=======
extern const stm32_pin_info PIN_MAP_SHORTS[BOARD_NR_SHORTED_PINS] = {
        PIN_ROW_D30_SHORTED
        PIN_ROW_D31_SHORTED
        PIN_ROW_D32_SHORTED
        PIN_ROW_D33_SHORTED
        PIN_ROW_D34_SHORTED
        PIN_ROW_D35_SHORTED
};

/* Return 0 if not shorted */
uint8 board_get_short_num(gpio_dev *dev, uint8 pin)
{
#if BOARD_NR_SHORTED_PINS == 0
    return 0;
#endif // BOARD_NR_SHORTED_PINS == 0

    if (dev != GPIOD) {
        return 0;
    }
    switch (pin) {
#if defined(PIN_D30_SHORTED)
    case PIN_MAP[D30].gpio_bit:
        return PIN_D30_SHORTED + 1;
#endif // defined(PIN_D30_SHORTED)
#if defined(PIN_D31_SHORTED)
    case PIN_MAP[D31].gpio_bit:
        return PIN_D31_SHORTED + 1;
#endif // defined(PIN_D31_SHORTED)
#if defined(PIN_D32_SHORTED)
    case PIN_MAP[D32].gpio_bit:
        return PIN_D32_SHORTED + 1;
#endif // defined(PIN_D32_SHORTED)
#if defined(PIN_D33_SHORTED)
    case PIN_MAP[D33].gpio_bit:
        return PIN_D33_SHORTED + 1;
#endif // defined(PIN_D33_SHORTED)
#if defined(PIN_D34_SHORTED)
    case PIN_MAP[D34].gpio_bit:
        return PIN_D34_SHORTED + 1;
#endif // defined(PIN_D34_SHORTED)
#if defined(PIN_D35_SHORTED)
    case PIN_MAP[D35].gpio_bit:
        return PIN_D35_SHORTED + 1;
#endif // defined(PIN_D35_SHORTED)
    default:
        return 0;
    }
}

uint8 board_can_chng_gpio(gpio_dev *dev, uint8 pin)
{
    if (uint8 short_num = board_get_short_num(dev, pin)) {
        short_num -= 1;
        // GPIOE is used if the alt function is not GPIO. GPIOE/bit5 should have a mask of 7, but this is fine for now.
        if ((0x3 & (GPIOE->regs->hd.PBFSEL) >> (PIN_MAP_SHORTS[short_num].gpio_bit * 2)) !=
                0) {
            return 0;
        }
    }
    return 1;
}
>>>>>>> remotes/NG_Repo/silabs

    // Primary pin
    if (dev == GPIOD) {
        switch (pin) {
#if defined(PIN_D30_SHORTED)
        case 6:
            return PIN_D30_SHORTED + 1;
#endif // defined(PIN_D30_SHORTED)
#if defined(PIN_D31_SHORTED)
        case 8:
            return PIN_D31_SHORTED + 1;
#endif // defined(PIN_D31_SHORTED)
#if defined(PIN_D32_SHORTED)
        case 9:
            return PIN_D32_SHORTED + 1;
#endif // defined(PIN_D32_SHORTED)
#if defined(PIN_D33_SHORTED)
        case 11:
            return PIN_D33_SHORTED + 1;
#endif // defined(PIN_D33_SHORTED)
#if defined(PIN_D34_SHORTED)
        case 3:
            return PIN_D34_SHORTED + 1;
#endif // defined(PIN_D34_SHORTED)
#if defined(PIN_D35_SHORTED)
        case 2:
            return PIN_D35_SHORTED + 1;
#endif // defined(PIN_D35_SHORTED)
        default:
            return 0;
        }
    }

    // Secondary pin
    else if (dev == GPIOE) {
        switch (pin) {
#if defined(PIN_D30_SHORTED)
        case 0:
            return PIN_D30_SHORTED + 1;
#endif // defined(PIN_D30_SHORTED)
#if defined(PIN_D31_SHORTED)
        case 1:
            return PIN_D31_SHORTED + 1;
#endif // defined(PIN_D31_SHORTED)
#if defined(PIN_D32_SHORTED)
        case 2:
            return PIN_D32_SHORTED + 1;
#endif // defined(PIN_D32_SHORTED)
#if defined(PIN_D33_SHORTED)
        case 3:
            return PIN_D33_SHORTED + 1;
#endif // defined(PIN_D33_SHORTED)
#if defined(PIN_D34_SHORTED)
        case 4:
            return PIN_D34_SHORTED + 1;
#endif // defined(PIN_D34_SHORTED)
#if defined(PIN_D35_SHORTED)
        case 5:
            return PIN_D35_SHORTED + 1;
#endif // defined(PIN_D35_SHORTED)
        default:
            return 0;
        }
    }

    return 0;
}
