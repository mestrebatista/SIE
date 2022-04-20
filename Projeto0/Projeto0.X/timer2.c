#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include "timer2.h"

#define PBCLOCK 40000000L
/*
#define TCKPS_1     0 // TCKPS code for 1 pre-scaler
#define TCKPS_2     1 // TCKPS code for 2 pre-scaler
#define TCKPS_4     2 // TCKPS code for 4 pre-scaler
#define TCKPS_8     3 // TCKPS code for 8 pre-scaler
#define TCKPS_16    4 // TCKPS code for 16 pre-scaler
#define TCKPS_32    5 // TCKPS code for 32 pre-scaler
#define TCKPS_64    6 // TCKPS code for 64 pre-scaler
#define TCKPS_256   7 // TCKPS code for 256 pre-scaler
*/ //defines used on old tests

const uint16_t tckps_scaler[]={1,2,4,8,16,32,64,256};

int setupTimer2(uint16_t Fout, uint8_t starter)
{
    
    T2CONbits.ON=0;  //Stop timer
    IFS0bits.T2IF=0; //Reset interrupt flag
    IPC2bits.T2IP=5; //Interrupt priority
    IEC0bits.T2IE=0; //Enable T2 interrupts
    // Timer period configuration
        
    T2CONbits.T32 = 0; // 16 bit timer operation
    TMR2=0;
    
    uint16_t i=7;
    do
    {
        if(i==(sizeof tckps_scaler))
        {
            printf("prescaler error!!\n\r");
            return -1;
        }
        
        T2CONbits.TCKPS=i; //devide by prescaler
        PR2=(PBCLOCK/(tckps_scaler[i]*Fout))-1; //PR value
        i--;
    }while(PR2>=65535); //pr2 larger than 2^16bits
    
    printf("PR2: %d\n\r",PR2);
    printf("prescaler: %d\n\r",i);
    printf("tckps: %d\n\r",tckps_scaler[i]);
    T2CONbits.ON=starter; //start timer
    
    return 0;// flag to confirm the func
}

void pooling_T2(void)
{
    while(IFS0bits.T2IF==0);  //wait for polling clock signal
    IFS0bits.T2IF=0;          //reset the timer interrupt flag
}