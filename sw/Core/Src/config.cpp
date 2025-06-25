/*
 * config.cpp
 *
 *  Created on: May 8, 2024
 *      Author: akona
 */

#include "config.h"

#define TIMEOUT 2000

ConfigElement::ConfigElement(matrix_size_t id, UART_HandleTypeDef* uart, Matrix* matrix)
 : id(id), uart(uart), matrix(matrix)
{ }

OneNumElement::OneNumElement(matrix_size_t id, UART_HandleTypeDef* uart, Matrix* matrix, matrix_size_t* nums_x, matrix_size_t* nums_y, matrix_size_t size)
 : ConfigElement(id, uart, matrix), nums_x(nums_x), nums_y(nums_y), size(size), prev_value(MATRIX_SIZE * MATRIX_SIZE + 1)
{ }

void OneNumElement::sendBack()
{
	matrix_size_t data = 0;
	for (ssize_t i = size - 1; i >= 0; i--)
	{
		if (matrix->get(nums_x[i], nums_y[i]))
		{
			data = i + 1;
		}
	}
	if (data != prev_value)
	{
		HAL_UART_Transmit(uart, &id, sizeof(matrix_size_t), 500);
		HAL_UART_Transmit(uart, &data, sizeof(matrix_size_t), 500);
		prev_value = data;
	}
}

OneNumElement::~OneNumElement()
{
	free(nums_x);
	free(nums_y);
}

OneStatusElement::OneStatusElement(matrix_size_t id, UART_HandleTypeDef* uart, Matrix* matrix, matrix_size_t num_x, matrix_size_t num_y)
 : ConfigElement(id, uart, matrix), num_x(num_x), num_y(num_y), prev_value(1)
{ }

void OneStatusElement::sendBack()
{
	//HAL_UART_Transmit(uart,(const uint8_t*) ONE_STATUS_ELEMENT_ID, sizeof(matrix_size_t), 500);

	uint8_t data = matrix->get(num_x, num_y);
	if (data != prev_value)
	{
		HAL_UART_Transmit(uart, &id, sizeof(matrix_size_t), 500);
		HAL_UART_Transmit(uart, &data, 1, 500);
		prev_value = data;
	}
}

void ConfigController::work()
{
	if (__HAL_UART_GET_FLAG(uart, UART_FLAG_RXNE))
		update();

	//if (HAL_GetTick() - time > TIMEOUT)
	//{
	//time = HAL_GetTick();
	for (auto &element: config)
		element->sendBack();
	//}
}

void ConfigController::update()
{
	config.clear();
	while(1)
	{
		matrix_size_t data;
		HAL_StatusTypeDef status = HAL_UART_Receive(uart, &data, sizeof(matrix_size_t), 500);
		switch (data)
		{
		case END_ID:
			return;
		case ONE_NUM_ELEMENT_ID:
		{
			matrix_size_t id;
			HAL_UART_Receive(uart, &id, sizeof(matrix_size_t), 500);

			matrix_size_t size;
			HAL_UART_Receive(uart, &size, sizeof(matrix_size_t), 500);
			matrix_size_t* nums_x = (matrix_size_t*)malloc(size * sizeof(matrix_size_t));
			matrix_size_t* nums_y = (matrix_size_t*)malloc(size * sizeof(matrix_size_t));
			for (matrix_size_t i = 0; i < size; i++)
			{
				HAL_UART_Receive(uart, nums_x + i, sizeof(matrix_size_t), 500);
				HAL_UART_Receive(uart, nums_y + i, sizeof(matrix_size_t), 500);
			}

			OneNumElement* new_element = new OneNumElement(id, uart, matrix, nums_x, nums_y, size);
			config.push_back(dynamic_cast<ConfigElement*>(new_element));
			break;
		}
		case ONE_STATUS_ELEMENT_ID:
		{
			matrix_size_t id;
			HAL_UART_Receive(uart, &id, sizeof(matrix_size_t), 500);

			matrix_size_t num_x;
			HAL_UART_Receive(uart, &num_x, sizeof(matrix_size_t), 500);

			matrix_size_t num_y;
			HAL_UART_Receive(uart, &num_y, sizeof(matrix_size_t), 500);

			OneStatusElement* new_element = new OneStatusElement(id, uart, matrix, num_x, num_y);
			config.push_back(dynamic_cast<ConfigElement*>(new_element));
			break;
		}
		default:
			return;
		}
	}

}

ConfigController::ConfigController(UART_HandleTypeDef* uart, Matrix* matrix)
 : uart(uart), matrix(matrix), time(0)
{ }
