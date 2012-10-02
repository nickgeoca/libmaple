/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * @file wirish/boards.cpp
 * @brief init() and board routines.
 *
 * This file is mostly interesting for the init() function, which
 * configures Flash, the core clocks, and a variety of other available
 * peripherals on the board so the rest of Wirish doesn't have to turn
 * things on before using them.
 *
 * Prior to returning, init() calls boardInit(), which allows boards
 * to perform any initialization they need to. This file includes a
 * weak no-op definition of boardInit(), so boards that don't need any
 * special initialization don't have to define their own.
 *
 * How init() works is chip-specific. See the boards_setup.cpp files
 * under e.g. wirish/stm32f1/, wirish/stmf32f2 for the details, but be
 * advised: their contents are unstable, and can/will change without
 * notice.
 */

#include <wirish/boards.h>
#include <libmaple/libmaple_types.h>
#include <libmaple/flash.h>
#include <libmaple/nvic.h>
#include <libmaple/systick.h>
#include "boards_private.h"

static void setup_flash(void);
static void setup_clocks(void);
static void setup_nvic(void);
static void setup_adcs(void);
static void setup_timers(void);

/*
 * Exported functions
 */

void init(void) {

    //setup_flash();
    setup_clocks();
    setup_nvic();
    systick_init(SYSTICK_RELOAD_VAL);
    wirish::priv::board_setup_gpio();
    setup_adcs();
    setup_timers();
    //wirish::priv::board_setup_usb();
    wirish::priv::series_init();
    boardInit();
}

/* Provide a default no-op boardInit(). */
__weak void boardInit(void) {
}

/* You could farm this out to the files in boards/ if e.g. it takes
 * too long to test on boards with lots of pins. */
bool boardUsesPin(uint8 pin) {

    return false;
}

/*
 * Auxiliary routines
 */

static void setup_flash(void) {
    // Turn on as many Flash "go faster" features as
    // possible. flash_enable_features() just ignores any flags it
    // can't support.
    flash_enable_features(FLASH_PREFETCH | FLASH_ICACHE | FLASH_DCACHE);
    // Configure the wait states, assuming we're operating at "close
    // enough" to 3.3V.
    flash_set_latency(FLASH_CFGR_SPMD_MODE0);
}


static void setup_clocks(void) {
    clk_init(CLOCK_SPEED_HZ, AHB_CLK_DIVIDER, APB_CLK_DIVIDER);
}

/*
 * These addresses are where usercode starts when a bootloader is
 * present. If no bootloader is present, the user NVIC usually starts
 * at the Flash base address, 0x08000000.
 *
 * FIXME Let the build specify the vector table address numerically to
 * avoid having these magic values -- some people have been fixing up
 * the bootloader so it uses less space.
 */
#define USER_ADDR_ROM 0x1400
#define USER_ADDR_RAM 0x20000000

static void setup_nvic(void) {
    nvic_init(USER_ADDR_ROM, 0);
}

static void adc_default_config(const adc_dev *dev) {
    adc_enable_single_swstart(dev);
    adc_set_sample_rate(dev, wirish::priv::w_adc_smp);
}

static void setup_adcs(void) {
    adc_foreach(adc_default_config);
}

static void timer_default_config(timer_dev *dev) {
    timer_init(dev);
    //timer_pause(dev);

    //timer_generate_update(dev);
    timer_resume(dev);

}

static void setup_timers(void) {

    timer_foreach(timer_default_config);
}
