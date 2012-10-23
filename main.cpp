// Demo code.

#include <string.h>
#include <wirish/wirish.h>

void init(void);

HardwareTimer Timer1(1);
HardwareTimer Timer2(2);
HardwareTimer Timer3(3);
HardwareTimer Timer4(4);
HardwareTimer Timer5(5);
const char g_clrBuff[] = {0x1b, 0x5b, 0x41, 0x00};
#define DISPLAY_CURSOR_DN(n) do{for (int i = 0; i < n; i++) Serial2.println(""); } while(0)
#define DISPLAY_CURSOR_UP(n) do{for (int i = 0; i < n; i++) Serial2.print(g_clrBuff); Serial2.print((char)'\r');} while(0)
#define DISPLAY_ERASE(n) do{for (int i = 0; i < n; i++) Serial2.print((char)' '); for (int i = 0; i < n; i++) Serial2.print((char)'\b');} while(0)

#define DISPLAY_INFO_CURSOR_UP BOARD_NR_ADC_PINS + 16


///////////////////////////////////////////////////////////////////////////////////////////////////
// Callbacks
///////////////////////////////////////////////////////////////////////////////////////////////////
const uint32 exti_D38Info = 38;
void *exti_varD38 = (void *)exti_D38Info;
__io uint32 g_extiCounter = 0;
__io uint32 g_extiLastPin = 0;
void extiCallback1(void *var) {
    g_extiLastPin = (uint32 )var;
    g_extiCounter +=1;
}

