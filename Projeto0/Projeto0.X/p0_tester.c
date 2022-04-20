/*
 * 
 * 
 * 
 */


#include "config_bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "uart.h"
#include "timer2.h"
#include "adc.h"

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz

const uint16_t Fout=2000*2; //freq=3Hz for the blinking of the led

int main(int argc, char** argv)
{

    //float val;
    //config RD0 digital output
    TRISDbits.TRISD0=0;
    PORTDbits.RD0=1;
    
    //config RA3 output
    TRISAbits.TRISA3=0;
    
    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
    
    //setup timer 2
    if(setupTimer2(Fout,1)!=0)
    {
        printf("Setup Timer2 error\n\r");
    }
    
    PWM(150);
    
    //setup ADC
    //setupADC();
    
    while(1)
    {
        //start timer 2
        pooling_T2();
        PORTAbits.RA3=!PORTAbits.RA3;
            
        printf("debug values\n\r");
        printf("Porta:%d\n\r",PORTAbits.RA3);
        printf("setupTimer2:%d\n\r",setupTimer2(Fout,1));
    
        //start_adc();
        
        //val=(ADC1BUF0*3.3)/1023;
        //printf("Voltage:%f\n\r",val);
        
    }
    return 0;
}
