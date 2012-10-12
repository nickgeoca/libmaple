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
#define CLKCTRL_CR_AHBSEL_MASK           0x00000007
#define CLKCTRL_CR_AHBDIV_MASK           0x00000700
#define CLKCTRL_CR_APBDIV_MASK           0x00010000
#define CLKCTRL_CR_EXTESEL_MASK          0x10000000
#define CLKCTRL_CR_OBUSYF_MASK           0x20000000
#define CLKCTRL_CR_AHBSEL_BIT            0  /* AHBSEL<2:0>: AHB Clock Source Select.          */
#define CLKCTRL_CR_AHBDIV_BIT            8  /* AHBDIV<10:8>: AHB Clock Divider.               */
#define CLKCTRL_CR_APBDIV_BIT            16 /* APBDIV<16>: APB Clock Divider.                 */
#define CLKCTRL_CR_EXTESEL_BIT           28 /* EXTESEL<28>: External Clock Edge Select.       */
#define CLKCTRL_CR_OBUSYF_BIT            29 /* OBUSYF<29>: Oscillators Busy Flag.             */
#define CLKCTRL_CR_AHBSEL_LPOSC0         (0 << CLKCTRL_CR_AHBSEL_BIT)
#define CLKCTRL_CR_AHBSEL_LFOSC0         (1 << CLKCTRL_CR_AHBSEL_BIT)
#define CLKCTRL_CR_AHBSEL_RTC0OSC        (2 << CLKCTRL_CR_AHBSEL_BIT)
#define CLKCTRL_CR_AHBSEL_EXTOSC0        (3 << CLKCTRL_CR_AHBSEL_BIT)
#define CLKCTRL_CR_AHBSEL_USB0OSC        (4 << CLKCTRL_CR_AHBSEL_BIT)
#define CLKCTRL_CR_AHBSEL_PLL0OSC        (5 << CLKCTRL_CR_AHBSEL_BIT)
#define CLKCTRL_CR_AHBSEL_LPOSC0_DIV     (6 << CLKCTRL_CR_AHBSEL_BIT)
#define CLKCTRL_CR_AHBDIV_DIV1           (0 << CLKCTRL_CR_AHBDIV_BIT)
#define CLKCTRL_CR_AHBDIV_DIV2           (1 << CLKCTRL_CR_AHBDIV_BIT)
#define CLKCTRL_CR_AHBDIV_DIV4           (2 << CLKCTRL_CR_AHBDIV_BIT)
#define CLKCTRL_CR_AHBDIV_DIV8           (3 << CLKCTRL_CR_AHBDIV_BIT)
#define CLKCTRL_CR_AHBDIV_DIV16          (4 << CLKCTRL_CR_AHBDIV_BIT)
#define CLKCTRL_CR_AHBDIV_DIV32          (5 << CLKCTRL_CR_AHBDIV_BIT)
#define CLKCTRL_CR_AHBDIV_DIV64          (6 << CLKCTRL_CR_AHBDIV_BIT)
#define CLKCTRL_CR_AHBDIV_DIV128         (7 << CLKCTRL_CR_AHBDIV_BIT)
#define CLKCTRL_CR_APBDIV_DIV1           (0 << CLKCTRL_CR_APBDIV_BIT)
#define CLKCTRL_CR_APBDIV_DIV2           (1 << CLKCTRL_CR_APBDIV_BIT)
#define CLKCTRL_CR_EXTESEL_BOTH_EDGES    (0 << CLKCTRL_CR_EXTESEL_BIT)
#define CLKCTRL_CR_EXTESEL_RISING_ONLY   (1 << CLKCTRL_CR_EXTESEL_BIT)
#define CLKCTRL_CR_OBUSYF_NOT_SET        (0 << CLKCTRL_CR_OBUSYF_BIT)
#define CLKCTRL_CR_OBUSYF_SET            (1 << CLKCTRL_CR_OBUSYF_BIT)

