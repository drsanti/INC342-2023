/**
 * Problem:
 * Write a program to control LEDs using PSWs.
 * 
 * Requirement:
 * 1) When program is run, only LED3 is turned ON for 3 seconds, then it is turned OFF.
 *    After the LED3 is turned OFF (after 3 seconds), the 4 digits of student's ID are printed to the terminal window.
 *    Note:
 *     The display format will be as follows:
 *       - dddd (for one student), 
 *       - dddd dddd (for group of two)
 *       - dddd dddd dddd (for group of three).  
 * 
 * After the LED3 is turned OFF (after 3 seconds).
 * 
 * 2) LED0 will be ON and OFF (blinking) with 1 Hz.
 * 3) LED1 is ON when LED0 is OFF and LED1 is OFF when LED0 is ON.
 * 4) When PSW2 is pressed, LED2 is toggled.
 * 5) When PSW3 is pressed, LED3 is toggled.
*/


#include "ecc.h"

/** Timeout flag, will be set after program is run for 3 seconds */
bool is_timeout = false;

/** Callback function called every 500 ms */
void blinking(void *event) 
{
	Led1_Inv();
}

/** Callback function called every 3 seconds */
void timeout(void *event)
{
	/**
	 * Check the flag.
	*/
	if( is_timeout == false )
	{	
		/**
		 * Set the flag.
		*/
		is_timeout = true;

		/**
		* Turn the LED3 OFF.
		*/
		Led3_Clr();

		/**
		* Print ID of all student.
		*/
		Uart1_Printf("1234 2345 3456\r\n");

		/**
		* Create 0.5 seconds timer.
		*/
		Timer_Create(500, blinking);
	}
}

/** Callback function called when PSW2 is pressed */
void psw2_pressed(void *event) 
{
	Led2_Inv();	/** Toggle LED2 */
}

/** Callback function called when PSW3 is pressed */
void psw3_pressed(void *event) 
{
	Led3_Inv();	/** Toggle LED3 */
}

/** Main function */
int main(void)
{
    System_Init();	/** Initialize the system */

    /**
	 * Turn all LEDs OFF.
	*/
	int16_t i;
	for( i = 0; i <= LED_ID_3; i++ )
	{
		Led_Clr( i );	/** Turn OFF LEDi */
	}
	
	/**
	 * Turn the LED3 ON.
	*/
	Led3_Set();

	/**
	 * Create three seconds timer.
	*/
	Timer_Create(3000, timeout);

	/**
	 * Set callbacks for switches.
	*/
	Psw_SetKeyDownCallback(PSW_ID_2, psw2_pressed);
	Psw_SetKeyDownCallback(PSW_ID_3, psw3_pressed);

    System_Start();	/** Start the system */
}
    