#include "main.h" 

/*
 * main.c
 */
 

 
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	                    // Stop watchdog timer
	
	/**************Init Ports**************/
	P1DIR |= LCD_D4 + LCD_D5 + LCD_D6 + LCD_D7;     // P1.{2,3,4,5} output
	P2DIR |= LCD_RS + LCD_EN;                       // P2.{4,5} output
	/**************************************/	

    LCD_Init();

    char str[100]= "Hi ! My name is\nMSP430F5529";
    char str1[100]= "Trololo"; 
    
    while(1){  
        LCD_WriteString(str);
        
        __delay_cycles(500000);
        
        LCD_WriteString(str1);   
    
        __delay_cycles(500000);
    }


	return 0;
}



