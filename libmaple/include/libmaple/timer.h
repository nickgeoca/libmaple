/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
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
 * @file   libmaple/include/libmaple/timer.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Timer interface.
 */

#ifndef _LIBMAPLE_TIMER_H_
#define _LIBMAPLE_TIMER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <series/timer.h>
#include <libmaple/libmaple.h>
#include <libmaple/rcc.h>
#include <libmaple/nvic.h>
#include <libmaple/bitband.h>

/*
 * Register maps
 */

/** Advanced control timer register map type */
typedef struct timer_reg_map {
    __io uint32 MODE; // Base Address + 0x0
    uint32      reserved0;
    uint32      reserved1;
    uint32      reserved2;
    __io uint32 CONTROL; // Base Address + 0x10
    __io uint32 CONTROL_SET;
    __io uint32 CONTROL_CLR;
    uint32      reserved3;
    __io uint32 STATUS; // Base Address + 0x20
    __io uint32 STATUS_SET;
    __io uint32 STATUS_CLR;
    uint32      reserved4;
    __io uint32 COUNTER; // Base Address + 0x30
    uint32      reserved5;
    uint32      reserved6;
    uint32      reserved7;
    __io uint32 LIMIT; // Base Address + 0x40
    uint32      reserved8;
    uint32      reserved9;
    union {
        struct {
            uint32      reserved10;
            __io uint32 LIMITUPD; // Base Address + 0x50
            uint32      reserved11;
            uint32      reserved12;
            uint32      reserved13;
            __io uint32 DTIME; // Base Address + 0x60
            uint32      reserved14;
            uint32      reserved15;
            uint32      reserved16;
            uint32      reserved17[4];
            __io uint32 DTARGET; // Base Address + 0x80
            uint32      reserved18;
            uint32      reserved19;
            uint32      reserved20;
        } adv;
        struct {
            uint32      reserved10;
        } gen;
    };
} timer_reg_map;

typedef struct timer_basic_reg_map
{
   __io uint32 CONFIG; // Base Address + 0x0
   __io uint32 CONFIG_SET;
   __io uint32 CONFIG_CLR;
   uint32      reserved0;
   __io uint32 CLKDIV; // Base Address + 0x10
   uint32      reserved1;
   uint32      reserved2;
   uint32      reserved3;
   __io uint32 COUNT; // Base Address + 0x20
   uint32      reserved4;
   uint32      reserved5;
   uint32      reserved6;
   __io uint32 CAPTURE; // Base Address + 0x30
   uint32      reserved7;
   uint32      reserved8;
   uint32      reserved9;
} timer_basic_reg_map;


typedef struct timer_chnl_reg_map {
   __io uint32 MODE; // Base Address + 0x0
   uint32      reserved0;
   uint32      reserved1;
   uint32      reserved2;
   __io uint32 CONTROL; // Base Address + 0x10
   __io uint32 CONTROL_SET;
   __io uint32 CONTROL_CLR;
   uint32      reserved3;
   __io uint32 CCAPV; // Base Address + 0x20
   uint32      reserved4;
   uint32      reserved5;
   uint32      reserved6;
   __io uint32 CCAPVUPD; // Base Address + 0x30
   uint32      reserved7;
   uint32      reserved8;
   uint32      reserved9;
} timer_chnl_reg_map;

#define TIMER1_CH0 ((timer_chnl_reg_map*)0x4000E000)
#define TIMER1_CH1 ((timer_chnl_reg_map*)0x4000E040)
#define TIMER1_CH2 ((timer_chnl_reg_map*)0x4000E080)
#define TIMER1_CH3 ((timer_chnl_reg_map*)0x4000E0C0)
#define TIMER1_CH4 ((timer_chnl_reg_map*)0x4000E100)
#define TIMER1_CH5 ((timer_chnl_reg_map*)0x4000E140)
#define TIMER2_CH0 ((timer_chnl_reg_map*)0x4000F000)
#define TIMER2_CH1 ((timer_chnl_reg_map*)0x4000F040)
#define TIMER3_CH0 ((timer_chnl_reg_map*)0x40010000)
#define TIMER3_CH1 ((timer_chnl_reg_map*)0x40010040)

/**
 * @brief Timer type
 *
 * Type marker for timer_dev.
 *
 * @see timer_dev
 */
typedef enum timer_type {
    TIMER_ADVANCED,             /**< Advanced type */
    TIMER_GENERAL,              /**< General purpose type */
    TIMER_BASIC,                /**< Basic timer */
} timer_type;

/** Timer device type */
typedef struct timer_dev {
    timer_reg_map *regs;         /**< Register map */
    clk_dev_id clk_id;          /**< RCC clock information */
    timer_type type;            /**< Timer's type */
    nvic_irqs_t nvic_irqs;            /**<  */
    timer_chnl_reg_map **chnl_regs;
    voidFuncPtr handlers[];
} timer_dev;

extern timer_dev *TIMER1;
extern timer_dev *TIMER2;
extern timer_dev *TIMER3;
extern timer_dev *TIMER4;
extern timer_dev *TIMER5;

/*
 * Register bit definitions
 */
