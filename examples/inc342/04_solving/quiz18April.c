
// #include "ecc.h"



//-------------------------[1A]------------------------------
// void timer_callback(void *evt)
// {
// 	uint8_t i;
// 	for(i=LED_ID_0; i<=LED_ID_3; i++)
// 	{
// 		Led_Flash(i, 500);
// 	}

// 	timer_event_t *t = (timer_event_t *)evt;
// 	if(t->counter >= 9)	// For the first call, t->counter is 0.
// 	{
// 		Timer_Delete(t->sender);
// 	}
// }

// int main(void)
// {
//     System_Init();
// 	Timer_Create((500 + 1500), timer_callback);
// 	System_Start();
// }



//-------------------------[2A]------------------------------
// void psw_callback(void *evt)
// {
// 	static int16_t psw0_count = 0;
// 	static int16_t psw1_count = 0;
// 	switch_event_t *psw = (switch_event_t *)evt;

// 	if(psw->id == PSW_ID_0)
// 	{
// 		if(++psw0_count >= 5)
// 		{
// 			psw0_count = 0;
// 			Led0_Inv();
// 		}
// 	}
// 	else if(psw->id == PSW_ID_2)
// 	{
// 		if(psw1_count == 0)
// 		{
// 			psw1_count += 1;
// 			Led3_Set();
// 		}
// 	}
// }

// void timer_callback(void *evt)
// {
// 	uint8_t i;
// 	for(i=LED_ID_0; i<=LED_ID_3; i++)
// 	{
// 		Led_Clr(i);
// 	}
// 	timer_event_t *t = (timer_event_t *)evt;
// 	Timer_Delete(t->sender);

// 	Psw_SetKeyDownCallback(PSW_ID_0, psw_callback);
// 	Psw_SetKeyDownCallback(PSW_ID_2, psw_callback);
// }

// int main(void)
// {
//     System_Init();
// 	uint8_t i;
// 	for(i=LED_ID_0; i<=LED_ID_3; i++)
// 	{
// 		Led_Set(i);
// 	}
// 	Timer_Create((2000), timer_callback);
// 	System_Start();
// }


//-------------------------[3A]------------------------------
// void psw_callback(void *evt)
// {
// 	const int16_t delta[] = {-1, 1, -10, 10};
// 	static int16_t counter = 0;
// 	switch_event_t *psw = (switch_event_t *)evt;
// 	counter += delta[psw->id];
// 	counter = counter < 0 ? 0 : counter;
// 	counter = counter > 99 ? 99 : counter;
// 	Uart1_PrintfAsync("Counter = %.2d\r\n", counter);

// }
// int main(void)
// {
//     System_Init();
// 	int16_t i;
// 	for(i=PSW_ID_0; i<=PSW_ID_3; i++)
// 	{
// 		Psw_SetKeyDownCallback(i, psw_callback);
// 	}
// 	Uart1_PrintfAsync("Counter = 00\r\n");
// 	System_Start();
// }




//-------------------------[1B]------------------------------
// void psw_callback(void *evt)
// {
// 	switch_event_t *psw = (switch_event_t *)evt;
// 	Led_Inv(psw->id);
// }

// void timer_callback(void *evt)
// {
// 	uint8_t i;
// 	for(i=LED_ID_0; i<=LED_ID_3; i++)
// 	{
// 		Led_Flash(i, 100);
// 	}
// 	timer_event_t *t = (timer_event_t *)evt;
// 	if(t->counter >= 19)	// For the first call, t->counter is 0.
// 	{
// 		Timer_Delete(t->sender);
// 		for(i=PSW_ID_0; i<=PSW_ID_3; i++)
// 		{
// 			Psw_SetKeyDownCallback(i, psw_callback);
// 		}
// 	}
// }

// int main(void)
// {
//     System_Init();
// 	Timer_Create(1000/5, timer_callback);
// 	System_Start();
// }



//-------------------------[2B]------------------------------
// bool is_psw3_down = false;
// bool is_blink = false;
// bool is_all_off = true;

// void psw_key_up_callback(void *evt)
// {
// 	is_psw3_down = false;
// }

// void psw_key_down_callback(void *evt)
// {
// 	switch_event_t *psw = (switch_event_t *)evt;

// 	if(psw->id == PSW_ID_3)
// 	{
// 		is_psw3_down = true;
// 	}
// 	if(is_psw3_down)
// 	{
// 		if(psw->id == PSW_ID_0)
// 		{
// 			is_blink = true;
// 		}
// 		else if(psw->id == PSW_ID_1)
// 		{
// 			is_blink = false;
// 		}
// 	}
// }

// void timer_callback(void *evt)
// {
// 	if(is_all_off)
// 	{
// 		is_all_off = false;
// 		uint8_t i;
// 		for(i=LED_ID_0; i<=LED_ID_3; i++)
// 		{
// 			Led_Clr(i);
// 		}
// 	}
// 	else if(is_blink)
// 	{
// 		Led_Flash(LED_ID_0, 500);
// 	}
// }

// int main(void)
// {
//     System_Init();
// 	uint8_t i;
// 	for(i=LED_ID_0; i<=LED_ID_3; i++)
// 	{
// 		Led_Set(i);
// 	}
// 	Timer_Create(1000, timer_callback);
// 	Psw_SetKeyDownCallback(PSW_ID_0, psw_key_down_callback);
// 	Psw_SetKeyDownCallback(PSW_ID_1, psw_key_down_callback);
// 	Psw_SetKeyDownCallback(PSW_ID_3, psw_key_down_callback);
// 	Psw_SetKeyUpCallback(PSW_ID_3, psw_key_up_callback);
// 	System_Start();
// }



//-------------------------[3B]------------------------------
// void psw_callback(void *evt)
// {
// 	const  float delta[] = {-0.01, 0.01, -0.1, 0.1};
// 	static float counter = 0;
// 	switch_event_t *psw = (switch_event_t *)evt;
// 	counter += delta[psw->id];
// 	counter = counter < 0 ? 0 : counter;
// 	counter = counter > 99 ? 99 : counter;
// 	Uart1_PrintfAsync("Counter = %.2f\r\n", counter);

// }
// int main(void)
// {
//     System_Init();
// 	int16_t i;
// 	for(i=PSW_ID_0; i<=PSW_ID_3; i++)
// 	{
// 		Psw_SetKeyDownCallback(i, psw_callback);
// 	}
// 	Uart1_PrintfAsync("Counter = 0.00\r\n");
// 	System_Start();
// }
