/*
 * gpio.cpp
 *
 *  Created on: May 5, 2024
 *      Author: akona
 */

#include "gpio.h"

Pin::Pin(GPIO_TypeDef* GPIOx, uint32_t pin)
	: GPIOx(GPIOx), pin(pin)
{ }

bool InputPin::Get()
{
	return HAL_GPIO_ReadPin(GPIOx, pin);
}

void OutputPin::Set()
{
	HAL_GPIO_WritePin(GPIOx, pin, GPIO_PIN_SET);
}

void OutputPin::Reset()
{
	HAL_GPIO_WritePin(GPIOx, pin, GPIO_PIN_RESET);
}
