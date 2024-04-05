#pragma once
#include "myRow.h"

class Matrix
{
	unsigned int rows = 2;
	unsigned int cols = 2;
	Row* matrix = nullptr;

	void free()
	{
		delete[] matrix;
	}

	void copyFrom(const Matrix& other)
	{
		rows = other.rows;
		cols = other.cols;
		if (other.matrix != nullptr)
		{
			matrix = other.matrix;
		}
	}
public:


	Matrix() = default;
	Matrix(const int& cols, const Row* matrix) : rows(rows), cols(cols), matrix(nullptr)
	{
		setRows(rows);
		setCols(cols);
		setMatrix(rows, cols, matrix);
	}
	Matrix(const Matrix& other)
	{
		copyFrom(other);
	}
	~Matrix()
	{
		free();
	}
	Matrix& operator=(const Matrix& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}
		return *this;
	}

	void setRows(const int& rows)
	{
		if (rows >= 2)
		{
			this->rows = rows;
		}
	}
	void setCols(const int& cols)
	{
		if (cols >= 2)
		{
			this->cols = cols;
		}
	}
	void setMatrix(const Row* matrix, const int& rows)
	{
		if (matrix != nullptr && this->matrix != matrix)
		{
			this->matrix = new Row[rows];
		}
	}

	const int getRows() const
	{
		return this->rows;
	}
	const int getCols() const
	{
		return this->cols;
	}
	const Row* getMatrix() const
	{
		return this->matrix;
	}

	Matrix& operator+=(const Matrix& matrix)
	{
		if (matrix.rows == this->rows)
		{
			for (int i = 0; i < this->rows; i++)
			{
				this->matrix[i] += matrix.matrix[i];
			}
		}
		else
		{
			std::cout << "Cannot be added - different sizes!" << std::endl;
		}
		return *this;
	}
	friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2)
	{
		if (matrix1.rows != matrix2.rows)
		{
			std::cout << "Cannot be added - different sizes!" << std::endl;
			return;
		}

		Matrix sum = matrix1;
		sum += matrix2;
		return sum;
	}

	Matrix& operator-=(const Matrix& matrix)
	{
		if (matrix.rows == this->rows)
		{
			for (int i = 0; i < this->rows; i++)
			{
				this->matrix[i] -= matrix.matrix[i];
			}
		}
		else
		{
			std::cout << "Cannot be added - different sizes!" << std::endl;
		}
		return *this;
	}
	friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2)
	{
		if (matrix1.rows != matrix2.rows)
		{
			std::cout << "Cannot be added - different sizes!" << std::endl;
			return;
		}

		Matrix sum = matrix1;
		sum -= matrix2;
		return sum;
	}

	Matrix& operator++()
	{
		for (int i = 0; i < this->rows; i++)
		{
			this->matrix[i]++;
		}
		return *this;
	}
	Matrix operator++(const int dummyNumber)
	{
		Matrix matrix(*this);

		for (int i = 0; i < this->rows; i++)
		{
			this->matrix[i]++;
		}
		return matrix;
	}

	Matrix& operator--()
	{
		for (int i = 0; i < this->rows; i++)
		{
			this->matrix[i]--;
		}
		return *this;
	}
	Matrix operator--(const int dummyNumber)
	{
		Matrix matrix(*this);

		for (int i = 0; i < this->rows; i++)
		{
			this->matrix[i]--;
		}
		return matrix;
	}

	Matrix& operator*=(const Matrix& other)
	{
		Matrix temp(*this);
		if (this->cols == other.rows && this->rows == other.cols)
		{
			for (int i = 0; i < other.rows; i++)
			{
				int sum = 0;
				for (int j = 0; j < other.cols; j++)
				{
					sum += this->matrix[i].getRow()[j] * other.matrix[j].getRow()[i];
				}
				temp.matrix[i]. = sum;
			}
		}
		return *this;

	}

	friend Row& operator*(const Row& row1, const int& a)
	{
		Row sum = row1;
		sum *= a;
		return sum;
	}

	bool operator==(const Row& row) const
	{
		if (this == &row)return 1;
		else return 0;
	}

	bool operator!=(const Row& row) const
	{
		if (this == &row) return 0;
		else return 1;
	}

	int operator[](const int& ind) const
	{
		if (ind < this->cols)
		{
			return this->row[ind];
		}
		else return;
	}

	bool operator<(const Row& row1) const
	{
		int sum1 = 0, sum2 = 0;

		for (int i = 0; i < this->cols; i++)
		{
			sum1 += this->row[i];
		}

		for (int i = 0; i < row1.cols; i++)
		{
			sum2 += row1.row[i];
		}

		if (sum1 < sum2) return 1;
		else return 0;

	}

	bool operator>(const Row& row1) const
	{
		int sum1 = 0, sum2 = 0;

		for (int i = 0; i < this->cols; i++)
		{
			sum1 += this->row[i];
		}

		for (int i = 0; i < row1.cols; i++)
		{
			sum2 += row1.row[i];
		}

		if (sum1 < sum2) return 0;
		else return 1;

	}

	bool operator>=(const Row& row1) const
	{
		int sum1 = 0, sum2 = 0;

		for (int i = 0; i < this->cols; i++)
		{
			sum1 += this->row[i];
		}

		for (int i = 0; i < row1.cols; i++)
		{
			sum2 += row1.row[i];
		}

		if (sum1 <= sum2) return 0;
		else return 1;

	}

	bool operator<=(const Row& row1) const
	{
		int sum1 = 0, sum2 = 0;

		for (int i = 0; i < this->cols; i++)
		{
			sum1 += this->row[i];
		}

		for (int i = 0; i < row1.cols; i++)
		{
			sum2 += row1.row[i];
		}

		if (sum1 >= sum2) return 0;
		else return 1;

	}

	Matrix operator()();
	operator bool();

};
