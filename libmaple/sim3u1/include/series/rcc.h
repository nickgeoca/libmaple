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
 * @file libmaple/stm32f2/include/series/rcc.h
 * @brief STM32F2 reset and clock control (RCC) support.
 */

#ifndef _LIBMAPLE_STM32F2_RCC_H_
#define _LIBMAPLE_STM32F2_RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple_types.h>

/*
 * Register map
 */

typedef struct clk_reg_map
{
   __io uint32 CONTROL; // Base Address + 0x0
   uint32      reserved0;
   uint32      reserved1;
   uint32      reserved2;
   __io uint32 AHBCLKG; // Base Address + 0x10
   __io uint32 AHBCLKG_SET;
   __io uint32 AHBCLKG_CLR;
   uint32      reserved3;
   __io uint32 APBCLKG0; // Base Address + 0x20
   __io uint32 APBCLKG0_SET;
   __io uint32 APBCLKG0_CLR;
   uint32      reserved4;
   __io uint32 APBCLKG1; // Base Address + 0x30
   __io uint32 APBCLKG1_SET;
   __io uint32 APBCLKG1_CLR;
   uint32      reserved5;
   __io uint32 PM3CN; // Base Address + 0x40
   uint32      reserved6;
   uint32      reserved7;
   uint32      reserved8;
} clk_reg_map;

#define CLK_BASE  ((clk_reg_map*)0x4002D000)

/*
 * Clock sources, domains, and peripheral clock IDs.
 */

#if 0
/**
 * @brief STM32F2 clock sources.
 */
typedef enum rcc_clk {
    RCC_CLK_PLLI2S = (uint16)((offsetof(struct rcc_reg_map, CR) << 8) |
                              RCC_CR_PLLI2SON_BIT), /**< Dedicated PLL
                                                       for I2S. */
    RCC_CLK_PLL    = (uint16)((offsetof(struct rcc_reg_map, CR) << 8) |
                              RCC_CR_PLLON_BIT), /**< Main PLL, clocked by
                                                    HSI or HSE. */
    RCC_CLK_HSE    = (uint16)((offsetof(struct rcc_reg_map, CR) << 8) |
                              RCC_CR_HSEON_BIT), /**< High speed external. */
    RCC_CLK_HSI    = (uint16)((offsetof(struct rcc_reg_map, CR) << 8) |
                              RCC_CR_HSION_BIT), /**< High speed internal. */
    RCC_CLK_LSE    = (uint16)((offsetof(struct rcc_reg_map, BDCR) << 8) |
                              RCC_BDCR_LSEON_BIT), /**< Low-speed external
                                                    * (32.768 KHz). */
    RCC_CLK_LSI    = (uint16)((offsetof(struct rcc_reg_map, CSR) << 8) |
                              RCC_CSR_LSION_BIT), /**< Low-speed internal
                                                   * (approximately 32 KHz). */
} rcc_clk;
#endif

/**
 * @brief STM32F2 clk_dev_id.
 */
typedef enum clk_dev_id {
    /* AHB */
    CLK_RAM,
    CLK_DMA,
    CLK_FLASH,
    CLK_EMIF,
    CLK_USB_BUFF,
    CLK_LAST_AHB_ENTRY_,
    /* APB0 */
    CLK_PLL,
    CLK_PB,
    CLK_USART1,
    CLK_USART2,
    CLK_UART1,
    CLK_UART2,
    CLK_SPI1,
    CLK_SPI2,
    CLK_SPI3,
    CLK_I2C1,
    CLK_I2C2,
    CLK_EPCA1,
    CLK_PCA1,
    CLK_PCA2,
    CLK_SSG,
    CLK_TIMER1,
    CLK_TIMER2,
    CLK_SARADC1,
    CLK_SARADC2,
    CLK_CMP1,
    CLK_CMP2,
    CLK_CS,
    CLK_AES,
    CLK_CRC,
    CLK_IDAC1,
    CLK_IDAC2,
    CLK_LPT,
    CLK_I2S,
    CLK_USB,
    CLK_EVREG,
    CLK_FLCTRL,
    CLK_LAST_APB0_ENTRY_,
    /* APB1 */
    CLK_MISC0,
    CLK_MISC1,
    CLK_MISC2,
    CLK_LAST_APB1_ENTRY_
} clk_dev_id;

/**
 * @brief STM32F2 Peripheral clock domains.
 */
typedef enum clk_domain{
    CLK_AHB,
    CLK_APB0,
    CLK_APB1
}clk_domain;

#define CLK_CR_AHBDIV_MASK           0x00000700
#define CLK_CR_APBDIV_MASK           0x00010000
#define CLK_CR_AHBDIV_BIT            8  /* AHBDIV<10:8>: AHB Clock Divider.               */
#define CLK_CR_APBDIV_BIT            16 /* APBDIV<16>: APB Clock Divider.                 */
#define CLK_CR_APBDIV_DIVn(div_in, cr_out)  cr_out |= ((div_in) == 2) << CLK_CR_APBDIV_BIT;
#define CLK_CR_AHBDIV_DIVn(div_in, cr_out)  do { \
                                                uint32 tmp = (div_in); \
                                                int32 i; \
                                                for (i = -1; tmp; i++) tmp = tmp >> 1; \
                                                cr_out |= i << CLK_CR_AHBDIV_BIT; \
                                            } while(0)
void clk_init(uint32 sys_clk, uint32 ahb_div, uint32 apb_div);
void clk_enable_dev(clk_dev_id clock);


#if 0
/**
 * @brief STM32F2 PLL entry clock source
 * @see rcc_configure_pll()
 */
