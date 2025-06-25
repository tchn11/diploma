/*
 * gpio.h
 *
 *  Created on: May 5, 2024
 *      Author: akona
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stm32f3xx.h"
#include "stm32f3xx_hal_gpio.h"

class Pin {
protected:
	GPIO_TypeDef* 	GPIOx;
	uint32_t		pin;
public:
	Pin(GPIO_TypeDef* GPIOx, uint32_t pin);
};

class OutputPin: public Pin{
public:
	OutputPin(GPIO_TypeDef* GPIOx, uint32_t pin)
	: Pin(GPIOx, pin) {}

	void Set();
	void Reset();
};

class InputPin: public Pin{
public:
	InputPin(GPIO_TypeDef* GPIOx, uint32_t pin)
	: Pin(GPIOx, pin) {}

	bool Get();
};

#endif /* INC_GPIO_H_ */
