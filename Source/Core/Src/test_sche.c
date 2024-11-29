/*
 * test_sche.c
 *
 *  Created on: Nov 13, 2024
 *      Author: Admin
 */

#include "test_sche.h"

void Led_Display(){
	HAL_GPIO_TogglePin(blinky_GPIO_Port, blinky_Pin);
}
