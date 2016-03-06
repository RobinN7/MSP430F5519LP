#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    P1DIR |= BIT0;                      // P1.0 output
    
    P3SEL |= BIT3+BIT4;                 // P3.3,4 = USCI_A0 TXD/RXD
    	
    UCA0CTL1 |= UCSWRST;                // Reset the state machine
    	
    UCA0CTL1 |= UCSSEL_2;               // SMCLK
    	
    UCA0BR0 = 0x68;                     // 1MHz/9600=0x68 (see Data Sheet for calculations)
    UCA0BR1 = 0x00;   
    	
    UCA0MCTL |= UCBRS_1 + UCBRF_0;      // Modulation UCBRSx=1, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST;               // Initialize the state machine
    UCA0IE |= UCRXIE;                   // Enable USCI_A0 RX interrupt
    
    while(1){
        
        while (!(UCA0IFG&UCTXIFG));     // Is the USCI_A0 TX buffer ready?
        UCA0TXBUF = 0x41;               // TX -> A 
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = 0x42;               // TX -> B 
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = 'C';                // TX –> C
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = '\n';               // TX –> \n
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = '\r';               // TX –> \r
        
        P1OUT ^= BIT0;
        __delay_cycles(400000);
        
    }
    
    bis_SR_register(GIE);               //interrupts enabled

	
	return 0;
}
