#include "adc.h"

volatile long internal_temp;

void adc_Init(void)
{
  /* Initialize the shared reference module */
  REFCTL0 |= REFMSTR + REFVSEL_0 + REFON;    // Enable internal 1.5V reference

  /* Initialize ADC12_A */
  ADC12CTL0 = ADC12SHT0_15 + ADC12ON;        // Set sample time
  ADC12CTL1 = ADC12SHP;                     // Enable sample timer
  ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // ADC input ch A10 => temp sense
  //ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO

  __delay_cycles(75);                       // 35us delay to allow Ref to settle
                                            // based on default DCO frequency.
                                            // See Datasheet for typical settle
                                            // time.
  ADC12CTL0 |= ADC12ENC;
}

int16_t adc_GetTemp(void)
{
    volatile long IntDegC;

    ADC12IFG &= ~0x0001;
    ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start

    //__bis_SR_register(LPM4_bits + GIE);     // LPM4 with interrupts enabled
    //__no_operation();

    while((ADC12IFG & 0x0001) == 0);
    internal_temp = ADC12MEM0;

    // Temperature in Celsius
    // ((A10/4096*1500mV) - 894mV)*(1/3.66mV) = (A10/4096*410) - 244
    // = (A10 - 2438) * (410 / 4096)
    IntDegC = ((internal_temp - 2438) * 410) / 4096;

    return (int16_t )IntDegC;
}

uint16_t adc_GetRawTemp(void)
{
    ADC12IFG &= ~0x0001;
    ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start

    //__bis_SR_register(LPM4_bits + GIE);     // LPM4 with interrupts enabled
    //__no_operation();

    while((ADC12IFG & 0x0001) == 0);
    internal_temp = ADC12MEM0;

    return (uint16_t )internal_temp;
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
      internal_temp = ADC12MEM0;                       // Move results, IFG is cleared
    __bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU
    break;
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}
