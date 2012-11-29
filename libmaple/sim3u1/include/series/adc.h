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
 * @file libmaple/sim3u1/include/series/adc.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>,
 * @brief STM32F2 ADC support.
 */

#ifndef _LIBMAPLE_SIM3U1_ADC_H_
#define _LIBMAPLE_SIM3U1_ADC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Common register map
 */
/** ADC register map type. */
typedef struct adc_reg_map
{
   volatile uint32_t CONFIG;    // Base Address + 0x0
   volatile uint32_t CONFIG_SET;
   volatile uint32_t CONFIG_CLR;
   uint32_t          reserved0;
   volatile uint32_t CONTROL;   // Base Address + 0x10
   volatile uint32_t CONTROL_SET;
   volatile uint32_t CONTROL_CLR;
   uint32_t          reserved1;
   volatile uint32_t SQ7654;    // Base Address + 0x20
   uint32_t          reserved2;
   uint32_t          reserved3;
   uint32_t          reserved4;
   volatile uint32_t SQ3210;    // Base Address + 0x30
   uint32_t          reserved5;
   uint32_t          reserved6;
   uint32_t          reserved7;
   volatile uint32_t CHAR32;    // Base Address + 0x40
   volatile uint32_t CHAR32_SET;
   volatile uint32_t CHAR32_CLR;
   uint32_t          reserved8;
   volatile uint32_t CHAR10;    // Base Address + 0x50
   volatile uint32_t CHAR10_SET;
   volatile uint32_t CHAR10_CLR;
   uint32_t          reserved9;
   volatile uint32_t DATA;      // Base Address + 0x60
   uint32_t          reserved10;
   uint32_t          reserved11;
   uint32_t          reserved12;
   volatile uint32_t WCLIMITS;  // Base Address + 0x70
   uint32_t          reserved13;
   uint32_t          reserved14;
   uint32_t          reserved15;
   volatile uint32_t ACC;       // Base Address + 0x80
   uint32_t          reserved16;
   uint32_t          reserved17;
   uint32_t          reserved18;
   volatile uint32_t STATUS;    // Base Address + 0x90
   volatile uint32_t STATUS_SET;
   volatile uint32_t STATUS_CLR;
   uint32_t          reserved19;
   volatile uint32_t FIFOSTATUS;// Base Address + 0xa0
   uint32_t          reserved20;
   uint32_t          reserved21;
   uint32_t          reserved22;
   uint32_t          reserved23[4];
} adc_reg_map;


/*
 * Register map base pointers
 */

#define ADC1_BASE       ((struct adc_reg_map*)0x4001A000)
#define ADC2_BASE       ((struct adc_reg_map*)0x4001B000)

/*
 * Registers
 */
