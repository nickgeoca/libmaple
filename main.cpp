// Demo code.

#include <string.h>
#include <wirish/wirish.h>

void init(void);
HardwareSerial &Serial = Serial2;
HardwareSPI &Spi = Spi3;

//**************************************************************************************************
//                                      Miscellaneous
//**************************************************************************************************
void mem_read(uint32 count, uint32 address, Print *p_out)
{
    for (int i = 0; i < (count / 16); i++) {
        p_out->println("");
        p_out->print((uint16)(address + i * 16), HEX);
        p_out->print(":");
        for (int i2 = 0; i2 < 16; i2++) {
            uint8 data = *(__io uint8 *)(address + i * 16 + i2);
            if ((i2 % 4) == 0) p_out->print(" ");
            if (data < 16) p_out->print("0");
            p_out->print(data, HEX);
        }
    }
    p_out->println("");
}

//**************************************************************************************************
//                                      Hardware Initialization
//**************************************************************************************************
void initUARTs(void) {
    //Serial1.begin(115200);
    Serial2.begin(115200);
    //Serial3.begin(115200);
    //Serial4.begin(115200);
}

void initTimer(void)
{
    HardwareTimer *timerArray[] = {&Timer1, &Timer2, &Timer3, &Timer4, &Timer5};

    // Set prescalers and overflows
    for (int i = 0; i < 5; i++) {
        timerArray[i]->pause();
        timerArray[i]->setPrescaleFactor(1);
        timerArray[i]->setOverflow(10000);
        timerArray[i]->resume();
    }

    // Set compares and channel modes
    for (int i = 1; i <= 6; i++) {
        timerArray[0]->setCompare(i, 4000);

    }
    for (int i = 1; i <= 2; i++) {
        timerArray[1]->setCompare(i, 4000);
        timerArray[2]->setCompare(i, 4000);
    }
    timerArray[3]->setCompare(1, 30000);
    timerArray[4]->setCompare(1, 30000);

    // Set timer channels to PWM
    // for (int i = 1; i <= 6; i++) timerArray[0]->setMode(i, TIMER_PWM);
    // for (int i = 1; i <= 2; i++) timerArray[1]->setMode(i, TIMER_PWM);
    // for (int i = 1; i <= 1; i++) timerArray[2]->setMode(i, TIMER_PWM);
    // timerArray[3]->setMode(1, TIMER_PWM);
    // timerArray[4]->setMode(1, TIMER_PWM);

    // Set GPIO pins to PWM
    // for (int i = 0; i < BOARD_NR_PWM_PINS; i++) pinMode(boardPWMPins[i], PWM);
}

void initSPI(void)
{
    //Spi1.begin(2500000, LSBFIRST, 0);
    //Spi2.begin(2500000, LSBFIRST, 0);
    //Spi3.begin(2500000, LSBFIRST, 0);
}

//**************************************************************************************************
//                                      Wiring setup/loop
//**************************************************************************************************
void setup() {
    // Init peripherals
    initUARTs();
    initTimer();
    initSPI();

    // Setup terminal
    //char formFeed[] = {0x1B, 0x5B, 0x32, 0x4A, 0x00};
    //Serial.print(formFeed);
    //Serial.println("\fProgram Start");

    pinMode(D13, OUTPUT);
}

void loop () {
    static uint32 delay_time = 50;
    delay_time += 13;
    delay_time = delay_time % 200;
    delay(delay_time);
    togglePin(D13);
}


// -- premain() and main() ----------------------------------------------------

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}

