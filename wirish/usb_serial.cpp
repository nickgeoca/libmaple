/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * @brief USB virtual serial terminal
 */

#include <wirish/usb_serial.h>

#include <string.h>
#include <stdint.h>

#include <libmaple/nvic.h>
#include <libmaple/usb_cdcacm.h>
#include <libmaple/usb.h>

#include <wirish/wirish.h>

/*
 * Hooks used for bootloader reset signalling
 */

#if BOARD_HAVE_SERIALUSB
static void rxHook(unsigned, void*);
static void ifaceSetupHook(unsigned, void*);
#endif

/*
 * USBSerial interface
 */

#define USB_TIMEOUT 50

USBSerial::USBSerial(void) {
#if !BOARD_HAVE_SERIALUSB
    ASSERT(0);
#endif
}

void USBSerial::begin(void) {
}

void USBSerial::end(void) {
}

void USBSerial::write(uint8 ch) {
    this->write(&ch, 1);
}

void USBSerial::write(const char *str) {
    this->write(str, strlen(str));
}

void USBSerial::write(const void *buf, uint32 len) {

}

uint32 USBSerial::available(void) {
    return 0;
}

uint32 USBSerial::read(void *buf, uint32 len) {
    return 0;
}

/* Blocks forever until 1 byte is received */
uint8 USBSerial::read(void) {
    return 0;
}

uint8 USBSerial::pending(void) {
    return usb_cdcacm_get_pending();
}

uint8 USBSerial::isConnected(void) {
    return 0;
}

uint8 USBSerial::getDTR(void) {
    return 0;
}

uint8 USBSerial::getRTS(void) {
    return 0;
}

#if BOARD_HAVE_SERIALUSB
USBSerial SerialUSB;
#endif

/*
 * Bootloader hook implementations
 */

#if BOARD_HAVE_SERIALUSB

enum reset_state_t {
    DTR_UNSET,
    DTR_HIGH,
    DTR_NEGEDGE,
    DTR_LOW
};

static reset_state_t reset_state = DTR_UNSET;

static void ifaceSetupHook(unsigned hook, void *requestvp) {

}

#define RESET_DELAY 100000
static void wait_reset(void) {

}

#define STACK_TOP 0x20000800
#define EXC_RETURN 0xFFFFFFF9
#define DEFAULT_CPSR 0x61000000
static void rxHook(unsigned hook, void *ignored) {

}

#endif  // BOARD_HAVE_SERIALUSB
