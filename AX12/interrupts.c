#include "main.h"

#pragma vector = TIMER0_A0_VECTOR;
__interrupt void TIMER0_A0_ISR(void){
    
    TA0IV=0; // clear flag
    
    if (Delay_TimeOut_AX12) Delay_TimeOut_AX12--;
    
}
