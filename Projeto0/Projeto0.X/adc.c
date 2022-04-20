
#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void setupADC(void)
{
    // Initialize the adc
    DDPCONbits.JTAGEN=0;    //Disable JTAG interface
    
    AD1CON1bits.SSRC=7; //internal counter end sampling and starts conv
    AD1CON1bits.CLRASAM=1;//Stop converstion when first A/D converter interrupt generated and clears ASAM bit automatically 
    AD1CON1bits.FORM=0;//Output format 16bit integer
    AD1CON2bits.VCFG=0;//VR+=AVdd;VR-=Avss
    AD1CON2bits.SMPI=0;//Number(+1) of consecutive conversions, stored in ADC1BUF0...ADCBUF
    AD1CON3bits.ADRC=1;//ADC uses internal RC clock
    AD1CON3bits.SAMC=16;//Sample time 16TAD(TAD=100ns)
    
    //AN0 as input
    AD1CHSbits.CH0SA=0;//Select AN0 input for A/D
    TRISBbits.TRISB0=1;//Set AN0 to input mode
    AD1PCFGbits.PCFG0=0;//Set AN0 to analog mode
    
    //enable
    AD1CON1bits.ON=1;// A/D module enable
    
}

void start_adc(void)
{
    AD1CON1bits.ASAM=1;//Start conversion
    while(IFS1bits.AD1IF==0);//wait for
    IFS1bits.AD1IF=0;//reset interrupt flag

}
