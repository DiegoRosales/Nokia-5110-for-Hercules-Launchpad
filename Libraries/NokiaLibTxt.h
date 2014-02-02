/*******************************************************
 * Nokia 5110 library of text-related functions for the Cortex R Family,
 * more specifically for the Hercules Launchpad
 *
 * Version 1.0
 *
 * By: Diego Rosales
 * inspired by several codes such as Jim Lindblom's and Julian Ilett's codes
 *
 * Created on February 2 / 2014
 * Last edited on February 2 / 2014
 *
 * Recent changes: Created the library
 *
 * License: FREE FOR ALL!! just don't use it to destroy the world
 *
 * The order of the pins can be anyone, as it does not use
 * any hardware SPI interface, but a software one instead
 * to change the pins, just change the definitions in NokiaLib.h
 *
 * Note that this code assumes that the basic components
 * are created by HALcoGen, such as "het.h" and "gio.h".
 * This code also assumes one RTI counter with enabled interrupts,
 * and of course, the NokiaLib.h/.c files
 * for more info go to www.produccionyelectronica.blogspot.com
 *
 * THIS IS WORK IN PROGRSS! DO NOT ASSUME EVERYTHING WILL WORK
 * BECAUSE IT MAY OR MAY NOT WORK
 *******************************************************/
#ifndef NOKIALIBTXT_H
#define NOKIALIBTXT_H

#include "NokiaLib.h"

void bufferSetCharacter(byte character, byte x, byte y);
void bufferSetString(byte *string, byte size, byte x, byte y);










#endif
