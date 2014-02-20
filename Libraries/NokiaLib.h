/*******************************************************
 * Nokia 5110 library of basic functions for the Cortex R Family,
 * more specifically for the Hercules Launchpad
 *
 * Version 1.11
 *
 * By: Diego Rosales
 * inspired by several codes such as Jim Lindblom's and Julian Ilett's codes
 *
 * Created on January 26 / 2014
 * Last edited on February 20 / 2014
 *
 * Recent changes: Changed the default SPI1 CS1 pin to the GIO[6] pin
 * to make it compatible with the standard boosterpack pinout
 *
 * License: FREE FOR ALL!! just don't use it to destroy the world
 *
 * The order of the non-SPI pins can be anyone.
 * To change the pins, just change the pin definition in NokiaLib.h
 *
 * Note that this code assumes that the basic components
 * are created by HALcoGen, such as "het.h" and "gio.h".
 * This code also assumes one RTI counter with enabled interrupts
 * for more info go to www.produccionyelectronica.blogspot.com and
 * http://produccionyelectronica.blogspot.mx/2014/01/hercules-launchpad-6-nokia-5110-lcd.html
 *
 * THIS IS WORK IN PROGRSS! DO NOT ASSUME EVERYTHING WILL WORK
 * BECAUSE IT MAY OR MAY NOT WORK
 *******************************************************/

#ifndef NOKIALIB_H
#define NOKIALIB_H

#include "het.h"
#include "gio.h"
#include "rti.h"
#include "spi.h"

#define BIT(x,n) (((x) >> (n)) & 1) // To obtain single bits of a char we need to define this

// General definitions
#define byte unsigned char
#define xLength 84
#define yLength 6
#define displayData true
#define commandData false
#define WHITE true
#define BLACK false


// Pin definition
#define LIGHTPIN 0 // Light pin (N2HET, PWM)
#define VCCPIN 2 // Vcc pin (N2HET)
#define DCPIN 4 // Data/Command pin (N2HET)
#define RSTPIN 6 // Reset pin (N2HET)
#define CEPIN 6 // Chip-enable pin for compatibility with boosterpack standard pinout

// Function prototypes
void displayInit(void);
void clearDisplay(bool BlackWhite);
void writeData(byte data, bool d_c);
void resetDisplay(void);
void setBacklight(unsigned int intensity);
void demo(void);
void demo2(void);
void ckDelay(void);
void setCursor(byte x, byte y);
void setLine(byte x);
void setColumn(byte y);
void clearBuffer(bool BlackWhite);
void sendBuffer(void);
void bufferSetByte(byte x, byte y, byte Data);
void bufferSetBit(byte x, byte y, bool BlackWhite);

#endif
