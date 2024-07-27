
#include "app.h"
#include "sensor.h"
#include "i2c_slave.h"
#include "serialization.h"
#include "i2c_master.h"
#include "slip_packet.h"

#define MESSAGE_SIZE 12

static uint8_t master = 1;
static SLIP_t *slipPacket = NULL;

void invalidateData();

void app_init(I2C_HandleTypeDef* hi2c)
{
  slipPacket = Slip_Create(32);
  master = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(BOOT_GPIO_Port,BOOT_Pin));



  if(master)
  {
    I2C_master_init(hi2c);
    Sensor_init(master, NULL); // do not need to invalidate data as the master.
  }
  else
  {
    I2C_slave_init(hi2c);
    Sensor_init(master, &invalidateData); // Data will be invalidated after the lockout period.
  }
}

void taskCyclic()
{
  if(Sensor_newValue())
  {
    int32_t position = Sensor_getPos();
    float speedF = Sensor_getSpeed();
    Sensor_clear();

    int32_t speed = (int32_t)speedF;
    //int32_t speedDecimal = (int32_t)((speedF - speed) * 1000); // to use if more resoultion is needed...


    if(master)
    {

      // Read data from slave.
      uint8_t buffer[DATA_LENGTH];
      uint8_t *bufferP = buffer;
      uint32_t bufferSize = DATA_LENGTH;

      I2C_master_read(buffer, DATA_LENGTH);

      int32_t positionY = 0;
      int32_t speedY = 0;;
      bufferP = deserialize_int32_t(bufferP, &bufferSize, &positionY);
      bufferP = deserialize_int32_t(bufferP, &bufferSize, &speedY);

      // for now use the largest speed value.
      if(speedY > speed)
      {
        speed = speedY;
      }

      // Transmit data, serial over USB
      uint8_t message[MESSAGE_SIZE];
      uint8_t *messageP = message;
      uint32_t messageSize = MESSAGE_SIZE;

      messageP = serialize_int32_t(messageP, &messageSize, &position);
      messageP = serialize_int32_t(messageP, &messageSize, &positionY);
      messageP = serialize_int32_t(messageP, &messageSize, &speed);

      Slip_Packetize(message, 12, slipPacket);

      CDC_Transmit_FS(slipPacket->payload, slipPacket->packetSize);

    }
    else
    {
      uint8_t buffer[DATA_LENGTH];
      uint8_t *bufferP = buffer;
      uint32_t bufferSize = DATA_LENGTH;

      bufferP = serialize_int32_t(bufferP, &bufferSize, &position);
      bufferP = serialize_int32_t(bufferP, &bufferSize, &speed);

      I2C_slave_updateData(buffer);
    }
    //LOG_ENTRY("Position: %d, Speed: %d,%d", (int)position, (int)speedInt, (int)speedDecimal);


  }
}

void invalidateData()
{
  uint8_t buffer[DATA_LENGTH] = {0};
  uint8_t *bufferP = buffer;
  uint32_t bufferSize = DATA_LENGTH;

  int32_t position = ERROR;
  int32_t speed = SPEED_ERROR;

  bufferP = serialize_int32_t(bufferP, &bufferSize, &position);
  bufferP = serialize_int32_t(bufferP, &bufferSize, &speed);

  I2C_slave_updateData(buffer);
}
