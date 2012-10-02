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

/* STM32F2 ISR weak declarations */

        .thumb

/* Default handler, as with STM32F1 */
        .globl __default_handler
        .type __default_handler, %function

__default_handler:
        b .

        .weak  __exc_nmi
        .globl __exc_nmi
        .set   __exc_nmi, __default_handler
        .weak  __exc_hardfault
        .globl __exc_hardfault
        .set   __exc_hardfault, __default_handler
        .weak  __exc_memmanage
        .globl __exc_memmanage
        .set   __exc_memmanage, __default_handler
        .weak  __exc_busfault
        .globl __exc_busfault
        .set   __exc_busfault, __default_handler
        .weak  __exc_usagefault
        .globl __exc_usagefault
        .set   __exc_usagefault, __default_handler
        .weak  __stm32reservedexception7
        .globl __stm32reservedexception7
        .set   __stm32reservedexception7, __default_handler
        .weak  __stm32reservedexception8
        .globl __stm32reservedexception8
        .set   __stm32reservedexception8, __default_handler
        .weak  __stm32reservedexception9
        .globl __stm32reservedexception9
        .set   __stm32reservedexception9, __default_handler
        .weak  __stm32reservedexception10
        .globl __stm32reservedexception10
        .set   __stm32reservedexception10, __default_handler
        .weak  __exc_svc
        .globl __exc_svc
        .set   __exc_svc, __default_handler
        .weak  __exc_debug_monitor
        .globl __exc_debug_monitor
        .set   __exc_debug_monitor, __default_handler
        .weak  __stm32reservedexception13
        .globl __stm32reservedexception13
        .set   __stm32reservedexception13, __default_handler
        .weak  __exc_pendsv
        .globl __exc_pendsv
        .set   __exc_pendsv, __default_handler
        .weak  __exc_systick
        .globl __exc_systick
        .set   __exc_systick, __default_handler
        .globl __irq_wwdg
        .set   __irq_wwdg, __default_handler
        .weak  __irq_wwdg
        .globl __irq_exti0
        .set   __irq_exti0, __default_handler
        .weak  __irq_exti0
        .globl __irq_exti1
        .set   __irq_exti1, __default_handler
        .weak  __irq_exti1
        .globl __irq_rtc_wkup
        .set   __irq_rtc_wkup   , __default_handler
        .weak  __irq_rtc_wkup
        .globl __irq_dma1_stream0
        .set   __irq_dma1_stream0, __default_handler
        .weak  __irq_dma1_stream0
        .globl __irq_dma1_stream1
        .set   __irq_dma1_stream1, __default_handler
        .weak  __irq_dma1_stream1
        .globl __irq_dma1_stream2
        .set   __irq_dma1_stream2, __default_handler
        .weak  __irq_dma1_stream2
        .globl __irq_dma1_stream3
        .set   __irq_dma1_stream3, __default_handler
        .weak  __irq_dma1_stream3
        .globl __irq_dma1_stream4
        .set   __irq_dma1_stream4, __default_handler
        .weak  __irq_dma1_stream4
        .globl __irq_dma1_stream5
        .set   __irq_dma1_stream5, __default_handler
        .weak  __irq_dma1_stream5
        .globl __irq_dma1_stream6
        .set   __irq_dma1_stream6, __default_handler
        .weak  __irq_dma1_stream6
        .globl __irq_dma1_stream7
        .set   __irq_dma1_stream7, __default_handler
        .weak  __irq_dma1_stream7
        .globl __irq_dma1_stream8
        .set   __irq_dma1_stream8, __default_handler
        .weak  __irq_dma1_stream8
        .globl __irq_dma1_stream9
        .set   __irq_dma1_stream9, __default_handler
        .weak  __irq_dma1_stream9
        .globl __irq_dma1_stream10
        .set   __irq_dma1_stream10, __default_handler
        .weak  __irq_dma1_stream10
        .globl __irq_dma1_stream11
        .set   __irq_dma1_stream11, __default_handler
        .weak  __irq_dma1_stream11
        .globl __irq_dma1_stream12
        .set   __irq_dma1_stream12, __default_handler
        .weak  __irq_dma1_stream12
        .globl __irq_dma1_stream13
        .set   __irq_dma1_stream13, __default_handler
        .weak  __irq_dma1_stream13
        .globl __irq_dma1_stream14
        .set   __irq_dma1_stream14, __default_handler
        .weak  __irq_dma1_stream14
        .globl __irq_dma1_stream15
        .set   __irq_dma1_stream15, __default_handler
        .weak  __irq_dma1_stream15
        .globl __irq_tim1_low
        .set   __irq_tim1_low, __default_handler
        .weak  __irq_tim1_low
        .globl __irq_tim1_high
        .set   __irq_tim1_high, __default_handler
        .weak  __irq_tim1_high
        .globl __irq_tim2_low
        .set   __irq_tim2_low, __default_handler
        .weak  __irq_tim2_low
        .globl __irq_tim2_high
        .set   __irq_tim2_high, __default_handler
        .weak  __irq_tim2_high
        .globl __irq_epca1
        .set   __irq_epca1, __default_handler
        .weak  __irq_epca1
        .globl __irq_pca1
        .set   __irq_pca1, __default_handler
        .weak  __irq_pca1
        .globl __irq_pca2
        .set   __irq_pca2, __default_handler
        .weak  __irq_pca2
        .globl __irq_usart1
        .set   __irq_usart1, __default_handler
        .weak  __irq_usart1
        .globl __irq_usart2
        .set   __irq_usart2, __default_handler
        .weak  __irq_usart2
        .globl __irq_spi1
        .set   __irq_spi1, __default_handler
        .weak  __irq_spi1
        .globl __irq_spi2
        .set   __irq_spi2, __default_handler
        .weak  __irq_spi2
        .globl __irq_spi3
        .set   __irq_spi3, __default_handler
        .weak  __irq_spi3
        .globl __irq_i2c1
        .set   __irq_i2c1, __default_handler
        .weak  __irq_i2c1
        .globl __irq_i2c2
        .set   __irq_i2c2, __default_handler
        .weak  __irq_i2c2
        .globl __irq_usb
        .set   __irq_usb, __default_handler
        .weak  __irq_usb
        .globl __irq_adc1
        .set   __irq_adc1, __default_handler
        .weak  __irq_adc1
        .globl __irq_adc2
        .set   __irq_adc2       , __default_handler
        .weak  __irq_adc2
        .globl __irq_cmp1
        .set   __irq_cmp1, __default_handler
        .weak  __irq_cmp1
        .globl __irq_cmp2
        .set   __irq_cmp2 , __default_handler
        .weak  __irq_cmp2
        .globl __irq_capsense
        .set   __irq_capsense, __default_handler
        .weak  __irq_capsense
        .globl __irq_i2s1rx
        .set   __irq_i2s1rx, __default_handler
        .weak  __irq_i2s1rx
        .globl __irq_i2s1tx
        .set   __irq_i2s1tx, __default_handler
        .weak  __irq_i2s1tx
        .globl __irq_aes
        .set   __irq_aes, __default_handler
        .weak  __irq_aes
        .globl __irq_vddlow
        .set   __irq_vddlow, __default_handler
        .weak  __irq_vddlow
        .globl __irq_rtcfail
        .set   __irq_rtcfail, __default_handler
        .weak  __irq_rtcfail
        .globl __irq_pmatch
        .set   __irq_pmatch, __default_handler
        .weak  __irq_pmatch
        .globl __irq_uart1
        .set   __irq_uart1, __default_handler
        .weak  __irq_uart1
        .globl __irq_uart2
        .set   __irq_uart2, __default_handler
        .weak  __irq_uart2
        .globl __irq_dac1
        .set   __irq_dac1, __default_handler
        .weak  __irq_dac1
        .globl __irq_dac2
        .set   __irq_dac2, __default_handler
        .weak  __irq_dac2
        .globl __irq_lptimer
        .set   __irq_lptimer, __default_handler
        .weak  __irq_lptimer
        .globl __irq_pll
        .set   __irq_pll, __default_handler
        .weak  __irq_pll
        .globl __irq_vbusinvalid
        .set   __irq_vbusinvalid, __default_handler
        .weak  __irq_vbusinvalid
        .globl __irq_vreglow
        .set   __irq_vreglow, __default_handler
        .weak  __irq_vreglow
