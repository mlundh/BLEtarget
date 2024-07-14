#ifndef APP_H
#define APP_H

#include "main.h"
#include "sensor.h"
/**
 * @brief Cyclic task called in the while-true loop in main.
 *
 *
 */
void app_init(I2C_HandleTypeDef* hi2c1);


void taskCyclic();

#endif //APP_H
