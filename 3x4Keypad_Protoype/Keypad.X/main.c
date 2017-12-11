#include "mcc_generated_files/mcc.h"
#define FCY 4000000UL //FCY = FOSC / 2 unsigned long (UL) 
// PC24FJ128GA204 = 8MHz internal oscillator
// must be defined before importing <libpic30.h>
#include <libpic30.h>
#include "LCD.h"
#include "xc.h"

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    LCD_Init();
    LCD_ClearCommand();
    LCD_PrintString("Hello World!");
    LATAbits.LATA0 = 1;
    LATAbits.LATA1 = 1;
    LATAbits.LATA7 = 1;
    LATAbits.LATA10 = 1;
    
    while (1)
    {
        // Add your application code
         __delay_ms(5000);
        LCD_ClearCommand();
        LCD_PrintString("Hello World!");

    }

    return -1;
}