//------------------------[B]------------------------------------

// Sampling Interval (seconds)

// Sampling Frequency (Hz)
// Sampling Rate (Hz)

#include "ecc.h"


// void adc_sampling(void *evt)
// {
// 	int16_t adc_value = Adc1_Get(); // 10-bit data -> 0x000 - 0x3FF (0-1023)
// 	Uart1_Printf("adc value: 0x%.3X, (%.4d)\r\n", adc_value, adc_value);

// 	// 0.00V => 0x000 (0)
// 	// 3.30V => 0x3FF (1023)
// 	//float voltage1 = (adc_value / 1023.0) * 3.3;
// 	float voltage = (adc_value * 3.3) / 1023.0;
// 	Uart1_Printf("V: %.5f volts\r\n", voltage);

// 	// int x, y, a, b;
// 	// x = 10;
// 	// y = 11;
// 	// a = (x / y) * 5;
// 	// b = (x * 5) / y;
// 	// Uart1_Printf("a: %d, b: %d\r\n", a, b);

// }


#define NUM_SAMPLES 10
int16_t adc_data[NUM_SAMPLES];
int16_t counter = 0;

void adc_sampling(void *evt)
{
	int16_t adc_value = Adc1_Get(); 
	Uart1_Printf("%d ", adc_value);
	adc_data[counter] = adc_value;
	counter++;
	if(counter == NUM_SAMPLES)
	{
		counter = 0;
		//--- Find the minimum value

		int16_t i;
		int16_t min = adc_data[0];
		int16_t max = adc_data[0];
		for( i = 1; i < NUM_SAMPLES; i++ )
		{
			if( adc_data[i] < min ) {
				min = adc_data[i];
			}

			else if( adc_data[i] > max ) {
				max = adc_data[i];
			}
		}
		Uart1_Printf("\r\nmin: %d, max: %d\r\n", min, max);

		// Find Summation
		// Find Average
		// Count Odd or Even numbers
		// Count numbers that less than 200
	}
	
}

int main(void)
{
    System_Init();

	Timer_Create(500, adc_sampling);

	System_Start();
}








































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
