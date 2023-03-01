
#include "ecc.h"

/**
 * Event-Driven
 * Digital Inputs (Push Button Switches)
*/


/**
 * Event-Driven
 * Timer Event
*/


timer_t *timer0;
timer_t *timer1;

void timer_callback(void *event)
{
	/**
	 * Cast the void* to timer_event_t*
	*/
	timer_event_t *p = (timer_event_t *)event;

	/**
	 * Print information
	*/
	Uart1_Printf("id: %d, ticks: %d\t\n", p->id, p->counter);

	/**
	 * Check conditions, if true, delete the timer0
	*/
	if(p->id == 0 && p->counter >= 5) {
		Timer_Delete(timer0);
	}

	/**
	 * Check conditions, if true, delete the timer1
	*/
	if(p->id == 1 && p->counter >= 7) {
		Timer_Delete(timer1);
	}

	/**
	 * Toggle LED
	*/
	Led_Inv(p->id);	
}


int main(void)
{
    System_Init();

	/**
	 * Create two timers.
	*/
	timer0 = Timer_Create(1000, timer_callback);
	timer1 = Timer_Create(1300, timer_callback);

	/**
	 * Assign an unique id to the timers
	*/
	timer0->id = 0;
	timer1->id = 1;

	System_Start();
}
