#include "main.h"


void US_Init(){
    P2DIR &= ~US_TRIGECHO;                  // P2.US_TRIGECHO as input
	P2IES &= ~US_TRIGECHO;                  // low-to-high transition interrupt
	P2IE  |= US_TRIGECHO;                   // Enable P2.US_TRIGECHO interrupts
    P2IFG &= ~US_TRIGECHO;                  // clear flag
}

void US_UpdateValue(){
    P2DIR |= US_TRIGECHO;                   // P2.US_TRIGECHO as output
    US_PORT |= US_TRIGECHO;                 // P2.US_TRIGECHO high
    __delay_cycles(500);
    US_PORT &= ~US_TRIGECHO;                // P2.US_TRIGECHO low
    P2DIR &= ~US_TRIGECHO;                  // P2.US_TRIGECHO as input    
    TA0CCR0 = 65;                           // Enable CC timer interrupt   
                                            // Timer counts for 65us (1cm round trip)
    __delay_cycles(32000);
    TA0CCR0 = 0;                            // Disable CC timer interrupt   
}