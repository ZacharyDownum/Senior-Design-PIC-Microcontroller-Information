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

//basic initialization for all pins
void PIC_Initialization(void)
{
    //changes all pins to digital
    ANSB = 0x0000;
    Nop();
    
    //changes all pins to output
    TRISB = 0x0000;
    Nop();
}

//uses OC1's PWM functionality and the RB0 pin
void Example_PWM_Initialization(void)
{
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
}

//uses AN3/RB1 pin for the AD conversion functionality
//uses RB2 pin for the output response based on evaluation of input
void Example_ADC_Initialization(int analogInputPinMask)
{
    //Configures pin B1 as an analog input for AD conversion example
    ANSBbits.ANSB1 = 1;
    TRISBbits.TRISB1 = 1;
    
    //sets the two bits for the PVCFG to 0
    //this makes the positive voltage reference use AVdd (3.3V from initial config)
    AD1CON2bits.PVCFG = 0x0000;
    //sets the single bit for NVCFG0 to 0
    //this makes the negative voltage reference use AVss (0.0V from initial config)
    AD1CON2bits.NVCFG0 = 0x0000;
    
    //AD Channel B uses Vss for negative input (bits set to 000)
    AD1CHSbits.CH0NB = 0x0000;
    //AD Channel B uses AN3 for positive input (bits set to 00011)
    AD1CHSbits.CH0SB = 0x0003;
    //AD Channel A uses Vss for negative input (bits set to 000)
    AD1CHSbits.CH0NA = 0x0000;
    //AD Channel A uses AN3 for positive input (bits set to 00011)
    AD1CHSbits.CH0SA = 0x0003;
    
    //AD conversion clock synced with Tcy (Tad = Tcy)
    //(bits set to 00000000)
    AD1CON3bits.ADCS = 0x0000;
    //AD Clock Source set to Timer5
    AD1CON1bits.SSRC = 0x0003;
    //Internal Clock auto sample rate set to 1*Tad (bits set to 00001)
    AD1CON3bits.SAMC = 0x0001;
    
    //Turns off input scanning on the high-word channel (bits set to 0000)
    AD1CSSH = 0x0000;
    //Turns off input scanning on the low-word channel (bits set to 0000)
    AD1CSSL = 0x0000;
    
    //Sets the format for the AD conversion data as a signed, decimal result
    //and right-justified (bits set to 01)
    AD1CON1bits.FORM = 0x0001;
    
    //auto scan enabled (bit set to 1)
    AD1CON5bits.ASEN = 0x0001;
    //high power enabled after scan (bit set to 0)
    AD1CON5bits.LPEN = 0x0000;
    //CTMU is not enabled by AD conversion (bit set to 0)
    AD1CON5bits.CTMREQ = 0x0000;
    //Band gap is not enabled by AD conversion (bit set to 0)
    AD1CON5bits.BGREQ = 0x0000;
    //
    
}

int main(void)
{
    PIC_Initialization();
    //Example_PWM_Initialization();
    Example_ADC_Initialization();
    
    while (true)
    {
        if (PORTBbits.RB8 >= 0.01)
        {
            //setting RB5 to active HIGH (pin 14)
            //This operation will remain here for a while to ensure
            //The PIC is actually working as the PWM functionality
            //is added and built upon
            LATBbits.LATB5 = 1;
            Nop();
        }
        else
        {
            LATBbits.LATB5 = 0;
            Nop();
        }
    }
    
    return EXIT_SUCCESS;
}