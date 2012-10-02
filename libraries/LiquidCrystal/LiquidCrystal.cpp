#include "LiquidCrystal.h"

#include <stdio.h>
#include <string.h>
#include <wirish/WProgram.h>

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x8 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

// This library has been modified to be compatible with the LeafLabs Maple;
// very conservative timing is used due to problems with delayMicroseconds()
// that should be fixed in the 0.0.7 release of the libmaple. [bnewbold]

LiquidCrystal::LiquidCrystal(uint8 rs, uint8 rw, uint8 enable,
                             uint8 d0, uint8 d1, uint8 d2, uint8 d3,
                             uint8 d4, uint8 d5, uint8 d6, uint8 d7)
{

}

LiquidCrystal::LiquidCrystal(uint8 rs, uint8 enable,
                             uint8 d0, uint8 d1, uint8 d2, uint8 d3,
                             uint8 d4, uint8 d5, uint8 d6, uint8 d7)
{

}

LiquidCrystal::LiquidCrystal(uint8 rs, uint8 rw, uint8 enable,
                             uint8 d0, uint8 d1, uint8 d2, uint8 d3)
{

}

LiquidCrystal::LiquidCrystal(uint8 rs,  uint8 enable,
                             uint8 d0, uint8 d1, uint8 d2, uint8 d3)
{

}

void LiquidCrystal::init(uint8 fourbitmode, uint8 rs, uint8 rw, uint8 enable,
                         uint8 d0, uint8 d1, uint8 d2, uint8 d3,
                         uint8 d4, uint8 d5, uint8 d6, uint8 d7)
{

}

void LiquidCrystal::begin(uint8 cols, uint8 lines, uint8 dotsize) {

}

/********** high level commands, for the user! */
void LiquidCrystal::clear()
{

}

void LiquidCrystal::home()
{

}

void LiquidCrystal::setCursor(uint8 col, uint8 row)
{
}

// Turn the display on/off (quickly)
void LiquidCrystal::noDisplay() {

}
void LiquidCrystal::display() {

}

// Turns the underline cursor on/off
void LiquidCrystal::noCursor() {

}
void LiquidCrystal::cursor() {

}

// Turn on and off the blinking cursor
void LiquidCrystal::noBlink() {

}
void LiquidCrystal::blink() {

}

// These commands scroll the display without changing the RAM
void LiquidCrystal::scrollDisplayLeft(void) {

}
void LiquidCrystal::scrollDisplayRight(void) {

}

// This is for text that flows Left to Right
void LiquidCrystal::leftToRight(void) {

}

// This is for text that flows Right to Left
void LiquidCrystal::rightToLeft(void) {

}

// This will 'right justify' text from the cursor
void LiquidCrystal::autoscroll(void) {

}

// This will 'left justify' text from the cursor
void LiquidCrystal::noAutoscroll(void) {

}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal::createChar(uint8 location, uint8 charmap[]) {

}

/*********** mid level commands, for sending data/cmds */

inline void LiquidCrystal::command(uint8 value) {

}

inline void LiquidCrystal::write(uint8 value) {

}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void LiquidCrystal::send(uint8 value, uint8 mode) {

}

void LiquidCrystal::pulseEnable(void) {

}

void LiquidCrystal::write4bits(uint8 value) {

}

void LiquidCrystal::write8bits(uint8 value) {

}
