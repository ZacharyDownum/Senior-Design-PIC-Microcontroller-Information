/*
 * File:   main.c
 * Author: crouchcd
 *
 * Created on October 24, 2017, 11:29 PM
 */

#define FCY 4000000UL //FCY = FOSC / 2 unsigned long (UL) 
// PC24FJ128GA204 = 8MHz internal oscillator
// must be defined before importing <libpic30.h>
#include <libpic30.h>
#include "LCD.h"
#include "xc.h"

int main(void) {

    ANSC = 0; //turn analog bits off
    Nop();
    TRISC = 0; //turn digital bits to output
    Nop();

    LCD_Init();
    LCD_ClearCommand();

    LCD_SetDisplayAddressCommand(0x0040);
    LCD_PrintString("DES:");
    LCD_PrintInteger(33);
    LCD_PrintString("+C");
    LCD_SetDisplayAddressCommand(0x0044);

    int i = 33;
    while (i < 42)
    {
        LCD_PrintInteger(i);
        __delay_ms(100);
        LCD_SetDisplayAddressCommand(0x0044);
        i++;
    }

    while(1){}
    return 0;
}