__io uint32 g_timerCounter = 0;
void timerOutputCmpCallback(void)
{
    g_timerCounter += 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// ADC code
///////////////////////////////////////////////////////////////////////////////////////////////////
void measure_adc_noise(uint8 pin, uint32 smpl_cnt) {
    uint16 x;
    float mean = 0;
    float delta = 0;
    float M2 = 0;

    // Variance algorithm from Welford, via Knuth, by way of Wikipedia:
    // http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#On-line_algorithm
    for (int sample = 0; sample < 1; sample++) {
        for (int i = 1; i <= smpl_cnt; i++) {
            x = analogRead(pin);
            delta = x - mean;
            mean += delta / i;
            M2 = M2 + delta * (x - mean);
        }
        Serial2.print("A");
        Serial2.print(pin - A0, DEC);
        Serial2.print("\tn: ");
        Serial2.print(smpl_cnt, DEC);
        Serial2.print("\tmean: ");
        DISPLAY_ERASE(9);
        Serial2.print(mean);
        Serial2.print("\tvariance: ");
        DISPLAY_ERASE(9);
        Serial2.println(M2 / (float)(smpl_cnt-1));
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// UART code
///////////////////////////////////////////////////////////////////////////////////////////////////
void initUARTs(void) {
    //Serial1.begin(115200);
    Serial2.begin(115200);
    Serial3.begin(115200);
    Serial4.begin(115200);
}

void serial2_Display(void)
{
    const int N = 20;

    // UART Rx
    DISPLAY_CURSOR_UP(1);
    Serial2.println("- Command Processor:");


    // SysTick
    Serial2.println("\n\n- SysTick");
    Serial2.print("System Time: ");
    uint32 ms = millis();
    Serial2.print(ms / 1000);
    Serial2.print((char)'.');
    Serial2.print(ms % 1000);
    Serial2.println("s");
    Serial2.print("5 ms delay test: measured ");
    uint32 t1 = micros();
    delay(5);
    uint32 t2 = micros();
    Serial2.print(t2 - t1);
    Serial2.println("us\n");

    // ADC
    Serial2.println("- ADC");
    for (int i = 0; i < BOARD_NR_ADC_PINS; i++)
        measure_adc_noise(boardADCPins[i], N);

    // Timers
    Serial2.println("\n- Timers");
    Serial2.print("Prescalers: T1-");
    Serial2.print(Timer1.getPrescaleFactor());
    Serial2.print(" | T2-");
    Serial2.print(Timer2.getPrescaleFactor());
    Serial2.print(" | T3-");
    Serial2.print(Timer3.getPrescaleFactor());
    Serial2.print(" | T4-");
    Serial2.print(Timer4.getPrescaleFactor());
    Serial2.print(" | T5-");
    DISPLAY_ERASE(6);
    Serial2.println(Timer5.getPrescaleFactor());
    Serial2.print("Overflow Values: T1-");
    Serial2.print(Timer1.getOverflow());
    Serial2.print(" | T2-");
    Serial2.print(Timer2.getOverflow());
    Serial2.print(" | T3-");
    Serial2.print(Timer3.getOverflow());
    Serial2.print(" | T4-");
    Serial2.print(Timer4.getOverflow());
    Serial2.print(" | T5-");
    DISPLAY_ERASE(6);
    Serial2.println(Timer5.getOverflow());
    Serial2.print("Compare Values: T1C1-");
    Serial2.print(Timer1.getCompare(1));
    Serial2.print(" | T1C2-");
    Serial2.print(Timer1.getCompare(2));
    Serial2.print(" | T2C1-");
    Serial2.print(Timer2.getCompare(1));
    Serial2.print(" | T2C2-");
    Serial2.print(Timer2.getCompare(2));
    Serial2.print(" | T5Cx-");
    DISPLAY_ERASE(6);
    Serial2.println(Timer5.getCompare(1));
    Serial2.print("IRQ Counter: ");
    Serial2.println(g_timerCounter);

    // EXTI
    Serial2.println("\n- EXTI");
    Serial2.print("IRQ Counter: ");
    Serial2.print(g_extiCounter);
    Serial2.print("  (last changed by Pin D");
    Serial2.print(g_extiLastPin);
    Serial2.println(')');

    // Move cursor up
    DISPLAY_CURSOR_UP(DISPLAY_INFO_CURSOR_UP);
}

void serial2_Start(void)
{
    char formFeed[] = {0x1B, 0x5B, 0x32, 0x4A, 0x00};
    Serial2.print(formFeed);
    Serial2.println("\f\tExample Program");
    Serial2.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    Serial2.print("Board freqency: ");
    Serial2.println(clk_get_sys_freq());
    Serial2.println(" * Timers\tD30 - D35, A1, D22 - D24, A9, A11");
    Serial2.println(" * ADC\tsee ADC output pins");
    Serial2.println(" * SysTick");
    Serial2.println(" * UART2");
    Serial2.println(" * EXTI\tshort D38 & D39");
    Serial2.println("Enter 1 to control Timers");
    Serial2.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Miscellaneous
///////////////////////////////////////////////////////////////////////////////////////////////////
void tglLed(void)
{
    static int32 rate = 50;
    for (int8 count = 4; count; count--) {
        delay(rate);
        toggleLED();
        delay(rate);
        toggleLED();
    }
    rate = ((rate + 24) % 50) + 1;
}

void timerControl(void) {
    HardwareTimer *timerArray[] = {&Timer1, &Timer2, &Timer3, &Timer4, &Timer5};
    char mode, tNum, cNum;
    Serial2.print("0-pause 1-resume 2-prescl 3-ovflow 4-cmpr .exit: ");
    mode = Serial2.read();
    mode -= 0x30;
    Serial2.println(int(mode));

    if (mode > 4) {
        goto exit;
    }

    Serial2.print("Enter timer #: \r");
    tNum = Serial2.read();
    tNum -= 0x31;
    if (tNum > 5) {
        goto exit;
    }
    if (mode == 0) {
        timerArray[tNum]->pause();
        goto exit;
    }
    if (mode == 1) {
        timerArray[tNum]->resume();
        goto exit;
    }
    DISPLAY_ERASE(20);
    if (mode > 3) {
        Serial2.print("Enter chnl#: \r");
        cNum = Serial2.read();
        cNum -= 0x30;
    }
    DISPLAY_ERASE(20);
    Serial2.print("Use to change: '-','+',<other>");
    char tmp;
    while ((tmp = Serial2.read()) == '-' || tmp == '+') {
        switch (mode) {
        case 2:
            timerArray[tNum]->setPrescaleFactor(timerArray[tNum]->getPrescaleFactor() + (tmp == '+' ? 1 : -1));
            break;
        case 3:
            timerArray[tNum]->setOverflow(timerArray[tNum]->getOverflow() + (tmp == '+' ? 20 : -20));
            break;
        case 4:
            timerArray[tNum]->setCompare(cNum, timerArray[tNum]->getCompare(cNum) + (tmp == '+' ? 200 : -200));
            break;
        }
    }
exit:
    Serial2.print('\r');
    DISPLAY_ERASE(55);
    DISPLAY_CURSOR_UP(1);
    return;
}

void cmdProc(void)
{
    char mode;
    int numChars;

    if (!Serial2.available()) {
        return;
    }
    mode = Serial2.read();

    Serial2.flush();

    if (mode == '1') {
        timerControl();
        Serial2.flush();
    }
    DISPLAY_ERASE(55);
    Serial2.print('\r');
    Serial2.flush();
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Wiring setup/loop
///////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    // Setup analog pins
    for (int i = 0; i < BOARD_NR_ADC_PINS; i++)
        pinMode(boardADCPins[i], INPUT_ANALOG);

    // Exti pin
    pinMode(D39, OUTPUT);
    pinMode(D38, INPUT);
    pinMode(D13, OUTPUT);
    attachInterrupt(D38, extiCallback1, exti_varD38, RISING);

    // Uart
    initUARTs();
    serial2_Start();

    // Timer init
    for (int i = 0; i < BOARD_NR_PWM_PINS; i++) {
        pinMode(boardPWMPins[i], PWM);
        pwmWrite(boardPWMPins[i], 65535 * (i + 1) / (BOARD_NR_PWM_PINS + 5));
    }

    HardwareTimer *timerArray[] = {&Timer1, &Timer2, &Timer3, &Timer4, &Timer5};
    for (int i = 0; i < 5; i++) {
        timerArray[i]->setPrescaleFactor(1);
        timerArray[i]->setOverflow(10000);
    }
    for (int i = 1; i <= 6; i++) {
        timerArray[0]->setMode(i, TIMER_PWM);
        timerArray[0]->setCompare(i, 4000);
    }
    for (int i = 1; i <= 2; i++) {
        timerArray[1]->setMode(i, TIMER_PWM);
        timerArray[2]->setMode(i, TIMER_PWM);
        timerArray[1]->setCompare(i, 4000);
        timerArray[2]->setCompare(i, 4000);
    }
    timerArray[3]->setMode(1, TIMER_PWM);
    timerArray[3]->setCompare(1, 30000);
    timerArray[4]->setMode(1, TIMER_PWM);
    timerArray[4]->setCompare(1, 30000);
    timerArray[0]->setPeriod(300);
    timerArray[1]->setPrescaleFactor(1024);
    timerArray[1]->setMode(1, TIMER_OUTPUT_COMPARE);
    timerArray[1]->attachInterrupt(1, timerOutputCmpCallback);


}

void loop () {
    tglLed();
    togglePin(D39);

    delay(750);
    serial2_Display();

    cmdProc();
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

