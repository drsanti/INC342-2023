
#include "ecc.h"

/**
 * Embedded C
 * Dynamic Memory and Pointer
*/


int main(void)
{
    System_Init();


	/**
	 * Example 1 -------------------------------------------------------
	*/

	/**
	 * Memory Allocation
	*/
	char *p_memory = (char *)malloc(10);	/** Allocate 10 bytes */

	char *pc = p_memory;	/** Pointer to the memory */

	/**
	 * Access the memory as an array
	*/
	int16_t i;
	for( i = 0; i<10; i++ )
	{
		pc[i] = 'a' + i;
		Uart1_Printf( "pc[%d] = %c\r\n", i, pc[i] );
	}


	/**
	 * Access the memory using pointer
	*/
	for( i = 0; i<10; i++ )
	{
		*pc = 'A' + i;
		Uart1_Printf( "pc = 0x%.4X, *pc = %c\r\n", pc, *pc );
		pc++;	/** Point to the next byte */
	}


	/**
	 * Memory Free
	*/
	free(p_memory);


	


	/**
	 * Example 2 -------------------------------------------------------
	*/



	/**
	 * Declare number of memory elements.
	*/
	int16_t elements = 15;

	/**
	 * Allocate memory for floating numbers.
	*/
	float *p_buffer = ( float *)malloc(sizeof(float) * elements );

	float *pf = p_buffer;	/** Pointer to the memory 					*/

	*pf = 0.12;				/** Write 0.12 to the first element 		*/

	*(pf + 1) = 1.23;		/** Write 1.23 to the second element 		*/

	pf = pf + 2;			/** Change the pointer to the third element */

	*pf = 2.34;				/** Write 2.34 to the third element 		*/

	pf = pf - 2;			/** Change the pointer to the first element */

	for(i=0; i<elements; i++) 
	{
		Uart1_Printf( "pf = 0x%.4X, *pf = %.2f\r\n", pf, *pf );
		pf++;				/** Point to the next element */
	}

	/**
	 * Free the memory.
	*/
	free(p_buffer);




	/**
	 * Example 3 -------------------------------------------------------
	*/




	/** Declare structure of student. */
	struct Student
	{
		char*   name;
		uint8_t age;
		float   weight;
	};

	/** Check the structure size */
	Uart1_Printf("size of Student is %d\r\n", sizeof(struct Student));

	/** Allocate memory for 5 students */
	int16_t total = 5;
	struct Student *students = malloc(sizeof(struct Student) * total);

	/** Declare a pointer and point to the first student */
	struct Student *ps = students;

	/** Write data to the first student */
	ps->name   = "Student A";
	ps->age    = 17;
	ps->weight = 42.3;

	/** Point to the next student */
	ps++;

	/** Write data to the second student */
	ps->name   = "Student B";
	ps->age    = 18;
	ps->weight = 45.2;

	/** Write data to the first student */
	ps = students;

	/** Print student information */
	for(i = 0; i<total; i++)
	{
		Uart1_Printf("Name: %s Age: %d Weight: %.2f\r\n", ps->name, ps->age, ps->weight);
		ps++;
	}

	/** Free the memory */
	free(students);
	

	System_Start();
}
