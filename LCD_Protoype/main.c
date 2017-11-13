/*
 * File:   main.c
 * Author: crouchcd
 *
 * Created on October 24, 2017, 11:29 PM
 */


#include "xc.h"
#define FCY 4000000UL //FCY = FOSC / 2 unsigned long (UL) 
// pc24fj128ga204 = 8MHz internal oscillator
#include <libpic30.h>
#include <stdio.h>
#include <string.h>
void LCD_ClearCommand();
void LCD_Init();
void LCD_SetDisplayAddressCommand(int address);
void LCD_PrintString(char *str);

int main(void) {

    char str1[17] = "DES:32°C ACT:34°";
    int len = strlen(str1); // = to 5
    LCD_PrintString(str1);

    //    ANSC = 0; //turn analog bits off
    //    Nop();
    //    TRISC = 0; //turn digital bits to output
    //    Nop();
    //
    //    LCD_Init();
    //    LCD_SetDisplayAddressCommand(0x40);
    //    LCD_ClearCommand();
    //
    //    while (1) {
    //        __delay_ms(1000);
    //    }

    return 0;
}

void LCD_ClearCommand() {
    /*
     * This function clears the RC8 bit for Command Mode, Sets E (RC9), and Sets RC0
     * to complete the clear command
     */

    //clear display
    LATC = 0x0201; //0000 0010 0000 0001
    __delay_ms(1);
    LATCbits.LATC9 = 0; // toggle E pin
    __delay_ms(1);
}

//address can only be a number between $20 - $2F OR $40 - $4F

void LCD_SetDisplayAddressCommand(int address) {
    /*
     * This function clears the RC8 bit for Command Mode & Sets E (RC9)
     * RC7 must be set; RC0 - RC6 is used to set the address to a value between
     * $20-2F OR $40-$4F
     * @param: address: must be between $20-2F or $40-4F
     */

    if (0x0020 > address || address > 0x004F)
        return;

    LATC = address; // sets the LCD display address
    LATC |= 0x0280; // 0000 0010 1000 0000 Required configuration
    __delay_ms(1);
    LATCbits.LATC9 = 0; // toggle E pin
    __delay_ms(1);
}

void LCD_Init() {
    /*
     * This function clears the RC8 bit for Command Mode & Sets E (RC9), Reference the LCD
     * documentation for the listing of commands
     */

    //display on command
    LATC = 0x020F; // 0000 0010 0000 1111
    __delay_ms(1);
    LATCbits.LATC9 = 0; // toggle E pin
    __delay_ms(1);

    //set function command
    LATC = 0x023F; // 0000 0010 0011 1111
    __delay_ms(1);
    LATCbits.LATC9 = 0; // toggle E pin
    __delay_ms(1);
}

void LCD_PrintString(char *str) {
    /*
     * This function takes a char[] (null terminated) and outputs each char in
     * the array to the LCD controller. Special characters require a different
     * method
     * @param: str: the string to be output on the LCD 
    */
    char ch;
    int i = 0;

    for (; i < strlen(str); i++) {
        ch = str[i];
        if (ch == 0x00b0) {
            //it is the ° symbol, so print it manually
        } else {
            LATC = ch;
            LATC |= 0x0300; // 0000 0011 ---- ---- RS set for Data Mode
            __delay_ms(1);
            LATCbits.LATC9 = 0; // toggle E pin
            // delay?
        }
    }
}