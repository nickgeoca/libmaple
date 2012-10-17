/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
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
 * @file libmaple/usb/stm32f1/usb.c
 * @brief USB support.
 *
 * This is a mess. What we need almost amounts to a ground-up rewrite.
 */

#include <libmaple/usb.h>

#include <libmaple/libmaple.h>
#include <libmaple/rcc.h>

/* Private headers */
#include "usb_reg_map.h"
#include "usb_lib_globals.h"

/* usb_lib headers */
#include "usb_type.h"
#include "usb_core.h"

static void dispatch_ctr_lp(void);

/*
 * usb_lib/ globals
 */

uint16 SaveTState;              /* caches TX status for later use */
uint16 SaveRState;              /* caches RX status for later use */

/*
 * Other state
 */

typedef enum {
    RESUME_EXTERNAL,
    RESUME_INTERNAL,
    RESUME_LATER,
    RESUME_WAIT,
    RESUME_START,
    RESUME_ON,
    RESUME_OFF,
    RESUME_ESOF
} RESUME_STATE;

struct {
  volatile RESUME_STATE eState;
  volatile uint8 bESOFcnt;
} ResumeS;

static usblib_dev usblib = {
    .irq_mask = USB_ISR_MSK,
    .state = USB_UNCONNECTED,
    .clk_id = CLK_USB,
};
usblib_dev *USBLIB = &usblib;

/*
 * Routines
 */

void usb_init_usblib(usblib_dev *dev,
                     void (**ep_int_in)(void),
                     void (**ep_int_out)(void)) {

}

static void usb_suspend(void) {

}

static void usb_resume_init(void) {

}

static void usb_resume(RESUME_STATE eResumeSetVal) {

}

#define SUSPEND_ENABLED 1
void __irq_usb_lp_can_rx0(void) {


}

/*
 * Auxiliary routines
 */

static inline uint8 dispatch_endpt_zero(uint16 istr_dir);
static inline void dispatch_endpt(uint8 ep);
static inline void set_rx_tx_status0(uint16 rx, uint16 tx);

static void handle_setup0(void);
static void handle_in0(void);
static void handle_out0(void);

static void dispatch_ctr_lp() {

}

/* FIXME Dataflow on endpoint 0 RX/TX status is based off of ST's
 * code, and is ugly/confusing in its use of SaveRState/SaveTState.
 * Fixing this requires filling in handle_in0(), handle_setup0(),
 * handle_out0(). */
static inline uint8 dispatch_endpt_zero(uint16 istr_dir) {

}

static inline void set_rx_tx_status0(uint16 rx, uint16 tx) {

}

/* TODO Rip out usb_lib/ dependency from the following functions: */

static void handle_setup0(void) {

}

static void handle_in0(void) {

}

static void handle_out0(void) {

}
