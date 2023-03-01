
#include "ecc.h"

/**
 * Embedded C
 * Array
*/

/**
 * Declare 1 element array (Not recommended).
*/
int16_t arr1[];		// Warning: array 'arr1' assumed to have one element.


/**
 * Declare 1 element array (Recommended).
*/
int32_t arr2[1];	// Better way to define 1 element array


/**
 * Declare 2 element array.
*/
uint8_t arr3[2];


/**
 * Declare and initialize 3 element array.
 * Number of elements must be defined in the [].
*/
float arr4[3] = {1.23, 2.34, 3.45};


/**
 * Declare and initialize array.
 * Number of elements in the [] will be defined automatically by compiler.
*/
char arr5[] = {'H', 'e', 'l', 'l', 'o'};



int main(void)
{
    System_Init();

	/**
	 * Read data from array.
	*/
	Uart1_Printf("c1 = arr5[0] = %c\r\n", arr5[0]);

	float f1 = arr4[1];
	Uart1_Printf("f1 = arr4[1] = %f\r\n", f1);


	/**
	 * Write data to array.
	*/
	Uart1_Printf("Before: arr2[0] = %d\r\n", arr2[0]);
	arr2[0] = 123;
	Uart1_Printf("After: arr2[0] = %d\r\n", arr2[0]);


	Uart1_Printf("Before: arr5[0] = %d\r\n", arr5[0]);
	arr5[0] = 'h';
	Uart1_Printf("After: arr5[0] = %d\r\n", arr5[0]);


	/**
	 * Get size of array (memory taken by array).
	*/
	Uart1_Printf("Size of array arr4: %d\r\n", sizeof(arr4));
	Uart1_Printf("Size of array arr5: %d\r\n", sizeof(arr5));

	/**
	 * Get size of each element in array.
	*/
	Uart1_Printf("Number of elements in arr4: %d\r\n", sizeof(arr4) / sizeof(arr4[0]));
	Uart1_Printf("Number of elements in arr5: %d\r\n", sizeof(arr5) / sizeof(arr5[0]));


	/**
	 * Loop through array.
	*/
	int16_t i;
	int16_t n = sizeof(arr4) / sizeof(arr4[0]);
	for(i=0; i<n; i++) {
		Uart1_Printf("arr4[%d] = %d\r\n", arr4[i]);	
	}

	/**
	 * Read 4 channels of ADC and write to array.
	*/
	adc_arr[4];
	for(i=0; i<4; i++) {
		adc_arr[i] = Adc_Get(i);	
		Uart1_Printf("adc[%d] = %d\r\n", adc_arr[i]);	
	}


	System_Start();
}
    