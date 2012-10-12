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
 * @file libmaple/stm32f2/include/series/gpio.h
 * @brief STM32F2 GPIO support.
 */

#ifndef _LIBMAPLE_STM32F2_GPIO_H_
#define _LIBMAPLE_STM32F2_GPIO_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple_types.h>

/*
 * GPIO register maps and devices
 */

/** GPIO register map type */

typedef struct gpio_reg_map
{
    __io uint32 PB; // Base Address + 0x0
    __io uint32 PB_SET;
    __io uint32 PB_CLR;
    __io uint32 PB_MSK;
    __io uint32 PBPIN; // Base Address + 0x10
    uint32      reserved0;
    uint32      reserved1;
    uint32      reserved2;
    __io uint32 PBMDSEL; // Base Address + 0x20
    __io uint32 PBMDSEL_SET;
    __io uint32 PBMDSEL_CLR;
    uint32      reserved3;
    union {
        struct
        {
            __io uint32 PBSKIPEN; // Base Address + 0x30
            __io uint32 PBSKIPEN_SET;
            __io uint32 PBSKIPEN_CLR;
            uint32      reserved4;
            __io uint32 PBOUTMD; // Base Address + 0x40
            __io uint32 PBOUTMD_SET;
            __io uint32 PBOUTMD_CLR;
            uint32      reserved5;
            __io uint32 PBDRV; // Base Address + 0x50
            __io uint32 PBDRV_SET;
            __io uint32 PBDRV_CLR;
            uint32      reserved6;
            __io uint32 PM; // Base Address + 0x60
            __io uint32 PM_SET;
            __io uint32 PM_CLR;
            uint32      reserved7;
            __io uint32 PMEN; // Base Address + 0x70
            __io uint32 PMEN_SET;
            __io uint32 PMEN_CLR;
            uint32      reserved8;
            __io uint32 PBLOCK; // Base Address + 0x80
            uint32      reserved9;
            uint32      reserved10;
            uint32      reserved11;
            __io uint32 PBPGEN; // Base Address + 0x90
            uint32      reserved12;
            uint32      reserved13;
            uint32      reserved14;
            __io uint32 PBPGPHASE; // Base Address + 0xa0
            uint32      reserved15;
            uint32      reserved16;
            uint32      reserved17;
        }std;
        struct {
            __io uint32 PBDEN; // Base Address + 0x30
            __io uint32 PBDEN_SET;
            __io uint32 PBDEN_CLR;
            uint32      reserved4;
            __io uint32 PBDRV; // Base Address + 0x40
            __io uint32 PBDRV_SET;
            __io uint32 PBDRV_CLR;
            uint32      reserved5;
            __io uint32 PBILIMIT; // Base Address + 0x50
            __io uint32 PBILIMIT_SET;
            __io uint32 PBILIMIT_CLR;
            uint32      reserved6;
            uint32      reserved7[4];
            __io uint32 PBFSEL; // Base Address + 0x70
            uint32      reserved8;
            uint32      reserved9;
            uint32      reserved10;
            __io uint32 PBSS; // Base Address + 0x80
            __io uint32 PBSS_SET;
            __io uint32 PBSS_CLR;
            uint32      reserved11;
            __io uint32 PBLOCK; // Base Address + 0x90
            uint32      reserved12;
            uint32      reserved13;
            uint32      reserved14;
        }hd;
    };
}gpio_reg_map;

#define GPIOA_BASE      ((gpio_reg_map*)0x4002A0A0)
#define GPIOB_BASE      ((gpio_reg_map*)0x4002A140)
#define GPIOC_BASE      ((gpio_reg_map*)0x4002A1E0)
#define GPIOD_BASE      ((gpio_reg_map*)0x4002A320)
#define GPIOE_BASE      ((gpio_reg_map*)0x4002A3C0)


typedef struct pbcfg_reg_map
{
   __io uint32 CONTROL0; // Base Address + 0x0
   __io uint32 CONTROL0_SET;
   __io uint32 CONTROL0_CLR;
   uint32      reserved0;
   __io uint32 CONTROL1; // Base Address + 0x10
   __io uint32 CONTROL1_SET;
   __io uint32 CONTROL1_CLR;
   uint32      reserved1;
   __io uint32 XBAR0L; // Base Address + 0x20
   __io uint32 XBAR0L_SET;
   __io uint32 XBAR0L_CLR;
   uint32      reserved2;
   __io uint32 XBAR0H; // Base Address + 0x30
   __io uint32 XBAR0H_SET;
   __io uint32 XBAR0H_CLR;
   uint32      reserved3;
   __io uint32 XBAR1; // Base Address + 0x40
   __io uint32 XBAR1_SET;
   __io uint32 XBAR1_CLR;
   uint32      reserved4;
   __io uint32 PBKEY; // Base Address + 0x50
   uint32      reserved5;
   uint32      reserved6;
   uint32      reserved7;
} pbcfg_reg_map;

