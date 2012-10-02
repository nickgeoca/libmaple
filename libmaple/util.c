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
 * @file libmaple/util.c
 * @brief Utility procedures for debugging
 */

#include <libmaple/libmaple.h>
#include <libmaple/usart.h>
#include <libmaple/gpio.h>
#include <libmaple/nvic.h>

/* (Undocumented) hooks used by Wirish to direct our behavior here */
extern __weak void __lm_error(void);
extern __weak usart_dev* __lm_enable_error_usart(void);

/* If you define ERROR_LED_PORT and ERROR_LED_PIN, then a failed
 * ASSERT() will also throb() an LED connected to that port and pin.
 */
#if defined(ERROR_LED_PORT) && defined(ERROR_LED_PIN)
#define HAVE_ERROR_LED
#endif

/* (Called from exc.S with global interrupts disabled.) */
__attribute__((noreturn)) void __error(void) {

}

/*
 * Print an error message on a UART upon a failed assertion (if one is
 * available), and punt to __error().
 *
 * @param file Source file of failed assertion
 * @param line Source line of failed assertion
 * @param exp String representation of failed assertion
 * @sideeffect Turns of all peripheral interrupts except USB.
 */
void _fail(const char* file, int line, const char* exp) {

}

/*
 * Provide an __assert_func handler to libc so that calls to assert()
 * get redirected to _fail.
 */
void __assert_func(const char* file, int line, const char* method,
                   const char* expression) {

}

/*
 * Provide an abort() implementation that aborts execution and punts
 * to __error().
 */
void abort() {


}

/* This was public as of v0.0.12, so we've got to keep it public. */
/**
 * @brief Fades the error LED on and off
 * @sideeffect Sets output push-pull on ERROR_LED_PIN.
 */
__attribute__((noreturn)) void throb(void) {

}
