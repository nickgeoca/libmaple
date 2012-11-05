// Demo code.

#include <string.h>
#include <wirish/wirish.h>

void init(void);
HardwareSerial &Serial = Serial2;
HardwareSPI &Spi = Spi3;


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
void spiTestMaster(void)
{
    uint32 cntr = 256;
    uint8 curr = 0;
    uint8 last = 0;
    uint8 tmp;
    while (cntr--) {
        curr += 1;
        tmp = Spi.transfer(curr, 0);
        if (tmp != last) {
            Serial.println("Fail ");
            Serial.print("\tExpected: ");
            Serial.println(last);
            Serial.print("\tReceived: ");
            Serial.println(tmp);
        }
        last = curr;
        delay(20);
    }
    Serial.println("Spi test complete.");
}
void spiTestSlave(void)
{
    uint8 curr = 0;
    uint8 last = 0;
    while (1) {
        last = curr;
        Serial.print("tx ");
        Serial.print(last);
        curr = Spi.transfer(curr);
        Serial.print("; rx ");
        Serial.println(curr);

        curr = Spi.transfer(curr);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// Wiring setup/loop
///////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
//// Init peripherals
    // Uart
    initUARTs();

    // Timers
    initTimer();

    // SPI
    Spi.begin(2500000, LSBFIRST, 0);
    //Spi.beginSlave(LSBFIRST, 0);

////
    char formFeed[] = {0x1B, 0x5B, 0x32, 0x4A, 0x00};
    Serial.print(formFeed);
    Serial.println("\f\tExample Program");
}

void loop () {
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