#define CLKCTRL_PM3CN_PM3CSEL_MASK       0x00000007
#define CLKCTRL_PM3CN_PM3CEN_MASK        0x00010000
#define CLKCTRL_PM3CN_PM3CSEL_BIT        0  /* PM3CSEL<2:0>: Power Mode 3 Fast-Wake Clock Source. */
#define CLKCTRL_PM3CN_PM3CEN_BIT         16 /* PM3CEN<16>: Power Mode 3 Fast-Wake Clock Enable. */
#define CLKCTRL_PM3CN_PM3CSEL_LPOSC0     (0 << CLKCTRL_PM3CN_PM3CSEL_BIT)
#define CLKCTRL_PM3CN_PM3CSEL_LFOSC0     (1 << CLKCTRL_PM3CN_PM3CSEL_BIT)
#define CLKCTRL_PM3CN_PM3CSEL_RTC0OSC    (2 << CLKCTRL_PM3CN_PM3CSEL_BIT)
#define CLKCTRL_PM3CN_PM3CSEL_EXTOSC0    (3 << CLKCTRL_PM3CN_PM3CSEL_BIT)
#define CLKCTRL_PM3CN_PM3CSEL_USB0OSC    (4 << CLKCTRL_PM3CN_PM3CSEL_BIT)
#define CLKCTRL_PM3CN_PM3CSEL_PLL0OSC    (5 << CLKCTRL_PM3CN_PM3CSEL_BIT)
#define CLKCTRL_PM3CN_PM3CSEL_LPOSC0_DIV (6 << CLKCTRL_PM3CN_PM3CSEL_BIT)
#define CLKCTRL_PM3CN_PM3CEN_DS          (0 << CLKCTRL_PM3CN_PM3CEN_BIT)
#define CLKCTRL_PM3CN_PM3CEN_EN          (1 << CLKCTRL_PM3CN_PM3CEN_BIT)

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


/**
 * @brief STM32F2 clock sources.
 */

typedef enum clk_sysclk_src {
    CLK_SRC_LP     = CLKCTRL_CR_AHBSEL_LPOSC0,     /**< Low power internal * (20 MHz) */
    //CLK_SRC_LF     = CLKCTRL_CR_AHBSEL_LFOSC0,     /**< Low frequency internal * (approximately 16.4 kHz)*/
    //CLK_SRC_RTC    = CLKCTRL_CR_AHBSEL_RTC0OSC,    /**< External real time clock. */
    //CLK_SRC_EXT    = CLKCTRL_CR_AHBSEL_EXTOSC0,    /**< External source.   */
    //CLK_SRC_USB    = CLKCTRL_CR_AHBSEL_USB0OSC,    /**< USB * (48 Mhz). */
    CLK_SRC_PLL    = CLKCTRL_CR_AHBSEL_PLL0OSC,    /**< Phase lock loop * (23 MHz to 80 MHz). */
    CLK_SRC_LP_DIV = CLKCTRL_CR_AHBSEL_LPOSC0_DIV, /**< Low-speed internal * (2.5 MHz). */
} clk_sysclk_src;

typedef enum clk_prescaler{
    CLK_PRESCALE_AHB,
    CLK_PRESCALE_APB,
}clk_prescaler;

/**
 * @brief SiM3U1 APB prescaler dividers.
 */
typedef enum clk_apb_divider {
    CLK_APB_HCLK_DIV_1,
    CLK_APB_HCLK_DIV_2
} clk_apb_divider;

/**
 * @brief SiM3U1 APB prescaler dividers.
 */
typedef enum clk_ahb_divider {
    CLK_AHB_SYSCLK_DIV_1,
    CLK_AHB_SYSCLK_DIV_2,
    CLK_AHB_SYSCLK_DIV_4,
    CLK_AHB_SYSCLK_DIV_8,
    CLK_AHB_SYSCLK_DIV_16,
    CLK_AHB_SYSCLK_DIV_32,
    CLK_AHB_SYSCLK_DIV_64,
    CLK_AHB_SYSCLK_DIV_128,
} clk_ahb_divider;

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

void clk_enable_dev(clk_dev_id clock);
void clk_set_clk_variable(uint32 sys_clk);

/*
 * PLL Device
 */

typedef struct pll_reg_map
{
   __io uint32 DIVIDER; // Base Address + 0x0
   uint32      reserved0;
   uint32      reserved1;
   uint32      reserved2;
   __io uint32 CONTROL; // Base Address + 0x10
   __io uint32 CONTROL_SET;
   __io uint32 CONTROL_CLR;
   uint32      reserved3;
   __io uint32 SSPR; // Base Address + 0x20
   uint32      reserved4;
   uint32      reserved5;
   uint32      reserved6;
   __io uint32 CALCONFIG; // Base Address + 0x30
   uint32      reserved7;
   uint32      reserved8;
   uint32      reserved9;
   uint32      reserved10[4];
   uint32      reserved11[4];
   uint32      reserved12[4];
} pll_reg_map;