#define EPCA_MODE_CLKDIV_MASK              0x000003FF
#define EPCA_MODE_CLKSEL_MASK              0x00001C00
#define EPCA_MODE_HDOSEL_MASK              0x0000C000
#define EPCA_MODE_DEND_MASK                0x00070000
#define EPCA_MODE_DPTR_MASK                0x00380000
#define EPCA_MODE_DSTART_MASK              0x01C00000
#define EPCA_MODE_DBUSYF_MASK              0x02000000
#define EPCA_MODE_STDOSEL_MASK             0x18000000
#define EPCA_MODE_CLKDIV_BIT               0  /* CLKDIV<9:0>: Input Clock Divider.              */
#define EPCA_MODE_CLKSEL_BIT               10 /* CLKSEL<12:10>: Input Clock (FCLKIN) Select.    */
#define EPCA_MODE_HDOSEL_BIT               14 /* HDOSEL<15:14>: High Drive Port Bank Output Select. */
#define EPCA_MODE_DEND_BIT                 16 /* DEND<18:16>: DMA Write End Index.              */
#define EPCA_MODE_DPTR_BIT                 19 /* DPTR<21:19>: DMA Write Transfer Pointer.       */
#define EPCA_MODE_DSTART_BIT               22 /* DSTART<24:22>: DMA Target Start Index.         */
#define EPCA_MODE_DBUSYF_BIT               25 /* DBUSYF<25>: DMA Busy Flag.                     */
#define EPCA_MODE_STDOSEL_BIT              27 /* STDOSEL<28:27>: Standard Port Bank Output Select. */
#define EPCA_MODE_CLKSEL_APB               (0 << EPCA_MODE_CLKSEL_BIT)
#define EPCA_MODE_CLKSEL_TIMER0            (1 << EPCA_MODE_CLKSEL_BIT)
#define EPCA_MODE_CLKSEL_HL_ECI            (2 << EPCA_MODE_CLKSEL_BIT)
#define EPCA_MODE_CLKSEL_EXTOSCN           (3 << EPCA_MODE_CLKSEL_BIT)
#define EPCA_MODE_CLKSEL_ECI               (4 << EPCA_MODE_CLKSEL_BIT)
#define EPCA_MODE_HDOSEL_THREE_DIFF        (0 << EPCA_MODE_HDOSEL_BIT)
#define EPCA_MODE_HDOSEL_TWO_DIFF          (1 << EPCA_MODE_HDOSEL_BIT)
#define EPCA_MODE_HDOSEL_ONE_DIFF          (2 << EPCA_MODE_HDOSEL_BIT)
#define EPCA_MODE_HDOSEL_NO_DIFF           (3 << EPCA_MODE_HDOSEL_BIT)
#define EPCA_MODE_DEND_LIMIT               (0 << EPCA_MODE_DEND_BIT)
#define EPCA_MODE_DEND_CH0                 (1 << EPCA_MODE_DEND_BIT)
#define EPCA_MODE_DEND_CH1                 (2 << EPCA_MODE_DEND_BIT)
#define EPCA_MODE_DEND_CH2                 (3 << EPCA_MODE_DEND_BIT)
#define EPCA_MODE_DEND_CH3                 (4 << EPCA_MODE_DEND_BIT)
#define EPCA_MODE_DEND_CH4                 (5 << EPCA_MODE_DEND_BIT)
#define EPCA_MODE_DEND_CH5                 (6 << EPCA_MODE_DEND_BIT)
#define EPCA_MODE_DEND_EMPTY               (7 << EPCA_MODE_DEND_BIT)
#define EPCA_MODE_DPTR_LIMIT               (0 << EPCA_MODE_DPTR_BIT)
#define EPCA_MODE_DPTR_CH0                 (1 << EPCA_MODE_DPTR_BIT)
#define EPCA_MODE_DPTR_CH1                 (2 << EPCA_MODE_DPTR_BIT)
#define EPCA_MODE_DPTR_CH2                 (3 << EPCA_MODE_DPTR_BIT)
#define EPCA_MODE_DPTR_CH3                 (4 << EPCA_MODE_DPTR_BIT)
#define EPCA_MODE_DPTR_CH4                 (5 << EPCA_MODE_DPTR_BIT)
#define EPCA_MODE_DPTR_CH5                 (6 << EPCA_MODE_DPTR_BIT)
#define EPCA_MODE_DPTR_EMPTY               (7 << EPCA_MODE_DPTR_BIT)
#define EPCA_MODE_DSTART_LIMIT             (0 << EPCA_MODE_DSTART_BIT)
#define EPCA_MODE_DSTART_CH0               (1 << EPCA_MODE_DSTART_BIT)
#define EPCA_MODE_DSTART_CH1               (2 << EPCA_MODE_DSTART_BIT)
#define EPCA_MODE_DSTART_CH2               (3 << EPCA_MODE_DSTART_BIT)
#define EPCA_MODE_DSTART_CH3               (4 << EPCA_MODE_DSTART_BIT)
#define EPCA_MODE_DSTART_CH4               (5 << EPCA_MODE_DSTART_BIT)
#define EPCA_MODE_DSTART_CH5               (6 << EPCA_MODE_DSTART_BIT)
#define EPCA_MODE_DSTART_EMPTY             (7 << EPCA_MODE_DSTART_BIT)
#define EPCA_MODE_DBUSYF_IDLE              (0 << EPCA_MODE_DBUSYF_BIT)
#define EPCA_MODE_DBUSYF_BUSY              (1 << EPCA_MODE_DBUSYF_BIT)
#define EPCA_MODE_STDOSEL_NO_DIFF          (0 << EPCA_MODE_STDOSEL_BIT)
#define EPCA_MODE_STDOSEL_ONE_DIFF         (1 << EPCA_MODE_STDOSEL_BIT)
#define EPCA_MODE_STDOSEL_TWO_DIFF         (2 << EPCA_MODE_STDOSEL_BIT)
#define EPCA_MODE_STDOSEL_THREE_DIFF       (3 << EPCA_MODE_STDOSEL_BIT)

#define EPCA_CR_OVFIEN_MASK                0x00000001
#define EPCA_CR_OVFDEN_MASK                0x00000002
#define EPCA_CR_OVFSEN_MASK                0x00000004
#define EPCA_CR_HALTIEN_MASK               0x00000008
#define EPCA_CR_NOUPD_MASK                 0x00000010
#define EPCA_CR_IDLEBEN_MASK               0x00000020
#define EPCA_CR_DBGMD_MASK                 0x00000040
#define EPCA_CR_HALTEN_MASK                0x00000200
#define EPCA_CR_STSEL_MASK                 0x00001800
#define EPCA_CR_STESEL_MASK                0x00002000
#define EPCA_CR_STEN_MASK                  0x00004000
#define EPCA_CR_DIVST_MASK                 0x00200000
#define EPCA_CR_DIV_MASK                   0xFFC00000
#define EPCA_CR_OVFIEN_BIT                 0  /* OVFIEN<0>: EPCA Counter Overflow/Limit Interrupt Enable. */
#define EPCA_CR_OVFDEN_BIT                 1  /* OVFDEN<1>: EPCA Counter Overflow/Limit DMA Request Enable. */
#define EPCA_CR_OVFSEN_BIT                 2  /* OVFSEN<2>: EPCA Counter Overflow/Limit Synchronization Signal Enable. */
#define EPCA_CR_HALTIEN_BIT                3  /* HALTIEN<3>: EPCA Halt Input Interrupt Enable.  */
#define EPCA_CR_NOUPD_BIT                  4  /* NOUPD<4>: Internal Register Update Inhibit.    */
#define EPCA_CR_IDLEBEN_BIT                5  /* IDLEBEN<5>: Idle Bypass Enable.                */
#define EPCA_CR_DBGMD_BIT                  6  /* DBGMD<6>: EPCA Debug Mode.                     */
#define EPCA_CR_HALTEN_BIT                 9  /* HALTEN<9>: Halt Input Enable.                  */
#define EPCA_CR_STSEL_BIT                  11 /* STSEL<12:11>: Synchronous Input Trigger Select. */
#define EPCA_CR_STESEL_BIT                 13 /* STESEL<13>: Synchronous Input Trigger Edge Select. */
#define EPCA_CR_STEN_BIT                   14 /* STEN<14>: Synchronous Input Trigger Enable.    */
#define EPCA_CR_DIVST_BIT                  21 /* DIVST<21>: Clock Divider Output State.         */
#define EPCA_CR_DIV_BIT                    22 /* DIV<31:22>: Current Clock Divider Count.       */
#define EPCA_CR_OVFIEN_DS                  (0 << EPCA_CR_OVFIEN_BIT)
#define EPCA_CR_OVFIEN_EN                  (1 << EPCA_CR_OVFIEN_BIT)
#define EPCA_CR_OVFDEN_DS                  (0 << EPCA_CR_OVFDEN_BIT)
#define EPCA_CR_OVFDEN_EN                  (1 << EPCA_CR_OVFDEN_BIT)
#define EPCA_CR_OVFSEN_DS                  (0 << EPCA_CR_OVFSEN_BIT)
#define EPCA_CR_OVFSEN_EN                  (1 << EPCA_CR_OVFSEN_BIT)
#define EPCA_CR_HALTIEN_DS                 (0 << EPCA_CR_HALTIEN_BIT)
#define EPCA_CR_HALTIEN_EN                 (1 << EPCA_CR_HALTIEN_BIT)
#define EPCA_CR_NOUPD_INACTV               (0 << EPCA_CR_NOUPD_BIT)
#define EPCA_CR_NOUPD_ACTV                 (1 << EPCA_CR_NOUPD_BIT)
#define EPCA_CR_IDLEBEN_DS                 (0 << EPCA_CR_IDLEBEN_BIT)
#define EPCA_CR_IDLEBEN_EN                 (1 << EPCA_CR_IDLEBEN_BIT)
#define EPCA_CR_DBGMD_HALT                 (0 << EPCA_CR_DBGMD_BIT)
#define EPCA_CR_DBGMD_RUN                  (1 << EPCA_CR_DBGMD_BIT)
#define EPCA_CR_HALTEN_DS                  (0 << EPCA_CR_HALTEN_BIT)
#define EPCA_CR_HALTEN_EN                  (1 << EPCA_CR_HALTEN_BIT)
#define EPCA_CR_STSEL_EPCANT0              (0 << EPCA_CR_STSEL_BIT)
#define EPCA_CR_STSEL_EPCANT1              (1 << EPCA_CR_STSEL_BIT)
#define EPCA_CR_STSEL_EPCANT2              (2 << EPCA_CR_STSEL_BIT)
#define EPCA_CR_STSEL_EPCANT3              (3 << EPCA_CR_STSEL_BIT)
#define EPCA_CR_STESEL_FALLING             (0 << EPCA_CR_STESEL_BIT)
#define EPCA_CR_STESEL_RISING              (1 << EPCA_CR_STESEL_BIT)
#define EPCA_CR_STEN_DS                    (0 << EPCA_CR_STEN_BIT)
#define EPCA_CR_STEN_EN                    (1 << EPCA_CR_STEN_BIT)
#define EPCA_CR_DIVST_OUTPUT_HIGH          (0 << EPCA_CR_DIVST_BIT)
#define EPCA_CR_DIVST_OUTPUT_LOW           (1 << EPCA_CR_DIVST_BIT)