/** SARADC configuration register */
#define SARADC_CFGR_SPSEL_MASK          0x0000000F
#define SARADC_CFGR_SPEN_MASK           0x00000010
#define SARADC_CFGR_SSGEN_MASK          0x00000020
#define SARADC_CFGR_PACKMD_MASK         0x000000C0
#define SARADC_CFGR_SIMCEN_MASK         0x00000100
#define SARADC_CFGR_INTLVEN_MASK        0x00000200
#define SARADC_CFGR_SCANEN_MASK         0x00000400
#define SARADC_CFGR_SCANMD_MASK         0x00001000
#define SARADC_CFGR_DMAEN_MASK          0x00004000
#define SARADC_CFGR_BCLKSEL_MASK        0x00008000
#define SARADC_CFGR_CLKDIV_MASK         0x07FF0000
#define SARADC_CFGR_SCCIEN_MASK         0x08000000
#define SARADC_CFGR_SDIEN_MASK          0x10000000
#define SARADC_CFGR_FORIEN_MASK         0x20000000
#define SARADC_CFGR_FURIEN_MASK         0x40000000
#define SARADC_CFGR_SPSEL_BIT           0  /* SPSEL<3:0>: Sampling Phase Select.             */
#define SARADC_CFGR_SPEN_BIT            4  /* SPEN<4>: Sampling Phase Enable.                */
#define SARADC_CFGR_SSGEN_BIT           5  /* SSGEN<5>: Synchronous Sample Generator Enable. */
#define SARADC_CFGR_PACKMD_BIT          6  /* PACKMD<7:6>: Output Packing Mode.              */
#define SARADC_CFGR_SIMCEN_BIT          8  /* SIMCEN<8>: Simultaneous Conversion Packing Enable. */
#define SARADC_CFGR_INTLVEN_BIT         9  /* INTLVEN<9>: Interleaved Conversion Packing Enable. */
#define SARADC_CFGR_SCANEN_BIT          10 /* SCANEN<10>: Scan Mode Enable.                  */
#define SARADC_CFGR_SCANMD_BIT          12 /* SCANMD<12>: Scan Mode Select.                  */
#define SARADC_CFGR_DMAEN_BIT           14 /* DMAEN<14>: DMA Interface Enable .              */
#define SARADC_CFGR_BCLKSEL_BIT         15 /* BCLKSEL<15>: Burst Mode Clock Select.          */
#define SARADC_CFGR_CLKDIV_BIT          16 /* CLKDIV<26:16>: SAR Clock Divider.              */
#define SARADC_CFGR_SCCIEN_BIT          27 /* SCCIEN<27>: Single Conversion Complete Interrupt Enable. */
#define SARADC_CFGR_SDIEN_BIT           28 /* SDIEN<28>: Scan Done Interrupt Enable.         */
#define SARADC_CFGR_FORIEN_BIT          29 /* FORIEN<29>: FIFO Overrun Interrupt Enable.     */
#define SARADC_CFGR_FURIEN_BIT          30 /* FURIEN<30>: FIFO Underrun Interrupt Enable.    */
#define SARADC_CFGR_SPSEL_PHASE0        (0 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE1        (1 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE2        (2 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE3        (3 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE4        (4 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE5        (5 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE6        (6 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE7        (7 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE8        (8 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE9        (9 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE10       (10 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE11       (11 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE12       (12 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE13       (13 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE14       (14 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPSEL_PHASE15       (15 << SARADC_CFGR_SPSEL_BIT)
#define SARADC_CFGR_SPEN_DS             (0 << SARADC_CFGR_SPEN_BIT)
#define SARADC_CFGR_SPEN_EN             (1 << SARADC_CFGR_SPEN_BIT)
#define SARADC_CFGR_SSGEN_DS            (0 << SARADC_CFGR_SSGEN_BIT)
#define SARADC_CFGR_SSGEN_EN            (1 << SARADC_CFGR_SSGEN_BIT)
#define SARADC_CFGR_PACKMD_UPPER_ONLY   (0 << SARADC_CFGR_PACKMD_BIT)
#define SARADC_CFGR_PACKMD_LOWER_ONLY   (1 << SARADC_CFGR_PACKMD_BIT)
#define SARADC_CFGR_PACKMD_UPPER_FIRST  (2 << SARADC_CFGR_PACKMD_BIT)
#define SARADC_CFGR_PACKMD_LOWER_FIRST  (3 << SARADC_CFGR_PACKMD_BIT)
#define SARADC_CFGR_SIMCEN_DS           (0 << SARADC_CFGR_SIMCEN_BIT)
#define SARADC_CFGR_SIMCEN_EN           (1 << SARADC_CFGR_SIMCEN_BIT)
#define SARADC_CFGR_INTLVEN_DS          (0 << SARADC_CFGR_INTLVEN_BIT)
#define SARADC_CFGR_INTLVEN_EN          (1 << SARADC_CFGR_INTLVEN_BIT)
#define SARADC_CFGR_SCANEN_DS           (0 << SARADC_CFGR_SCANEN_BIT)
#define SARADC_CFGR_SCANEN_EN           (1 << SARADC_CFGR_SCANEN_BIT)
#define SARADC_CFGR_SCANMD_ONCE         (0 << SARADC_CFGR_SCANMD_BIT)
#define SARADC_CFGR_SCANMD_LOOP         (1 << SARADC_CFGR_SCANMD_BIT)
#define SARADC_CFGR_DMAEN_DS            (0 << SARADC_CFGR_DMAEN_BIT)
#define SARADC_CFGR_DMAEN_EN            (1 << SARADC_CFGR_DMAEN_BIT)
#define SARADC_CFGR_BCLKSEL_LPOSC0      (0 << SARADC_CFGR_BCLKSEL_BIT)
#define SARADC_CFGR_BCLKSEL_APB         (1 << SARADC_CFGR_BCLKSEL_BIT)
#define SARADC_CFGR_SCCIEN_DS           (0 << SARADC_CFGR_SCCIEN_BIT)
#define SARADC_CFGR_SCCIEN_EN           (1 << SARADC_CFGR_SCCIEN_BIT)
#define SARADC_CFGR_SDIEN_DS            (0 << SARADC_CFGR_SDIEN_BIT)
#define SARADC_CFGR_SDIEN_EN            (1 << SARADC_CFGR_SDIEN_BIT)
#define SARADC_CFGR_FORIEN_DS           (0 << SARADC_CFGR_FORIEN_BIT)
#define SARADC_CFGR_FORIEN_EN           (1 << SARADC_CFGR_FORIEN_BIT)
#define SARADC_CFGR_FURIEN_DS           (0 << SARADC_CFGR_FURIEN_BIT)
#define SARADC_CFGR_FURIEN_EN           (1 << SARADC_CFGR_FURIEN_BIT)

