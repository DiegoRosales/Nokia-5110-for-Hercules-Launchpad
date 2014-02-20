/* Demo code for the Nokia 5110 Library.
 * This code uses NokiaLib.c, NokiaLib.h,
 * NokiaLibTxt.c and NokiaLib.h libraries
 *
 * Created by Diego Rosales
 * 19/02/2014
 *
 * For more info go to
 * http://produccionyelectronica.blogspot.mx/2014/01/hercules-launchpad-6-nokia-5110-lcd.html
 *
 */

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
#include "het.h"
#include "gio.h"
#include "NokiaLib.h"
#include "NokiaLibTxt.h"
#include "rti.h"
#include "spi.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */

	// Initialize all the modules
	gioInit();
	hetInit();
	rtiInit();
	spiInit();

	// Initialize the display
	displayInit();


	// Create a demo text
	static byte string[] = "This is a\n\rNokia 5110\n\r Demo";
	// Write the text to the buffer inside the Hercules
	bufferSetString((byte *)string, sizeof(string)-1, 0, 0);
	// Send the buffer to the display
	sendBuffer();

	// Set the backlight to 30%
	setBacklight(30);

	// Wait forever...
	while(1);
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
