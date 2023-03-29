#include "ecc.h"

void timer_callback(void *te)
{
	timer_event_t *pe = (timer_event_t *)te;
	uint16_t cnt = pe->counter;

	Led_Flash(cnt%4, 10 + (cnt*20));

	// Uart1_PrintfAsync("counter: %u\r\n", cnt);
	
	// if( cnt > 10 )
	// {
	// 	Uart1_PrintfAsync("\tcounter > 10: %u\r\n", cnt);
	// 	Timer_Delete(pe->sender);
	// }
}

void psw_callback(void *se)
{
	switch_event_t *pe = (switch_event_t *)se;
	int id = pe->id;
	Led_Flash(id, 100);
}

int main(void)
{
    System_Init();
	Timer_Create(500, timer_callback);
	Psw_SetKeyDownCallback(PSW_ID_0, psw_callback);
	Psw_SetKeyDownCallback(PSW_ID_1, psw_callback);
	Psw_SetKeyDownCallback(PSW_ID_2, psw_callback);
	Psw_SetKeyDownCallback(PSW_ID_3, psw_callback);
	System_Start();
}
