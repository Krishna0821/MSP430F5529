#include <msp430.h>
volatile unsigned int adcvalue;
int main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop WDT
P1DIR |= BIT2; // P1.2 output
P1SEL |= BIT2; // P1.2 option select
TA0CCR0 = 4095; // PWM Period
TA0CCTL1 = OUTMOD_7; // CCR1 reset/set
TA0CCR1 = 0; // CCR1 PWM duty cycle
TA0CTL = TASSEL_2 + MC_1 + TACLR; // SMCLK, up mode, clear TAR
ADC12CTL0 = ADC12SHT02 + ADC12ON; // Sampling time, ADC12 on
ADC12MCTL0 = ADC12INCH_1;
ADC12CTL1 = ADC12SHP; // Use sampling timer
ADC12IE = 0x01; // Enable interrupt
ADC12CTL0 |= ADC12ENC;
P6SEL |= 0x02;
while (1)
{
ADC12CTL0 |= ADC12SC; // Start sampling/conversion
__bis_SR_register(GIE); // LPM0, ADC12_ISR will force exit
__no_operation(); // For debugger
}
}
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
adcvalue = ADC12MEM0;
TA0CCR1= ADC12MEM0;

}

