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
 * @file libmaple/stm32f2/include/series/nvic.h
 * @brief STM32F2 nested vectored interrupt controller (NVIC) header.
 */

#ifndef _LIBMAPLE_SIM3U1_NVIC_H_
#define _LIBMAPLE_SIM3U1_NVIC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



/** NVIC register map type. */
typedef struct nvic_reg_map {
    volatile uint32_t ISER[8];      /**< Interrupt Set Enable Registers */
    uint32_t RESERVED0[24];
    volatile uint32_t ICER[8];      /**< Interrupt Clear Enable Registers */
    uint32_t RESERVED1[24];
    volatile uint32_t ISPR[8];      /**< Interrupt Set Pending Registers */
    uint32_t RESERVED2[24];
    volatile uint32_t ICPR[8];      /**< Interrupt Clear Pending Registers */
    uint32_t RESERVED3[24];
    volatile uint32_t IABR[8];      /**< Interrupt Active bit Registers */
    uint32_t RESERVED4[56];
    volatile uint8_t  IP[240];      /**< Interrupt Priority Registers */
    uint32_t RESERVED5[644];
    volatile uint32_t STIR;         /**< Software Trigger Interrupt Registers */
} nvic_reg_map;

/** NVIC register map base pointer. */
#define NVIC_BASE                       ((struct nvic_reg_map*)0xE000E100)


/**
 * @brief STM32F2 interrupt vector table interrupt numbers.
 */
typedef enum nvic_irq_num {
    NVIC_NMI              = -14, /**< Non-maskable interrupt */
    NVIC_HARDFAULT        = -13, /**< Hard fault (all class of fault) */
    NVIC_MEM_MANAGE       = -12, /**< Memory management */
    NVIC_BUS_FAULT        = -11, /**< Bus fault: prefetch fault, memory
                                          access fault. */
    NVIC_USAGE_FAULT      = -10, /**< Usage fault: Undefined instruction
                                          or illegal state. */
    NVIC_SVC              = -5,  /**< System service call via SWI
                                          instruction */
    NVIC_DEBUG_MON        = -4,  /**< Debug monitor */
    NVIC_PEND_SVC         = -2,  /**< Pendable request for system
                                          service */
    NVIC_SYSTICK          = -1,  /**< System tick timer */

    NVIC_WDTIMER          = 0,
    NVIC_PBEXT0           = 1,
    NVIC_PBEXT1           = 2,
    NVIC_RTC0ALRM         = 3,
    NVIC_DMACH0           = 4,
    NVIC_DMACH1           = 5,
    NVIC_DMACH2           = 6,
    NVIC_DMACH3           = 7,
    NVIC_DMACH4           = 8,
    NVIC_DMACH5           = 9,
    NVIC_DMACH6           = 10,
    NVIC_DMACH7           = 11,
    NVIC_DMACH8           = 12,
    NVIC_DMACH9           = 13,
    NVIC_DMACH10          = 14,
    NVIC_DMACH11          = 15,
    NVIC_DMACH12          = 16,
    NVIC_DMACH13          = 17,
    NVIC_DMACH14          = 18,
    NVIC_DMACH15          = 19,
    NVIC_TIMER0L          = 20,
    NVIC_TIMER0H          = 21,
    NVIC_TIMER1L          = 22,
    NVIC_TIMER1H          = 23,
    NVIC_EPCA1            = 24,
    NVIC_PCA1             = 25,
    NVIC_PCA2             = 26,
    NVIC_USART1           = 27,
    NVIC_USART2           = 28,
    NVIC_SPI1             = 29,
    NVIC_SPI2             = 30,
    NVIC_SPI3             = 31,
    NVIC_I2C1             = 32,
    NVIC_I2C2             = 33,
    NVIC_USB1             = 34,
    NVIC_SARADC1          = 35,
    NVIC_SARADC2          = 36,
    NVIC_CMP1             = 37,
    NVIC_CMP2             = 38,
    NVIC_CAPSENSE1        = 39,
    NVIC_I2S0RX           = 40,
    NVIC_I2S0TX           = 41,
    NVIC_AES1             = 42,
    NVIC_VDDLOW           = 43,
    NVIC_RTC0FAIL         = 44,
    NVIC_PMATCH           = 45,
    NVIC_UART1            = 46,
    NVIC_UART2            = 47,
    NVIC_IDAC1            = 48,
    NVIC_IDAC2            = 49,
    NVIC_LPTIMER1         = 50,
    NVIC_PLL1             = 51,
    NVIC_VBUSINVALID      = 52,
    NVIC_VREG0LOW         = 53,
    NVIC_NUM_OF_PERIPHERALS_
} nvic_irq_num;

#ifdef __cplusplus
}
#endif

#endif
