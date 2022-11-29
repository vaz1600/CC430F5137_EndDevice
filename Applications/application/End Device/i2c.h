/*
 * i2c.h
 *
 *  Created on: 16 џэт. 2022 у.
 *      Author: bryki
 */

#ifndef APPLICATIONS_APPLICATION_END_DEVICE_I2C_H_
#define APPLICATIONS_APPLICATION_END_DEVICE_I2C_H_


#include <msp430.h>
#include <stdint.h>

void init_i2c(void);
void i2c_write(uint8_t, uint8_t *, int, int);
void i2c_read(uint8_t, uint8_t *, int);
int i2c_busy(void);
int i2c_nack_received(void);

enum {STOP = 1, RSTART = 0};

#endif /* APPLICATIONS_APPLICATION_END_DEVICE_I2C_H_ */
