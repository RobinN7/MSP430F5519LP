#include "main.h"
/*
 * main.c
 */
 
byte a= 0x11; 
byte * b = &a;

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	InitAll();
	
    while(1){
        
        while (!(UCA0IFG&UCTXIFG));     // Is the USCI_A0 TX buffer ready?
        UCA0TXBUF = 0x41;               // TX -> A 
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = 0x42;               // TX -> B 
        while (!(UCA0IFG&UCTXIFG));
        __delay_cycles(250000);
        UCA0TXBUF = 'C';                // TX –> C
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = '\n';               // TX –> \n
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = '\r';               // TX –> \r
        
        //PushUART('t');
        PutAX(AX_BROADCAST,AX_GOAL_POSITION,220);
        
        
        P1OUT ^= BIT0;
        __delay_cycles(1000000);
    }
	
	
	return 0;
}
