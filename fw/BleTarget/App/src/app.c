
#include "app.h"
#include "sensor.h"
#include "i2c_slave.h"
#include "serialization.h"
#include "i2c_master.h"

uint8_t* serialize_int32_t(uint8_t *buffer, uint32_t* size, int32_t *value);
uint8_t* deserialize_int32_t(uint8_t *buffer, uint32_t* size, int32_t* value);

static uint8_t master = 1;


void app_init(I2C_HandleTypeDef* hi2c)
{
  master = (GPIO_PIN_SET == HAL_GPIO_ReadPin(BOOT_GPIO_Port,BOOT_Pin));
  if(master)
  {
    I2C_slave_init(hi2c);
  }
  else
  {
    // any other init needed?
  }



}


void taskCyclic()
{
  if(Sensor_newValue())
  {
    int32_t position = Sensor_getPos();
    float speed = Sensor_getSpeed();
    Sensor_clear();

    uint8_t buffer[DATA_LENGTH] = {0};
    uint8_t* buffP = buffer;
    uint32_t buffSize = DATA_LENGTH;

    int32_t speedInt = (int32_t)speed;
    int32_t speedDecimal = (int32_t)((speed - speedInt) * 1000);

    LOG_ENTRY("Position: %d, Speed: %d,%d", (int)position, (int)speedInt, (int)speedDecimal);
    if(master)
    {
      serialize_int32_t(buffP, &buffSize, &position);
      serialize_int32_t(buffP, &buffSize, &speedDecimal);

      I2C_slave_updateData(buffer);
    }
    else
    {

      I2C_master_read(buffer, DATA_LENGTH);
      // send on uart or BLE!

    }

  }
}
