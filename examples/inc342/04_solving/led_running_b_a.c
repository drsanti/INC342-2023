
//----------------------------------------------------------------------------
//----------------------------------B-----------------------------------------
//----------------------------------------------------------------------------


#include "ecc.h"

const uint8_t data1[] = { 0b0001, 0b0011, 0b0110, 0b1100, 0b1000, 0b0000, 0b1111 };
const uint8_t data2[] = { 0b1000, 0b1100, 0b0110, 0b0011, 0b0001, 0b0000, 0b1111 };
int8_t sw_3_0;
int8_t steps;
timer_t *timer = NULL;

void kill_timer()
{

}

void timer_callback(void *te)
{
	timer_event_t *pe = (timer_event_t *)te;
	
	if(sw_3_0 == PSW_ID_3)
	{
		Led_Write(data1[steps]);
		steps++;
	}
	else if(sw_3_0 == PSW_ID_0)
	{
		Led_Write(data2[steps]);
		steps++;
	}
	
	
	if(steps >= 6)
	{	
		Timer_Delete(timer);
		timer = NULL;
	}
}

void psw_callback(void *se)
{
	switch_event_t *pe = (switch_event_t *)se;
	int id = pe->id;
	if(id == 1 || id == 2)
	{
		Led_Write(id == 1 ? 0b0000 : 0b1111);
		Timer_Delete(timer);
		timer = NULL;
	}
	else {
		sw_3_0 = id;
		steps = 0;
		if(timer == NULL)
		{
			timer = Timer_Create(500, timer_callback);
		}
	}

	
}

int main(void)
{
    System_Init();
	
	Psw_SetKeyDownCallback(PSW_ID_0, psw_callback);
	Psw_SetKeyDownCallback(PSW_ID_1, psw_callback);
	Psw_SetKeyDownCallback(PSW_ID_2, psw_callback);
	Psw_SetKeyDownCallback(PSW_ID_3, psw_callback);
	System_Start();
}





//----------------------------------------------------------------------------
//----------------------------------A-----------------------------------------
//----------------------------------------------------------------------------

// #include "ecc.h"



// timer_t *timer = NULL;
// int16_t direction;
// int16_t data; 

// void kill_timer(void)
// {
// 	Timer_Delete(timer);
// 	timer = NULL;
// }

// void timer_callback(void *te)
// {
// 	Uart1_PrintfAsync("%d\r\n", data);
// 	if(direction == PSW_ID_0)
// 	{
// 		if(data&0x10 >= 0b10000)
// 		{
// 			kill_timer();
// 			data = 0xFF;
// 		}
// 		Led_Write(data);
// 		data <<= 1;
// 	}
// 	else if(direction == PSW_ID_3)
// 	{
// 		if(data&0xF <= 0b0000)
// 		{
// 			kill_timer();
// 			data = 0xFF;
// 		}
// 		data >>= 1;
// 		Led_Write(data);
// 	}
// }

// void psw_callback(void *se)
// {
// 	switch_event_t *pe = (switch_event_t *)se;
// 	int id = pe->id;

// 	if(id == PSW_ID_0 || id == PSW_ID_3)
// 	{
// 		direction = id;
// 		if(timer == NULL)
// 		{
// 			timer = Timer_Create(500, timer_callback);	
// 		}
// 		data = id == PSW_ID_0 ? 0x01 : 0x80;
// 	}
// 	else
// 	{
// 		Led_Write(id == PSW_ID_1 ? 0xF : 0x0);
// 		kill_timer();
// 	}
// }

// int main(void)
// {
//     System_Init();
    
// 	//Timer_Create(250, timer_callback);
// 	Psw_SetKeyDownCallback(PSW_ID_0, psw_callback);
// 	Psw_SetKeyDownCallback(PSW_ID_1, psw_callback);
// 	Psw_SetKeyDownCallback(PSW_ID_2, psw_callback);
// 	Psw_SetKeyDownCallback(PSW_ID_3, psw_callback);

// 	System_Start();
// }
