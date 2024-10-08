/*
 * i2c_master.h
 *
 *  Created on: Jul 9, 2024
 *      Author: mlundh
 */

#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

#include "app.h"

#define DATA_LENGTH (8)

typedef struct
{
   uint8_t slaveAddr;
   uint8_t data[DATA_LENGTH];
   I2C_HandleTypeDef *i2c_handler;
 }i2cM_t;


void I2C_master_init(I2C_HandleTypeDef *hi2c);


uint8_t I2C_master_read(uint8_t *buffer, uint16_t Size);

#endif /* I2C_MASTER_H_ */
