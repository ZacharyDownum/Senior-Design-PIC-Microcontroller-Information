#include <p24FJ128GA204.h>
#include "KeypadHandler.h"
#define FCY 4000000UL //FCY = FOSC / 2
#include <libpic30.h>
#define NUM_ROWS 4
#define NUM_COLS 3

/*
 Column pins set as positive edge interrupts
 */
// RB7 - INT0 (PIC pin 43) - COL0 - keypad pin 3
// RB8 - INT1 (PIC pin 44) - COL1 - keypad pin 1
// RB9 - INT2 (PIC pin 1) - COL2 - keypad pin 5

/*
 Row pins set as general output pins (default HIGH)
 */
// RA0 - ROW0 - keypad pin 2
// RA1 - ROW1 - keypad pin 7
// RA7 - ROW2 - keypad pin 6
// RA10 - ROW3 - keypad pin 4

char keypadArray[NUM_ROWS][NUM_COLS] = {
    {'1', '2', '3'}, 
    {'4', '5', '6'}, 
    {'7', '8', '9'}, 
    {'*', '0', '#'}
};
    
#define ROW0 PORTAbits.RA0
#define ROW1 PORTAbits.RA1
#define ROW2 PORTAbits.RA7
#define ROW3 PORTAbits.RA10
    
#define COL0 PORTBbits.RB7
#define COL1 PORTBbits.RB8
#define COL2 PORTBbits.RB9
    
char getCol_0_Keypress() {
    /*
     * toggles row pins LOW to determine which key was pressed on
     * column 0
     */
        int i = 0;
        char keyPressed = '\0';
        
        for (; i < NUM_ROWS; i++) {
            switch (i) {
                case 0:
                    ROW0 = 0;
                    __delay_ms(10);
                    if (COL0 == 0)
                        keyPressed = keypadArray[0][0];
                    ROW0 = 1;
                    break;
                case 1:
                    ROW1 = 0;
                    __delay_ms(10);
                    if (COL0 == 0)
                        keyPressed = keypadArray[1][0];
                    ROW1 = 1;
                    break;
                case 2:
                    ROW2 = 0;
                    __delay_ms(10);
                    if (COL0 == 0)
                        keyPressed = keypadArray[2][0];
                    ROW2 = 1;
                    break;
                case 3:
                    ROW3 = 0;
                    __delay_ms(10);
                    if (COL0 == 0)
                        keyPressed = keypadArray[3][0];
                    ROW3 = 1;
                    break;
            }
            if (keyPressed != '\0')
                break;
        }
        
        return keyPressed;
}

char getCol_1_Keypress() {
    /*
     * toggles row pins LOW to determine which key was pressed on
     * column 1
     */
        int i = 0;
        char keyPressed = '\0';
        
        for (; i < NUM_ROWS; i++) {
            switch (i) {
                case 0:
                    ROW0 = 0;
                    __delay_ms(10);
                    if (COL1 == 0)
                        keyPressed = keypadArray[0][1];
                    ROW0 = 1;
                    break;
                case 1:
                    ROW1 = 0;
                    __delay_ms(10);
                    if (COL1 == 0)
                        keyPressed = keypadArray[1][1];
                    ROW1 = 1;
                    break;
                case 2:
                    ROW2 = 0;
                    __delay_ms(10);
                    if (COL1 == 0)
                        keyPressed = keypadArray[2][1];
                    ROW2 = 1;
                    break;
                case 3:
                    ROW3 = 0;
                    __delay_ms(10);
                    if (COL1 == 0)
                        keyPressed = keypadArray[3][1];
                    ROW3 = 1;
                    break;
            }
            if (keyPressed != '\0')
                break;
        }

        return keyPressed;
}

char getCol_2_Keypress() {
    /*
     * toggles row pins LOW to determine which key was pressed on
     * column 2
     */
        int i = 0;
        char keyPressed = '\0';
        
        for (; i < NUM_ROWS; i++) {
            switch (i) {
                case 0:
                    ROW0 = 0;
                    __delay_ms(10);
                    if (COL2 == 0)
                        keyPressed = keypadArray[0][2];
                    ROW0 = 1;
                    break;
                case 1:
                    ROW1 = 0;
                    __delay_ms(10);
                    if (COL2 == 0)
                        keyPressed = keypadArray[1][2];
                    ROW1 = 1;
                    break;
                case 2:
                    ROW2 = 0;
                    __delay_ms(10);
                    if (COL2 == 0)
                        keyPressed = keypadArray[2][2];
                    ROW2 = 1;
                    break;
                case 3:
                    ROW3 = 0;
                    __delay_ms(10);
                    if (COL2 == 0)
                        keyPressed = keypadArray[3][2];
                    ROW3 = 1;
                    break;
            }
            if (keyPressed != '\0')
                break;
        }
        
        return keyPressed;
}