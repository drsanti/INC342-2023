#include "ecc.h"

int main(void)
{
    System_Init();

    Uart1_Printf("Hello, from MCU!!\r\n");


    System_Start();
}
    