#define PBCFG_BASE    ((pbcfg_reg_map*)0x4002A000)


struct gpio_dev;
extern struct gpio_dev* const GPIOA;
extern struct gpio_dev gpioa;
extern struct gpio_dev* const GPIOB;
extern struct gpio_dev gpiob;
extern struct gpio_dev* const GPIOC;
extern struct gpio_dev gpioc;
extern struct gpio_dev* const GPIOD;
extern struct gpio_dev gpiod;
extern struct gpio_dev* const GPIOE;
extern struct gpio_dev gpioe;

/*
 * Register bit definitions
 *
 * Currently, we only provide masks to be used for shifting for some
 * registers, rather than repeating the same values 16 times.
 */


/*
 * Standard Port Bank
 */

/* Mode register */
#define PBSTD_PBMDSEL_MASK           0x0000FFFF

#define PBSTD_PBMDSEL_BIT            0  /* PBMDSEL<15:0>: Mode Select.                    */

#define PBSTD_PBMDSEL_DIGITAL        1
#define PBSTD_PBMDSEL_ANALOG         0

/* Output mode register */
#define PBSTD_PBOUTMD_MASK           0x0000FFFF

#define PBSTD_PBOUTMD_BIT            0  /* PBOUTMD<15:0>: Output Mode.                    */

/* Pulse generator register */
#define PBSTD_PBPGEN_MASK            0x0000FFFF

#define PBSTD_PBPGEN_BIT             0  /* PBPGEN<15:0>: Pulse Generator Pin Enable.      */

/* Drive strength register */
#define PBSTD_PBDRV_MASK             0x0000FFFF
#define PBSTD_PBDRV_PBPUEN_MASK      0x00010000

#define PBSTD_PBDRV_BIT              0  /* PBDRV<15:0>: Drive Strength.                   */
#define PBSTD_PBDRV_PBPUEN_BIT       16 /* PBPUEN<16>: Port Bank Weak Pull-up Enable.     */

#define PBSTD_PBDRV_PBPUEN_DS        (0 << PBSTD_PBDRV_PBPUEN_BIT)
#define PBSTD_PBDRV_PBPUEN_EN        (1 << PBSTD_PBDRV_PBPUEN_BIT)

/*
 * High Drive Port Bank
 */

/* Mode register */
#define PBHD_PBMDSEL_MASK            0x0000003F

#define PBHD_PBMDSEL_BIT             0  /* PBMDSEL<5:0>: Mode Select.                     */

#define PBHD_PBMDSEL_DIGITAL         1
#define PBHD_PBMDSEL_ANALOG          0

/* Drive strength register */
#define PBHD_PBDRV_MASK              0x0000003F
#define PBHD_PBDRV_PBPUEN_MASK       0x00010000
#define PBHD_PBDRV_PBLVMD_MASK       0x00020000
#define PBHD_PBDRV_PBSLEW_MASK       0x000C0000
#define PBHD_PBDRV_PBBIASEN_MASK     0x00200000
#define PBHD_PBDRV_PBDRVEN_MASK      0x00400000
#define PBHD_PBDRV_PBVTRKEN_MASK     0x00800000

#define PBHD_PBDRV_BIT               0  /* PBDRV<5:0>: Drive Strength.                    */
#define PBHD_PBDRV_PBPUEN_BIT        16 /* PBPUEN<16>: Port Bank Weak Pull-up Enable.     */
#define PBHD_PBDRV_PBLVMD_BIT        17 /* PBLVMD<17>: Port Low Voltage Mode.             */
#define PBHD_PBDRV_PBSLEW_BIT        18 /* PBSLEW<19:18>: Port Slew Control.              */
#define PBHD_PBDRV_PBBIASEN_BIT      21 /* PBBIASEN<21>: Port Bias Enable.                */
#define PBHD_PBDRV_PBDRVEN_BIT       22 /* PBDRVEN<22>: Port Drive Enable.                */
#define PBHD_PBDRV_PBVTRKEN_BIT      23 /* PBVTRKEN<23>: Port Voltage Supply Tracking Enable. */

