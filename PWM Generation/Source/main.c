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
    
    //sets the remappable pin RP0 to output the value of OC1 (the output compare
    //pin that is being used to generate the PWM)
    //See page 174 in the PIC24FJ128GA204 documentation to find the list
    //of all values that can be mapped to the remappable pins
    RPOR0 = 13;
    
    //OC1R / OC1RS = duty cycle %
    OC1R = 0x0021;
    //sets the period
    OC1RS = 0x0042;
    
    //sets OC1 as the synchronization source
    OC1CON2 = 0x001F;
    OC1CON2bits.OCTRIG = 0;
    
    //sets the pwm timer to the peripheral clock (Fcy)
    //(bits set to 111)
    OC1CON1bits.OCTSEL = 0x0007;
    
    //turns on edge-aligned pwm functionality (bits set to 110)
    OC1CON1bits.OCM = 0x0006;
    
    //The period and frequency are based off of the equation
    //Period = [PRx + 1] * Tcy * [Timer Prescale Value]
    //Frequency = 1 / Period
    //Where Tcy = 2 * Tosc
    //and Fcy = Fosc / 2
    //for the PIC24FJ128GA202, Tosc = 31.25 ns, and Fosc = 8MHz
    //PR2 = 0x00F0;
    //IPC1bits.T2IP = 1;
    //IFS0bits.T2IF = 0;
    //IEC0bits.T2IE = 1;
    
    //bit 15 is the enable/disable bit (TON)
    //bits 4-5 are the timer prescaler bits (TCKPS)
    //(00 = 1:1, 01 = 1:8, 10 = 1:64, 11 = 1:256)
    //This turns timer2 on with the prescaler value set to 1:1
    //T2CON = 0x8000;
}

//uses AN3/RB1 pin for the AD conversion functionality
//uses RB2 pin for the output response based on evaluation of input
void Example_ADC_Initialization(void)
{
    //Configures pin B1 as an analog input for AD conversion example
    ANSBbits.ANSB1 = 1;
    TRISBbits.TRISB1 = 1;
    
    //enables 10-bit A/D conversion (bit set to 0)
    AD1CON1bits.MODE12 = 0x0000;
    //Sets the format for the AD conversion data as a signed, decimal result
    //and right-justified (bits set to 01)
    AD1CON1bits.FORM = 0x0001;
    //AD Sampling ends when the sample bit (SAMP) is cleared (bits set to 0000)
    AD1CON1bits.SSRC = 0x0000;
    
    //sets the two bits for the PVCFG to 0
    //this makes the positive voltage reference use AVdd (3.3V from initial config)
    AD1CON2bits.PVCFG = 0x0000;
    //sets the single bit for NVCFG0 to 0
    //this makes the negative voltage reference use AVss (0.0V from initial config)
    AD1CON2bits.NVCFG0 = 0x0000;
    //generates an interrupt after completing the AD conversion for each sample
    //(bits set to 00000)
    AD1CON2bits.SMPI = 0x0000;
    
    //clock source is derived from system clock (bit set to 0)
    AD1CON3bits.ADRC = 0x0000;
    //Internal Clock sample rate set to 1*Tad (bits set to 00001)
    AD1CON3bits.SAMC = 0x0001;
    //AD conversion clock synced with Tcy (Tad = Tcy)
    //(bits set to 00000000)
    AD1CON3bits.ADCS = 0x0000;

    //AD Channel B uses Vss for negative input (bits set to 000)
    AD1CHSbits.CH0NB = 0x0000;
    //AD Channel B uses AN3 for positive input (bits set to 00011)
    AD1CHSbits.CH0SB = 0x0003;
    //AD Channel A uses Vss for negative input (bits set to 000)
    AD1CHSbits.CH0NA = 0x0000;
    //AD Channel A uses AN3 for positive input (bits set to 00011)
    AD1CHSbits.CH0SA = 0x0003;
    
    //Turns off input scanning on the high-word channel (bits set to 0000)
    AD1CSSH = 0x0000;
    //Turns off input scanning on the low-word channel (bits set to 0000)
    AD1CSSL = 0x0000;
    
    //turns on the A/D module after initialization of all registers
    AD1CON1bits.ADON = 1;
    
    //turns off the bit notifying that the A/D interrupt has occurred
    //(sets bit to 0)
    IFS0bits.AD1IF = 0x0000;
    //Enables the A/D interrupt (sets bit to 1)
    IEC0bits.AD1IE = 0x0001;
    //Sets the priority of the interrupt to Level 2 (sets bits to 010)
    IPC3bits.AD1IP = 0x0002;
}

int main(void)
{
    PIC_Initialization();
    Example_PWM_Initialization();
    //Example_ADC_Initialization();
    
    while (true)
    {
        //starts the A/D sampling process on AN3 (according to the initialization)
        //AD1CON1bits.SAMP = 1;
        //while (!AD1CON1bits.DONE);
    }
    
    return EXIT_SUCCESS;
}