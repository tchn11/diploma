/*
 * matrix.h
 *
 *  Created on: May 5, 2024
 *      Author: akona
 */

#ifndef INC_MATRIX_H_
#define INC_MATRIX_H_

#include "worker.h"
#include "gpio.h"
#include "main.h"

class Matrix: public IWorker {
private:
	bool values[MATRIX_SIZE][MATRIX_SIZE];
	InputPin* rows;
	OutputPin* collumns;
public:
	Matrix(InputPin rows[], OutputPin collumns[]);

	void work() override;

	bool get(matrix_size_t x, matrix_size_t y)
	{ return values[x][y]; }
};

#endif /* INC_MATRIX_H_ */
