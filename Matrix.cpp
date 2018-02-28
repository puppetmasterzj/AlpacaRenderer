#include "Matrix.h"
#include "Stdfx.h"

Matrix::Matrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			value[i][j] = 0;
		}
	}
}

Matrix::~Matrix()
{
}

Matrix Matrix::operator + (const Matrix& right) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = this->value[i][j] + right.value[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator - (const Matrix& right) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = this->value[i][j] - right.value[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator * (const Matrix& right) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = 0;//temp
			for (int k = 0; k < 4; k++)
			{
				m.value[i][j] += this->value[i][k] * right.value[k][j];
			}
		}
	}
	return m;
}

Matrix Matrix::operator * (float k) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = this->value[i][j] * k;
		}
	}
	return m;
}

void Matrix::Print()
{
	std::cout << "-----------------Matrix Begin--------------" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << "[" << value[i][j] << "]   ";
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------Matrix End----------------" << std::endl;
}