/** SARADC control register */
#define SARADC_CR_REFGNDSEL_MASK        0x00000001
#define SARADC_CR_CLKESEL_MASK          0x00000002
#define SARADC_CR_BMTK_MASK             0x000000FC
#define SARADC_CR_SCSEL_MASK            0x00000F00
#define SARADC_CR_PWRTIME_MASK          0x0000F000
#define SARADC_CR_BURSTEN_MASK          0x00010000
#define SARADC_CR_ADCEN_MASK            0x00020000
#define SARADC_CR_AD12BSSEL_MASK        0x00040000
#define SARADC_CR_VCMEN_MASK            0x00080000
#define SARADC_CR_ACCMD_MASK            0x00200000
#define SARADC_CR_TRKMD_MASK            0x00400000
#define SARADC_CR_ADBUSY_MASK           0x00800000
#define SARADC_CR_BIASSEL_MASK          0x03000000
#define SARADC_CR_LPMDEN_MASK           0x04000000
#define SARADC_CR_MREFLPEN_MASK         0x08000000
#define SARADC_CR_VREFSEL_MASK          0xC0000000
#define SARADC_CR_REFGNDSEL_BIT         0  /* REFGNDSEL<0>: Reference Ground Select.         */
#define SARADC_CR_CLKESEL_BIT           1  /* CLKESEL<1>: Sampling Clock Edge Select.        */
#define SARADC_CR_BMTK_BIT              2  /* BMTK<64>: – + ? ? 3 TRKMD ?                    */
#define SARADC_CR_SCSEL_BIT             8  /* SCSEL<11:8>: Start-Of-Conversion Source Select. */
#define SARADC_CR_PWRTIME_BIT           12 /* PWRTIME<8>: ?                                  */
#define SARADC_CR_BURSTEN_BIT           16 /* BURSTEN<16>: Burst Mode Enable.                */
#define SARADC_CR_ADCEN_BIT             17 /* ADCEN<17>: ADC Enable.                         */
#define SARADC_CR_AD12BSSEL_BIT         18 /* AD12BSSEL<18>: 12-Bit Mode Sample Select.      */
#define SARADC_CR_VCMEN_BIT             19 /* VCMEN<19>: Common Mode Buffer Enable.          */
#define SARADC_CR_ACCMD_BIT             21 /* ACCMD<21>: Accumulation Mode.                  */
#define SARADC_CR_TRKMD_BIT             22 /* TRKMD<22>: ADC Tracking Mode.                  */
#define SARADC_CR_ADBUSY_BIT            23 /* ADBUSY<23>: ADC Busy.                          */
#define SARADC_CR_BIASSEL_BIT           24 /* BIASSEL<25:24>: Bias Power Select.             */
#define SARADC_CR_LPMDEN_BIT            26 /* LPMDEN<26>: Low Power Mode Enable.             */
#define SARADC_CR_MREFLPEN_BIT          27 /* MREFLPEN<27>: MUX and VREF Low Power Enable.   */
#define SARADC_CR_VREFSEL_BIT           30 /* VREFSEL<31:30>: Voltage Reference Select.      */
#define SARADC_CR_REFGNDSEL_INTERNAL    (0 << SARADC_CR_REFGNDSEL_BIT)
#define SARADC_CR_REFGNDSEL_EXTERNAL    (1 << SARADC_CR_REFGNDSEL_BIT)
#define SARADC_CR_CLKESEL_RISING        (0 << SARADC_CR_CLKESEL_BIT)
#define SARADC_CR_CLKESEL_FALLING       (1 << SARADC_CR_CLKESEL_BIT)
#define SARADC_CR_SCSEL_ADCNT0          (0 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT1          (1 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT2          (2 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT3          (3 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT4          (4 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT5          (5 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT6          (6 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT7          (7 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT8          (8 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT9          (9 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT10         (10 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT11         (11 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT12         (12 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT13         (13 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT14         (14 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_SCSEL_ADCNT15         (15 << SARADC_CR_SCSEL_BIT)
#define SARADC_CR_BURSTEN_DS            (0 << SARADC_CR_BURSTEN_BIT)
#define SARADC_CR_BURSTEN_EN            (1 << SARADC_CR_BURSTEN_BIT)
#define SARADC_CR_ADCEN_DS              (0 << SARADC_CR_ADCEN_BIT)
#define SARADC_CR_ADCEN_EN              (1 << SARADC_CR_ADCEN_BIT)
#define SARADC_CR_AD12BSSEL_FOUR        (0 << SARADC_CR_AD12BSSEL_BIT)
#define SARADC_CR_AD12BSSEL_ONE         (1 << SARADC_CR_AD12BSSEL_BIT)
#define SARADC_CR_VCMEN_DS              (0 << SARADC_CR_VCMEN_BIT)
#define SARADC_CR_VCMEN_EN              (1 << SARADC_CR_VCMEN_BIT)
#define SARADC_CR_ACCMD_ACCUMULATE      (0 << SARADC_CR_ACCMD_BIT)
#define SARADC_CR_ACCMD_REPEAT          (1 << SARADC_CR_ACCMD_BIT)
#define SARADC_CR_TRKMD_NORMAL          (0 << SARADC_CR_TRKMD_BIT)
#define SARADC_CR_TRKMD_DELAYED         (1 << SARADC_CR_TRKMD_BIT)
#define SARADC_CR_BIASSEL_MODE0         (0 << SARADC_CR_BIASSEL_BIT)
#define SARADC_CR_BIASSEL_MODE1         (1 << SARADC_CR_BIASSEL_BIT)
#define SARADC_CR_BIASSEL_MODE2         (2 << SARADC_CR_BIASSEL_BIT)
#define SARADC_CR_BIASSEL_MODE3         (3 << SARADC_CR_BIASSEL_BIT)
#define SARADC_CR_LPMDEN_DS             (0 << SARADC_CR_LPMDEN_BIT)
#define SARADC_CR_LPMDEN_EN             (1 << SARADC_CR_LPMDEN_BIT)
#define SARADC_CR_MREFLPEN_DS           (0 << SARADC_CR_MREFLPEN_BIT)
#define SARADC_CR_MREFLPEN_EN           (1 << SARADC_CR_MREFLPEN_BIT)
#define SARADC_CR_VREFSEL_INTERNAL_VREF (0U << SARADC_CR_VREFSEL_BIT)
#define SARADC_CR_VREFSEL_VDD           (1U << SARADC_CR_VREFSEL_BIT)
#define SARADC_CR_VREFSEL_LDO_OUT       (2U << SARADC_CR_VREFSEL_BIT)
#define SARADC_CR_VREFSEL_EXTERNAL_VREF (3U << SARADC_CR_VREFSEL_BIT)

