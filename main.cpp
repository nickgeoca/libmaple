// Demo/test code.

#include <string.h>
#include <wirish/wirish.h>

void init(void);

HardwareTimer Timer1(1);
HardwareTimer Timer2(2);
HardwareTimer Timer3(3);
HardwareTimer Timer4(4);
HardwareTimer Timer5(5);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Exti code
///////////////////////////////////////////////////////////////////////////////////////////////////
const uint32 exti_D38Info[] = {38, 0};
void *exti_varD38 = (void *)exti_D38Info;
void *cback_var2;
void *cback_var3;

#define DISPLAY_CURSOR_DN(n) do{for (int i = 0; i < n; i++) Serial2.println(""); } while(0)
#define DISPLAY_CURSOR_UP(n) do{for (int i = 0; i < n; i++) Serial2.print((char)141); Serial2.print((char)'\r');} while(0)
#define DISPLAY_ERASE(n) do{for (int i = 0; i < n; i++) Serial2.print((char)' '); for (int i = 0; i < n; i++) Serial2.print((char)'\b');} while(0)
#define DISPLAY_LOC_EXTI 21

void extiCallback1(void *var) {
    static int cntr = 0;
    uint32 *varInt = (uint32 *)var;
    // EXTI
    DISPLAY_CURSOR_DN(DISPLAY_LOC_EXTI + varInt[1] * 4);
    Serial2.println("- EXTI");
    Serial2.print("Pin D");
    Serial2.println(varInt[0]);
    Serial2.print("Counter: ");
    Serial2.print(cntr++);
    DISPLAY_CURSOR_UP(DISPLAY_LOC_EXTI + 2 + varInt[1] * 4);
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
    Serial2.println("- UART2 Rx");
    DISPLAY_ERASE(15);
    while (Serial2.available()) {
        Serial2.print((char)Serial2.read());
    }
    Serial2.println("\n");

    // SysTick
    Serial2.println("- SysTick");
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
    Serial2.println("us\n\n");

    // ADC
    Serial2.println("- ADC");
    for (int i = 0; i < BOARD_NR_ADC_PINS; i++)
        measure_adc_noise(boardADCPins[i], N);

    // Move cursor up
    DISPLAY_CURSOR_UP(BOARD_NR_ADC_PINS + 9);

    //
    Serial2.print("\t\t\t\t\t\t\t\t");
    Serial2.print("Timer Prescalers: T1-");
    Serial2.print(Timer1.getPrescaleFactor());
    Serial2.print(" | T2-");
    Serial2.print(Timer2.getPrescaleFactor());
    Serial2.print(" | T3-");
    Serial2.print(Timer3.getPrescaleFactor());
    Serial2.print(" | T4-");
    Serial2.print(Timer4.getPrescaleFactor());
    Serial2.print(" | T5-");
    Serial2.println(Timer5.getPrescaleFactor());
    Serial2.print("\t\t\t\t\t\t\t\t");
    Serial2.print("Timer Overflow Values: T1-");
    Serial2.print(Timer1.getOverflow());
    Serial2.print(" | T2-");
    Serial2.print(Timer2.getOverflow());
    Serial2.print(" | T3-");
    Serial2.print(Timer3.getOverflow());
    Serial2.print(" | T4-");
    Serial2.print(Timer4.getOverflow());
    Serial2.print(" | T5-");
    Serial2.println(Timer5.getOverflow());
    Serial2.print("\t\t\t\t\t\t\t\t");
    Serial2.print("Timer Compare Values: T1C1-");
    Serial2.print(Timer1.getCompare(1));
    Serial2.print(" | T1C2-");
    Serial2.print(Timer1.getCompare(2));
    Serial2.print(" | T2C1-");
    Serial2.print(Timer2.getCompare(1));
    Serial2.print(" | T2C2-");
    Serial2.print(Timer2.getCompare(2));
    Serial2.print(" | T3C1-");
    Serial2.println(Timer3.getCompare(1));
    DISPLAY_CURSOR_UP(2);
}

void serial2_Start(void)
{
    Serial2.println("\f\tExample Program");
    Serial2.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    Serial2.print("Board freqency: ");
    Serial2.println(clk_get_sys_freq());
    Serial2.println(" * Timers\tD30 - D35, A1, D22 - D24, A9, A11");
    Serial2.println("     * Ground D40 to turn off timers (PWM)");
    Serial2.println(" * ADC\tsee ADC output pins");
    Serial2.println(" * SysTick");
    Serial2.println(" * UART2");
    Serial2.println(" * EXTI2\tshort D38 & D39");
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

void D40D41_inputFnct(void)
{
    if (digitalRead(D40)) {
        Timer1.pause();
        Timer2.pause();
        Timer3.pause();
        Timer4.pause();
        Timer5.pause();
    }
    else {
        Timer1.resume();
        Timer2.resume();
        Timer3.resume();
        Timer4.resume();
        Timer5.resume();
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
// Wiring setup/loop
///////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {

    // Setup pwm
    for (int i = 0; i < BOARD_NR_PWM_PINS; i++) {
        pinMode(boardPWMPins[i], PWM);
        pwmWrite(boardPWMPins[i], 65535 * (i + 1) / (BOARD_NR_PWM_PINS + 5));
    }

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

    // Timer1 operations
    pinMode(D40, INPUT);
}

void loop () {
    tglLed();
    togglePin(D39);

    delay(750);
    serial2_Display();

    D40D41_inputFnct();
    Timer1.setOverflow(500);
    Timer2.setOverflow(500);
    Timer3.setOverflow(500);
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