/* Current Limit register */
#define PBHD_PBILIMIT_PBILEN_MASK    0x0000003F
#define PBHD_PBILIMIT_NILIMIT_MASK   0x000F0000
#define PBHD_PBILIMIT_PILIMIT_MASK   0x00F00000

#define PBHD_PBILIMIT_PBILEN_BIT     0  /* PBILEN<5:0>: Current Limit Enable.             */
#define PBHD_PBILIMIT_NILIMIT_BIT    16 /* NILIMIT<19:16>: N-Channel Current Limit.       */
#define PBHD_PBILIMIT_PILIMIT_BIT    20 /* PILIMIT<23:20>: P-Channel Current Limit.       */

#define PBHD_PBILIMIT_NILIMIT_MODE(n) (n << PBHD_PBILIMIT_NILIMIT_BIT)
#define PBHD_PBILIMIT_PILIMIT_MODE(n) (n << PBHD_PBILIMIT_PILIMIT_BIT)

/* Function Select register */
#define PBHD_PBFSEL_PB0SEL_MASK      0x00000003
#define PBHD_PBFSEL_PB1SEL_MASK      0x0000000C
#define PBHD_PBFSEL_PB2SEL_MASK      0x00000030
#define PBHD_PBFSEL_PB3SEL_MASK      0x000000C0
#define PBHD_PBFSEL_PB4SEL_MASK      0x00000300
#define PBHD_PBFSEL_PB5SEL_MASK      0x00001C00

#define PBHD_PBFSEL_PB0SEL_BIT       0  /* PB0SEL<1:0>: Port Bank n.0 Function Select.    */
#define PBHD_PBFSEL_PB1SEL_BIT       2  /* PB1SEL<3:2>: Port Bank n.1 Function Select.    */
#define PBHD_PBFSEL_PB2SEL_BIT       4  /* PB2SEL<5:4>: Port Bank n.2 Function Select.    */
#define PBHD_PBFSEL_PB3SEL_BIT       6  /* PB3SEL<7:6>: Port Bank n.3 Function Select.    */
#define PBHD_PBFSEL_PB4SEL_BIT       8  /* PB4SEL<9:8>: Port Bank n.4 Function Select.    */
#define PBHD_PBFSEL_PB5SEL_BIT       10 /* PB5SEL<12:10>: Port Bank n.5 Function Select.  */

#define PBHD_PBFSEL_PB0SEL_GPIO      (0 << PBHD_PBFSEL_PB0SEL_BIT)
#define PBHD_PBFSEL_PB0SEL_PMLS      (1 << PBHD_PBFSEL_PB0SEL_BIT)
#define PBHD_PBFSEL_PB0SEL_EPCA0     (2 << PBHD_PBFSEL_PB0SEL_BIT)
#define PBHD_PBFSEL_PB1SEL_GPIO      (0 << PBHD_PBFSEL_PB1SEL_BIT)
#define PBHD_PBFSEL_PB1SEL_PMLS      (1 << PBHD_PBFSEL_PB1SEL_BIT)
#define PBHD_PBFSEL_PB1SEL_EPCA0     (2 << PBHD_PBFSEL_PB1SEL_BIT)
#define PBHD_PBFSEL_PB2SEL_GPIO      (0 << PBHD_PBFSEL_PB2SEL_BIT)
#define PBHD_PBFSEL_PB2SEL_PMLS      (1 << PBHD_PBFSEL_PB2SEL_BIT)
#define PBHD_PBFSEL_PB2SEL_EPCA0     (2 << PBHD_PBFSEL_PB2SEL_BIT)
#define PBHD_PBFSEL_PB2SEL_UART1     (3 << PBHD_PBFSEL_PB2SEL_BIT)
#define PBHD_PBFSEL_PB3SEL_GPIO      (0 << PBHD_PBFSEL_PB3SEL_BIT)
#define PBHD_PBFSEL_PB3SEL_PMLS      (1 << PBHD_PBFSEL_PB3SEL_BIT)
#define PBHD_PBFSEL_PB3SEL_EPCA0     (2 << PBHD_PBFSEL_PB3SEL_BIT)
#define PBHD_PBFSEL_PB3SEL_UART1     (3 << PBHD_PBFSEL_PB3SEL_BIT)
#define PBHD_PBFSEL_PB4SEL_GPIO      (0 << PBHD_PBFSEL_PB4SEL_BIT)
#define PBHD_PBFSEL_PB4SEL_PMLS      (1 << PBHD_PBFSEL_PB4SEL_BIT)
#define PBHD_PBFSEL_PB4SEL_EPCA0     (2 << PBHD_PBFSEL_PB4SEL_BIT)
#define PBHD_PBFSEL_PB4SEL_UART1     (3 << PBHD_PBFSEL_PB4SEL_BIT)
#define PBHD_PBFSEL_PB5SEL_GPIO      (0 << PBHD_PBFSEL_PB5SEL_BIT)
#define PBHD_PBFSEL_PB5SEL_PMLS      (1 << PBHD_PBFSEL_PB5SEL_BIT)
#define PBHD_PBFSEL_PB5SEL_EPCA0     (2 << PBHD_PBFSEL_PB5SEL_BIT)
#define PBHD_PBFSEL_PB5SEL_UART1     (3 << PBHD_PBFSEL_PB5SEL_BIT)
#define PBHD_PBFSEL_PB5SEL_LPTIMER0  (4 << PBHD_PBFSEL_PB5SEL_BIT)

