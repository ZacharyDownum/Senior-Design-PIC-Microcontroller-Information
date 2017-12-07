/* 
 * File:   main.c
 * Author: crouchcd
 *
 * Created on December 6, 2017, 6:08 PM
 */
#define FCY 4000000UL //FCY = FOSC / 2 unsigned long (UL) 
// PC24FJ128GA204 = 8MHz internal oscillator
// must be defined before importing <libpic30.h>
#include <libpic30.h>
#include "LCD.h"
#include "xc.h"
#include "mcc_generated_files/mcc.h"
/*
 * 
 */
int main() {
    SYSTEM_Initialize();
    LCD_Init();
    LCD_ClearCommand();
    LCD_PrintString("Hello World!");
    while (1)
    {
        __delay_ms(5000);
        LCD_ClearCommand();
        LCD_PrintString("Hello World!");
    }
}