#define EPCA_STATUS_C0CCI_MASK             0x00000001
#define EPCA_STATUS_C1CCI_MASK             0x00000002
#define EPCA_STATUS_C2CCI_MASK             0x00000004
#define EPCA_STATUS_C3CCI_MASK             0x00000008
#define EPCA_STATUS_C4CCI_MASK             0x00000010
#define EPCA_STATUS_C5CCI_MASK             0x00000020
#define EPCA_STATUS_RUN_MASK               0x00000040
#define EPCA_STATUS_OVFI_MASK              0x00000080
#define EPCA_STATUS_UPDCF_MASK             0x00000100
#define EPCA_STATUS_HALTI_MASK             0x00000200
#define EPCA_STATUS_C0IOVFI_MASK           0x00000400
#define EPCA_STATUS_C1IOVFI_MASK           0x00000800
#define EPCA_STATUS_C2IOVFI_MASK           0x00001000
#define EPCA_STATUS_C3IOVFI_MASK           0x00002000
#define EPCA_STATUS_C4IOVFI_MASK           0x00004000
#define EPCA_STATUS_C5IOVFI_MASK           0x00008000
#define EPCA_STATUS_C0CCI_BIT              0  /* C0CCI<0>: Channel 0 Capture/Compare Interrupt Flag. */
#define EPCA_STATUS_C1CCI_BIT              1  /* C1CCI<1>: Channel 1 Capture/Compare Interrupt Flag. */
#define EPCA_STATUS_C2CCI_BIT              2  /* C2CCI<2>: Channel 2 Capture/Compare Interrupt Flag. */
#define EPCA_STATUS_C3CCI_BIT              3  /* C3CCI<3>: Channel 3 Capture/Compare Interrupt Flag. */
#define EPCA_STATUS_C4CCI_BIT              4  /* C4CCI<4>: Channel 4 Capture/Compare Interrupt Flag. */
#define EPCA_STATUS_C5CCI_BIT              5  /* C5CCI<5>: Channel 5 Capture/Compare Interrupt Flag. */
#define EPCA_STATUS_RUN_BIT                6  /* RUN<6>: Counter/Timer Run.                     */
#define EPCA_STATUS_OVFI_BIT               7  /* OVFI<7>: Counter/Timer Overflow/Limit Interrupt Flag. */
#define EPCA_STATUS_UPDCF_BIT              8  /* UPDCF<8>: Register Update Complete Flag.       */
#define EPCA_STATUS_HALTI_BIT              9  /* HALTI<9>: Halt Input Interrupt Flag.           */
#define EPCA_STATUS_C0IOVFI_BIT            10 /* C0IOVFI<10>: Channel 0 Intermediate Overflow Interrupt Flag. */
#define EPCA_STATUS_C1IOVFI_BIT            11 /* C1IOVFI<11>: Channel 1 Intermediate Overflow Interrupt Flag. */
#define EPCA_STATUS_C2IOVFI_BIT            12 /* C2IOVFI<12>: Channel 2 Intermediate Overflow Interrupt Flag. */
#define EPCA_STATUS_C3IOVFI_BIT            13 /* C3IOVFI<13>: Channel 3 Intermediate Overflow Interrupt Flag. */
#define EPCA_STATUS_C4IOVFI_BIT            14 /* C4IOVFI<14>: Channel 4 Intermediate Overflow Interrupt Flag. */
#define EPCA_STATUS_C5IOVFI_BIT            15 /* C5IOVFI<15>: Channel 5 Intermediate Overflow Interrupt Flag. */
#define EPCA_STATUS_C0CCI_NOT_SET          (0 << EPCA_STATUS_C0CCI_BIT)
#define EPCA_STATUS_C0CCI_SET              (1 << EPCA_STATUS_C0CCI_BIT)
#define EPCA_STATUS_C1CCI_NOT_SET          (0 << EPCA_STATUS_C1CCI_BIT)
#define EPCA_STATUS_C1CCI_SET              (1 << EPCA_STATUS_C1CCI_BIT)
#define EPCA_STATUS_C2CCI_NOT_SET          (0 << EPCA_STATUS_C2CCI_BIT)
#define EPCA_STATUS_C2CCI_SET              (1 << EPCA_STATUS_C2CCI_BIT)
#define EPCA_STATUS_C3CCI_NOT_SET          (0 << EPCA_STATUS_C3CCI_BIT)
#define EPCA_STATUS_C3CCI_SET              (1 << EPCA_STATUS_C3CCI_BIT)
#define EPCA_STATUS_C4CCI_NOT_SET          (0 << EPCA_STATUS_C4CCI_BIT)
#define EPCA_STATUS_C4CCI_SET              (1 << EPCA_STATUS_C4CCI_BIT)
#define EPCA_STATUS_C5CCI_NOT_SET          (0 << EPCA_STATUS_C5CCI_BIT)
#define EPCA_STATUS_C5CCI_SET              (1 << EPCA_STATUS_C5CCI_BIT)
#define EPCA_STATUS_RUN_STOP               (0 << EPCA_STATUS_RUN_BIT)
#define EPCA_STATUS_RUN_START              (1 << EPCA_STATUS_RUN_BIT)
#define EPCA_STATUS_OVFI_NOT_SET           (0 << EPCA_STATUS_OVFI_BIT)
#define EPCA_STATUS_OVFI_SET               (1 << EPCA_STATUS_OVFI_BIT)
#define EPCA_STATUS_UPDCF_EMPTY            (0 << EPCA_STATUS_UPDCF_BIT)
#define EPCA_STATUS_UPDCF_FULL             (1 << EPCA_STATUS_UPDCF_BIT)
#define EPCA_STATUS_HALTI_NOT_SET          (0 << EPCA_STATUS_HALTI_BIT)
#define EPCA_STATUS_HALTI_SET              (1 << EPCA_STATUS_HALTI_BIT)
#define EPCA_STATUS_C0IOVFI_NOT_SET        (0 << EPCA_STATUS_C0IOVFI_BIT)
#define EPCA_STATUS_C0IOVFI_SET            (1 << EPCA_STATUS_C0IOVFI_BIT)
#define EPCA_STATUS_C1IOVFI_NOT_SET        (0 << EPCA_STATUS_C1IOVFI_BIT)
#define EPCA_STATUS_C1IOVFI_SET            (1 << EPCA_STATUS_C1IOVFI_BIT)
#define EPCA_STATUS_C2IOVFI_NOT_SET        (0 << EPCA_STATUS_C2IOVFI_BIT)
#define EPCA_STATUS_C2IOVFI_SET            (1 << EPCA_STATUS_C2IOVFI_BIT)
#define EPCA_STATUS_C3IOVFI_NOT_SET        (0 << EPCA_STATUS_C3IOVFI_BIT)
#define EPCA_STATUS_C3IOVFI_SET            (1 << EPCA_STATUS_C3IOVFI_BIT)
#define EPCA_STATUS_C4IOVFI_NOT_SET        (0 << EPCA_STATUS_C4IOVFI_BIT)
#define EPCA_STATUS_C4IOVFI_SET            (1 << EPCA_STATUS_C4IOVFI_BIT)
#define EPCA_STATUS_C5IOVFI_NOT_SET        (0 << EPCA_STATUS_C5IOVFI_BIT)
#define EPCA_STATUS_C5IOVFI_SET            (1 << EPCA_STATUS_C5IOVFI_BIT)


#define EPCA_COUNTER_MASK                  0x0000FFFF
#define EPCA_COUNTER_BIT                   0  /* COUNTER<15:0>: Counter/Timer.                  */