/* Safe State Select register */
#define PBHD_PBSS_PB0SSSEL_MASK      0x00000003
#define PBHD_PBSS_PB1SSSEL_MASK      0x0000000C
#define PBHD_PBSS_PB2SSSEL_MASK      0x00000030
#define PBHD_PBSS_PB3SSSEL_MASK      0x000000C0
#define PBHD_PBSS_PB4SSSEL_MASK      0x00000300
#define PBHD_PBSS_PB5SSSEL_MASK      0x00000C00
#define PBHD_PBSS_SSMDEN_MASK        0x00010000
#define PBHD_PBSS_PBSSSMD_MASK       0x00020000

#define PBHD_PBSS_PB0SSSEL_BIT       0  /* PB0SSSEL<1:0>: Port Bank n.0 Safe State Select. */
#define PBHD_PBSS_PB1SSSEL_BIT       2  /* PB1SSSEL<3:2>: Port Bank n.1 Safe State Select. */
#define PBHD_PBSS_PB2SSSEL_BIT       4  /* PB2SSSEL<5:4>: Port Bank n.2 Safe State Select. */
#define PBHD_PBSS_PB3SSSEL_BIT       6  /* PB3SSSEL<7:6>: Port Bank n.3 Safe State Select. */
#define PBHD_PBSS_PB4SSSEL_BIT       8  /* PB4SSSEL<9:8>: Port Bank n.4 Safe State Select. */
#define PBHD_PBSS_PB5SSSEL_BIT       10 /* PB5SSSEL<11:10>: Port Bank n.5 Safe State Select. */
#define PBHD_PBSS_SSMDEN_BIT         16 /* SSMDEN<16>: Enter Safe State Mode.             */
#define PBHD_PBSS_PBSSSMD_BIT        17 /* PBSSSMD<17>: Safe State Signal Mode.           */


#define PBHD_PBSS_PBSSSEL(val, pb_num) (val (1 << pb_num))
#define PBHD_PBSS_SSMDEN_DS          (0 << PBHD_PBSS_SSMDEN_BIT)
#define PBHD_PBSS_SSMDEN_EN          (1 << PBHD_PBSS_SSMDEN_BIT)
#define PBHD_PBSS_PBSSSMD_DEGLITCH   (0 << PBHD_PBSS_PBSSSMD_BIT)
#define PBHD_PBSS_PBSSSMD_IMMEDIATE  (1 << PBHD_PBSS_PBSSSMD_BIT)

/* Driver enable */
#define PBHD_PBDEN_PBNDEN_MASK       0x0000003F
#define PBHD_PBDEN_PBPDEN_MASK       0x003F0000

#define PBHD_PBDEN_PBNDEN_BIT        0  /* PBNDEN<5:0>: Port Bank N-Channel Driver Enable (low side). */
#define PBHD_PBDEN_PBPDEN_BIT        16 /* PBPDEN<21:16>: Port Bank P-Channel Driver Enable (high side). */

