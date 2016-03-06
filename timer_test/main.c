#include "main.h" 

/*
 * main.c
 */
 
int Delay_TimeOut = 0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	            // Stop watchdog timer
	
    P1DIR |= BIT0;                          // P1.0 output (LED)
    
    TA0CCTL0 = CCIE;                        // Enable CC interrupt
    TA0CCR0 = 1000; 	                    // Timer counts for 1 ms
    TA0CTL = TASSEL_2 + MC_1 + TACLR + TAIE;// Timer source = SMCLK, 
                                            // up mode until TA0CCR0, 
                                            // clr timer
    
    __bis_SR_register(GIE);                 //enable maskable interrupts 
  
  
	while(1){
	    Delay_TimeOut = 500;
        
	    while(Delay_TimeOut);             // While the timer didn't finish to count
	
	    P1OUT ^= BIT0;                      // Switch led's state
	}
	
	return 0;
}


#pragma vector = TIMER0_A0_VECTOR;
__interrupt void TIMER0_A0_ISR(void){
    
    TA0IV=0; // clear flag
    
    if (Delay_TimeOut) Delay_TimeOut--;
    
}