/** SARADC sequencer timer slots 4-7 register */
#define SARADC_SQ7654_TS4CHR_MASK       0x00000003
#define SARADC_SQ7654_TS4MUX_MASK       0x0000007C
#define SARADC_SQ7654_TS5CHR_MASK       0x00000300
#define SARADC_SQ7654_TS5MUX_MASK       0x00007C00
#define SARADC_SQ7654_TS6CHR_MASK       0x00030000
#define SARADC_SQ7654_TS6MUX_MASK       0x007C0000
#define SARADC_SQ7654_TS7CHR_MASK       0x03000000
#define SARADC_SQ7654_TS7MUX_MASK       0x7C000000
#define SARADC_SQ7654_TS4CHR_BIT        0  /* TS4CHR<1:0>: Time Slot 4 Conversion Characteristic. */
#define SARADC_SQ7654_TS4MUX_BIT        2  /* TS4MUX<6:2>: Time Slot 4 Input Channel.        */
#define SARADC_SQ7654_TS5CHR_BIT        8  /* TS5CHR<9:8>: Time Slot 5 Conversion Characteristic. */
#define SARADC_SQ7654_TS5MUX_BIT        10 /* TS5MUX<14:10>: Time Slot 5 Input Channel.      */
#define SARADC_SQ7654_TS6CHR_BIT        16 /* TS6CHR<17:16>: Time Slot 6 Conversion Characteristic. */
#define SARADC_SQ7654_TS6MUX_BIT        18 /* TS6MUX<22:18>: Time Slot 6 Input Channel.      */
#define SARADC_SQ7654_TS7CHR_BIT        24 /* TS7CHR<25:24>: Time Slot 7 Conversion Characteristic. */
#define SARADC_SQ7654_TS7MUX_BIT        26 /* TS7MUX<30:26>: Time Slot 7 Input Channel.      */

/** SARADC sequencer timer slots 0-3 register */
#define SARADC_SQ3210_TS0CHR_MASK       0x00000003
#define SARADC_SQ3210_TS0MUX_MASK       0x0000007C
#define SARADC_SQ3210_TS1CHR_MASK       0x00000300
#define SARADC_SQ3210_TS1MUX_MASK       0x00007C00
#define SARADC_SQ3210_TS2CHR_MASK       0x00030000
#define SARADC_SQ3210_TS2MUX_MASK       0x007C0000
#define SARADC_SQ3210_TS3CHR_MASK       0x03000000
#define SARADC_SQ3210_TS3MUX_MASK       0x7C000000
#define SARADC_SQ3210_TS0CHR_BIT        0  /* TS0CHR<1:0>: Time Slot 0 Conversion Characteristic. */
#define SARADC_SQ3210_TS0MUX_BIT        2  /* TS0MUX<6:2>: Time Slot 0 Input Channel.        */
#define SARADC_SQ3210_TS1CHR_BIT        8  /* TS1CHR<9:8>: Time Slot 1 Conversion Characteristic. */
#define SARADC_SQ3210_TS1MUX_BIT        10 /* TS1MUX<14:10>: Time Slot 1 Input Channel.      */
#define SARADC_SQ3210_TS2CHR_BIT        16 /* TS2CHR<17:16>: Time Slot 2 Conversion Characteristic. */
#define SARADC_SQ3210_TS2MUX_BIT        18 /* TS2MUX<22:18>: Time Slot 2 Input Channel.      */
#define SARADC_SQ3210_TS3CHR_BIT        24 /* TS3CHR<25:24>: Time Slot 3 Conversion Characteristic. */
#define SARADC_SQ3210_TS3MUX_BIT        26 /* TS3MUX<30:26>: Time Slot 3 Input Channel.      */

