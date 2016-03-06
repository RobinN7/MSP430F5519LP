#include "main.h"

void LCD_Init(){
 
    ///////////////////////////////////////
    /// TRICK : SET 4-BIT DATA BUS MODE ///
    // Send 3 times 0x3 and one time 0x2 //
    ///////////////////////////////////////
    LCD_WriteConf(0x33); 
    LCD_WriteConf(0x32); 
    ///////////////////////////////////////
 
    LCD_WriteConf(0x28);                        // Function set, interface data length 4-bit, 
                                                // 2 display lines, 5x8 dots display font type 

    LCD_WriteConf(0x0E);                        // Display ON, blinking cursor

    LCD_WriteConf(0x01);                        // CLR screen
}

void LCD_SendData(byte data){
    LCD_DATAPORT = LCD_D7 *  (data>>7)          // Send higher bits to LCD
                 + LCD_D6 * ((data>>6)%2) 
                 + LCD_D5 * ((data>>5)%2) 
                 + LCD_D4 * ((data>>4)%2);  
    LCD_RSENPORT |= LCD_EN;                     // SET EN
    LCD_RSENPORT &= ~LCD_EN;                    // CLR EN
    LCD_DATAPORT = LCD_D7 * ((data>>3)%2)       // Send lower bits to LCD
                 + LCD_D6 * ((data>>2)%2) 
                 + LCD_D5 * ((data>>1)%2)
                 + LCD_D4 *  (data%2);
    LCD_RSENPORT |= LCD_EN;                     // SET EN
    LCD_RSENPORT &= ~LCD_EN;                    // CLR EN
    __delay_cycles(5000); 
}

void LCD_WriteConf(byte data){
    LCD_RSENPORT &= ~LCD_RS;                    // CLR RS
    LCD_SendData(data);
}

void LCD_WriteChar(byte data){
    LCD_RSENPORT |= LCD_RS;                     // SET RS
    LCD_SendData(data);
}

void LCD_WriteString(byte *data){
    LCD_WriteConf(0x01);                        // CLR screen
    LCD_WriteConf(0x02);                        // Return home
    while(*data){
        if (*data=='\n'){   
            LCD_WriteConf(0xC0);
            data++;
        }
        else
            LCD_WriteChar(*data++);  
    }
}
