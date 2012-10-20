cs-make clean
cs-make
Si32FlashUtility\Si32FlashUtility -i build\si_arduino.hex
COPY build\si_arduino.hex Si32FlashUtility\SiM3U167_ACB_Rev000\si_wiring.hex

PAUSE