#define EPCA_LIMIT_MASK                    0x0000FFFF
#define EPCA_LIMIT_BIT                     0  /* LIMIT<15:0>: Upper Limit.                      */


#define EPCA_LIMITUPD_MASK                 0x0000FFFF
#define EPCA_LIMITUPD_BIT                  0  /* LIMITUPD<15:0>: Module Upper Limit Update Value. */

#define EPCA_DTIME_DTIMEX_MASK             0x000000FF
#define EPCA_DTIME_DTIMEY_MASK             0x0000FF00
#define EPCA_DTIME_DTIMEX_BIT              0  /* DTIMEX<7:0>: X Phase Delay Time.               */
#define EPCA_DTIME_DTIMEY_BIT              8  /* DTIMEY<15:8>: Y Phase Delay Time.              */

#define EPCA_DTARGET_MASK                  0xFFFFFFFF
#define EPCA_DTARGET_BIT                   0  /* DTARGET<31:0>: DMA Transfer Target.            */


#define EPCACH_MODE_COSEL_MASK             0x00000003
#define EPCACH_MODE_PWMMD_MASK             0x0000003C
#define EPCACH_MODE_DIFGEN_MASK            0x00000040
#define EPCACH_MODE_CMD_MASK               0x00000700
#define EPCACH_MODE_COSEL_BIT              0
#define EPCACH_MODE_PWMMD_BIT              2
#define EPCACH_MODE_DIFGEN_BIT             6
#define EPCACH_MODE_CMD_BIT                8
#define EPCACH_MODE_COSEL_TOGGLE_OUTPUT    (0 << EPCACH_MODE_COSEL_BIT)
#define EPCACH_MODE_COSEL_SET_OUTPUT       (1 << EPCACH_MODE_COSEL_BIT)
#define EPCACH_MODE_COSEL_CLEAR_OUTPUT     (2 << EPCACH_MODE_COSEL_BIT)
#define EPCACH_MODE_COSEL_NO_CHANGE        (3 << EPCACH_MODE_COSEL_BIT)
#define EPCACH_MODE_DIFGEN_DS              (0 << EPCACH_MODE_DIFGEN_BIT)
#define EPCACH_MODE_DIFGEN_EN              (1 << EPCACH_MODE_DIFGEN_BIT)
#define EPCACH_MODE_CMD_EDGE_PWM           (0 << EPCACH_MODE_CMD_BIT)
#define EPCACH_MODE_CMD_CENTER_ALIGNED_PWM (1 << EPCACH_MODE_CMD_BIT)
#define EPCACH_MODE_CMD_HF_SQUARE_WAVE     (2 << EPCACH_MODE_CMD_BIT)
#define EPCACH_MODE_CMD_TIMER_CAPTURE      (3 << EPCACH_MODE_CMD_BIT)
#define EPCACH_MODE_CMD_N_BIT_PWM          (4 << EPCACH_MODE_CMD_BIT)

#define EPCACH_CR_COUTST_MASK              0x00000001
#define EPCACH_CR_CPCAPEN_MASK             0x00000002
#define EPCACH_CR_CNCAPEN_MASK             0x00000004
#define EPCACH_CR_CUPDCF_MASK              0x00000008
#define EPCACH_CR_YPHST_MASK               0x00000020
#define EPCACH_CR_ACTVPH_MASK              0x00000040
#define EPCACH_CR_XPHST_MASK               0x00000080
#define EPCACH_CR_CCIEN_MASK               0x00000100
#define EPCACH_CR_CCDEN_MASK               0x00000200
#define EPCACH_CR_CCSEN_MASK               0x00000400
#define EPCACH_CR_CIOVFIEN_MASK            0x00000800
#define EPCACH_CR_CIOVFDEN_MASK            0x00001000
#define EPCACH_CR_CIOVFSEN_MASK            0x00002000
#define EPCACH_CR_COUTST_BIT               0
#define EPCACH_CR_CPCAPEN_BIT              1
#define EPCACH_CR_CNCAPEN_BIT              2
#define EPCACH_CR_CUPDCF_BIT               3
#define EPCACH_CR_YPHST_BIT                5
#define EPCACH_CR_ACTVPH_BIT               6
#define EPCACH_CR_XPHST_BIT                7
#define EPCACH_CR_CCIEN_BIT                8
#define EPCACH_CR_CCDEN_BIT                9
#define EPCACH_CR_CCSEN_BIT                10
#define EPCACH_CR_CIOVFIEN_BIT             11
#define EPCACH_CR_CIOVFDEN_BIT             12
#define EPCACH_CR_CIOVFSEN_BIT             13
#define EPCACH_CR_COUTST_LOW               (0 << EPCACH_CR_COUTST_BIT)
#define EPCACH_CR_COUTST_HIGH              (1 << EPCACH_CR_COUTST_BIT)
#define EPCACH_CR_CPCAPEN_DS               (0 << EPCACH_CR_CPCAPEN_BIT)
#define EPCACH_CR_CPCAPEN_EN               (1 << EPCACH_CR_CPCAPEN_BIT)
#define EPCACH_CR_CNCAPEN_DS               (0 << EPCACH_CR_CNCAPEN_BIT)
#define EPCACH_CR_CNCAPEN_EN               (1 << EPCACH_CR_CNCAPEN_BIT)
#define EPCACH_CR_CUPDCF_NOT_SET           (0 << EPCACH_CR_CUPDCF_BIT)
#define EPCACH_CR_CUPDCF_SET               (1 << EPCACH_CR_CUPDCF_BIT)
#define EPCACH_CR_YPHST_LOW                (0 << EPCACH_CR_YPHST_BIT)
#define EPCACH_CR_YPHST_HIGH               (1 << EPCACH_CR_YPHST_BIT)
#define EPCACH_CR_ACTVPH_YACTIVE           (0 << EPCACH_CR_ACTVPH_BIT)
#define EPCACH_CR_ACTVPH_XACTIVE           (1 << EPCACH_CR_ACTVPH_BIT)
#define EPCACH_CR_XPHST_LOW                (0 << EPCACH_CR_XPHST_BIT)
#define EPCACH_CR_XPHST_HIGH               (1 << EPCACH_CR_XPHST_BIT)
#define EPCACH_CR_CCIEN_DS                 (0 << EPCACH_CR_CCIEN_BIT)
#define EPCACH_CR_CCIEN_EN                 (1 << EPCACH_CR_CCIEN_BIT)
#define EPCACH_CR_CCDEN_DS                 (0 << EPCACH_CR_CCDEN_BIT)
#define EPCACH_CR_CCDEN_EN                 (1 << EPCACH_CR_CCDEN_BIT)
#define EPCACH_CR_CCSEN_DS                 (0 << EPCACH_CR_CCSEN_BIT)
#define EPCACH_CR_CCSEN_EN                 (1 << EPCACH_CR_CCSEN_BIT)
#define EPCACH_CR_CIOVFIEN_DS              (0 << EPCACH_CR_CIOVFIEN_BIT)
#define EPCACH_CR_CIOVFIEN_EN              (1 << EPCACH_CR_CIOVFIEN_BIT)
#define EPCACH_CR_CIOVFDEN_DS              (0 << EPCACH_CR_CIOVFDEN_BIT)
#define EPCACH_CR_CIOVFDEN_EN              (1 << EPCACH_CR_CIOVFDEN_BIT)
#define EPCACH_CR_CIOVFSEN_DS              (0 << EPCACH_CR_CIOVFSEN_BIT)
#define EPCACH_CR_CIOVFSEN_EN              (1 << EPCACH_CR_CIOVFSEN_BIT)

#define EPCACH_CCAPV_MASK                  0x0003FFFF
#define EPCACH_CCAPV_BIT                   0

#define EPCACH_CCAPVUPD_MASK               0x0003FFFF
#define EPCACH_CCAPVUPD_BIT                0

#define EPCA_STATUS_CXCCI_MASK             (EPCA_STATUS_C0CCI_MASK | EPCA_STATUS_C1CCI_MASK | EPCA_STATUS_C2CCI_MASK | \
                                            EPCA_STATUS_C3CCI_MASK | EPCA_STATUS_C4CCI_MASK | EPCA_STATUS_C5CCI_MASK)
