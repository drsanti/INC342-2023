
#include "ecc.h"

void byte_callback(void *evt)
{
	uart_event_t *ue = (uart_event_t *)evt;
	
	/*
	Q1: '0' LED0 OFF
	    '1' LED0 ON
		'2' LED0 TOGGLE
	*/
	if(ue->byte == '0'){
		Led_Clr(LED_ID_0);
	}
	else if(ue->byte == '1'){
		Led_Set(LED_ID_0);	
	}
	else if(ue->byte == '2'){
		Led_Inv(LED_ID_0);	
	}
}

void line_callback(void *evt) {

	uart_event_t *ue = (uart_event_t *)evt;

	// Uart1_Printf("%d %s", ue->length, ue->line);

	/*
		Q2: "led-on"  ->  LED0 ON
		    "led-off" ->  LED0 OFF
			"led-tog" ->  LED0 TOGGLE
	*/
	// if( 0 == strcmp(ue->line, "led-on\r\n") ) {
	// 	Led0_Set();
	// }
	// else if( 0 == strcmp(ue->line, "led-off\r\n") ) {
	// 	Led0_Clr();
	// }
	// else if( 0 == strcmp(ue->line, "led-tog\r\n") ) {
	// 	Led0_Inv();
	// }
	// else {
	// 	Uart1_Printf("Error: command not found!\r\n");	
	// }

	/**
	 * Q3: "led-i-0"	LEDi OFF 
	 *     "led-i-1"	LEDi ON
	 *     "led-i-2"	LEDi TOGGLE
	 * 
	 * Note: i is 0..3
	*/
	// "led-i-0" --> [l] [e] [d] [-] [i] [-] [0]
	//                0   1   2   3   4   5   6
	char *s = ue->line;
	if( (s[0] == 'l') && (s[1] == 'e') && (s[2] == 'd') && (s[3] == '-') ) {
		if( (s[4] >= '0') && (s[4] <= '3') && (s[5] == '-') ) {
			if( (s[6] >= '0') && (s[6] <= '2') ) {
				Uart1_Printf("command is accepted\r\n");
				// int16_t id = s[4] - 48; // '0' = 48, '1' = 49, ...
				// int16_t id = s[4] - 0x30;
				// int16_t id = s[4] - '0';
				int16_t id = (int16_t)s[4] - (int16_t)'0';
				if( s[6] == '0') {
					Led_Clr(id);// OFF
				}
				else if( s[6] == '1') {
					Led_Set(id);// ON
				}
				else if( s[6] == '2') {
					Led_Inv(id);// TOGGLE
				}
				Uart1_Printf("id: %d\r\n", id);
				return;
			}	
		}
	}
	Uart1_Printf("command not is allowed\r\n");
}


int main(void)
{
    System_Init();

	// For Q1
	//Uart1_SetRxCallback(byte_callback);

	Uart1_SetRxLineCallback(line_callback, 64);


	System_Start();
}


//  ecc-pic24-cli -build -flash -monitor
// ecc-pic24-cli -build


// ecc-pic24-cli -monitor
































//------------------------[A]------------------------------------

// #include "ecc.h"


// Sampling interval (seconds)
// Sampling frequency (Hz)
// Sampling rate (Hz)

// printf
// %f  %3.3f  .ddd
// %d  %.4d  0008 0015 0999 1024
//      %d   ___8 __15 _999 1024
// void signal_sampling(void *evt)
// {
// 	// 0.00V -> 0x000 (0)
// 	// 3.50V -> 0x3FF (1023)
// 	int16_t adc_value = Adc1_Get(); // Get 10-bit data
// 	float voltage = (3.3 * adc_value) / 1023.0;
// 	Uart1_PrintfAsync("0x%.3X %4d %.5f\r\n", adc_value, adc_value, voltage);
	
// }



// #define NUM_SAMPLES  10
// int16_t adc_data[NUM_SAMPLES];
// int16_t counter = 0;
// void signal_sampling(void *evt)
// {
// 	int16_t adc_value = Adc1_Get(); // Get 10-bit data
// 	Uart1_Printf("%d ", adc_value);
// 	adc_data[counter++] = adc_value;
// 	if(counter == NUM_SAMPLES) {
// 		counter = 0;
// 		int16_t min = adc_data[0];
// 		int16_t max = adc_data[0];
// 		int16_t i;
// 		for( i = 0; i < NUM_SAMPLES; i++ ) {
// 			if( adc_data[i] < min ) {
// 				min = adc_data[i];
// 			}
// 			if( adc_data[i] > max ) {
// 				max = adc_data[i];
// 			}
// 		}
// 		Uart1_Printf("\r\nmin: %d, max: %d\r\n", min, max);
// 	}
// 	// Find Summation
// 	// Find Average
// 	// Count Odd or Even numbers
// 	// Count numbers that less than 100

// }

// int main(void)
// {
//     System_Init();


// 	Timer_Create(500, signal_sampling);


// 	System_Start();
// }
