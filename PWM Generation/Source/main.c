//set the specific PIC to be used so xc.h includes the proper
//headers automatically
//Not necessary if using MPLAB X IDE because the proper PIC is
//recognized automatically.  It is only included as a failsafe.
#define __PIC24FJ128GA202__

#include <xc.h>
#include <stdlib.h>

//aliases for additional layers of abstraction
#define true 1
#define false 0


void __attribute__ ((__interrupt__)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;
}

int main(void)
{
    //turn off analog bits and change all digital bits to output
    ANSB = 0;
    Nop();
    TRISB = 0;
    Nop();
    
    
    //setting RB5 to active HIGH (pin 14)
    //This operation will remain here for a while to ensure
    //The PIC is actually working as the PWM functionality
    //is added and built upon
    LATBbits.LATB5 = 1;
    Nop();
    
    OC1CON1 = 0x0000;
    OC1R = 0x0026;
    OC1RS = 0x0026;
    OC1CON1 = 0x0006;
    PR2 = 0x0046;
    IPC1bits.T2IP = 1;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    T2CONbits.TON = 1;
    
    //sets the remappable pin RP0 to output the value of OC1 (the output compare
    //pin that is being used to generate the PWM)
    //See page 174 in the PIC24FJ128GA204 documentation to find the list
    //of all values that can be mapped to the remappable pins
    RPOR0 = 13;
    
    while (true)
    {
        
    }
    
    return EXIT_SUCCESS;
}