/** SARADC conversion characteristic 2 & 3 register */
#define SARADC_CHAR32_CHR2GN_MASK       0x00000001
#define SARADC_CHAR32_CHR2RPT_MASK      0x0000000E
#define SARADC_CHAR32_CHR2LS_MASK       0x00000070
#define SARADC_CHAR32_CHR2RSEL_MASK     0x00000080
#define SARADC_CHAR32_CHR2WCIEN_MASK    0x00000100
#define SARADC_CHAR32_CHR3GN_MASK       0x00010000
#define SARADC_CHAR32_CHR3RPT_MASK      0x000E0000
#define SARADC_CHAR32_CHR3LS_MASK       0x00700000
#define SARADC_CHAR32_CHR3RSEL_MASK     0x00800000
#define SARADC_CHAR32_CHR3WCIEN_MASK    0x01000000
#define SARADC_CHAR32_CHR2GN_BIT        0  /* CHR2GN<0>: Conversion Characteristic 2 Gain.   */
#define SARADC_CHAR32_CHR2RPT_BIT       1  /* CHR2RPT<3:1>: Conversion Characteristic 2 Repeat Counter. */
#define SARADC_CHAR32_CHR2LS_BIT        4  /* CHR2LS<6:4>: Conversion Characteristic 2 Left-Shift Bits. */
#define SARADC_CHAR32_CHR2RSEL_BIT      7  /* CHR2RSEL<7>: Conversion Characteristic 2 Resolution Selection. */
#define SARADC_CHAR32_CHR2WCIEN_BIT     8  /* CHR2WCIEN<8>: Conversion Characteristic 2 Window Comparator Interrupt Enable. */
#define SARADC_CHAR32_CHR3GN_BIT        16 /* CHR3GN<16>: Conversion Characteristic 3 Gain.  */
#define SARADC_CHAR32_CHR3RPT_BIT       17 /* CHR3RPT<19:17>: Conversion Characteristic 3 Repeat Counter. */
#define SARADC_CHAR32_CHR3LS_BIT        20 /* CHR3LS<22:20>: Conversion Characteristic 3 Left-Shift Bits. */
#define SARADC_CHAR32_CHR3RSEL_BIT      23 /* CHR3RSEL<23>: Conversion Characteristic 3 Resolution Selection. */
#define SARADC_CHAR32_CHR3WCIEN_BIT     24 /* CHR3WCIEN<24>: Conversion Characteristic 3 Window Comparator Interrupt Enable. */
#define SARADC_CHAR32_CHR2GN_UNITY      (0 << SARADC_CHAR32_CHR2GN_BIT)
#define SARADC_CHAR32_CHR2GN_HALF       (1 << SARADC_CHAR32_CHR2GN_BIT)
#define SARADC_CHAR32_CHR2RPT_ACC1      (0 << SARADC_CHAR32_CHR2RPT_BIT)
#define SARADC_CHAR32_CHR2RPT_ACC4      (1 << SARADC_CHAR32_CHR2RPT_BIT)
#define SARADC_CHAR32_CHR2RPT_ACC8      (2 << SARADC_CHAR32_CHR2RPT_BIT)
#define SARADC_CHAR32_CHR2RPT_ACC16     (3 << SARADC_CHAR32_CHR2RPT_BIT)
#define SARADC_CHAR32_CHR2RPT_ACC32     (4 << SARADC_CHAR32_CHR2RPT_BIT)
#define SARADC_CHAR32_CHR2RPT_ACC64     (5 << SARADC_CHAR32_CHR2RPT_BIT)
#define SARADC_CHAR32_CHR2RSEL_B10      (0 << SARADC_CHAR32_CHR2RSEL_BIT)
#define SARADC_CHAR32_CHR2RSEL_B12      (1 << SARADC_CHAR32_CHR2RSEL_BIT)
#define SARADC_CHAR32_CHR2WCIEN_DS      (0 << SARADC_CHAR32_CHR2WCIEN_BIT)
#define SARADC_CHAR32_CHR2WCIEN_EN      (1 << SARADC_CHAR32_CHR2WCIEN_BIT)
#define SARADC_CHAR32_CHR3GN_UNITY      (0 << SARADC_CHAR32_CHR3GN_BIT)
#define SARADC_CHAR32_CHR3GN_HALF       (1 << SARADC_CHAR32_CHR3GN_BIT)
#define SARADC_CHAR32_CHR3RPT_ACC1      (0 << SARADC_CHAR32_CHR3RPT_BIT)
#define SARADC_CHAR32_CHR3RPT_ACC4      (1 << SARADC_CHAR32_CHR3RPT_BIT)
#define SARADC_CHAR32_CHR3RPT_ACC8      (2 << SARADC_CHAR32_CHR3RPT_BIT)
#define SARADC_CHAR32_CHR3RPT_ACC16     (3 << SARADC_CHAR32_CHR3RPT_BIT)
#define SARADC_CHAR32_CHR3RPT_ACC32     (4 << SARADC_CHAR32_CHR3RPT_BIT)
#define SARADC_CHAR32_CHR3RPT_ACC64     (5 << SARADC_CHAR32_CHR3RPT_BIT)
#define SARADC_CHAR32_CHR3RSEL_B10      (0 << SARADC_CHAR32_CHR3RSEL_BIT)
#define SARADC_CHAR32_CHR3RSEL_B12      (1 << SARADC_CHAR32_CHR3RSEL_BIT)
#define SARADC_CHAR32_CHR3WCIEN_DS      (0 << SARADC_CHAR32_CHR3WCIEN_BIT)
#define SARADC_CHAR32_CHR3WCIEN_EN      (1 << SARADC_CHAR32_CHR3WCIEN_BIT)

