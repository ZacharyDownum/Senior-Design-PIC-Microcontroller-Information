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
    
    //disables OC1 while the pwm is set up
    OC1CON1 = 0x0000;
    
    //OC1R / OC1RS = duty cycle %
    OC1R = 0x7A12;
    OC1RS = 0xF424;
    //turns on edge-aligned pwm functionality (110 on bits 0-2) and
    //sets the timer to timer2 (000 on bits 10-12)
    OC1CON1 = 0x0006;
    
    //synchronizes the pwm to this OC module
    OC1CON2 = 0x001F;
    OC1CON2bits.OCTRIG = 0;
    
    //The period and frequency are based off of the equation
    //Period = [PRx + 1] * Tcy * [Timer Prescale Value]
    //Frequency = 1 / Period
    //Where Tcy = 2 * Tosc
    //and Fcy = Fosc / 2
    //for the PIC24FJ128GA202, Tosc = 31.25 ns, and Fosc = 8MHz
    PR2 = 0xF424;
    IPC1bits.T2IP = 1;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    
    //bit 15 is the enable/disable bit (TON)
    //bits 4-5 are the timer prescaler bits (TCKPS)
    //(00 = 1:1, 01 = 1:8, 10 = 1:64, 11 = 1:256)
    //This turns timer2 on with the prescaler value set to 1:1
    T2CON = 0x8000;
    
    
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