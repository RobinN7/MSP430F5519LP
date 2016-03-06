#include "main.h"


void InitAll(){
    
    InitPorts();
    
    InitUART();
    
    InitTimers();
    
   __bis_SR_register(GIE); //enable maskable interrupts
}


void InitPorts(){
    P1DIR |= BIT0;                      // P1.0 output
}

void InitUART(){
/*
    P4SEL |= BIT4+BIT5;              // Switch P4.4 to secondary function
    UCA1IE |= UCRXIE;           // Enable the RX interrupt.  Now, when bytes are
                                // received, the USCI_A1 vector will be generated.
*/

    P3SEL |= BIT3+BIT4;                 // P3.3,4 = USCI_A0 TXD/RXD
    	
    UCA0CTL1 |= UCSWRST;                // Reset the state machine
    UCA0CTL1 |= UCSSEL_2;               // SMCLK
    	
    UCA0BR0 = 0x68;                     // 1MHz/9600=0x68 (see Data Sheet for calculations)
    UCA0BR1 = 0x00;   
    	
    UCA0MCTL |= UCBRS_1 + UCBRF_0;      // Modulation UCBRSx=1, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST;               // Initialize the state machine
    UCA0IE |= UCRXIE;                   // Enable USCI_A0 RX interrupt
}

void InitTimers(){
    TA0CCTL0 = CCIE;                        // Enable CCR0 interrupt
    TA0CCR0 = 1000; 	                    // Timer counts for 1 ms
    TA0CTL = TASSEL_2 + MC_1 + TACLR + TAIE;// Timer source = SMCLK, 
                                            // up mode until TA0CCR0, 
                                            // clr timer
}