/** SARADC conversion characteristic 1 & 0 register */
#define SARADC_CHAR10_CHR0GN_MASK       0x00000001
#define SARADC_CHAR10_CHR0RPT_MASK      0x0000000E
#define SARADC_CHAR10_CHR0LS_MASK       0x00000070
#define SARADC_CHAR10_CHR0RSEL_MASK     0x00000080
#define SARADC_CHAR10_CHR0WCIEN_MASK    0x00000100
#define SARADC_CHAR10_CHR1GN_MASK       0x00010000
#define SARADC_CHAR10_CHR1RPT_MASK      0x000E0000
#define SARADC_CHAR10_CHR1LS_MASK       0x00700000
#define SARADC_CHAR10_CHR1RSEL_MASK     0x00800000
#define SARADC_CHAR10_CHR1WCIEN_MASK    0x01000000
#define SARADC_CHAR10_CHR0GN_BIT        0  /* CHR0GN<0>: Conversion Characteristic 0 Gain.   */
#define SARADC_CHAR10_CHR0RPT_BIT       1  /* CHR0RPT<3:1>: Conversion Characteristic 0 Repeat Counter. */
#define SARADC_CHAR10_CHR0LS_BIT        4  /* CHR0LS<6:4>: Conversion Characteristic 0 Left-Shift Bits. */
#define SARADC_CHAR10_CHR0RSEL_BIT      7  /* CHR0RSEL<7>: Conversion Characteristic 0 Resolution Selection. */
#define SARADC_CHAR10_CHR0WCIEN_BIT     8  /* CHR0WCIEN<8>: Conversion Characteristic 0 Window Comparator Interrupt Enable. */
#define SARADC_CHAR10_CHR1GN_BIT        16 /* CHR1GN<16>: Conversion Characteristic 1 Gain.  */
#define SARADC_CHAR10_CHR1RPT_BIT       17 /* CHR1RPT<19:17>: Conversion Characteristic 1 Repeat Counter. */
#define SARADC_CHAR10_CHR1LS_BIT        20 /* CHR1LS<22:20>: Conversion Characteristic 1 Left-Shift Bits. */
#define SARADC_CHAR10_CHR1RSEL_BIT      23 /* CHR1RSEL<23>: Conversion Characteristic 1 Resolution Selection. */
#define SARADC_CHAR10_CHR1WCIEN_BIT     24 /* CHR1WCIEN<24>: Conversion Characteristic 1 Window Comparator Interrupt Enable. */
#define SARADC_CHAR10_CHR0GN_UNITY      (0 << SARADC_CHAR10_CHR0GN_BIT)
#define SARADC_CHAR10_CHR0GN_HALF       (1 << SARADC_CHAR10_CHR0GN_BIT)
#define SARADC_CHAR10_CHR0RPT_ACC1      (0 << SARADC_CHAR10_CHR0RPT_BIT)
#define SARADC_CHAR10_CHR0RPT_ACC4      (1 << SARADC_CHAR10_CHR0RPT_BIT)
#define SARADC_CHAR10_CHR0RPT_ACC8      (2 << SARADC_CHAR10_CHR0RPT_BIT)
#define SARADC_CHAR10_CHR0RPT_ACC16     (3 << SARADC_CHAR10_CHR0RPT_BIT)
#define SARADC_CHAR10_CHR0RPT_ACC32     (4 << SARADC_CHAR10_CHR0RPT_BIT)
#define SARADC_CHAR10_CHR0RPT_ACC64     (5 << SARADC_CHAR10_CHR0RPT_BIT)
#define SARADC_CHAR10_CHR0RSEL_B10      (0 << SARADC_CHAR10_CHR0RSEL_BIT)
#define SARADC_CHAR10_CHR0RSEL_B12      (1 << SARADC_CHAR10_CHR0RSEL_BIT)
#define SARADC_CHAR10_CHR0WCIEN_DS      (0 << SARADC_CHAR10_CHR0WCIEN_BIT)
#define SARADC_CHAR10_CHR0WCIEN_EN      (1 << SARADC_CHAR10_CHR0WCIEN_BIT)
#define SARADC_CHAR10_CHR1GN_UNITY      (0 << SARADC_CHAR10_CHR1GN_BIT)
#define SARADC_CHAR10_CHR1GN_HALF       (1 << SARADC_CHAR10_CHR1GN_BIT)
#define SARADC_CHAR10_CHR1RPT_ACC1      (0 << SARADC_CHAR10_CHR1RPT_BIT)
#define SARADC_CHAR10_CHR1RPT_ACC4      (1 << SARADC_CHAR10_CHR1RPT_BIT)
#define SARADC_CHAR10_CHR1RPT_ACC8      (2 << SARADC_CHAR10_CHR1RPT_BIT)
#define SARADC_CHAR10_CHR1RPT_ACC16     (3 << SARADC_CHAR10_CHR1RPT_BIT)
#define SARADC_CHAR10_CHR1RPT_ACC32     (4 << SARADC_CHAR10_CHR1RPT_BIT)
#define SARADC_CHAR10_CHR1RPT_ACC64     (5 << SARADC_CHAR10_CHR1RPT_BIT)
#define SARADC_CHAR10_CHR1RSEL_B10      (0 << SARADC_CHAR10_CHR1RSEL_BIT)
#define SARADC_CHAR10_CHR1RSEL_B12      (1 << SARADC_CHAR10_CHR1RSEL_BIT)
#define SARADC_CHAR10_CHR1WCIEN_DS      (0 << SARADC_CHAR10_CHR1WCIEN_BIT)
#define SARADC_CHAR10_CHR1WCIEN_EN      (1 << SARADC_CHAR10_CHR1WCIEN_BIT)

