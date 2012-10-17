MCU := SIM3U167
PRODUCT_ID := 0003
ERROR_LED_PORT := GPIOD
ERROR_LED_PIN  := 0
MCU_SERIES := sim3u1
# This crap is due to ld-script limitations. If you know of a better
# way to go about this (like some magic ld switches to specify MEMORY
# at the command line), please tell us!
LD_MEM_DIR := sim3u1_sram_32k_flash_256k
