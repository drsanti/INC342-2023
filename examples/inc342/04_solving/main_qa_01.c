/**
 * Problem:
 * Write a program to control LEDs using PSWs.
 * 
 * Requirement:
 * 1) When program is run, only LED3 is turned ON for 3 seconds, then it is turned OFF.
 * 2) After the LED3 is turned OFF (after 3 seconds), the 4 digits of student's ID are printed to the terminal window.
 *    Note:
 *    The display format will be as follows:
 *    - dddd (for one student), 
 *    - dddd dddd (for group of two)
 *    - dddd dddd dddd (for group of three).  
*/


#include "ecc.h"

void timeout(void *event)
{
	/**
	 * Turn the LED3 OFF.
	*/
	if( Led3_Get() == LED_OFF )
	{	
		Led3_Clr();

		/**
		* Print ID of all student.
		*/
		Uart1_Printf("1234 2345 3456\r\n");
	}
}

int main(void)
{
    System_Init();

    /**
	 * Turn all LEDs OFF.
	*/
	int16_t i;
	for( i = 0; i <= LED_ID_3; i++ )
	{
		Led_Clr( i );
	}
	
	/**
	 * Turn the LED3 ON.
	*/
	Led3_Set();

	/**
	 * Create a timer.
	*/
	Timer_Create(3000, timeout);


    System_Start();
}