#define PLL_BASE            ((pll_reg_map *)0x4003B000)

#define PLL_DIVIDER_M_MASK         0x00000FFF
#define PLL_DIVIDER_N_MASK         0x0FFF0000
#define PLL_DIVIDER_M_BIT          0  /* M<11:0>: M Divider Value.                      */
#define PLL_DIVIDER_N_BIT          16 /* N<27:16>: N Divider Value.                     */

#define PLL_CR_LLMTF_MASK          0x00000001
#define PLL_CR_HLMTF_MASK          0x00000002
#define PLL_CR_LCKI_MASK           0x00000004
#define PLL_CR_LMTIEN_MASK         0x00000200
#define PLL_CR_LCKIEN_MASK         0x00000400
#define PLL_CR_LCKPOL_MASK         0x00000800
#define PLL_CR_REFSEL_MASK         0x00030000
#define PLL_CR_LOCKTH_MASK         0x00300000
#define PLL_CR_STALL_MASK          0x04000000
#define PLL_CR_DITHEN_MASK         0x10000000
#define PLL_CR_EDGSEL_MASK         0x20000000
#define PLL_CR_OUTMD_MASK          0xC0000000
#define PLL_CR_LLMTF_BIT           0  /* LLMTF<0>: CAL Saturation (Low) Flag.           */
#define PLL_CR_HLMTF_BIT           1  /* HLMTF<1>: CAL Saturation (High) Flag.          */
#define PLL_CR_LCKI_BIT            2  /* LCKI<2>: Phase-Lock and Frequency-Lock Locked Interrupt Flag. */
#define PLL_CR_LMTIEN_BIT          9  /* LMTIEN<9>: Limit Interrupt Enable.             */
#define PLL_CR_LCKIEN_BIT          10 /* LCKIEN<10>: Locked Interrupt Enable.           */
#define PLL_CR_LCKPOL_BIT          11 /* LCKPOL<11>: Lock Interrupt Polarity.           */
#define PLL_CR_REFSEL_BIT          16 /* REFSEL<17:16>: Reference Clock Selection Control. */
#define PLL_CR_LOCKTH_BIT          20 /* LOCKTH<21:20>: Lock Threshold Control.         */
#define PLL_CR_STALL_BIT           26 /* STALL<26>: DCO Output Updates Stall.           */
#define PLL_CR_DITHEN_BIT          28 /* DITHEN<28>: Dithering Enable.                  */
#define PLL_CR_EDGSEL_BIT          29 /* EDGSEL<29>: Edge Lock Select.                  */
#define PLL_CR_OUTMD_BIT           30 /* OUTMD<31:30>: PLL Output Mode.                 */
#define PLL_CR_LLMTF_NOT_SET       (0 << PLL_CR_LLMTF_BIT)
#define PLL_CR_LLMTF_SET           (1 << PLL_CR_LLMTF_BIT)
#define PLL_CR_HLMTF_NOT_SET       (0 << PLL_CR_HLMTF_BIT)
#define PLL_CR_HLMTF_SET           (1 << PLL_CR_HLMTF_BIT)
#define PLL_CR_LCKI_NOT_SET        (0 << PLL_CR_LCKI_BIT)
#define PLL_CR_LCKI_SET            (1 << PLL_CR_LCKI_BIT)
#define PLL_CR_LMTIEN_DS           (0 << PLL_CR_LMTIEN_BIT)
#define PLL_CR_LMTIEN_EN           (1 << PLL_CR_LMTIEN_BIT)
#define PLL_CR_LCKIEN_DS           (0 << PLL_CR_LCKIEN_BIT)
#define PLL_CR_LCKIEN_EN           (1 << PLL_CR_LCKIEN_BIT)
#define PLL_CR_LCKPOL_ACTV_LOW     (0 << PLL_CR_LCKPOL_BIT)
#define PLL_CR_LCKPOL_ACTV_HIGH    (1 << PLL_CR_LCKPOL_BIT)
#define PLL_CR_REFSEL_RTC0OSC      (0 << PLL_CR_REFSEL_BIT)
#define PLL_CR_REFSEL_LPOSC0DIV    (1 << PLL_CR_REFSEL_BIT)
#define PLL_CR_REFSEL_EXTOSC0      (2 << PLL_CR_REFSEL_BIT)
#define PLL_CR_REFSEL_USBOSC0      (3 << PLL_CR_REFSEL_BIT)
#define PLL_CR_STALL_DS            (0 << PLL_CR_STALL_BIT)
#define PLL_CR_STALL_EN            (1 << PLL_CR_STALL_BIT)
#define PLL_CR_DITHEN_DS           (0 << PLL_CR_DITHEN_BIT)
#define PLL_CR_DITHEN_EN           (1 << PLL_CR_DITHEN_BIT)
#define PLL_CR_EDGSEL_FALLING_EDGE (0 << PLL_CR_EDGSEL_BIT)
#define PLL_CR_EDGSEL_RISING_EDGE  (1 << PLL_CR_EDGSEL_BIT)
#define PLL_CR_OUTMD_OFF           (0U << PLL_CR_OUTMD_BIT)
#define PLL_CR_OUTMD_DCO           (1U << PLL_CR_OUTMD_BIT)
#define PLL_CR_OUTMD_FLL           (2U << PLL_CR_OUTMD_BIT)
#define PLL_CR_OUTMD_PLL           (3U << PLL_CR_OUTMD_BIT)

