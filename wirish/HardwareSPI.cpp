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
#include <libmaple/spi.h>

#include <wirish/wirish.h>
#include <wirish/boards.h>

HardwareSPI Spi1(1);
HardwareSPI Spi2(2);
HardwareSPI Spi3(3);


struct spi_pins {
    uint8 nss;
    uint8 sck;
    uint8 miso;
    uint8 mosi;
};

static const spi_pins* dev_to_spi_pins(spi_dev *dev);

static void enable_device(spi_dev *dev,
                          bool as_master,
                          uint32 frequency,
                          spi_cfg_flag endianness,
                          spi_mode mode);


static const spi_pins board_spi_pins[] __FLASH__ = {

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

};


/*
 * Constructor
 */

HardwareSPI::HardwareSPI(uint32 spi_num) {
    switch (spi_num) {
    case 1:
        this->spi_d = SPI1;
        break;
    case 2:
        this->spi_d = SPI2;
        break;
    case 3:
        this->spi_d = SPI3;
        break;
    default:
        ASSERT(0);
    }
}

/*
 * Set up/tear down
 */

void HardwareSPI::begin(uint32 frequency, uint32 bitOrder, uint32 mode) {

    if (mode >= 4 || frequency > 10000000) {

        ASSERT(0);
        return;
    }
    spi_cfg_flag end = bitOrder == MSBFIRST ? SPI_FRAME_MSB : SPI_FRAME_LSB;
    spi_mode m = (spi_mode)mode;
    enable_device(this->spi_d, true, frequency, end, m);
}

void HardwareSPI::begin(void) {

    this->begin(5000000, MSBFIRST, 0);

}

void HardwareSPI::beginSlave(uint32 bitOrder, uint32 mode) {
    if (mode >= 4) {
        ASSERT(0);
        return;
    }
    spi_cfg_flag end = bitOrder == MSBFIRST ? SPI_FRAME_MSB : SPI_FRAME_LSB;
    spi_mode m = (spi_mode)mode;

    enable_device(this->spi_d, false, 0, end, m);

}

void HardwareSPI::beginSlave(void) {
    this->beginSlave(MSBFIRST, 0);
}

void HardwareSPI::end(void) {
    if (!spi_is_enabled(this->spi_d)) {
        return;
    }
    while (spi_is_busy(this->spi_d))
        ;
    spi_peripheral_disable(this->spi_d);
}

/*
 * I/O
 */

uint8 HardwareSPI::read(void) {
    uint8 buf[1];
    this->read(buf, 1);
    return buf[0];
}

void HardwareSPI::read(uint8 *buf, uint32 len) {
    uint32 rxed = 0;
    while (rxed < len) {
        while (!spi_is_rx_nonempty(this->spi_d))
            ;
        buf[rxed++] = (uint8)spi_rx_reg(this->spi_d);
    }
}

void HardwareSPI::write(uint8 byte) {
    this->write(&byte, 1);
}

void HardwareSPI::write(const uint8 *data, uint32 length) {
    uint32 txed = 0;

    // Transfer data
    while (txed < length) {
        txed += spi_tx(this->spi_d, data + txed, length - txed);
    }
    // Wait till transfer is complete
    while (spi_is_busy(this->spi_d));
}

void HardwareSPI::write(const uint8 *data, uint32 length, uint8 slaveNum) {
    uint32 txed = 0;

    // Select chip
    digitalWrite(this->nssPin(), LOW);
    // Transfer data
    while (txed < length) {
        txed += spi_tx(this->spi_d, data + txed, length - txed);
    }
    // Wait till transfer is complete
    while (spi_is_busy(this->spi_d));
    // De-select chip
    digitalWrite(this->nssPin(), HIGH);
}

uint8 HardwareSPI::transfer(uint8 byte) {
    this->write(byte);
    return this->read();
}

uint8 HardwareSPI::transfer(uint8 byte, uint8 slaveNum) {
    this->write(&byte, 1, slaveNum);
    return this->read();
}



/*
 * Pin accessors
 */

uint8 HardwareSPI::misoPin(void) {
    return dev_to_spi_pins(this->spi_d)->miso;
}

uint8 HardwareSPI::mosiPin(void) {
    return dev_to_spi_pins(this->spi_d)->mosi;
}

uint8 HardwareSPI::sckPin(void) {
    return dev_to_spi_pins(this->spi_d)->sck;
}

uint8 HardwareSPI::nssPin(void) {
    return dev_to_spi_pins(this->spi_d)->nss;
}

/*
 * Deprecated functions
 */

uint8 HardwareSPI::send(uint8 data) {
    uint8 buf[] = {data};
    return this->send(buf, 1);
}

uint8 HardwareSPI::send(uint8 *buf, uint32 len) {
    uint32 txed = 0;
    uint8 ret = 0;
    while (txed < len) {
        this->write(buf[txed++]);
        ret = this->read();
    }
    return ret;
}

uint8 HardwareSPI::recv(void) {
    return this->read();
}

/*
 * Auxiliary functions
 */

static void configure_gpios(spi_dev *dev, bool as_master);

static const spi_pins* dev_to_spi_pins(spi_dev *dev) {
    switch (dev->clk_id) {
    case CLK_SPI1: return board_spi_pins;
    case CLK_SPI2: return board_spi_pins + 1;
    case CLK_SPI3: return board_spi_pins + 2;
    default:       return NULL;
    }
}

/* Enables the device in master or slave full duplex mode.  If you
 * change this code, you must ensure that appropriate changes are made
 * to HardwareSPI::end(). */
static void enable_device(spi_dev *dev,
                          bool as_master,
                          uint32 freq,
                          spi_cfg_flag endianness,
                          spi_mode mode) {
    uint32 cfg_flags = (endianness | SPI_DFF_8_BIT |
                        (as_master ?
                                SPI_MASTER | SPI_MODE_MST_SLV_3WIRE:  // Master flags
                                SPI_MODE_SLV_4WIRE | SPI_SLVNSS_LOW)); // Slave flags

    spi_init(dev);
    configure_gpios(dev, as_master);
    if (as_master) {
        spi_master_enable(dev, freq, mode, cfg_flags);
    } else {
        spi_slave_enable(dev, mode, cfg_flags);
    }
}


static void disable_pwm(const stm32_pin_info *i) {
    if (i->timer_device) {
        timer_set_mode(i->timer_device, i->timer_channel, TIMER_DISABLED);
    }
}

static void configure_gpios(spi_dev *dev, bool as_master) {
    const spi_pins *pins = dev_to_spi_pins(dev);
    if (!pins) {
        return;
    }

    const stm32_pin_info *nssi = &PIN_MAP[pins->nss];
    const stm32_pin_info *scki = &PIN_MAP[pins->sck];
    const stm32_pin_info *misoi = &PIN_MAP[pins->miso];
    const stm32_pin_info *mosii = &PIN_MAP[pins->mosi];

    disable_pwm(nssi);
    disable_pwm(scki);
    disable_pwm(misoi);
    disable_pwm(mosii);

    spi_config_gpios(dev, as_master, nssi->gpio_device, nssi->gpio_bit,
                     scki->gpio_device, scki->gpio_bit, misoi->gpio_bit,
                     mosii->gpio_bit);
}
