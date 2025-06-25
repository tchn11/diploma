/*
 * matrix.c
 *
 *  Created on: May 5, 2024
 *      Author: akona
 */

#include "matrix.h"

Matrix::Matrix(InputPin rows[], OutputPin collumns[])
 : rows(rows), collumns(collumns)
{
	for (size_t i = 0; i < MATRIX_SIZE; i++)
		collumns[i].Reset();
}

void Matrix::work()
{
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		collumns[i].Set();
		HAL_Delay(1);
		for (size_t j = 0; j < MATRIX_SIZE; j++)
			values[i][j] = rows[j].Get();
		collumns[i].Reset();
		HAL_Delay(1);
	}
}
