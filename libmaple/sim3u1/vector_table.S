/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 by Silicon Laboratories. 
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

/* SiM3U1 vector table */

        .section ".stm32.interrupt_vector"

        .globl __stm32_vector_table
        .type __stm32_vector_table, %object

__stm32_vector_table:
/* CM3 core interrupts */
        .long __msp_init
        .long __exc_reset
        .long __exc_nmi
        .long __exc_hardfault
        .long __exc_memmanage
        .long __exc_busfault
        .long __exc_usagefault
        .long __stm32reservedexception7
        .long __stm32reservedexception8
        .long __stm32reservedexception9
        .long __stm32reservedexception10
        .long __exc_svc
        .long __exc_debug_monitor
        .long __stm32reservedexception13
        .long __exc_pendsv
        .long __exc_systick
/* Peripheral interrupts */
        .long __irq_wwdg
        .long __irq_exti0
        .long __irq_exti1
        .long __irq_rtc_wkup   
        .long __irq_dma1_stream0
        .long __irq_dma1_stream1
        .long __irq_dma1_stream2
        .long __irq_dma1_stream3
        .long __irq_dma1_stream4
        .long __irq_dma1_stream5
        .long __irq_dma1_stream6
        .long __irq_dma1_stream7
        .long __irq_dma1_stream8
        .long __irq_dma1_stream9
        .long __irq_dma1_stream10
        .long __irq_dma1_stream11
        .long __irq_dma1_stream12
        .long __irq_dma1_stream13
        .long __irq_dma1_stream14
        .long __irq_dma1_stream15
        .long __irq_tim1_low
        .long __irq_tim1_high
        .long __irq_tim2_low
        .long __irq_tim2_high
        .long __irq_epca1
        .long __irq_pca1
        .long __irq_pca2
        .long __irq_usart1
        .long __irq_usart2
        .long __irq_spi1
        .long __irq_spi2
      	.long __irq_spi3
        .long __irq_i2c1
      	.long __irq_i2c2
  	    .long __irq_usb
      	.long __irq_adc1
      	.long __irq_adc2       
        .long __irq_cmp1
      	.long __irq_cmp2 
      	.long __irq_capsense
      	.long __irq_i2s1rx
      	.long __irq_i2s1tx
      	.long __irq_aes
      	.long __irq_vddlow
      	.long __irq_rtcfail
      	.long __irq_pmatch
      	.long __irq_uart1
      	.long __irq_uart2
      	.long __irq_dac1
      	.long __irq_dac2
      	.long __irq_lptimer
      	.long __irq_pll
      	.long __irq_vbusinvalid
      	.long __irq_vreglow
      	
        .size __stm32_vector_table, . - __stm32_vector_table