#define EPCA_STATUS_CXIOVFI_MASK           (EPCA_STATUS_C0IOVFI_MASK | EPCA_STATUS_C1IOVFI_MASK | EPCA_STATUS_C2IOVFI_MASK | \
                                            EPCA_STATUS_C3IOVFI_MASK | EPCA_STATUS_C4IOVFI_MASK | EPCA_STATUS_C5IOVFI_MASK)


#define TIMER_CFGR_LCLK_MASK            0x00000003
#define TIMER_CFGR_LMSTREN_MASK         0x00000010
#define TIMER_CFGR_SPLITEN_MASK         0x00000020
#define TIMER_CFGR_LEXIEN_MASK          0x00000040
#define TIMER_CFGR_LOVFIEN_MASK         0x00000080
#define TIMER_CFGR_LMD_MASK             0x00000700
#define TIMER_CFGR_LSTATE_MASK          0x00001000
#define TIMER_CFGR_LRUN_MASK            0x00002000
#define TIMER_CFGR_LEXI_MASK            0x00004000
#define TIMER_CFGR_LOVFI_MASK           0x00008000
#define TIMER_CFGR_HCLK_MASK            0x00030000
#define TIMER_CFGR_MSTRUN_MASK          0x00080000
#define TIMER_CFGR_HMSTREN_MASK         0x00100000
#define TIMER_CFGR_DBGMD_MASK           0x00200000
#define TIMER_CFGR_HEXIEN_MASK          0x00400000
#define TIMER_CFGR_HOVFIEN_MASK         0x00800000
#define TIMER_CFGR_HMD_MASK             0x0F000000
#define TIMER_CFGR_HSTATE_MASK          0x10000000
#define TIMER_CFGR_HRUN_MASK            0x20000000
#define TIMER_CFGR_HEXI_MASK            0x40000000
#define TIMER_CFGR_HOVFI_MASK           0x80000000
#define TIMER_CFGR_LCLK_BIT             0  /* LCLK<1:0>: Low Clock Source.                   */
#define TIMER_CFGR_LMSTREN_BIT          4  /* LMSTREN<4>: Low Run Master Enable.             */
#define TIMER_CFGR_SPLITEN_BIT          5  /* SPLITEN<5>: Split Mode Enable.                 */
#define TIMER_CFGR_LEXIEN_BIT           6  /* LEXIEN<6>: Low Timer Extra Interrupt Enable.   */
#define TIMER_CFGR_LOVFIEN_BIT          7  /* LOVFIEN<7>: Low Timer Overflow Interrupt Enable. */
#define TIMER_CFGR_LMD_BIT              8  /* LMD<10:8>: Low Timer Mode.                     */
#define TIMER_CFGR_LSTATE_BIT           12 /* LSTATE<12>: Low Multi Purpose State Indicator. */
#define TIMER_CFGR_LRUN_BIT             13 /* LRUN<13>: Run Control Low.                     */
#define TIMER_CFGR_LEXI_BIT             14 /* LEXI<14>: Low Timer Extra Interrupt Flag.      */
#define TIMER_CFGR_LOVFI_BIT            15 /* LOVFI<15>: Low Timer Overflow Interrupt.       */
#define TIMER_CFGR_HCLK_BIT             16 /* HCLK<17:16>: High Clock Source.                */
#define TIMER_CFGR_MSTRUN_BIT           19 /* MSTRUN<19>: Master Run Control.                */
#define TIMER_CFGR_HMSTREN_BIT          20 /* HMSTREN<20>: High Master Enable.               */
#define TIMER_CFGR_DBGMD_BIT            21 /* DBGMD<21>: Timer Debug Mode.                   */
#define TIMER_CFGR_HEXIEN_BIT           22 /* HEXIEN<22>: High Timer Extra Interrupt Enable. */
#define TIMER_CFGR_HOVFIEN_BIT          23 /* HOVFIEN<23>: High Timer Overflow Interrupt Enable. */
#define TIMER_CFGR_HMD_BIT              24 /* HMD<27:24>: High Timer Mode.                   */
#define TIMER_CFGR_HSTATE_BIT           28 /* HSTATE<28>: High Multi Purpose State Indicator. */
#define TIMER_CFGR_HRUN_BIT             29 /* HRUN<29>: High Run Control.                    */
#define TIMER_CFGR_HEXI_BIT             30 /* HEXI<30>: High Timer Extra Interrupt Flag.     */
#define TIMER_CFGR_HOVFI_BIT            31 /* HOVFI<31>: High Timer Overflow Interrupt Flag. */
#define TIMER_CFGR_LCLK_APB             (0 << TIMER_CFGR_LCLK_BIT)
#define TIMER_CFGR_LCLK_EXTOSCN         (1 << TIMER_CFGR_LCLK_BIT)
#define TIMER_CFGR_LCLK_TIMER_CLKDIV    (2 << TIMER_CFGR_LCLK_BIT)
#define TIMER_CFGR_LCLK_CT_FALLING_EDGE (3 << TIMER_CFGR_LCLK_BIT)
#define TIMER_CFGR_LMSTREN_DS           (0 << TIMER_CFGR_LMSTREN_BIT)
#define TIMER_CFGR_LMSTREN_EN           (1 << TIMER_CFGR_LMSTREN_BIT)
#define TIMER_CFGR_SPLITEN_DS           (0 << TIMER_CFGR_SPLITEN_BIT)
#define TIMER_CFGR_SPLITEN_EN           (1 << TIMER_CFGR_SPLITEN_BIT)
#define TIMER_CFGR_LEXIEN_DS            (0 << TIMER_CFGR_LEXIEN_BIT)
#define TIMER_CFGR_LEXIEN_EN            (1 << TIMER_CFGR_LEXIEN_BIT)
#define TIMER_CFGR_LOVFIEN_DS           (0 << TIMER_CFGR_LOVFIEN_BIT)
#define TIMER_CFGR_LOVFIEN_EN           (1 << TIMER_CFGR_LOVFIEN_BIT)
#define TIMER_CFGR_LMD_AUTO_RELOAD      (0 << TIMER_CFGR_LMD_BIT)
#define TIMER_CFGR_LMD_UP_DOWN          (1 << TIMER_CFGR_LMD_BIT)
#define TIMER_CFGR_LMD_FALL_CAPTURE     (2 << TIMER_CFGR_LMD_BIT)
#define TIMER_CFGR_LMD_RISE_CAPTURE     (3 << TIMER_CFGR_LMD_BIT)
#define TIMER_CFGR_LMD_LOW_CAPTURE      (4 << TIMER_CFGR_LMD_BIT)
#define TIMER_CFGR_LMD_HIGH_CAPTURE     (5 << TIMER_CFGR_LMD_BIT)
#define TIMER_CFGR_LMD_DC_CAPTURE       (6 << TIMER_CFGR_LMD_BIT)
#define TIMER_CFGR_LMD_ONESHOT          (7 << TIMER_CFGR_LMD_BIT)
#define TIMER_CFGR_LSTATE_NOT_SET       (0 << TIMER_CFGR_LSTATE_BIT)
#define TIMER_CFGR_LSTATE_SET           (1 << TIMER_CFGR_LSTATE_BIT)
#define TIMER_CFGR_LRUN_STOP            (0 << TIMER_CFGR_LRUN_BIT)
#define TIMER_CFGR_LRUN_START           (1 << TIMER_CFGR_LRUN_BIT)
#define TIMER_CFGR_LEXI_NOT_SET         (0 << TIMER_CFGR_LEXI_BIT)
#define TIMER_CFGR_LEXI_SET             (1 << TIMER_CFGR_LEXI_BIT)
#define TIMER_CFGR_LOVFI_NOT_SET        (0 << TIMER_CFGR_LOVFI_BIT)
#define TIMER_CFGR_LOVFI_SET            (1 << TIMER_CFGR_LOVFI_BIT)
#define TIMER_CFGR_HCLK_APB             (0 << TIMER_CFGR_HCLK_BIT)
#define TIMER_CFGR_HCLK_EXTOSCN         (1 << TIMER_CFGR_HCLK_BIT)
#define TIMER_CFGR_HCLK_TIMER_CLKDIV    (2 << TIMER_CFGR_HCLK_BIT)
#define TIMER_CFGR_HCLK_CT_FALLING_EDGE (3 << TIMER_CFGR_HCLK_BIT)
#define TIMER_CFGR_MSTRUN_STOP          (0 << TIMER_CFGR_MSTRUN_BIT)
#define TIMER_CFGR_MSTRUN_START         (1 << TIMER_CFGR_MSTRUN_BIT)
#define TIMER_CFGR_HMSTREN_DS           (0 << TIMER_CFGR_HMSTREN_BIT)
#define TIMER_CFGR_HMSTREN_EN           (1 << TIMER_CFGR_HMSTREN_BIT)
#define TIMER_CFGR_DBGMD_RUN            (0 << TIMER_CFGR_DBGMD_BIT)
#define TIMER_CFGR_DBGMD_HALT           (1 << TIMER_CFGR_DBGMD_BIT)
#define TIMER_CFGR_HEXIEN_DS            (0 << TIMER_CFGR_HEXIEN_BIT)
#define TIMER_CFGR_HEXIEN_EN            (1 << TIMER_CFGR_HEXIEN_BIT)
#define TIMER_CFGR_HOVFIEN_DS           (0 << TIMER_CFGR_HOVFIEN_BIT)
#define TIMER_CFGR_HOVFIEN_EN           (1 << TIMER_CFGR_HOVFIEN_BIT)
#define TIMER_CFGR_HMD_AUTO_RELOAD      (0 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HMD_UP_DOWN          (1 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HMD_FALL_CAPTURE     (2 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HMD_RISE_CAPTURE     (3 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HMD_LOW_CAPTURE      (4 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HMD_HIGH_CAPTURE     (5 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HMD_DC_CAPTURE       (6 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HMD_ONESHOT          (7 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HMD_TOGGLE           (8 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HMD_PWM              (9 << TIMER_CFGR_HMD_BIT)
#define TIMER_CFGR_HSTATE_NOT_SET       (0 << TIMER_CFGR_HSTATE_BIT)
#define TIMER_CFGR_HSTATE_SET           (1 << TIMER_CFGR_HSTATE_BIT)
#define TIMER_CFGR_HRUN_STOP            (0 << TIMER_CFGR_HRUN_BIT)
#define TIMER_CFGR_HRUN_START           (1 << TIMER_CFGR_HRUN_BIT)
#define TIMER_CFGR_HEXI_NOT_SET         (0 << TIMER_CFGR_HEXI_BIT)
#define TIMER_CFGR_HEXI_SET             (1 << TIMER_CFGR_HEXI_BIT)
#define TIMER_CFGR_HOVFI_NOT_SET        (0U << TIMER_CFGR_HOVFI_BIT)
#define TIMER_CFGR_HOVFI_SET            (1U << TIMER_CFGR_HOVFI_BIT)

