/*
 * i2c_slave.c
 *
 *  Created on: Jul 8, 2024
 *      Author: mlundh
 */

#include "i2c_slave.h"

i2cS_t I2C_slave_obj;

void I2C_slave_init(I2C_HandleTypeDef *hi2c)
{
  I2C_slave_obj.i2c_handler = hi2c;
  I2C_slave_obj.regAddr = 0;
  I2C_slave_obj.txcount = 0;
  memset(&(I2C_slave_obj.data), 0, DATA_LENGTH);


  HAL_I2C_EnableListen_IT(hi2c);
}

void I2C_slave_updateData(uint8_t data[DATA_LENGTH])
{
  memcpy(&(I2C_slave_obj.data), data, DATA_LENGTH);
}

static void ResetI2C(I2C_HandleTypeDef *rev_i2c)
{
  HAL_I2C_DeInit(rev_i2c);
  HAL_I2C_Init(rev_i2c);
  I2C_slave_obj.regAddr = 0;
  I2C_slave_obj.txcount = 0;
  memset(I2C_slave_obj.data, 0, DATA_LENGTH);
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection,
    uint16_t AddrMatchCode)
{
  if (TransferDirection == I2C_DIRECTION_TRANSMIT)
  {
    I2C_slave_obj.regAddr = 0; // reset the register address
    HAL_I2C_Slave_Seq_Receive_IT(hi2c, &(I2C_slave_obj.regAddr), 1, I2C_FIRST_AND_LAST_FRAME);
  }
  else
  {
    HAL_I2C_Slave_Seq_Transmit_IT(hi2c, I2C_slave_obj.data, DATA_LENGTH, I2C_FIRST_AND_LAST_FRAME);
  }
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  // We never want to receive data other than the reg address.
  HAL_I2C_EnableListen_IT(hi2c);
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
  HAL_I2C_EnableListen_IT(hi2c);
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  HAL_I2C_EnableListen_IT(hi2c);
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
  uint32_t error_code = HAL_I2C_GetError(hi2c);

  if (error_code == HAL_I2C_ERROR_AF)
  {

  }
  else if(error_code == HAL_I2C_ERROR_BERR)
  {
    ResetI2C(hi2c);
  }
  HAL_I2C_EnableListen_IT(hi2c);
}
