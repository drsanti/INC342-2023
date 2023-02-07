
#include "ecc.h"

void toggle()
{
    int i;
    for(i=0; i<4; i++)
    {
        Led_Inv(i);
    }
}

int main(void)
{
    System_Init();

    Uart1_Printf("Hello, from MCU!!\r\n");

    Led0_Inv();
    Led2_Inv();

    Timer_Create(250, toggle);

    System_Start();
}
    