#define TIMER_CLKDIV_CLKDIVRL_MASK      0x000000FF
#define TIMER_CLKDIV_CLKDIVCT_MASK      0x00FF0000
#define TIMER_CLKDIV_CLKDIVRL_BIT       0  /* CLKDIVRL<7:0>: Clock Divider Reload Value.     */
#define TIMER_CLKDIV_CLKDIVCT_BIT       16 /* CLKDIVCT<23:16>: Clock Divider Counter.        */

#define TIMER_COUNT_LCOUNT_MASK         0x0000FFFF
#define TIMER_COUNT_HCOUNT_MASK         0xFFFF0000
#define TIMER_COUNT_LCOUNT_BIT          0  /* LCOUNT<15:0>: Low Timer Count.                 */
#define TIMER_COUNT_HCOUNT_BIT          16 /* HCOUNT<31:16>: High Timer Count.               */

#define TIMER_CAPTURE_LCCR_MASK         0x0000FFFF
#define TIMER_CAPTURE_HCCR_MASK         0xFFFF0000
#define TIMER_CAPTURE_LCCR_BIT          0  /* LCCR<15:0>: Low Timer Capture/Reload.          */
#define TIMER_CAPTURE_HCCR_BIT          16 /* HCCR<31:16>: High Timer Capture/Reload.        */


/*
 * Convenience routines
 */

/**
 * @brief Used to configure the behavior of a timer channel.
 *
 * Be careful: not all timers can be configured in every mode.
 */
typedef enum timer_mode {
    /**
     * The timer stops counting, channel interrupts are detached, and
     * no state changes are output. */
    TIMER_DISABLED,

    /** PWM output. */
    TIMER_PWM,

    /* TIMER_PWM_CENTER_ALIGNED, TODO: Center-aligned PWM output mode. */

    /**
     * The timer counts from 0 to its reload value repeatedly; every
     * time the counter value reaches one of the channel compare
     * values, the corresponding interrupt is fired. */
    TIMER_OUTPUT_COMPARE,

    /* TIMER_INPUT_CAPTURE, TODO: In this mode, the timer can measure the
     *                            pulse lengths of input signals */
    /* TIMER_ONE_PULSE, TODO: In this mode, the timer can generate a single
     *                        pulse on a GPIO pin for a specified amount of
     *                        time. */
} timer_mode;

/** Timer channel numbers */
typedef enum timer_channel {
    TIMER_CH1 = 1, /**< Channel 1 */
    TIMER_CH2 = 2, /**< Channel 2 */
    TIMER_CH3 = 3, /**< Channel 3 */
    TIMER_CH4 = 4, /**< Channel 4 */
    TIMER_CH5 = 5, /**< Channel 5 */
    TIMER_CH6 = 6, /**< Channel 6 */
} timer_channel;



/*
 * Note: Don't require timer_channel arguments! We want to be able to say
 *
 * for (int channel = 1; channel <= 4; channel++) {
 *    ...
 * }
 *
 * without the compiler yelling at us.
 */

void timer_init(timer_dev *dev);
void timer_disable(timer_dev *dev);
void timer_set_mode(timer_dev *dev, uint8 channel, timer_mode mode);
void timer_foreach(void (*fn)(timer_dev*));
int timer_has_cc_channel(timer_dev *dev, uint8 channel);

/**
 * @brief Timer interrupt number.
 *
 * Not all timers support all of these values. All timers support
 * TIMER_UPDATE_INTERRUPT. "General purpose" timers can be a special
 * nuisance in this regard, as they individually support different
 * subsets of the available interupts. Consult your target's reference
 * manual for the details.
 */
typedef enum timer_interrupt_id {
    TIMER_CC1_INTERRUPT,            /**< Capture/compare 1 interrupt. */
    TIMER_CC2_INTERRUPT,            /**< Capture/compare 2 interrupt. */
    TIMER_CC3_INTERRUPT,            /**< Capture/compare 3 interrupt. */
    TIMER_CC4_INTERRUPT,            /**< Capture/compare 4 interrupt. */
    TIMER_CC5_INTERRUPT,            /**< Capture/compare 5 interrupt. */
    TIMER_CC6_INTERRUPT,            /**< Capture/compare 6 interrupt. */
    TIMER_OVERFLOW_INTERRUPT,       /**< Occurs when the timer reached the limit register. */
    TIMER_HALT_INTERRUPT,           // TODO [silabs] implement hdkill timer irq */
    TIMER_OVFL1_INTERRUPT,          /**< Intermediate overflow 1 interrupt. Used in n-bit PWM mode. */
    TIMER_OVFL2_INTERRUPT,          /**< Intermediate overflow 2 interrupt. Used in n-bit PWM mode. */
    TIMER_OVFL3_INTERRUPT,          /**< Intermediate overflow 3 interrupt. Used in n-bit PWM mode. */
    TIMER_OVFL4_INTERRUPT,          /**< Intermediate overflow 4 interrupt. Used in n-bit PWM mode. */
    TIMER_OVFL5_INTERRUPT,          /**< Intermediate overflow 5 interrupt. Used in n-bit PWM mode. */
    TIMER_OVFL6_INTERRUPT,          /**< Intermediate overflow 6 interrupt. Used in n-bit PWM mode. */
} timer_interrupt_id;


