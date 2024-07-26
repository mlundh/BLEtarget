/*
 * sensor.h
 *
 *  Created on: May 27, 2024
 *      Author: mlundh
 *
 * The sensor will register any hit on the front row (scoring) and back row(side indication) and measure the time between the two if the pellet
 * triggers both.
 *
 * It uses one timer to both time the pellet between the rows and to use as a 1 ms timeout to allow for registration from multiple channels
 * triggered by the same pellet.
 *
 * The sensor will average the result between the adjacent triggered diodes. It doubles the resolution of the system by using this method.
 *
 * Output is in scale [-16, 16] with all even numbers representing a single photodiode, and every odd number representing two photodiodes triggered
 * at the same time.
 *
 */

#ifndef SENSOR_H_
#define SENSOR_H_
#include "main.h"


/**
 * Get the position of the last recorded hit.
 * @return [-16,16] where 0 is in the middle.
 */
int Sensor_getPos();
/**
 * Get the speed of the pellet if available. The pellet must hit both rows of photodetectors to
 * register a speed value.
 *
 * @return speed in m/s.
 */
float Sensor_getSpeed();
/**
 * Check if there is a new value registered.
 *
 * @return 1 if there is a new value, 0 otherwise.
 */
unsigned int Sensor_newValue();

/**
 * Clear the sensor in preparation for a new hit.
 *
 */
void Sensor_clear();

void timer2UpdateISR();

void timer16UpdateISR();


#endif /* SENSOR_H_ */