/** SARADC data register */
#define SARADC_DATA_MASK                0xFFFFFFFF
#define SARADC_DATA_BIT                 0  /* DATA<31:0>: Output Data Word.                  */

/** SARADC window comparator limits register */
#define SARADC_WCLIMITS_WCLT_MASK       0x0000FFFF
#define SARADC_WCLIMITS_WCGT_MASK       0xFFFF0000
#define SARADC_WCLIMITS_WCLT_BIT        0  /* WCLT<15:0>: Less-Than Window Comparator Limit. */
#define SARADC_WCLIMITS_WCGT_BIT        16 /* WCGT<31:16>: Greater-Than Window Comparator Limit. */

/** SARADC accumulator initial value register */
#define SARADC_ACC_MASK                 0x0000FFFF
#define SARADC_ACC_BIT                  0  /* ACC<15:0>: Accumulator Initial Value.          */

/** SARADC status register */
#define SARADC_STATUS_WCI_MASK          0x00000001
#define SARADC_STATUS_SCCI_MASK         0x00000002
#define SARADC_STATUS_SDI_MASK          0x00000004
#define SARADC_STATUS_FORI_MASK         0x00000008
#define SARADC_STATUS_FURI_MASK         0x00000010
#define SARADC_STATUS_WCI_BIT           0  /* WCI<0>: Window Compare Interrupt.              */
#define SARADC_STATUS_SCCI_BIT          1  /* SCCI<1>: Single Conversion Complete Interrupt. */
#define SARADC_STATUS_SDI_BIT           2  /* SDI<2>: Scan Done Interrupt.                   */
#define SARADC_STATUS_FORI_BIT          3  /* FORI<3>: FIFO Overrun Interrupt.               */
#define SARADC_STATUS_FURI_BIT          4  /* FURI<4>: FIFO Underrun Interrupt.              */
#define SARADC_STATUS_WCI_NOT_SET       (0 << SARADC_STATUS_WCI_BIT)
#define SARADC_STATUS_WCI_SET           (1 << SARADC_STATUS_WCI_BIT)
#define SARADC_STATUS_SCCI_NOT_SET      (0 << SARADC_STATUS_SCCI_BIT)
#define SARADC_STATUS_SCCI_SET          (1 << SARADC_STATUS_SCCI_BIT)
#define SARADC_STATUS_SDI_NOT_SET       (0 << SARADC_STATUS_SDI_BIT)
#define SARADC_STATUS_SDI_SET           (1 << SARADC_STATUS_SDI_BIT)
#define SARADC_STATUS_FORI_NOT_SET      (0 << SARADC_STATUS_FORI_BIT)
#define SARADC_STATUS_FORI_SET          (1 << SARADC_STATUS_FORI_BIT)
#define SARADC_STATUS_FURI_NOT_SET      (0 << SARADC_STATUS_FURI_BIT)
#define SARADC_STATUS_FURI_SET          (1 << SARADC_STATUS_FURI_BIT)

