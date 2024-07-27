/*
 * i2c_master.c
 *
 *  Created on: Jul 9, 2024
 *      Author: mlundh
 */
#include "i2c_master.h"

i2cM_t I2C_master_obj;
static uint16_t slaveAddr = (0x2<<1);

void I2C_master_init(I2C_HandleTypeDef *hi2c)
{
  I2C_master_obj.i2c_handler = hi2c;
  I2C_master_obj.slaveAddr = slaveAddr;
  memset(&(I2C_master_obj.data), 0, DATA_LENGTH);
}

void I2C_master_read(uint8_t *buffer, uint16_t Size)
{
  HAL_I2C_Master_Receive(I2C_master_obj.i2c_handler, I2C_master_obj.slaveAddr, buffer, Size, 500);
}
