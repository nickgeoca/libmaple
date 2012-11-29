/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Michael Hope.
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
 * @file libmaple/dma.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>;
 *         Original implementation by Michael Hope
 * @brief Portable DMA routines.
 */

#include <libmaple/dma.h>
#include "dma_private.h"
#include <wirish/../arch/arch.h> //todo fix header here

/*
 * Convenience routines
 */

/**
 * @brief Initialize a DMA device.
 * @param dev Device to initialize.
 */
void dma_init(dma_dev *dev) {

}

/*
 * Private API
 */
#if 0
enum dma_atype _dma_addr_type(__io void *addr) {
    return DMA_ATYPE_OTHER;
}
#endif

/* Hack to ensure inlining in dma_irq_handler() */
#define DMA_GET_HANDLER(dev, tube) (dev->handlers[tube].handler)
#include "dma_private.h"

/*
 * Devices
 */
#if 0
static dma_dev dma1 = {
    .regs = DMA1_BASE,
    .clk_id = RCC_DMA1,
    .handlers = {{ .handler = NULL, .irq_line = NVIC_DMA1_STREAM0 },
                 { .handler = NULL, .irq_line = NVIC_DMA1_STREAM1 },
                 { .handler = NULL, .irq_line = NVIC_DMA1_STREAM2 },
                 { .handler = NULL, .irq_line = NVIC_DMA1_STREAM3 },
                 { .handler = NULL, .irq_line = NVIC_DMA1_STREAM4 },
                 { .handler = NULL, .irq_line = NVIC_DMA1_STREAM5 },
                 { .handler = NULL, .irq_line = NVIC_DMA1_STREAM6 },
                 { .handler = NULL, .irq_line = NVIC_DMA1_STREAM7 }},
};
dma_dev *DMA1 = &dma1;

static dma_dev dma2 = {
    .regs = DMA2_BASE,
    .clk_id = RCC_DMA2,
    .handlers = {{ .handler = NULL, .irq_line = NVIC_DMA2_STREAM0 },
                 { .handler = NULL, .irq_line = NVIC_DMA2_STREAM1 },
                 { .handler = NULL, .irq_line = NVIC_DMA2_STREAM2 },
                 { .handler = NULL, .irq_line = NVIC_DMA2_STREAM3 },
                 { .handler = NULL, .irq_line = NVIC_DMA2_STREAM4 },
                 { .handler = NULL, .irq_line = NVIC_DMA2_STREAM5 },
                 { .handler = NULL, .irq_line = NVIC_DMA2_STREAM6 },
                 { .handler = NULL, .irq_line = NVIC_DMA2_STREAM7 }},
};
dma_dev *DMA2 = &dma2;

/*
 * Helpers for dealing with dma_request_src's bit encoding (see the
 * comments in the dma_request_src definition).
 */

/* clk_dev_id of dma_dev which supports src. */
static __always_inline rcc_clk_id src_clk_id(dma_request_src src) {
    return 0;
}

/* Bit vector of streams supporting src (e.g., bit 0 set => DMA_S0 support). */
static __always_inline uint32 src_stream_mask(dma_request_src src) {
    return 0;
}

/* Channel corresponding to src. */
static __always_inline dma_channel src_channel(dma_request_src src) {
    return (dma_channel)(src & 0x7);
}

/*
 * Routines
 */

/* For convenience */
#define ASSERT_NOT_ENABLED(dev, tube) ASSERT(!dma_is_enabled(dev, tube))

/* Helpers for dma_tube_cfg() */
static int preconfig_check(dma_dev *dev, dma_tube tube, dma_tube_config *cfg);
static int postconfig_check(dma_tube_reg_map *dummy, dma_tube_config *cfg);
static int config_fifo(dma_tube_reg_map *dummy, dma_tube_config *cfg);
static int config_src_dst(dma_tube_reg_map *dummy, dma_tube_config *cfg);
static void copy_regs(dma_tube_reg_map *src, dma_tube_reg_map *dst);

int dma_tube_cfg(dma_dev *dev, dma_tube tube, dma_tube_config *cfg) {
    return 0;
}

void dma_set_priority(dma_dev *dev, dma_stream stream, dma_priority priority) {

}

void dma_set_num_transfers(dma_dev *dev, dma_tube tube, uint16 num_transfers) {

}

/**
 * @brief Set memory 0 or memory 1 address.
 *
 * This is a general function for setting one of the two memory
 * addresses available on the double-buffered STM32F2 DMA controllers.
 *
 * @param dev     DMA device
 * @param tube    Tube on dev.
 * @param n       If 0, set memory 0 address. If 1, set memory 1 address.
 * @param address Address to set
 */
