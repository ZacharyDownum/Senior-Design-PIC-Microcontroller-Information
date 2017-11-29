//set the specific PIC to be used so xc.h includes the proper
//headers automatically
//Not necessary if using MPLAB X IDE because the proper PIC is
//recognized automatically.  Included as a failsafe.
#define __PIC24FJ128GA202__
#define true 1
#define false 0

#include <xc.h>
#include <stdlib.h>


int main(void)
{
    //turn off analog bits and change all digital bits to output
    ANSB = 0;
    Nop();
    TRISB = 0;
    Nop();
    
    //setting all pins on port B to HIGH
    PORTB = 0xffff;
    Nop();
    
    while (true)
    {
        Nop();
    }
    
    return EXIT_SUCCESS;
}