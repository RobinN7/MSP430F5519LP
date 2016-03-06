#include "main.h" 

/*
 * main.c
 */

volatile unsigned int US_TimeCounter = 0;
volatile unsigned int US_MesuredTime = 0;
volatile unsigned int US_MesuredDist = 0;

char US_MesuredDist_str[10] = "";


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    LCD_Init();
    
    US_Init(); 

    char strToSend[100] = "";
    
	////////////////// TIMER /////////////////
    TA0CCTL0 |= CCIE;                       // Enable CC timer interrupt
    TA0CCR0 = 0; 	                        // Timer count
    TA0CTL = TASSEL_2 + MC_1 + TACLR + TAIE;// Timer source = SMCLK, 
                                            // up mode until TA0CCR0, 
                                            // clr timer	
	//////////////////////////////////////////

    __bis_SR_register(GIE);                 //enable maskable interrupts 


    LCD_WriteString("Hi buddy !\nDistance: ");
    
    while(1){
        
        US_UpdateValue();
        
        __delay_cycles(200000);  
        
        
        strcpyint(US_MesuredDist_str,US_MesuredTime);

        LCD_Goto(1, 10);            
        LCD_WriteString("     ");    
        LCD_Goto(1, 10);
        LCD_WriteString(US_MesuredDist_str); 
        LCD_WriteString("cm"); 
    }
    
	return 0;
}


void strcpyint(char *str, int nb){
    int divider=1000;
    for (divider=1000; divider!=0; divider/=10){
        switch((nb/divider)%10){
            case 0:
                if ( ((nb/1000) && (divider<1000)) 
                            | ((nb/100) && (divider<100)) 
                                    | ((nb/10) && (divider<10)) )
                    *str++='0'; 
                break;
            case 1:
                *str++='1';  
                break;
            case 2:
                *str++='2'; 
                break;
            case 3:
                *str++='3'; 
                break;
            case 4:
                *str++='4'; 
                break;
            case 5:
                *str++='5'; 
                break;
            case 6:
                *str++='6'; 
                break;
            case 7:
                *str++='7'; 
                break;
            case 8:
                *str++='8'; 
                break;
            case 9:
                *str++='9'; 
                break;
        }
    }
    *str='\0';
}


#pragma vector = TIMER0_A0_VECTOR;
__interrupt void TIMER0_A0_ISR(void){
    if (P2IN & US_TRIGECHO)
        US_TimeCounter++;
    else{
        US_MesuredTime = US_TimeCounter;
    }
    TA0IV=0;                                // clear flag 
}

#pragma vector = PORT2_VECTOR;
__interrupt void PORT2_ISR(void){
	US_TimeCounter = 0;                   // Start to count
	
    P2IFG &= ~US_TRIGECHO;                  // clear flag
}



