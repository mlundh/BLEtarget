/*
 * sensor.c
 *
 *  Created on: May 27, 2024
 *      Author: mlundh
 */

#include "sensor.h"


#define NR_CHANNELS (10)
#define BACK_CHANNEL (9)
#define TIME_PERIOD_S (0.000000015625)//(1/64 000 000)
#define DISTANCE_ROWS_M (0.01)
#define MM_BETWEEN_SENSORS (5)

const uint16_t pins[]={CH_C_Pin, CH_1_Pin, CH_2_Pin, CH_3_Pin, CH_4_Pin, CH_5_Pin, CH_6_Pin, CH_7_Pin, CH_8_Pin, CH_B_Pin};

typedef struct {
  TIM_TypeDef *timer; // 64MHz timer used to measure speed of pellet. Also used for timeout to report the hit.
  TIM_TypeDef *timerLockout; // .
  uint8_t buffer[NR_CHANNELS]; // position of the hit. 0 Center, 1-7 channel, 8 back.
  uint8_t newValue;
  uint32_t speed;
  invalidateFcn invalidateData;
} sensor_t;

sensor_t sensor = { TIM2, TIM16, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0, NULL };

/**
 * Disable all external interrupts to ensure we do not have concurrency issues.
 */
void disableExternalInterrupt();

/**
 * Re-enable the external interrupts. This should be done when all data from the external interrupts are handled.
 */
void enableExternalInterrupt();

void Sensor_init(uint8_t master, invalidateFcn invalidateCb)
{
  sensor.invalidateData = invalidateCb;

  if(master)
  {
    // Master should have a longer timeout so that the slave definitely have data. Timeout 20ms.
    sensor.timer->ARR = ((640000*2)-1);
  }
  else
  {
    // Slave has shorter timeout, 10ms.
    sensor.timer->ARR = (640000-1);
  }

}

// Multiple adjacent triggered photodiodes are allowed, this would represent a hit between the channels.
// It is not allowed to have a gap in between. This would be an error condition.

int Sensor_getPos()
{
  int returnValue = ERROR;
  if (sensor.newValue)
  {
    uint8_t first = NOT_USED;
    uint8_t last = NOT_USED;

    for (int i = 0; i < (BACK_CHANNEL); i++)
    {
      if (sensor.buffer[i])
      {
        if (first == NOT_USED)    // If no hit is registered yet, then register.
        {
          first = i;
          last = i;
        }
        else
        {
          if ((last + 1) == i) // If there is a hit registered, make sure the last hit was the adjacent sensor.
          {
            last = i;
          }
          else
          {
            // error condition!
            //ERROR_ENTRY("Gaps between triggered sensors.");
            return returnValue;
          }
        }
      }
    }

    if (first != NOT_USED) // If there is a valid hit
    {
      returnValue = ((first * MM_BETWEEN_SENSORS) + (last * MM_BETWEEN_SENSORS))
          / 2; // integer values, scale to 5mm between channels.
    }

    if (sensor.buffer[BACK_CHANNEL]) // Left is negative.
    {
      returnValue = -(returnValue);
    }
  }
  //LOG_DBG_ENTRY("Position = %d",returnValue);
  return returnValue;
}

float Sensor_getSpeed()
{
  float returnValue = SPEED_ERROR;
  if (sensor.speed)
  {
    returnValue = DISTANCE_ROWS_M / (((float) sensor.speed) * TIME_PERIOD_S);
    //LOG_DBG_ENTRY("Speed = %d",(int)returnValue);
    if(returnValue < 2 || returnValue > 500)
    {
      // Error. Only support speed values between 2 and 500 m/s.
      returnValue = SPEED_ERROR;
    }
  }
  return returnValue;
}

unsigned int Sensor_newValue()
{
  return sensor.newValue;
}

