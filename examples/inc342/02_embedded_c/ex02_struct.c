
#include "ecc.h"

/**
 * Embedded C
 * Structure
*/


/**
 * Declare a structure named PLC.
*/
struct PLC {
	int16_t id;
	int16_t num_io;
	char    info[32];
};


/**
 * Declare a structure named Student using typedef.
*/
typedef struct
{
	char    name[32];
	uint8_t age;
	float   weight;
}Student;



int main(void)
{
    System_Init();


	/**
	 * Example 1 -------------------------------------------------------
	*/

	/** Create variable of PLC  */
	struct PLC plc;

	/** Create variable of Student  */
	Student student;

	/** Write data to the variables in the structures */
	plc.id     = 1;
	plc.num_io = 24;
	strcpy(plc.info, "Automation Line #1");

	strcpy(student.name, "Student A");
	student.age    =  17;
	student.weight = 45.67;

	/** Read data from the variables in the structures */
	Uart1_Printf("id: %d, num_io: %d, info: %s\r\n", plc.id, plc.num_io, plc.info);
	Uart1_Printf("name: %s, age: %d, %.2f\r\n", student.name, student.age, student.weight);



	/**
	 * Example 2 -------------------------------------------------------
	*/

	/** Declare an array of students */
	Student students[5];

	/** Write data to the array 	*/
	int16_t i;
	for(i=0; i<5; i++)
	{
		sprintf(students[i].name, "Student %c", 'A' + i); 
		students[i].age    = 17 + (i % 5);
		students[i].weight = 45.0 + (i * 1.234);
	}

	/** Read data from the array */
	for(i=0; i<5; i++)
	{
		Uart1_Printf("name: %s, age: %d, %.2f\r\n", students[i].name, students[i].age, students[i].weight);
	}


	System_Start();
}
    