void timer_attach_interrupt(timer_dev *dev,
                            uint8 interrupt,
                            voidFuncPtr handler);
void timer_detach_interrupt(timer_dev *dev, uint8 interrupt);

/**
 * Initialize all timer devices on the chip.
 */
static inline void timer_init_all(void) {

}

/**
 * Disables all timers on the device.
 */
static inline void timer_disable_all(void) {

}

/**
 * @brief Stop a timer's counter from changing.
 *
 * Does not affect the timer's mode or other settings.
 *
 * @param dev Device whose counter to pause.
 */
static inline void timer_pause(timer_dev *dev) {
    timer_basic_reg_map *regs_b;
    switch (dev->type) {
    case TIMER_BASIC:
        regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
        REG_SET_CLR(regs_b->CONFIG, 1, 0x20000000);
        break;
    default:
        REG_SET_CLR(dev->regs->STATUS, EPCA_STATUS_RUN_STOP, EPCA_STATUS_RUN_START);
        break;
    }

}

/**
 * @brief Start a timer's counter.
 *
 * Does not affect the timer's mode or other settings.
 *
 * @param dev Device whose counter to resume
 */
static inline void timer_resume(timer_dev *dev) {
    timer_basic_reg_map *regs_b;
    switch (dev->type) {
    case TIMER_BASIC:
        regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
        REG_SET_CLR(regs_b->CONFIG, 1, 0x20000000);
        break;
    default:
        REG_SET_CLR(dev->regs->STATUS, EPCA_STATUS_RUN_START, EPCA_STATUS_RUN_START);
        break;
    }
}

static inline uint32 timer_actl_freq(timer_dev *dev, uint32 tmr_clk) {
    uint32 bus_clk = clk_get_bus_freq(dev->clk_id);
    // PCA modules
    // 1) tmr_clk = bus_clk / (clk_div + 1)
    // 2) clk_div = bus_clk / tmr_clk - 1
    // => tmr_clk = bus_clk / ((bus_clk / tmr_clk - 1)  + 1)
    // Timer modules
    // 1) tmr_clk = bus_clk / (256 - clk_div)
    // 2) clk_div = 256 - bus_clk / tmr_clk
    // => tmr_clk = bus_clk / (256 - (256 - bus_clk / tmr_clk))
    return dev->type == TIMER_BASIC ? bus_clk / (256 - (256 - bus_clk / tmr_clk)) :
            bus_clk / ((bus_clk / tmr_clk - 1) + 1);
}

/**
 * @brief Returns the timer's counter value.
 *
 * This value is likely to be inaccurate if the counter is running
 * with a low prescaler.
 *
 * @param dev Timer whose counter to return
 */
static inline uint16 timer_get_count(timer_dev *dev) {
    return 0;
}

/**
 * @brief Sets the counter value for the given timer.
 * @param dev Timer whose counter to set
 * @param value New counter value
 */
static inline void timer_set_count(timer_dev *dev, uint16 value) {

}

/**
 * @brief Returns the given timer's prescaler.
 *
 * Note that if the timer's prescaler is set (e.g. via
 * timer_set_prescaler() or accessing a TIMx_PSC register), the value
 * returned by this function will reflect the new setting, but the
 * timer's counter will only reflect the new prescaler at the next
 * update event.
 *
 * @param dev Timer whose prescaler to return
 * @see timer_generate_update()
 */
static inline uint16 timer_get_prescaler(timer_dev *dev) {
    timer_reg_map *regs = dev->regs;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        return 256 - regs_b->CLKDIV;
    default:
        // psc = clk_in / Fepca - 1
        return 1 + ((regs->MODE & ~EPCA_MODE_CLKDIV_MASK) >> EPCA_MODE_CLKDIV_BIT);
    }
}

/**
 * @brief Set a timer's prescale value.
 *
 * Divides the input clock by (PSC+1).  The new value will not take
 * effect until the next update event.
 *
 * @param dev Timer whose prescaler to set
 * @param psc New prescaler value
 * @see timer_generate_update()
 */
static inline void timer_set_prescaler(timer_dev *dev, uint16 psc) {
    timer_reg_map *regs = dev->regs;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        regs_b->CLKDIV = 255 / (psc + 1);
        break;
    default:
        // psc = clk_in / Fepca - 1
        regs->MODE &= ~EPCA_MODE_CLKDIV_MASK;
        regs->MODE |= psc << EPCA_MODE_CLKDIV_BIT;
        break;
    }
}

/**
 * @brief Returns a timer's reload value.
 * @param dev Timer whose reload value to return
 */
static inline uint16 timer_get_reload(timer_dev *dev) {
    timer_reg_map *regs = dev->regs;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        return 0;
    default:
        return regs->LIMIT & EPCA_LIMIT_MASK;
    }

    return 0;
}

/**
 * @brief Set a timer's reload value.
 * @param dev Timer whose reload value to set
 * @param arr New reload value to use.  Takes effect at next update event.
 * @see timer_generate_update()
 */
static inline void timer_set_reload(timer_dev *dev, uint16 arr) {
    timer_reg_map *regs = dev->regs;
    timer_basic_reg_map *regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
    switch (dev->type) {
    case TIMER_BASIC:
        break;
    default:
        regs->LIMIT = arr;
        break;
    }
}

/**
 * @brief Get the compare value for the given timer channel.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose compare value to get.
 */
static inline uint16 timer_get_compare(timer_dev *dev, uint8 channel) {
    return 0;
}

/**
 * @brief Set the compare value for the given timer channel.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose compare value to set.
 * @param value   New compare value.
 */
static inline void timer_set_compare(timer_dev *dev,
                                     uint8 channel,
                                     uint16 value) {
    timer_chnl_reg_map *reg;
    timer_basic_reg_map *regs_b;
    uint32 limit;
    switch (dev->type) {
    case TIMER_BASIC:
        regs_b = (timer_basic_reg_map*)(void*)&dev->regs->MODE;
        // Set duty cycle: 0-65535
        regs_b->CAPTURE |= value << 16;
        break;
    default:
        limit = timer_actl_freq(dev, 1000000) / 1000;
        reg = dev->chnl_regs[channel - 1];
        reg->MODE &= ~EPCACH_MODE_COSEL_MASK;
        REG_SET_CLR(reg->CONTROL, 1, 1);
        // CCAPV = 2 * limit * (1 - DC)
        reg->CCAPV = 2 * limit * value / 65535;
        break;
    }
}

/**
 * @brief Generate an update event for the given timer.
 *
 * Normally, this will cause the prescaler and auto-reload values in
 * the PSC and ARR registers to take immediate effect.  However, this
 * function will do nothing if the UDIS bit is set in the timer's CR1
 * register (UDIS is cleared by default).
 *
 * @param dev Timer device to generate an update for.
 */
static inline void timer_generate_update(timer_dev *dev) {

}

/**
 * @brief Enable a timer's trigger DMA request
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL
 */
static inline void timer_dma_enable_trg_req(timer_dev *dev) {

}

/**
 * @brief Disable a timer's trigger DMA request
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL
 */
static inline void timer_dma_disable_trg_req(timer_dev *dev) {

}

/**
 * @brief Enable a timer channel's DMA request.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL
 * @param channel Channel whose DMA request to enable.
 */
static inline void timer_dma_enable_req(timer_dev *dev, uint8 channel) {

}

/**
 * @brief Disable a timer channel's DMA request.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose DMA request to disable.
 */
static inline void timer_dma_disable_req(timer_dev *dev, uint8 channel) {

}

/**
 * @brief Enable a timer interrupt.
 * @param dev Timer device.
 * @param interrupt Interrupt number to enable; this may be any
 *                  timer_interrupt_id value appropriate for the timer.
 * @see timer_interrupt_id
 * @see timer_channel
 */