#define PLL_SSPR_SSAMP_MASK        0x00000007
#define PLL_SSPR_SSUINV_MASK       0x00001F00
#define PLL_SSPR_SSAMP_BIT         0  /* SSAMP<2:0>: Spectrum Spreading Amplitude.      */
#define PLL_SSPR_SSUINV_BIT        8  /* SSUINV<12:8>: Spectrum Spreading Update Interval. */
#define PLL_SSPR_SSAMP_DS          (0 << PLL_SSPR_SSAMP_BIT)
#define PLL_SSPR_SSAMP_SETTING1    (1 << PLL_SSPR_SSAMP_BIT)
#define PLL_SSPR_SSAMP_SETTING2    (2 << PLL_SSPR_SSAMP_BIT)
#define PLL_SSPR_SSAMP_SETTING3    (3 << PLL_SSPR_SSAMP_BIT)
#define PLL_SSPR_SSAMP_SETTING4    (4 << PLL_SSPR_SSAMP_BIT)
#define PLL_SSPR_SSAMP_SETTING5    (5 << PLL_SSPR_SSAMP_BIT)

#define PLL_CALCONFIG_DITHER_MASK  0x0000000F
#define PLL_CALCONFIG_CAL_MASK     0x0000FFF0
#define PLL_CALCONFIG_RANGE_MASK   0x00070000
#define PLL_CALCONFIG_DITHER_BIT   0  /* DITHER<3:0>: DCO Dither Setting.               */
#define PLL_CALCONFIG_CAL_BIT      4  /* CAL<15:4>: DCO Calibration Value.              */
#define PLL_CALCONFIG_RANGE_BIT    16 /* RANGE<18:16>: DCO Range.                       */
#define PLL_CALCONFIG_RANGE_RANGE0 (0 << PLL_CALCONFIG_RANGE_BIT)
#define PLL_CALCONFIG_RANGE_RANGE1 (1 << PLL_CALCONFIG_RANGE_BIT)
#define PLL_CALCONFIG_RANGE_RANGE2 (2 << PLL_CALCONFIG_RANGE_BIT)
#define PLL_CALCONFIG_RANGE_RANGE3 (3 << PLL_CALCONFIG_RANGE_BIT)
#define PLL_CALCONFIG_RANGE_RANGE4 (4 << PLL_CALCONFIG_RANGE_BIT)


/**
 * @brief STM32F2 PLL entry clock source
 * @see rcc_configure_pll()
 */
typedef enum pll_src {
    PLL_SRC_RTC = 0,
    PLL_SRC_LP = 1,
    PLL_SRC_EXT = 2,
    PLL_SRC_USB = 3
} pll_src;


typedef struct pll_cfg {
    pll_src  pllsrc;     /**< PLL source */

    /** Series-specific configuration data. */
    void       *data;
} pll_cfg;

/*
 * Returns the actual frequency output by the PLL
 */
static inline uint32 pll_get_actl_freq(uint32 src_freq, uint32 targ_freq)
{
    return src_freq * (uint32)(targ_freq / src_freq);
}


#ifdef __cplusplus
}
#endif

#endif
