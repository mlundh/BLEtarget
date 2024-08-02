#ifndef APP_H
#define APP_H

#include "main.h"
#include "sensor.h"
#include "stm32wbxx_hal_uart.h"
/**
 * @brief Cyclic task called in the while-true loop in main.
 *
 *
 */

void app_init(I2C_HandleTypeDef* hi2c1, UART_HandleTypeDef* huart);


void taskCyclic();

void invalidateData();

void sendHeartbeat();

void timer17UpdateISR();

#endif //APP_H
