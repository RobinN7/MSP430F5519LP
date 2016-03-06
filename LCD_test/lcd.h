#ifndef LCD_H
#define LCD_H


#define LCD_RS          BIT4
#define LCD_EN          BIT5
#define LCD_RSENPORT    P2OUT

#define LCD_D4          BIT2
#define LCD_D5          BIT3
#define LCD_D6          BIT4
#define LCD_D7          BIT5
#define LCD_DATAPORT    P1OUT


void LCD_SendData(byte);
void LCD_WriteConf(byte);
void LCD_WriteChar(byte);
void LCD_Init(void);


#endif	/* MAIN_H */

