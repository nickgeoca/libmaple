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
 * @file libmaple/stm32f2/include/series/flash.h
 * @brief STM32F2 Flash header.
 *
 * Provides register map, base pointer, and register bit definitions
 * for the Flash controller on the STM32F2 series, along with
 * series-specific configuration values.
 */

#ifndef _LIBMAPLE_SIM3U1_FLASH_H_
#define _LIBMAPLE_SIM3U1_FLASH_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Register map
 */

/** @brief SiM3U1 Flash register map type */
typedef struct flash_reg_map {
   __io uint32  CFGR;       /**< Configuration Register */
   __io uint32  CFGR_SET;   /**< Configuration Register */
   __io uint32  CFGR_CLR;   /**< Configuration Register */
   uint32       reserved0;
   uint32       reserved1[4];
   uint32       reserved2[4];
   uint32       reserved3[4];
   uint32       reserved4[4];
   uint32       reserved5[4];
   uint32       reserved6[4];
   uint32       reserved7[4];
   uint32       reserved8[4];
   uint32       reserved9[4];
   __io uint32  WRADDRR;        /**< Configuration Register */
   uint32       reserved10;
   uint32       reserved11;
   uint32       reserved12;
   __io uint32  WRDATAR;        /**< Configuration Register */
   uint32       reserved13;
   uint32       reserved14;
   uint32       reserved15;
   __io uint32  KEYR;           /**< Configuration Register */
   uint32       reserved16;
   uint32       reserved17;
   uint32       reserved18;
   __io uint32  TCR;      /**< Configuration Register */
   uint32       reserved19;
   uint32       reserved20;
   uint32       reserved21;
   uint32       reserved22[4];
   uint32       reserved23[4];
   uint32       reserved24[4];
   uint32       reserved25[4];
   uint32       reserved26[4];
   uint32       reserved27[4];
   uint32       reserved28[4];
   uint32       reserved29[4];
} flash_reg_map;

#define FLASH_BASE                      ((struct flash_reg_map*)0x4002E000)

/* Configuration register */
#define FLASH_CFGR_SPMD_MASK      0x00000003
#define FLASH_CFGR_RDSEN_MASK     0x00000010
#define FLASH_CFGR_DPFEN_MASK     0x00000040
#define FLASH_CFGR_PFINH_MASK     0x00000080
#define FLASH_CFGR_SQWEN_MASK     0x00010000
#define FLASH_CFGR_ERASEEN_MASK   0x00040000
#define FLASH_CFGR_BUFSTS_MASK    0x00080000
#define FLASH_CFGR_BUSYF_MASK     0x00100000

#define FLASH_CFGR_SPMD_BIT       0  /* SPMD<1:0>: Flash Speed Mode.                   */
#define FLASH_CFGR_RDSEN_BIT      4  /* RDSEN<4>: Read Store Mode Enable.              */
#define FLASH_CFGR_DPFEN_BIT      6  /* DPFEN<6>: Data Prefetch Enable.                */
#define FLASH_CFGR_PFINH_BIT      7  /* PFINH<7>: Prefetch Inhibit.                    */
#define FLASH_CFGR_SQWEN_BIT      16 /* SQWEN<16>: Flash Write Sequence Enable.        */
#define FLASH_CFGR_ERASEEN_BIT    18 /* ERASEEN<18>: Flash Page Erase Enable.          */
#define FLASH_CFGR_BUFSTS_BIT     19 /* BUFSTS<19>: Flash Buffer Status.               */
#define FLASH_CFGR_BUSYF_BIT      20 /* BUSYF<20>: Flash Operation Busy Flag.          */