#define PBCFG_XBAR0L_USART0EN_MASK           0x00000001
#define PBCFG_XBAR0L_USART0FCEN_MASK         0x00000002
#define PBCFG_XBAR0L_USART0CEN_MASK          0x00000004
#define PBCFG_XBAR0L_SPI0EN_MASK             0x00000008
#define PBCFG_XBAR0L_SPI0NSSEN_MASK          0x00000010
#define PBCFG_XBAR0L_USART1EN_MASK           0x00000020
#define PBCFG_XBAR0L_USART1FCEN_MASK         0x00000040
#define PBCFG_XBAR0L_USART1CEN_MASK          0x00000080
#define PBCFG_XBAR0L_EPCA0EN_MASK            0x00000700
#define PBCFG_XBAR0L_PCA0_CEX0EN_MASK        0x00004000
#define PBCFG_XBAR0L_PCA0EN_MASK             0x0000C000
#define PBCFG_XBAR0L_PCA1_CEX0EN_MASK        0x00010000
#define PBCFG_XBAR0L_PCA1EN_MASK             0x00030000
#define PBCFG_XBAR0L_EECI0EN_MASK            0x00040000
#define PBCFG_XBAR0L_ECI0EN_MASK             0x00080000
#define PBCFG_XBAR0L_ECI1EN_MASK             0x00100000
#define PBCFG_XBAR0L_I2S0TXEN_MASK           0x00200000
#define PBCFG_XBAR0L_I2C0EN_MASK             0x00400000
#define PBCFG_XBAR0L_CMP0SEN_MASK            0x00800000
#define PBCFG_XBAR0L_CMP0AEN_MASK            0x01000000
#define PBCFG_XBAR0L_CMP1SEN_MASK            0x02000000
#define PBCFG_XBAR0L_CMP1AEN_MASK            0x04000000
#define PBCFG_XBAR0L_TMR0CTEN_MASK           0x08000000
#define PBCFG_XBAR0L_TMR0EXEN_MASK           0x10000000
#define PBCFG_XBAR0L_TMR1CTEN_MASK           0x20000000
#define PBCFG_XBAR0L_TMR1EXEN_MASK           0x40000000
#define PBCFG_XBAR0H_UART0EN_MASK            0x00000001
#define PBCFG_XBAR0H_UART0FCEN_MASK          0x00000002
#define PBCFG_XBAR0H_UART1EN_MASK            0x00000004
#define PBCFG_XBAR0H_SPI1EN_MASK             0x00000008
#define PBCFG_XBAR0H_SPI1NSSEN_MASK          0x00000010
#define PBCFG_XBAR0H_SPI2EN_MASK             0x00000020
#define PBCFG_XBAR0H_SPI2NSSEN_MASK          0x00000040
#define PBCFG_XBAR0H_AHBEN_MASK              0x00000080
#define PBCFG_XBAR0H_XBAR0EN_MASK            0x80000000
#define PBCFG_XBAR1_SSG0EN_MASK              0x00000003
#define PBCFG_XBAR1_CMP0SEN_MASK             0x00000004
#define PBCFG_XBAR1_CMP1SEN_MASK             0x00000008
#define PBCFG_XBAR1_SPI1EN_MASK              0x00000010
#define PBCFG_XBAR1_SPI1NSSEN_MASK           0x00000020
#define PBCFG_XBAR1_RTC0EN_MASK              0x00000040
#define PBCFG_XBAR1_SPI2EN_MASK              0x00000080
#define PBCFG_XBAR1_SPI2NSSEN_MASK           0x00000100
#define PBCFG_XBAR1_USART1EN_MASK            0x00000200
#define PBCFG_XBAR1_USART1FCEN_MASK          0x00000400
#define PBCFG_XBAR1_USART1CEN_MASK           0x00000800
#define PBCFG_XBAR1_UART0EN_MASK             0x00001000
#define PBCFG_XBAR1_UART0FCEN_MASK           0x00002000
#define PBCFG_XBAR1_I2S0TXEN_MASK            0x00004000
#define PBCFG_XBAR1_I2C0EN_MASK              0x00008000
#define PBCFG_XBAR1_UART1EN_MASK             0x00010000
#define PBCFG_XBAR1_I2S0RXEN_MASK            0x00020000
#define PBCFG_XBAR1_LPT0OEN_MASK             0x00080000
#define PBCFG_XBAR1_I2C1EN_MASK              0x00100000
#define PBCFG_XBAR1_KILLHDEN_MASK            0x00200000
#define PBCFG_XBAR1_XBAR1EN_MASK             0x80000000

#define PBCFG_PBKEY_KEY_BIT                  0  /* KEY<7:0>: Port Bank 2, 3, and 4 Key.           */
#define PBCFG_PBKEY_KEY_LOCKED               (0 << PBCFG_PBKEY_KEY_BIT)
#define PBCFG_PBKEY_KEY_INTERMEDIATE         (1 << PBCFG_PBKEY_KEY_BIT)
#define PBCFG_PBKEY_KEY_UNLOCKED             (2 << PBCFG_PBKEY_KEY_BIT)

