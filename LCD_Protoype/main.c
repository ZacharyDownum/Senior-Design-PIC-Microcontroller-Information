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
#include <string.h>
#define DEGREE_ALIAS 0x002B // is the '+' sign acting in place of the ° symbol
void LCD_ClearCommand();
void LCD_Init();
void LCD_SetDisplayAddressCommand(int address);
void LCD_PrintString(char *str);
void LCD_PrintChar(char ch);

int main(void) {

    char str1[18] = "DES:32+C ACT:34+C";
    char str2[10] = "BATT:067%";
    
    ANSC = 0; //turn analog bits off
    Nop();
    TRISC = 0; //turn digital bits to output
    Nop();

    LCD_Init();
    LCD_SetDisplayAddressCommand(0x40);
    LCD_ClearCommand();

//    LCD_PrintString(str1);
//    LCD_SetDisplayAddressCommand(0x0040);
//    LCD_PrintString(str2);
//    LCD_SetDisplayAddressCommand(0x0024);
    
    while(1){}
    
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
     * method. RS needs to be set for data transfer
     * @param: str: the string to be output on the LCD 
     */
    char ch;
    int i = 0;

    for (; i < strlen(str); i++) {
        ch = str[i];
        if (ch == DEGREE_ALIAS) {
            //it is the ° alias symbol, so print it manually
            LCD_PrintChar(ch);
        } else {
            LATC = ch;
            LATC |= 0x0300; // 0000 0011 ---- ---- RS set for Data Mode
            __delay_ms(1);
            LATCbits.LATC9 = 0; // toggle E pin
            // delay?
        }
    }
}

void LCD_PrintChar(char ch) {
    /*
     * This function takes a char (mainly special chars like the degree symbol)
     * and outputs it to the LCD controller. This has to be done by hard-coding
     * the hex value of the char to the LCD data bus
     * RS needs to be set for data transfer
     * @param: ch: the char to be output to the LCD
     */

    int charHexValue;

    //degree symbol
    if (ch == DEGREE_ALIAS) {
        charHexValue = 0x00DF;
    } else {
        // or something to make sure the value has a valid hex value
        charHexValue = ch;
    }

    LATC = charHexValue;
    LATC |= 0x0300; // 0000 0011 ---- ---- RS and E set
    __delay_ms(1);
    LATCbits.LATC9 = 0; // toggle E
    __delay_ms(1);
}