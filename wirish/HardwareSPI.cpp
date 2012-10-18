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
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief Wirish SPI implementation.
 */

#include <wirish/HardwareSPI.h>

#include <libmaple/timer.h>
#include <libmaple/util.h>
#include <libmaple/rcc.h>

#include <wirish/wirish.h>
#include <wirish/boards.h>

struct spi_pins {
    uint8 nss;
    uint8 sck;
    uint8 miso;
    uint8 mosi;
};

static const spi_pins* dev_to_spi_pins(spi_dev *dev);

static void enable_device(spi_dev *dev,
                          bool as_master,
                          SPIFrequency frequency,
                          spi_cfg_flag endianness,
                          spi_mode mode);


static const spi_pins board_spi_pins[] __FLASH__ = {
#if 0 // TODO [silabs]: HardwareSPI.cpp
    {BOARD_SPI1_NSS_PIN,
     BOARD_SPI1_SCK_PIN,
     BOARD_SPI1_MISO_PIN,
     BOARD_SPI1_MOSI_PIN},
    {BOARD_SPI2_NSS_PIN,
     BOARD_SPI2_SCK_PIN,
     BOARD_SPI2_MISO_PIN,
     BOARD_SPI2_MOSI_PIN},
    {BOARD_SPI3_NSS_PIN,
     BOARD_SPI3_SCK_PIN,
     BOARD_SPI3_MISO_PIN,
     BOARD_SPI3_MOSI_PIN},
#endif
};


/*
 * Constructor
 */

HardwareSPI::HardwareSPI(uint32 spi_num) {

}

/*
 * Set up/tear down
 */

void HardwareSPI::begin(SPIFrequency frequency, uint32 bitOrder, uint32 mode) {

}

void HardwareSPI::begin(void) {

}

void HardwareSPI::beginSlave(uint32 bitOrder, uint32 mode) {

}

void HardwareSPI::beginSlave(void) {

}

void HardwareSPI::end(void) {

}

/*
 * I/O
 */

uint8 HardwareSPI::read(void) {
    return 0;
}

void HardwareSPI::read(uint8 *buf, uint32 len) {

}

void HardwareSPI::write(uint8 byte) {

}

void HardwareSPI::write(const uint8 *data, uint32 length) {

}

uint8 HardwareSPI::transfer(uint8 byte) {
    return 0;
}

/*
 * Pin accessors
 */

uint8 HardwareSPI::misoPin(void) {
    return 0;
}

uint8 HardwareSPI::mosiPin(void) {
    return 0;
}

uint8 HardwareSPI::sckPin(void) {
    return 0;
}

uint8 HardwareSPI::nssPin(void) {
    return 0;
}

/*
 * Deprecated functions
 */

uint8 HardwareSPI::send(uint8 data) {
    return 0;
}

uint8 HardwareSPI::send(uint8 *buf, uint32 len) {
    return 0;
}

uint8 HardwareSPI::recv(void) {
    return 0;
}

/*
 * Auxiliary functions
 */

static void configure_gpios(spi_dev *dev, bool as_master);
static spi_baud_rate determine_baud_rate(spi_dev *dev, SPIFrequency freq);

static const spi_pins* dev_to_spi_pins(spi_dev *dev) {
    return NULL;
}

/* Enables the device in master or slave full duplex mode.  If you
 * change this code, you must ensure that appropriate changes are made
 * to HardwareSPI::end(). */
static void enable_device(spi_dev *dev,
                          bool as_master,
                          SPIFrequency freq,
                          spi_cfg_flag endianness,
                          spi_mode mode) {

}

static void disable_pwm(const stm32_pin_info *i) {

}

static void configure_gpios(spi_dev *dev, bool as_master) {

}

static const spi_baud_rate baud_rates[MAX_SPI_FREQS] __FLASH__ = {
    SPI_BAUD_PCLK_DIV_2,
    SPI_BAUD_PCLK_DIV_4,
    SPI_BAUD_PCLK_DIV_8,
    SPI_BAUD_PCLK_DIV_16,
    SPI_BAUD_PCLK_DIV_32,
    SPI_BAUD_PCLK_DIV_64,
    SPI_BAUD_PCLK_DIV_128,
    SPI_BAUD_PCLK_DIV_256,
};

/*
 * Note: This assumes you're on a LeafLabs-style board
 * (CYCLES_PER_MICROSECOND == 72, APB2 at 72MHz, APB1 at 36MHz).
 */
static spi_baud_rate determine_baud_rate(spi_dev *dev, SPIFrequency freq) {
    return SPI_BAUD_PCLK_DIV_4;
}