#define FLASH_CFGR_SPMD_MODE0     (0 << FLASH_CFGR_SPMD_BIT)
#define FLASH_CFGR_SPMD_MODE1     (1 << FLASH_CFGR_SPMD_BIT)
#define FLASH_CFGR_SPMD_MODE2     (2 << FLASH_CFGR_SPMD_BIT)
#define FLASH_CFGR_SPMD_MODE3     (3 << FLASH_CFGR_SPMD_BIT)
#define FLASH_CFGR_RDSEN_DS       (0 << FLASH_CFGR_RDSEN_BIT)
#define FLASH_CFGR_RDSEN_EN       (1 << FLASH_CFGR_RDSEN_BIT)
#define FLASH_CFGR_DPFEN_DS       (0 << FLASH_CFGR_DPFEN_BIT)
#define FLASH_CFGR_DPFEN_EN       (1 << FLASH_CFGR_DPFEN_BIT)
#define FLASH_CFGR_PFINH_INACTV   (0 << FLASH_CFGR_PFINH_BIT)
#define FLASH_CFGR_PFINH_ACTV     (1 << FLASH_CFGR_PFINH_BIT)
#define FLASH_CFGR_SQWEN_DS       (0 << FLASH_CFGR_SQWEN_BIT)
#define FLASH_CFGR_SQWEN_EN       (1 << FLASH_CFGR_SQWEN_BIT)
#define FLASH_CFGR_ERASEEN_DS     (0 << FLASH_CFGR_ERASEEN_BIT)
#define FLASH_CFGR_ERASEEN_EN     (1 << FLASH_CFGR_ERASEEN_BIT)
#define FLASH_CFGR_BUFSTS_EMPTY   (0 << FLASH_CFGR_BUFSTS_BIT)
#define FLASH_CFGR_BUFSTS_FULL    (1 << FLASH_CFGR_BUFSTS_BIT)
#define FLASH_CFGR_BUSYF_NOT_SET  (0 << FLASH_CFGR_BUSYF_BIT)
#define FLASH_CFGR_BUSYF_SET      (1 << FLASH_CFGR_BUSYF_BIT)


/* Write Address register */
#define FLASH_WRADDRR_MASK        0xFFFFFFFF

#define FLASH_WRADDRR_BIT         0  /* WRADDR<31:0>: Flash Write Address.             */


/* Write Data register */
#define FLASH_WRDATAR_MASK        0xFFFFFFFF

#define FLASH_WRDATAR_BIT         0  /* WRDATA<31:0>: Flash Write Data.                */


/* Modification Key register */
#define FLASH_KEYR_MASK           0x000000FF

#define FLASH_KEYR_BIT            0  /* KEY<7:0>: Flash Key.                           */

#define FLASH_KEYR_MULTI_LOCK     (90 << FLASH_KEYR_BIT)
#define FLASH_KEYR_INITIAL_UNLOCK (165 << FLASH_KEYR_BIT)
#define FLASH_KEYR_SINGLE_UNLOCK  (241 << FLASH_KEYR_BIT)
#define FLASH_KEYR_MULTI_UNLOCK   (242 << FLASH_KEYR_BIT)


/* Timing Control register */
#define FLASH_TCR_FLRTMD_MASK     0x00000040

#define FLASH_TCR_FLRTMD_BIT      6  /* FLRTMD<6>: Flash Read Timing Mode.             */

#define FLASH_TCR_FLRTMD_SLOW     (0 << FLASH_TCR_FLRTMD_BIT)
#define FLASH_TCR_FLRTMD_FAST     (1 << FLASH_TCR_FLRTMD_BIT)

/*
 * Series-specific configuration values
 */

/* Note that this value depends on a 2.7V--3.6V supply voltage */
#define FLASH_SAFE_WAIT_STATES          FLASH_WAIT_STATE_3

/* Flash memory features available via ACR. */
enum {
    FLASH_PREFETCH = FLASH_CFGR_PFINH_INACTV,
    FLASH_ICACHE   = 0,
    FLASH_DCACHE   = FLASH_CFGR_DPFEN_EN,
};


#ifdef __cplusplus
}
#endif

#endif