typedef enum rcc_pllsrc {
    RCC_PLLSRC_HSI = 0,
    RCC_PLLSRC_HSE = RCC_PLLCFGR_PLLSRC,
} rcc_pllsrc;




/*
 * Prescalers and dividers.
 */

/**
 * @brief STM32F2 Prescaler identifiers.
 */
typedef enum rcc_prescaler {
    RCC_PRESCALER_MCO2,
    RCC_PRESCALER_MCO1,
    RCC_PRESCALER_RTC,
    RCC_PRESCALER_APB2,
    RCC_PRESCALER_APB1,
    RCC_PRESCALER_AHB
} rcc_prescaler;

/**
 * @brief STM32F2 MCO2 prescaler dividers.
 */
typedef enum rcc_mco2_divider {
    RCC_MCO2_DIV_1 = RCC_CFGR_MCO2PRE_DIV_1,
    RCC_MCO2_DIV_2 = RCC_CFGR_MCO2PRE_DIV_2,
    RCC_MCO2_DIV_3 = RCC_CFGR_MCO2PRE_DIV_3,
    RCC_MCO2_DIV_4 = RCC_CFGR_MCO2PRE_DIV_4,
    RCC_MCO2_DIV_5 = RCC_CFGR_MCO2PRE_DIV_5,
} rcc_mco2_divider;

/**
 * @brief STM32F2 MCO1 prescaler dividers.
 */
typedef enum rcc_mco1_divider {
    RCC_MCO1_DIV_1 = RCC_CFGR_MCO1PRE_DIV_1,
    RCC_MCO1_DIV_2 = RCC_CFGR_MCO1PRE_DIV_2,
    RCC_MCO1_DIV_3 = RCC_CFGR_MCO1PRE_DIV_3,
    RCC_MCO1_DIV_4 = RCC_CFGR_MCO1PRE_DIV_4,
    RCC_MCO1_DIV_5 = RCC_CFGR_MCO1PRE_DIV_5,
} rcc_mco1_divider;

/**
 * @brief STM32F2 RTC prescaler dividers.
 */
typedef enum rcc_rtc_divider {  /* FIXME [0.0.13] TODO */
    RCC_RTC_DIV_TODO = 0xFFFFFFFF,
} rcc_rtc_divider;

/**
 * @brief STM32F2 AP2 prescaler dividers.
 */
typedef enum rcc_apb2_divider {
    RCC_APB2_HCLK_DIV_1  = 0,
    RCC_APB2_HCLK_DIV_2  = RCC_CFGR_PPRE2_AHB_DIV_2,
    RCC_APB2_HCLK_DIV_4  = RCC_CFGR_PPRE2_AHB_DIV_4,
    RCC_APB2_HCLK_DIV_8  = RCC_CFGR_PPRE2_AHB_DIV_8,
    RCC_APB2_HCLK_DIV_16 = RCC_CFGR_PPRE2_AHB_DIV_16,
} rcc_apb2_divider;

/**
 * @brief STM32F2 APB1 prescaler dividers.
 */
typedef enum rcc_apb1_divider {
    RCC_APB1_HCLK_DIV_1  = 0,
    RCC_APB1_HCLK_DIV_2  = RCC_CFGR_PPRE1_AHB_DIV_2,
    RCC_APB1_HCLK_DIV_4  = RCC_CFGR_PPRE1_AHB_DIV_4,
    RCC_APB1_HCLK_DIV_8  = RCC_CFGR_PPRE1_AHB_DIV_8,
    RCC_APB1_HCLK_DIV_16 = RCC_CFGR_PPRE1_AHB_DIV_16,
} rcc_apb1_divider;

/**
 * @brief STM32F2 AHB prescaler dividers.
 */
typedef enum rcc_ahb_divider {
    RCC_AHB_SYSCLK_DIV_1   = 0,
    RCC_AHB_SYSCLK_DIV_2   = RCC_CFGR_HPRE_SYSCLK_DIV_2,
    RCC_AHB_SYSCLK_DIV_4   = RCC_CFGR_HPRE_SYSCLK_DIV_4,
    RCC_AHB_SYSCLK_DIV_8   = RCC_CFGR_HPRE_SYSCLK_DIV_8,
    RCC_AHB_SYSCLK_DIV_16  = RCC_CFGR_HPRE_SYSCLK_DIV_16,
    RCC_AHB_SYSCLK_DIV_64  = RCC_CFGR_HPRE_SYSCLK_DIV_64,
    RCC_AHB_SYSCLK_DIV_128 = RCC_CFGR_HPRE_SYSCLK_DIV_128,
    RCC_AHB_SYSCLK_DIV_256 = RCC_CFGR_HPRE_SYSCLK_DIV_256,
    RCC_AHB_SYSCLK_DIV_512 = RCC_CFGR_HPRE_SYSCLK_DIV_512,
} rcc_ahb_divider;

/**
 * @brief STM32F2 PLL configuration values.
 * Point to one of these with the "data" field in a struct rcc_pll_cfg.
 * @see struct rcc_pll_cfg.
 */
typedef struct stm32f2_rcc_pll_data {
    uint8 pllq;      /**<
                      * @brief PLLQ value.
                      * Allowed values: 4, 5, ..., 15. */
    uint8 pllp;      /**<
                      * @brief PLLP value.
                      * Allowed values: 2, 4, 6, 8. */
    uint16 plln;     /**<
                      * @brief PLLN value.
                      * Allowed values: 192, 193, ..., 432. */
    uint8 pllm;      /**<
                      * @brief PLLM value.
                      * Allowed values: 2, 3, ..., 63. */
} stm32f2_rcc_pll_data;
#endif


#ifdef __cplusplus
}
#endif

#endif