void dma_set_mem_n_addr(dma_dev *dev, dma_tube tube, int n,
                        __io void *address) {

}

void dma_set_per_addr(dma_dev *dev, dma_tube tube, __io void *address) {

}

/**
 * @brief Enable a stream's FIFO.
 *
 * You may only call this function when the stream is disabled.
 *
 * @param dev  DMA device
 * @param tube Stream whose FIFO to enable.
 */
void dma_enable_fifo(dma_dev *dev, dma_tube tube) {

}

/**
 * @brief Disable a stream's FIFO.
 *
 * You may only call this function when the stream is disabled.
 *
 * @param dev  DMA device
 * @param tube Stream whose FIFO to disable.
 */
void dma_disable_fifo(dma_dev *dev, dma_tube tube) {

}

void dma_attach_interrupt(dma_dev *dev, dma_tube tube,
                          void (*handler)(void)) {

}

void dma_detach_interrupt(dma_dev *dev, dma_tube tube) {

}

void dma_enable(dma_dev *dev, dma_tube tube) {

}

void dma_disable(dma_dev *dev, dma_tube tube) {

}

dma_irq_cause dma_get_irq_cause(dma_dev *dev, dma_tube tube) {
    return DMA_TRANSFER_ERROR;
}

/*
 * IRQ handlers
 */

void __irq_dma1_stream0(void) {

}

void __irq_dma1_stream1(void) {

}

void __irq_dma1_stream2(void) {
}

void __irq_dma1_stream3(void) {

}

void __irq_dma1_stream4(void) {

}

void __irq_dma1_stream5(void) {

}

void __irq_dma1_stream6(void) {

}

void __irq_dma1_stream7(void) {

}

void __irq_dma2_stream0(void) {

}

void __irq_dma2_stream1(void) {

}

void __irq_dma2_stream2(void) {

}

void __irq_dma2_stream3(void) {

}

void __irq_dma2_stream4(void) {

}

void __irq_dma2_stream5(void) {

}

void __irq_dma2_stream6(void) {

}

void __irq_dma2_stream7(void) {

}

/*
 * Auxiliary routines for dma_tube_cfg()
 */

/* Is addr acceptable for use as DMA src/dst? */
static int cfg_mem_ok(__io void *addr) {
    return 0;
}

/* Is src -> dst a reasonable combination of [MEM,PER] -> [MEM,PER]? */
static int cfg_dir_ok(dma_dev *dev, __io void *src, __io void *dst) {
    return 0;
}

/* Initial sanity check for dma_tube_cfg() */
static int preconfig_check(dma_dev *dev, dma_tube tube,
                           dma_tube_config *cfg) {
    return DMA_TUBE_CFG_SUCCESS;
}

static int config_fifo(dma_tube_reg_map *dummy, dma_tube_config *cfg) {
    return DMA_TUBE_CFG_SUCCESS;
}

/* Helper for configuring (DMA_SxCR) */
#define BITS_WE_CARE_ABOUT                                              \
    (DMA_SCR_CHSEL | DMA_SCR_MBURST | DMA_SCR_PBURST | DMA_SCR_PINCOS | \
     DMA_SCR_MINC | DMA_SCR_PINC | DMA_SCR_CIRC | DMA_SCR_DIR |         \
     DMA_SCR_PFCTRL | DMA_SCR_TCIE | DMA_SCR_HTIE | DMA_SCR_TEIE |      \
     DMA_SCR_DMEIE)
static inline void config_scr(dma_tube_reg_map *dummy, dma_tube_config *cfg,
                              unsigned src_shift, uint32 src_inc,
                              unsigned dst_shift, uint32 dst_inc,
                              uint32 dir) {
}
#undef BITS_WE_CARE_ABOUT

/* Helper for when cfg->tube_dst is memory */
static int config_to_mem(dma_tube_reg_map *dummy, dma_tube_config *cfg) {
    return 0;
}

/* Helper for when cfg->tube_src is peripheral */
static int config_to_per(dma_tube_reg_map *dummy, dma_tube_config *cfg) {

    return 0;
}

/* Configures SCR, SPAR, SM0AR, and checks that the result is OK. */
static int config_src_dst(dma_tube_reg_map *dummy, dma_tube_config *cfg) {
    return 0;
}

/* Final checks we can only perform when fully configured */
static int postconfig_check(dma_tube_reg_map *dummy, dma_tube_config *cfg) {
    return DMA_TUBE_CFG_SUCCESS;
}

/* Convenience for dealing with dummy registers */
static void copy_regs(dma_tube_reg_map *src, dma_tube_reg_map *dst) {

}
#endif
