/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 Silicon Laboratories.
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

#if !defined(_LIBMAPLE_SIM3U1_XBAR_H_)
#define _LIBMAPLE_SIM3U1_XBAR_H_


#if defined(__cplusplus)
extern "C"{
#endif // defined(__cplusplus)

#include <libmaple/libmaple_types.h>


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
#define PBCFG_XBAR0L_USART0EN_BIT            0  /* USART0EN<0>: USART0 Enable.                    */
#define PBCFG_XBAR0L_USART0FCEN_BIT          1  /* USART0FCEN<1>: USART0 Flow Control Enable.     */
#define PBCFG_XBAR0L_USART0CEN_BIT           2  /* USART0CEN<2>: USART0 Clock Signal Enable.      */
#define PBCFG_XBAR0L_SPI0EN_BIT              3  /* SPI0EN<3>: SPI0 Enable.                        */
#define PBCFG_XBAR0L_SPI0NSSEN_BIT           4  /* SPI0NSSEN<4>: SPI0 NSS Pin Enable.             */
#define PBCFG_XBAR0L_USART1EN_BIT            5  /* USART1EN<5>: USART1 Enable.                    */
#define PBCFG_XBAR0L_USART1FCEN_BIT          6  /* USART1FCEN<6>: USART1 Flow Control Enable.     */
#define PBCFG_XBAR0L_USART1CEN_BIT           7  /* USART1CEN<7>: USART1 Clock Signal Enable.      */
#define PBCFG_XBAR0L_EPCA0EN_BIT             8  /* EPCA0EN<10:8>: EPCA0 Channel Enable.           */
#define PBCFG_XBAR0L_PCA0EN_BIT              14 /* PCA0EN<15:14>: PCA0 Channel Enable.            */
#define PBCFG_XBAR0L_PCA1EN_BIT              16 /* PCA1EN<17:16>: PCA1 Channel Enable.            */
#define PBCFG_XBAR0L_EECI0EN_BIT             18 /* EECI0EN<18>: EPCA0 ECI Enable.                 */
#define PBCFG_XBAR0L_ECI0EN_BIT              19 /* ECI0EN<19>: PCA0 ECI Enable.                   */
#define PBCFG_XBAR0L_ECI1EN_BIT              20 /* ECI1EN<20>: PCA1 ECI Enable.                   */
#define PBCFG_XBAR0L_I2S0TXEN_BIT            21 /* I2S0TXEN<21>: I2S0 TX Enable.                  */
#define PBCFG_XBAR0L_I2C0EN_BIT              22 /* I2C0EN<22>: I2C0 Enable.                       */
#define PBCFG_XBAR0L_CMP0SEN_BIT             23 /* CMP0SEN<23>: Comparator 0 Synchronous Output (CMP0S) Enable. */
#define PBCFG_XBAR0L_CMP0AEN_BIT             24 /* CMP0AEN<24>: Comparator 0 Asynchronous Output (CMP0A) Enable. */
#define PBCFG_XBAR0L_CMP1SEN_BIT             25 /* CMP1SEN<25>: Comparator 1 Synchronous Output (CMP1S) Enable. */
#define PBCFG_XBAR0L_CMP1AEN_BIT             26 /* CMP1AEN<26>: Comparator 1 Asynchronous Output (CMP1A) Enable. */
#define PBCFG_XBAR0L_TMR0CTEN_BIT            27 /* TMR0CTEN<27>: TIMER0 T0CT Enable.              */
#define PBCFG_XBAR0L_TMR0EXEN_BIT            28 /* TMR0EXEN<28>: TIMER0 T0EX Enable.              */
#define PBCFG_XBAR0L_TMR1CTEN_BIT            29 /* TMR1CTEN<29>: TIMER1 T1CT Enable.              */
#define PBCFG_XBAR0L_TMR1EXEN_BIT            30 /* TMR1EXEN<30>: TIMER1 T1EX Enable.              */
#define PBCFG_XBAR0H_UART0EN_BIT             0  /* UART0EN<0>: UART0 Enable.                      */
#define PBCFG_XBAR0H_UART0FCEN_BIT           1  /* UART0FCEN<1>: UART0 Flow Control Enable.       */
#define PBCFG_XBAR0H_UART1EN_BIT             2  /* UART1EN<2>: UART1 Enable.                      */
#define PBCFG_XBAR0H_SPI1EN_BIT              3  /* SPI1EN<3>: SPI1 Enable.                        */
#define PBCFG_XBAR0H_SPI1NSSEN_BIT           4  /* SPI1NSSEN<4>: SPI1 NSS Pin Enable.             */
#define PBCFG_XBAR0H_SPI2EN_BIT              5  /* SPI2EN<5>: SPI2 Enable.                        */
#define PBCFG_XBAR0H_SPI2NSSEN_BIT           6  /* SPI2NSSEN<6>: SPI2 NSS Pin Enable.             */
#define PBCFG_XBAR0H_AHBEN_BIT               7  /* AHBEN<7>: AHB Clock Output Enable.             */
#define PBCFG_XBAR0H_XBAR0EN_BIT             31 /* XBAR0EN<31>: Crossbar 0 Enable.                */
#define PBCFG_XBAR1_SSG0EN_BIT               0  /* SSG0EN<1:0>: SSG0 Enable.                      */
#define PBCFG_XBAR1_CMP0SEN_BIT              2  /* CMP0SEN<2>: Comparator 0 Synchronous Output (CMP0S) Enable. */
#define PBCFG_XBAR1_CMP1SEN_BIT              3  /* CMP1SEN<3>: Comparator 1 Synchronous Output (CMP1S) Enable. */
#define PBCFG_XBAR1_SPI1EN_BIT               4  /* SPI1EN<4>: SPI1 Enable.                        */
#define PBCFG_XBAR1_SPI1NSSEN_BIT            5  /* SPI1NSSEN<5>: SPI1 NSS Pin Enable.             */
#define PBCFG_XBAR1_RTC0EN_BIT               6  /* RTC0EN<6>: RTC0 Output Enable.                 */
#define PBCFG_XBAR1_SPI2EN_BIT               7  /* SPI2EN<7>: SPI2 Enable.                        */
#define PBCFG_XBAR1_SPI2NSSEN_BIT            8  /* SPI2NSSEN<8>: SPI2 NSS Pin Enable.             */
#define PBCFG_XBAR1_USART1EN_BIT             9  /* USART1EN<9>: USART1 Enable.                    */
#define PBCFG_XBAR1_USART1FCEN_BIT           10 /* USART1FCEN<10>: USART1 Flow Control Enable.    */
#define PBCFG_XBAR1_USART1CEN_BIT            11 /* USART1CEN<11>: USART1 Clock Signal Enable.     */
#define PBCFG_XBAR1_UART0EN_BIT              12 /* UART0EN<12>: UART0 Enable.                     */
#define PBCFG_XBAR1_UART0FCEN_BIT            13 /* UART0FCEN<13>: UART0 Flow Control Enable.      */
#define PBCFG_XBAR1_I2S0TXEN_BIT             14 /* I2S0TXEN<14>: I2S0 TX Enable.                  */
#define PBCFG_XBAR1_I2C0EN_BIT               15 /* I2C0EN<15>: I2C0 Enable.                       */
#define PBCFG_XBAR1_UART1EN_BIT              16 /* UART1EN<16>: UART1 Enable.                     */
#define PBCFG_XBAR1_I2S0RXEN_BIT             17 /* I2S0RXEN<17>: I2S0 RX Enable.                  */
#define PBCFG_XBAR1_LPT0OEN_BIT              19 /* LPT0OEN<19>: LPTIMER0 Output Enable.           */
#define PBCFG_XBAR1_I2C1EN_BIT               20 /* I2C1EN<20>: I2C1 Enable.                       */
#define PBCFG_XBAR1_KILLHDEN_BIT             21 /* KILLHDEN<21>: High Drive Kill Pin Enable.      */
#define PBCFG_XBAR1_XBAR1EN_BIT              31 /* XBAR1EN<31>: Crossbar 1 Enable.                */

enum {
    XBAR_NUM_0L,
    XBAR_NUM_0H,
    XBAR_NUM_1,
    XBAR_NUM_NULL,
    XBAR_NUM_GPIOE
};

#define XBAR_GET_MASK(xbar_num, xbar0, xbar1) \
    (xbar_num == XBAR_NUM_0L || xbar_num == XBAR_NUM_0H? xbar0: xbar_num == XBAR_NUM_1? xbar1: 255)
#define XBAR_UART0_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num,PBCFG_XBAR0H_UART0EN_MASK, PBCFG_XBAR1_UART0EN_MASK), pb_mask} /* XBAR_UART0 */
#define XBAR_UART1_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0H_UART1EN_MASK, PBCFG_XBAR1_UART1EN_MASK), pb_mask} /* XBAR_UART1 */
#define XBAR_USART0_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_USART0EN_MASK, 0), pb_mask} /* XBAR_USART0 */
#define XBAR_USART1_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_USART1EN_MASK, PBCFG_XBAR1_USART1EN_MASK), pb_mask} /* XBAR_USART1 */
#define XBAR_SPI0_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_SPI0EN_MASK, 0), pb_mask} /* XBAR_SPI0 */
#define XBAR_SPI0NSS_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_SPI0NSSEN_MASK, 0), pb_mask} /* XBAR_SPI0NSS */
#define XBAR_SPI1_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0H_SPI1EN_MASK, PBCFG_XBAR1_SPI1EN_MASK), pb_mask} /* XBAR_SPI1 */
#define XBAR_SPI1NSS_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0H_SPI1NSSEN_MASK, PBCFG_XBAR1_SPI1NSSEN_MASK), pb_mask} /* XBAR_SPI1NSS */
#define XBAR_SPI2_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0H_SPI2EN_MASK, PBCFG_XBAR1_SPI2EN_MASK), pb_mask} /* XBAR_SPI2 */
#define XBAR_SPI2NSS_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0H_SPI2NSSEN_MASK, PBCFG_XBAR1_SPI2NSSEN_MASK), pb_mask} /* XBAR_SPI2NSS */
#define XBAR_EPCA0_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_EPCA0EN_MASK, 0), pb_mask} /* XBAR_EPCA0 */
#define XBAR_PCA0_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_PCA0EN_MASK, 0), pb_mask} /* XBAR_PCA0 */
#define XBAR_PCA1_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_PCA1EN_MASK, 0), pb_mask} /* XBAR_PCA1 */
#define XBAR_TIMER0CT_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_TMR0CTEN_MASK, 0), pb_mask} /* XBAR_TIMER0CT */
#define XBAR_TIMER0EX_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_TMR0EXEN_MASK, 0), pb_mask} /* XBAR_TIMER0EX */
#define XBAR_TIMER1CT_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_TMR1CTEN_MASK, 0), pb_mask} /* XBAR_TIMER1CT */
#define XBAR_TIMER1EX_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_TMR1EXEN_MASK, 0), pb_mask} /* XBAR_TIMER1EX */
#define XBAR_I2S0TX_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_I2S0TXEN_MASK, PBCFG_XBAR1_I2S0TXEN_MASK), pb_mask} /* XBAR_I2S0TX */
#define XBAR_I2S0RX_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, 0, PBCFG_XBAR1_I2S0RXEN_MASK), pb_mask} /* XBAR_I2S0RX */
#define XBAR_I2C0_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0L_I2C0EN_MASK, PBCFG_XBAR1_I2C0EN_MASK), pb_mask} /* XBAR_I2C0 */
#define XBAR_I2C1_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, 0,PBCFG_XBAR1_I2C1EN_MASK), pb_mask} /* XBAR_I2C1 */
#define XBAR_AHB_OUT_ROW(pb_mask, xbar_num) {XBAR_GET_MASK(xbar_num, PBCFG_XBAR0H_AHBEN_MASK, 0), pb_mask} /* XBAR_AHB_OUT */


typedef struct si_xbar_info_tag {
    uint32 xbar_mask;
    uint32 pb_mask;
} si_xbar_info;

typedef struct xbar_dev_info_tag {
    uint8 info_cnt;
    uint8 xbar_num;
    si_xbar_info *xbar_info;
} xbar_dev_info;


typedef enum xbar_dev_id {
    // UART
    XBAR_USART1, XBAR_USART2, XBAR_USART3, XBAR_USART4,
    // SPI
    XBAR_SPI1, XBAR_SPI2, XBAR_SPI3,
    // Timers
    XBAR_TIMER1, XBAR_TIMER2,  XBAR_TIMER3, XBAR_TIMER4, XBAR_TIMER5,
    // I2S
    XBAR_I2S1,
    // I2C
    XBAR_I2C1, XBAR_I2C2,
    // Misc
    XBAR_AHB_OUT,
    // Must always be last. Is not a peripheral
    XBAR_NULL
} xbar_dev_id;

extern const xbar_dev_info XBAR_MAP[];

void xbar_set_dev(xbar_dev_id xbar_id, uint8 enable);

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

#endif // !defined(_LIBMAPLE_SIM3U1_XBAR_H_)