static inline void timer_enable_irq(timer_dev *dev, uint8 interrupt) {
    switch (dev->type) {
    case TIMER_ADVANCED:
        if (interrupt <= TIMER_CC6_INTERRUPT) {
            REG_SET_CLR(dev->chnl_regs[interrupt]->CONTROL, 1, EPCACH_CR_CCIEN_MASK);
        }
        else if (interrupt == TIMER_OVERFLOW_INTERRUPT) {
            REG_SET_CLR(dev->regs->CONTROL, 1, EPCACH_CR_CCIEN_MASK);
        }
        else if (interrupt == TIMER_HALT_INTERRUPT) {
            REG_SET_CLR(dev->regs->CONTROL, 1, EPCACH_CR_CCIEN_MASK);
        }
        else if (interrupt >= TIMER_OVFL1_INTERRUPT) {
            REG_SET_CLR(dev->chnl_regs[interrupt - TIMER_OVFL1_INTERRUPT]->CONTROL, 1, EPCACH_CR_CIOVFIEN_MASK);
        }
        break;
    case TIMER_GENERAL:
        break;
    case TIMER_BASIC:
        break;
    }
}

/**
 * @brief Disable a timer interrupt.
 * @param dev Timer device.
 * @param interrupt Interrupt number to disable; this may be any
 *                  timer_interrupt_id value appropriate for the timer.
 * @see timer_interrupt_id
 * @see timer_channel
 */
static inline void timer_disable_irq(timer_dev *dev, uint8 interrupt) {
    switch (dev->type) {
    case TIMER_ADVANCED:
        if (interrupt <= TIMER_CC6_INTERRUPT) {
            REG_SET_CLR(dev->chnl_regs[interrupt]->CONTROL, 0, EPCACH_CR_CCIEN_MASK);
        }
        else if (interrupt == TIMER_OVERFLOW_INTERRUPT) {
            REG_SET_CLR(dev->regs->CONTROL, 0, EPCACH_CR_CCIEN_MASK);
        }
        else if (interrupt == TIMER_HALT_INTERRUPT) {
            REG_SET_CLR(dev->regs->CONTROL, 0, EPCACH_CR_CCIEN_MASK);
        }
        else if (interrupt >= TIMER_OVFL1_INTERRUPT) {
            REG_SET_CLR(dev->chnl_regs[interrupt - TIMER_OVFL1_INTERRUPT]->CONTROL, 0, EPCACH_CR_CIOVFIEN_MASK);
        }
        break;
    case TIMER_GENERAL:
        break;
    case TIMER_BASIC:
        break;
    }
}

/**
 * @brief Enable a timer channel's capture/compare signal.
 *
 * If the channel is configured as output, the corresponding output
 * compare signal will be output on the corresponding output pin.  If
 * the channel is configured as input, enables capture of the counter
 * value into the input capture/compare register.
 *
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel to enable, from 1 to 4.
 */
static inline void timer_cc_enable(timer_dev *dev, uint8 channel) {

}

/**
 * @brief Disable a timer channel's output compare or input capture signal.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel to disable, from 1 to 4.
 * @see timer_cc_enable()
 */
static inline void timer_cc_disable(timer_dev *dev, uint8 channel) {

}

/**
 * @brief Get a channel's capture/compare output polarity
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose capture/compare output polarity to get.
 * @return Polarity, either 0 or 1.
 * @see timer_cc_set_polarity()
 */
static inline uint8 timer_cc_get_pol(timer_dev *dev, uint8 channel) {
    return 0;
}

/**
 * @brief Set a timer channel's capture/compare output polarity.
 *
 * If the timer channel is configured as output: polarity == 0 means
 * the output channel will be active high; polarity == 1 means active
 * low.
 *
 * If the timer channel is configured as input: polarity == 0 means
 * capture is done on the rising edge of ICn; when used as an external
 * trigger, ICn is non-inverted.  polarity == 1 means capture is done
 * on the falling edge of ICn; when used as an external trigger, ICn
 * is inverted.
 *
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel whose capture/compare output polarity to set.
 * @param pol New polarity, 0 or 1.
 */
static inline void timer_cc_set_pol(timer_dev *dev, uint8 channel, uint8 pol) {

}

/**
 * @brief Get a timer's DMA burst length.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @return Number of transfers per read or write to timer DMA register,
 *         from 1 to 18.
 */
static inline uint8 timer_dma_get_burst_len(timer_dev *dev) {
    return 0;
}

/**
 * @brief Set a timer's DMA burst length.
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param length DMA burst length; i.e., number of DMA transfers per
 *               read/write to timer DMA register, from 1 to 18.
 */
static inline void timer_dma_set_burst_len(timer_dev *dev, uint8 length) {

}

/**
 * @brief Timer DMA base address.
 *
 * Defines the base address for DMA transfers.
 */
typedef enum timer_dma_base_addr {
    /** Base is control register 1 */
    TIMER_DMA_BASE_CR1 = 1
} timer_dma_base_addr;

/**
 * @brief Get the timer's DMA base address.
 *
 * Some restrictions apply; see the reference manual for your chip.
 *
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @return DMA base address
 */
static inline timer_dma_base_addr timer_dma_get_base_addr(timer_dev *dev) {
    static timer_dma_base_addr tmp;
    return tmp;
}

/**
 * @brief Set the timer's DMA base address.
 *
 * Some restrictions apply; see the reference manual for your chip.
 *
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param dma_base DMA base address.
 */
static inline void timer_dma_set_base_addr(timer_dev *dev,
                                           timer_dma_base_addr dma_base) {

}

/**
 * Timer output compare modes.
 */
typedef enum timer_oc_mode {
    /**
     * Frozen: comparison between output compare register and counter
     * has no effect on the outputs. */
    TIMER_OC_MODE_FROZEN = 0 << 4,
    /**
     * OCxREF signal is forced high when the count matches the channel
     * capture/compare register. */
    TIMER_OC_MODE_ACTIVE_ON_MATCH = 1 << 4,
    /**
     * OCxREF signal is forced low when the counter matches the
     * channel capture/compare register. */
    TIMER_OC_MODE_INACTIVE_ON_MATCH = 2 << 4,
    /**
     * OCxREF toggles when counter matches the channel capture/compare
     * register. */
    TIMER_OC_MODE_TOGGLE = 3 << 4,
    /** OCxREF is forced low. */
    TIMER_OC_MODE_FORCE_INACTIVE = 4 << 4,
    /** OCxREF is forced high. */
    TIMER_OC_MODE_FORCE_ACTIVE = 5 << 4,
    /**
     * PWM mode 1.  In upcounting, channel is active as long as count
     * is less than channel capture/compare register, else inactive.
     * In downcounting, channel is inactive as long as count exceeds
     * capture/compare register, else active. */
    TIMER_OC_MODE_PWM_1 = 6 << 4,
    /**
     * PWM mode 2. In upcounting, channel is inactive as long as count
     * is less than capture/compare register, else active.  In
     * downcounting, channel is active as long as count exceeds
     * capture/compare register, else inactive. */
    TIMER_OC_MODE_PWM_2 = 7 << 4,
} timer_oc_mode;

/**
 * Timer output compare mode flags.
 * @see timer_oc_set_mode()
 */
typedef enum timer_oc_mode_flags {
    TIMER_OC_CE = 1U << 7,       /**< Output compare clear enable. */
    TIMER_OC_PE = 1U << 3,       /**< Output compare preload enable. */
    TIMER_OC_FE = 1U << 2,       /**< Output compare fast enable. */
} timer_oc_mode_flags;

/**
 * @brief Configure a channel's output compare mode.
 *
 * @param dev Timer device, must have type TIMER_ADVANCED or TIMER_GENERAL.
 * @param channel Channel to configure in output compare mode.
 * @param mode Timer mode to set.
 * @param flags OR of timer_oc_mode_flags.
 * @see timer_oc_mode
 * @see timer_oc_mode_flags
 */
static inline void timer_oc_set_mode(timer_dev *dev,
                                     uint8 channel,
                                     timer_oc_mode mode,
                                     uint8 flags) {

}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
