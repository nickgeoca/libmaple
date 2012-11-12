cs-make clean
cs-make
avrdude -p m2560 -c stk500v2 -P com9 -b 115200 -e -U build\si_arduino.hex
COPY build\si_arduino.hex Si32FlashUtility\SiM3U167_ACB_Rev000\si_wiring.hex

PAUSE