
#include "ecc.h"

/**
 * Embedded C
 * Pointer
*/


/**
 * Declare a structure named PLC.
*/
struct PLC {
	int16_t id;
	int16_t num_io;
	char *info;
};


int main(void)
{
    System_Init();

	/**
	 * Declare a variable and initialize to 123.
	*/
	int16_t v1 = 123;
	Uart1_Printf("v1 value:   %d\r\n", v1);			// Print value of v1
	Uart1_Printf("v1 address: %p\r\n", &v1);		// Print memory address of v1
	Uart1_Printf("v1 size:    %d\r\n", sizeof(v1));	// Print memory size in byte taken by v1

	/**
	 * Declare a pointer to int16_t.
	*/
	int16_t *p1;

	/**
	 * Pointer p1 points to the memory address of the v1.
	*/
	p1 = &v1;

	Uart1_Printf("p1 address:         %p\r\n", &p1);		// Print memory address of p1
	Uart1_Printf("p1 size:            %d\r\n", sizeof(p1));	// Print memory address of p1

	Uart1_Printf("p1 pointed address: %p\r\n", p1);			// Print value of p1
	Uart1_Printf("p1 pointed value:   %d\r\n", *p1);		// Print memory address of p1



	/**
	 * Declare an array.
	*/
	char text[] = {'H', 'e', 'l', 'l', 'o'};

	/**
	 * Declare a pointer to char.
	*/
	char *p2c;

	/**
	 * Assign the pointer to point to the memory address of the text array.
	*/
	p2c = text;	// OR p2c = &text[0];


	/**
	 * Access element of the text array using pointer.
	*/
	int i;
	for(i=0; i<sizeof(text) / sizeof(text[0]); i++) {
		Uart1_Printf("%c\r\n", *p2c);
		p2c++;	
	}


	/**
	 * Declare a structure variable.
	*/
	struct PLC plc1;

	/**
	 * Declare a pointer to structure variable.
	*/
	struct PLC *ptr2plc;

	/**
	 * Make the pointer to point to the memory address of the plc1 variable.
	*/
	ptr2plc = &plc1;


	/**
	 * Assign data to the member variable of the structure using the pointer.
	*/
	ptr2plc->id = 3;
	ptr2plc->num_io = 8;
	ptr2plc->info = "Robot #1";

	/**
	 * Read and print data of the structure variable.
	*/
	Uart1_Printf("%d %d %s\r\n", ptr2plc->id, ptr2plc->num_io, ptr2plc->info);

	System_Start();
}
    