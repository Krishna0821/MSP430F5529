#include <msp430f5529.h>
unsigned int ADC_result =0;
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 on
  ADC12CTL1 = ADC12SHP;                     // Use sampling timer
  ADC12IE = 0x01;                           // Enable interrupt
  ADC12CTL0 |= ADC12ENC;
  P6SEL |= 0x01;                            // P6.0 ADC option select
  P1DIR |= 0x01;                            // P1.0 output

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion

    __bis_SR_register(GIE);     // LPM0, ADC12_ISR will force exit
    __no_operation();                       // For debugger
  }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    ADC_result = ADC12MEM0;
    if (ADC12MEM0 >= 0x7ff)                 // ADC12MEM = A0 > 0.5AVcc?
      P1OUT |= BIT0;                        // P1.0 = 1
    else
      P1OUT &= ~BIT0;                       // P1.0 = 0
}
