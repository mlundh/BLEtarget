/*
 * i2c_slave.h
 *
 *  Created on: Jul 8, 2024
 *      Author: mlundh
 */

#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

#include "app.h"
#define DATA_LENGTH (8)
typedef struct
{
   uint8_t regAddr;
   uint8_t txcount;
   uint8_t data[DATA_LENGTH];
   I2C_HandleTypeDef *i2c_handler;
 }i2cS_t;



void I2C_slave_init(I2C_HandleTypeDef *hi2c);
void I2C_slave_updateData(uint8_t data[DATA_LENGTH]);


#endif /* I2C_SLAVE_H_ */
