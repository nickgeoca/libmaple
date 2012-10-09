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
    PMAP_ROW(GPIOA,  13,   NULL,  0,  NULL,  ADCx,   0), /* D22/PA13                                               */
    PMAP_ROW(GPIOA,  14,   NULL,  0,  NULL,  ADCx,   0), /* D23/PA14                                               */
    PMAP_ROW(GPIOA,  15,   NULL,  0,  NULL,  ADCx,  12), /* D24/PA15                                               */
    PMAP_ROW(GPIOB,   0,   NULL,  0,  NULL,  ADCx,   0), /* D25/PB0                                                */
    PMAP_ROW(GPIOB,   2,   NULL,  0,  NULL,  ADCx,   0), /* D26/PB2                                                */
    PMAP_ROW(GPIOE,   5, TIMER1,  6,  NULL,  ADCx,   0), /* D30/PE5    PWM           EPCA_CEX5  D3                 */
    PMAP_ROW(GPIOE,   4, TIMER1,  5,  NULL,  ADCx,   0), /* D31/PE4    PWM           EPCA_CEX4  D5                 */
    PMAP_ROW(GPIOE,   3, TIMER1,  4,  NULL,  ADCx,   0), /* D32/PE3    PWM           EPCA_CEX3  D6                 */
    PMAP_ROW(GPIOE,   2, TIMER1,  3,  NULL,  ADCx,   0), /* D33/PE2    PWM           EPCA_CEX2  D9                 */
    PMAP_ROW(GPIOE,   1, TIMER1,  2,  NULL,  ADCx,   0), /* D34/PE1    PWM           EPCA_CEX1  D10                */
    PMAP_ROW(GPIOE,   0, TIMER1,  1,  NULL,  ADCx,   0), /* D35/PE0    PWM           EPCA_CEX0  D11                */
    PMAP_ROW(GPIOC,   0,   NULL,  0,  ADC2,     2,   1), /* D36/PC0                                                */
    PMAP_ROW(GPIOC,   1,   NULL,  1,  ADC2,     1,   2), /* D37/PC1                                                */
    PMAP_ROW(GPIOC,   2,   NULL,  2,  ADC2,     0,   3), /* D38/PC2                                                */
    PMAP_ROW(GPIOC,   3,   NULL,  0,  NULL,  ADCx,   4), /* D39/PC3                                                */
    PMAP_ROW(GPIOC,   4,   NULL,  0,  NULL,  ADCx,   5), /* D40/PC4                                                */
    PMAP_ROW(GPIOC,   5,   NULL,  0,  NULL,  ADCx,   6), /* D41/PC5                                                */
    PMAP_ROW(GPIOC,   6,   NULL,  0,  NULL,  ADCx,   7), /* D42/PC6                                                */
    PMAP_ROW(GPIOC,   7,   NULL,  0,  NULL,  ADCx,   8), /* D45/PC7                                                */
    PMAP_ROW(GPIOC,   8,   NULL,  0,  NULL,  ADCx,   0), /* D46/PC8                                                */
    PMAP_ROW(GPIOC,  11,   NULL,  0,  NULL,  ADCx,   0), /* D49/PC11                                               */
    PMAP_ROW(GPIOC,  12,   NULL,  0,  NULL,  ADCx,   0), /* D50/PC12                                               */
    PMAP_ROW(GPIOC,  13,   NULL,  0,  NULL,  ADCx,   0), /* D51/PC13                                               */
    PMAP_ROW(GPIOC,  14,   NULL,  0,  NULL,  ADCx,   0), /* D52/PC14                                               */

    PMAP_ROW(GPIOA,   8,   NULL,  0,  ADC1,     7,   0), /* A0/PA8     ADC0          ADC0.7                        */
    PMAP_ROW(GPIOA,  11,   NULL,  0,  ADC1,     9,   0), /* A1/PA11    ADC1          ADC0.9                        */
    PMAP_ROW(GPIOB,   1,   NULL,  0,  ADC1,    11,   0), /* A2/PB1     ADC2          ADC0.11                       */
    PMAP_ROW(GPIOB,   3,   NULL,  0,  ADC1,    12,   0), /* A3/PB3     ADC3          ADC0.12                       */
    PMAP_ROW(GPIOB,   4,   NULL,  0,  ADC1,    13,   0), /* A4/PB4     ADC4/SDA      ADC0.13            I2C0_SDA   */
    PMAP_ROW(GPIOB,   5,   NULL,  0,  ADC1,    14,   0), /* A5/PB5     ADC5/SCL      ADC0.14            I2C0_SCL   */
    PMAP_ROW(GPIOB,   6,   NULL,  0,  ADC1,    15,   0), /* A6/PB6     ADC6          ADC0.15                       */
    PMAP_ROW(GPIOB,   7,   NULL,  0,  ADC2,    11,   0), /* A7/PB7     ADC7          ADC1.11                       */
    PMAP_ROW(GPIOB,   8,   NULL,  0,  ADC2,    10,   0), /* A8/PB8     ADC8          ADC1.10            TIMER0_CT  */
    PMAP_ROW(GPIOB,   9,   NULL,  0,  ADC2,     9,   0), /* A9/PB9     ADC9          ADC1.9             TIMER0_EX  */
    PMAP_ROW(GPIOB,  10,   NULL,  0,  ADC2,     8,   0), /* A10/PB10   ADC10         ADC1.8             TIMER1_CT  */
    PMAP_ROW(GPIOB,  11,   NULL,  0,  ADC2,     7,   0), /* A11/PB11   ADC11         ADC1.7             TIMER0_EX  */
    PMAP_ROW(GPIOB,  12,   NULL,  0,  ADC2,     6,   0), /* A12/PB12   ADC12         ADC1.6             UART0_TX   */
    PMAP_ROW(GPIOB,  13,   NULL,  0,  ADC2,     5,   0), /* A13/PB13   ADC13         ADC1.5             UART0_RX   */
    PMAP_ROW(GPIOB,  14,   NULL,  0,  ADC2,     4,   0), /* A14/PB14   ADC14         ADC1.4                        */
    PMAP_ROW(GPIOB,  15,   NULL,  0,  ADC2,     3,   0), /* A15/PB15   ADC15         ADC1.3                        */
    PMAP_ROW(GPIOA,  12,   NULL,  0,  NULL,  ADCx,   0), /* AREF/PA12  AREF          VREF                          */
};

// Array of pins you can use for pwmWrite(). Keep it in Flash because
// it doesn't change, and so we don't waste RAM.
extern const uint8 boardPWMPins[] __FLASH__ = {
    D30, D31, D32, D33, D34, D35
};

// Array of pins you can use for analogRead().
extern const uint8 boardADCPins[] __FLASH__ = {
    A0, A1, A2, A3, A4, A5, A7, A8, A11, A12, A13, A14, A15
};

// Array of pins that the board uses for something special. Other than
// the button and the LED, it's usually best to leave these pins alone
// unless you know what you're doing.
extern const uint8 boardUsedPins[] __FLASH__ = {

};