/**< High Drive Port Bank Configuration
1.  Set the safe state for each pin using PBSS.
2.  Set PBBIASEN in PBDRV to 1 to enable current biasing.
3.  In a separate write to PBDRV, set the PBLVMD bit according to the supply level. Low power mode (PBLVMD = 1) must be used if VIOHD is less than 2.7 V and is recommended if VIOHD is less than 3.0 V. PBLVMD must be cleared to 0 if VIOHD is greater than 3.6 V.
4.  In a third write to PBDRV, set PBDRVEN to 1 to release the pins.
5.  In another separate write, configure the appropriate drive strength for each pin and the global port controls for pull-ups (PBPUEN), slew rate (PBSLEW), and VIOHD tracking (PBVTRKEN) in the PBDRV register.
6.  Enable current limiting per pin as needed (PBILEN.x). The N-channel (NILIMIT) and P-channel (PILIMIT) current limit values are global to all pins that have current limiting enabled.
7.  Configure the remaining control registers PBDEN, PBMDSEL, and PBFSEL.
*/

typedef enum pb_high_drive_safe_select {
    HIZ,
    HIGH,
    LOW,
    DISABLE
} pb_high_drive_safe_select;

/*
 * GPIO routines
 */

/**
 * @brief GPIO pin modes
 */
#define GPIO_PBMDSEL_BIT 0
#define GPIO_PBOUTMD_BIT 1
#define GPIO_PB_BIT 2

typedef enum gpio_pin_mode {
    GPIO_ANALOG = (PBSTD_PBMDSEL_ANALOG << GPIO_PBMDSEL_BIT)| (0 << GPIO_PBOUTMD_BIT) | (1 << GPIO_PB_BIT),  /**< Analog mode */
    GPIO_DIGITAL_PP = (PBSTD_PBMDSEL_DIGITAL << GPIO_PBMDSEL_BIT) | (1 << GPIO_PBOUTMD_BIT), /**< Digital mode */
    GPIO_DIGITAL_OD = (PBSTD_PBMDSEL_DIGITAL << GPIO_PBMDSEL_BIT) | (0 << GPIO_PBOUTMD_BIT),
    GPIO_DIGITAL_INPUT_PULLUP = GPIO_DIGITAL_OD | (1 << GPIO_PB_BIT), /**< Digital mode */
} gpio_pin_mode;


/**
 * @brief
 */
#define GPIO_PBDRV_BIT 0

typedef enum gpio_mode_flags {
    GPIO_DRIVE_WEAK = (0 << GPIO_PBDRV_BIT),        /**< ... */
    GPIO_DRIVE_STRONG  = (1 << GPIO_PBDRV_BIT),       /**< .... */
}gpio_mode_flags;


void gpio_set_modef(struct gpio_dev *dev,
                    uint8 bit,
                    gpio_pin_mode mode,
                    unsigned flags);

/**
 * @brief Set the mode of a GPIO pin.
 *
 * Calling this function is equivalent to calling gpio_set_modef(dev,
 * pin, mode, GPIO_MODE_SPEED_HIGH). Note that this overrides the
 * default speed.
 *
 * @param dev GPIO device.
 * @param bit Bit on the device whose mode to set, 0--15.
 * @param mode Mode to set the pin to.
 */
static inline void gpio_set_mode(struct gpio_dev *dev,
                                 uint8 bit,
                                 gpio_pin_mode mode) {
    gpio_set_modef(dev, bit, mode, GPIO_DRIVE_WEAK);
}

/**
 * @brief GPIO alternate functions.
 * Use these to select an alternate function for a pin.
 * @see gpio_set_af()
 */
typedef enum gpio_af {
    GPIOHD_FNCT_GPIO = 0, /**< GPIO */
    GPIOHD_FNCT_PMLS = 1, /**< Port Mapped Level Shift. Buffers corresponding PB2 pin */
    GPIOHD_FNCT_EPCA0 = 2 , /**< Set to be controlled by Enhanced Programmable Counter Array 0 (EPCA).*/
    GPIOHD_FNCT_UART = 3, /**< UART. */
    GPIOHD_FNCT_LPTIMER = 4 /**< Low Power Timer*/
} gpio_af;

typedef enum gpio_type {
    GPIO_STANDARD,             /**< Advanced type */
    GPIO_HIGHDRIVE,              /**< General purpose type */
} gpio_type;

void gpio_set_af(struct gpio_dev *dev, uint8 bit, gpio_af af);

#ifdef __cplusplus
}
#endif

#endif
