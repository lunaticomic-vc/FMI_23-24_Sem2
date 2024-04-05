#pragma once
#include<iostream>

class Row
{
	unsigned int cols = 2;
	int* row = nullptr;

	void free()
	{
		delete[] row;
	}

	void copyFrom(const Row& other)
	{
		cols = other.cols;

		if (other.row != nullptr)
		{
			row = other.row;
		}
	}
public:

	Row() = default;

	Row(const int& cols, const int* row): cols(cols), row(nullptr)
	{
		setCols(cols);
		setRow(row, cols);
	}

	Row(const Row& other)
	{
		copyFrom(other);
	}

	~Row()
	{
		free();
	}

	Row& operator=(const Row& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}
		return *this;
	}

	void setCols(const int& cols)
	{
		if (cols >= 2)
		{
			this->cols = cols;
		}
	}
	void setRow(const int* row, const int& cols)
	{
		if (row != nullptr && this->row != row)
		{
			this->row = new int[cols];
		}
	}

	const int getCols() const
	{
		return this->cols;
	}
	const int* getRow() const
	{
		return this->row;
	}

	Row& operator+=(const Row& row)
	{
		if (row.cols == this->cols)
		{
			for (int i = 0; i < this->cols; i++)
			{
				this->row[i] += row.row[i];
			}
		}
		else
		{
			std::cout << "Cannot be added - different sizes!" << std::endl;
		}
		return *this;
	}
	friend Row operator+(const Row& row1, const Row& row2)
	{
		Row sum = row1;
		sum += row2;
		return sum;
	}

	Row& operator-=(const Row& row)
	{
		if (row.cols == this->cols)
		{
			for (int i = 0; i < this->cols; i++)
			{
				this->row[i] -= row.row[i];
			}
			return *this;
		}
		else
		{
			std::cout << "Cannot be substracted - different sizes!" << std::endl;
			return *this;
		}
	}

	friend Row operator-(const Row& row1, const Row& row2)
	{
		Row sum = row1;
		sum -= row2;
		return sum;
	}

	Row& operator++()
	{
		for (int i = 0; i < this->cols; i++)
		{
				this->row[i]++;
		}
			return *this;
	}

	Row operator++(const int dummyNumber)
	{
		Row row(*this);

		for (int i = 0; i < this->cols; i++)
		{
			this->row[i]++;
		}
		return row;
	}

	Row& operator--()
	{
		for (int i = 0; i < this->cols; i++)
		{
			this->row[i]--;
		}
		return *this;
	}

	Row& operator--(const int dummyNumber)
	{
		Row row(*this);

		for (int i = 0; i < this->cols; i++)
		{
			this->row[i]--;
		}

		return row;
	}

	Row& operator*=(const int& a)
	{
		for (int i = 0; i < this->cols; i++)
		{
			this->row[i]*=a;
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
};