/** SARADC FIFO status register */
#define SARADC_FIFOSTATUS_FIFOLVL_MASK  0x0000000F
#define SARADC_FIFOSTATUS_DPSTS_MASK    0x00000010
#define SARADC_FIFOSTATUS_DRDYF_MASK    0x00000020
#define SARADC_FIFOSTATUS_FIFOLVL_BIT   0  /* FIFOLVL<3:0>: FIFO Level.                      */
#define SARADC_FIFOSTATUS_DPSTS_BIT     4  /* DPSTS<4>: Data Packing Status.                 */
#define SARADC_FIFOSTATUS_DRDYF_BIT     5  /* DRDYF<5>: Data Ready Flag.                     */
#define SARADC_FIFOSTATUS_DPSTS_LOWER   (0 << SARADC_FIFOSTATUS_DPSTS_BIT)
#define SARADC_FIFOSTATUS_DPSTS_UPPER   (1 << SARADC_FIFOSTATUS_DPSTS_BIT)
#define SARADC_FIFOSTATUS_DRDYF_NOT_SET (0 << SARADC_FIFOSTATUS_DRDYF_BIT)
#define SARADC_FIFOSTATUS_DRDYF_SET     (1 << SARADC_FIFOSTATUS_DRDYF_BIT)


typedef enum adc_tslot_chnl {
    ADC_CHN_0, ADC_CHN_1, ADC_CHN_2, ADC_CHN_3,
    ADC_CHN_4, ADC_CHN_5, ADC_CHN_6, ADC_CHN_7,
    ADC_CHN_8, ADC_CHN_9, ADC_CHN_10, ADC_CHN_11,
    ADC_CHN_12, ADC_CHN_13, ADC_CHN_14, ADC_CHN_15,
    ADC_CHN_16, ADC_CHN_17, ADC_CHN_18, ADC_CHN_19,
    ADC_CHN_20, ADC_CHN_21, ADC_CHN_22, ADC_CHN_23,
    ADC_CHN_24, ADC_CHN_25, ADC_CHN_26, ADC_CHN_27,
    ADC_CHN_28, ADC_CHN_29, ADC_CHN_30, ADC_CHN_END
}adc_tslot_chnl;

typedef enum adc_grp_num {
    ADC_GRP_0,
    ADC_GRP_1,
    ADC_GRP_2,
    ADC_GRP_3,
}adc_grp_num;

typedef enum adc_bit_res {
    ADC_10_bit,
    ADC_12_bit
}adc_bit_res;

typedef enum adc_smp_cnt {
    ADC_SMPCNT_1,
    ADC_SMPCNT_4,
    ADC_SMPCNT_8,
    ADC_SMPCNT_16,
    ADC_SMPCNT_32,
    ADC_SMPCNT_64,
} adc_smp_cnt;

typedef enum adc_grp_gain {
    ADC_GN_UNITY,
    ADC_GN_HALF,
} adc_grp_gain;


/**
 * @brief STM32F2 external event selectors for regular group
 *        conversion.
 * @see adc_set_extsel()
 */

typedef enum adc_extsel_event {
    ADC_EXT_EV_TIM1_CC1    = 0,
    ADC_EXT_EV_TIM1_CC2    = 1,
    ADC_EXT_EV_TIM1_CC3    = 2,
    ADC_EXT_EV_TIM2_CC2    = 3,
    ADC_EXT_EV_TIM2_CC3    = 4,
    ADC_EXT_EV_TIM2_CC4    = 5,
    ADC_EXT_EV_TIM1_TRGO   = 6,
    ADC_EXT_EV_TIM3_CC1    = 7,
    ADC_EXT_EV_TIM3_TRGO   = 8,
    ADC_EXT_EV_TIM4_CC4    = 9,
    ADC_EXT_EV_TIM5_CC1    = 10,
    ADC_EXT_EV_TIM5_CC2    = 11,
    ADC_EXT_EV_TIM5_CC3    = 12,
    ADC_EXT_EV_TIM8_CC1    = 13,
    ADC_EXT_EV_TIM8_TRGO   = 14,
    ADC_EXT_EV_TIM1_EXTI11 = 15,
} adc_extsel_event;

/**
 * @brief STM32F2 sample times, in ADC clock cycles.
 */
typedef enum adc_smp_rate {
    ADC_SMPR_3,                 /**< 3 ADC cycles */
    ADC_SMPR_15,                /**< 15 ADC cycles */
    ADC_SMPR_28,                /**< 28 ADC cycles */
    ADC_SMPR_56,                /**< 56 ADC cycles */
    ADC_SMPR_84,                /**< 84 ADC cycles */
    ADC_SMPR_112,               /**< 112 ADC cycles */
    ADC_SMPR_144,               /**< 144 ADC cycles */
    ADC_SMPR_480,               /**< 480 ADC cycles */
} adc_smp_rate;

/**
 * @brief STM32F2 ADC prescalers, as divisors of PCLK2.
 */
typedef enum adc_prescaler {
    /** PCLK2 divided by 2 */
    ADC_PRE_PCLK2_DIV_2 = 0,
    /** PCLK2 divided by 4 */
    ADC_PRE_PCLK2_DIV_4 = 1,
    /** PCLK2 divided by 6 */
    ADC_PRE_PCLK2_DIV_6 = 2,
    /** PCLK2 divided by 8 */
    ADC_PRE_PCLK2_DIV_8 = 3,
} adc_prescaler;

#ifdef __cplusplus
}
#endif

#endif