void Sensor_clear()
{
  memset(sensor.buffer, 0, NR_CHANNELS); // clean up and get ready for next hit.
  sensor.speed = 0;
  sensor.newValue = 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == CH_C_Pin)
  {
    sensor.buffer[0] = 1;
  }
  if (GPIO_Pin == CH_1_Pin)
  {
    sensor.buffer[1] = 1;
  }
  if (GPIO_Pin == CH_2_Pin)
  {
    sensor.buffer[2] = 1;
  }
  if (GPIO_Pin == CH_3_Pin)
  {
    sensor.buffer[3] = 1;
  }
  if (GPIO_Pin == CH_4_Pin)
  {
    sensor.buffer[4] = 1;
  }
  if (GPIO_Pin == CH_5_Pin)
  {
    sensor.buffer[5] = 1;
  }
  if (GPIO_Pin == CH_6_Pin)
  {
    sensor.buffer[6] = 1;
  }
  if (GPIO_Pin == CH_7_Pin)
  {
    sensor.buffer[7] = 1;
  }
  if (GPIO_Pin == CH_8_Pin)
  {
    sensor.buffer[8] = 1;
  }

  if (GPIO_Pin == CH_B_Pin) // it is the back row.
  {
    sensor.buffer[BACK_CHANNEL] = 1;

    if (!LL_TIM_IsEnabledCounter(sensor.timer)) // If back detector was triggered, and the timer was not already going, start it.
    {
      LL_TIM_SetCounter(sensor.timer, 0);
      LL_TIM_ClearFlag_UPDATE(sensor.timer);
      LL_TIM_EnableIT_UPDATE(sensor.timer);
      LL_TIM_EnableCounter(sensor.timer); // measure time between back row and other rows.
    }
    else
    {
      //ERROR_ENTRY("Back row hit after scoring row."); // Todo write error to!
    }
  }
  else // it is not the back row.
  {
    if (!LL_TIM_IsEnabledCounter(sensor.timer)) //  The timer is not enabled. We should start the timer as it is also used to ensure enough time has passed before registering a new value.
    {
      LL_TIM_SetCounter(sensor.timer, 0);
      LL_TIM_ClearFlag_UPDATE(sensor.timer);
      LL_TIM_EnableIT_UPDATE(sensor.timer);
      LL_TIM_EnableCounter(sensor.timer); // measure time between back row and other rowes.
    }
    else // The timer is started, lets measure the time!
    {
      if ((sensor.buffer[BACK_CHANNEL] == 1) && (!sensor.speed)) // only take a measurement if the back row was triggered, and if no other speed was registered.
      {
        sensor.speed = LL_TIM_GetCounter(sensor.timer); //
      }
    }
  }
}

void timer2UpdateISR()
{
  // Stop the timer then enable the flag for new value.
  LL_TIM_DisableCounter(sensor.timer);
  LL_TIM_SetCounter(sensor.timer, 0);
  LL_TIM_DisableIT_UPDATE(sensor.timer);
  LL_TIM_ClearFlag_UPDATE(sensor.timer);

  sensor.newValue = 1;

  // Lockout timer, disable the external interrupts for 0.5s.
  disableExternalInterrupt();
  LL_TIM_SetCounter(sensor.timerLockout, 0);
  LL_TIM_ClearFlag_UPDATE(sensor.timerLockout);
  LL_TIM_EnableIT_UPDATE(sensor.timerLockout);
  LL_TIM_EnableCounter(sensor.timerLockout);
}

void timer16UpdateISR()
{
  // Stop the lockout timer and enable external interrupts.
  LL_TIM_DisableCounter(sensor.timerLockout);
  LL_TIM_SetCounter(sensor.timerLockout, 0);
  LL_TIM_DisableIT_UPDATE(sensor.timerLockout);
  LL_TIM_ClearFlag_UPDATE(sensor.timerLockout);
  if(sensor.invalidateData)
  {
    sensor.invalidateData();
  }
  enableExternalInterrupt();
}

void disableExternalInterrupt()
{
  HAL_NVIC_DisableIRQ(EXTI0_IRQn);

  HAL_NVIC_DisableIRQ(EXTI1_IRQn);

  HAL_NVIC_DisableIRQ(EXTI2_IRQn);

  HAL_NVIC_DisableIRQ(EXTI3_IRQn);

  HAL_NVIC_DisableIRQ(EXTI4_IRQn);

  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}

void clearAllExtInterrupts()
{
  for (int i = 0; i < NR_CHANNELS; i++)
  {
    if (__HAL_GPIO_EXTI_GET_IT(pins[i]) != 0x00u)
    {
      __HAL_GPIO_EXTI_CLEAR_IT(pins[i]);
    }
  }
}

void enableExternalInterrupt()
{
  /* EXTI line interrupt detected */
  clearAllExtInterrupts();

  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

