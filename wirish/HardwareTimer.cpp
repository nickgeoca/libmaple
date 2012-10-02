/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
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

#include <wirish/HardwareTimer.h>

#include <libmaple/rcc.h>
#include <wirish/ext_interrupts.h> // for noInterrupts(), interrupts()
#include <wirish/wirish_math.h>
#include <board/board.h>           // for CYCLES_PER_MICROSECOND

// TODO [0.1.0] Remove deprecated pieces

/*
 * Evil hack to infer this->dev from timerNum in the HardwareTimer
 * constructor. See:
 *
 * http://www.parashift.com/c++-faq-lite/pointers-to-members.html#faq-33.2
 * http://yosefk.com/c++fqa/function.html#fqa-33.2
 */

extern "C" {
    static timer_dev **this_devp;
    static clk_dev_id this_id;
    static void set_this_dev(timer_dev *dev) {

    }
}

/*
 * HardwareTimer routines
 */

HardwareTimer::HardwareTimer(uint8 timerNum) {

}

void HardwareTimer::pause(void) {

}

void HardwareTimer::resume(void) {

}

uint32 HardwareTimer::getPrescaleFactor(void) {
    return 0;
}

void HardwareTimer::setPrescaleFactor(uint32 factor) {

}

uint16 HardwareTimer::getOverflow() {
    return 0;
}

void HardwareTimer::setOverflow(uint16 val) {
    return;
}

uint16 HardwareTimer::getCount(void) {
    return 0;
}

void HardwareTimer::setCount(uint16 val) {
    return;
}

#define MAX_RELOAD ((1 << 16) - 1)
uint16 HardwareTimer::setPeriod(uint32 microseconds) {
    return 0;
}

void HardwareTimer::setMode(int channel, timer_mode mode) {

}

uint16 HardwareTimer::getCompare(int channel) {
    return 0;
}

void HardwareTimer::setCompare(int channel, uint16 val) {

}

void HardwareTimer::attachInterrupt(int channel, voidFuncPtr handler) {

}

void HardwareTimer::detachInterrupt(int channel) {

}

void HardwareTimer::refresh(void) {

}

/* -- Deprecated predefined instances -------------------------------------- */

HardwareTimer Timer1(1);
HardwareTimer Timer2(2);
HardwareTimer Timer3(3);
HardwareTimer Timer4(4);
#ifdef STM32_HIGH_DENSITY
HardwareTimer Timer5(5);
HardwareTimer Timer6(6);
HardwareTimer Timer7(7);
HardwareTimer Timer8(8);
#endif
