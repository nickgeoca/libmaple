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
 * @file Wire.cpp
 * @author Trystan Jones <crenn6977@gmail.com>
 * @brief Wire library, uses the WireBase to create the primary interface
 *        while keeping low level interactions invisible to the user.
 */

/*
 * Library updated by crenn to follow new Wire system.
 * Code was derived from the original Wire for maple code by leaflabs and the
 * modifications by gke and ala42.
 */

#include <Wire/Wire.h>

#define I2C_WRITE 0
#define I2C_READ  1

/* low level conventions:
 * - SDA/SCL idle high (expected high)
 * - always start with i2c_delay rather than end
 */

void TwoWire::set_scl(bool state) {

}

void TwoWire::set_sda(bool state) {

}

void TwoWire::i2c_start() {

}

void TwoWire::i2c_stop() {

}

bool TwoWire::i2c_get_ack() {

    return true;
}

void TwoWire::i2c_send_ack() {

}

void TwoWire::i2c_send_nack() {

}

uint8 TwoWire::i2c_shift_in() {
    return 0;
}

void TwoWire::i2c_shift_out(uint8 val) {

}

uint8 TwoWire::process() {
    return 0;
}

// TODO: Add in Error Handling if pins is out of range for other Maples
// TODO: Make delays more capable
TwoWire::TwoWire(uint8 scl, uint8 sda, uint8 delay) : i2c_delay(delay) {
}

void TwoWire::begin(uint8 self_addr) {

}

TwoWire::~TwoWire() {

}

// Declare the instance that the users of the library can use
TwoWire Wire(SCL, SDA, SOFT_STANDARD);
