/*
 * adc.h
 *
 *  Created on: 23 џэт. 2022 у.
 *      Author: bryki
 */

#ifndef APPLICATIONS_APPLICATION_END_DEVICE_ADC_H_
#define APPLICATIONS_APPLICATION_END_DEVICE_ADC_H_

#include <msp430.h>
#include <stdint.h>

void adc_Init(void);
int16_t adc_GetTemp(void);
uint16_t adc_GetRawTemp(void);

#endif /* APPLICATIONS_APPLICATION_END_DEVICE_ADC_H_ */
