/*
 * config.h
 *
 *  Created on: May 8, 2024
 *      Author: akona
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "main.h"
#include "matrix.h"
#include "string"
#include "vector"
#include "worker.h"

class ConfigElement {
protected:
	matrix_size_t id;
	UART_HandleTypeDef* uart;
	Matrix* matrix;

public:
	ConfigElement(matrix_size_t id, UART_HandleTypeDef* uart, Matrix* matrix);

	virtual void sendBack() = 0;
};

class OneNumElement: public ConfigElement {
private:
	matrix_size_t* nums_x;
	matrix_size_t* nums_y;
	matrix_size_t size;

	matrix_size_t prev_value;
public:
	OneNumElement(matrix_size_t id, UART_HandleTypeDef* uart, Matrix* matrix, matrix_size_t* nums_x, matrix_size_t* nums_y, matrix_size_t size);
	~OneNumElement();
	void sendBack() override;
};

class OneStatusElement: public ConfigElement {
private:
	matrix_size_t num_x;
	matrix_size_t num_y;

	bool prev_value;
public:
	OneStatusElement(matrix_size_t id, UART_HandleTypeDef* uart, Matrix* matrix, matrix_size_t num_x, matrix_size_t num_y);
	void sendBack() override;
};

class ConfigController: public IWorker
{
private:
	std::vector<ConfigElement*> config;
	UART_HandleTypeDef* uart;
	Matrix* matrix;
	uint32_t time;
public:
	ConfigController(UART_HandleTypeDef* uart, Matrix* matrix);

	void work() override;
private:
	void update();
};

#endif /* INC_CONFIG_H_ */
