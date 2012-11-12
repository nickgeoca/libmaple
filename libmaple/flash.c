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
 * @file libmaple/flash.c
 * @brief Flash management functions
 */

#include <libmaple/libmaple_types.h>
#include <libmaple/flash.h>

static inline void flash_unlock_multi(void)
{
    // Enable vdd supply monitor and set as reset source
    REG_SET_CLR(*(__io uint32*)0x4002F000, 1, 0x80000000);
    REG_SET_CLR(*(__io uint32*)0x4002D060, 1, 0x00000004);

    // Unlock for multiple writes
    FLASH_BASE->KEYR = FLASH_KEYR_INITIAL_UNLOCK;
    FLASH_BASE->KEYR = FLASH_KEYR_MULTI_UNLOCK;
}

static inline void flash_lock_multi(void)
{
    FLASH_BASE->KEYR = FLASH_KEYR_MULTI_LOCK;
}

static inline void flash_set_addr(uint32 addr) {
    FLASH_BASE->WRADDRR = addr;
}


void flash_erase_page(uint32 address) {
    // Enable flash erase
    REG_SET_CLR(FLASH_BASE->CFGR, 1, FLASH_CFGR_ERASEEN_EN);

    // Unlock flash for multiple write
    flash_unlock_multi();

    // Set address register
    flash_set_addr(address);

    // Erase page
    FLASH_BASE->WRDATAR = 0;

    // Lock
    flash_lock_multi();

    // Disable erase mode
    REG_SET_CLR(FLASH_BASE->CFGR, 0, FLASH_CFGR_ERASEEN_EN);
}

// Writes 16 bits to flash
void flash_write_data(uint32 address, uint16 data[], int32 count) {
    uint32 up_count;

    // Unlock flash for multiple write
    flash_unlock_multi();


    // Set address register
    flash_set_addr(address);

    for (up_count = 0; up_count != count; up_count++) {
        FLASH_BASE->WRDATAR = data[up_count];
    }

    flash_lock_multi();
}

