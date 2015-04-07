#include <vector>
#include <iterator>
#include <iostream>
#include <math.h>
#include <exception>
#include <stdexcept>

#ifndef MATRIX_H
#define MATRIX_H

#define DEFAULT_CTOR_HEIGHT 1

/**
* The Matrix class that holds a matrix.
*/
template<typename T> class Matrix;

/**
* print a matrix assume that type T has << operator by itself. print each cell in the matrix, with
* a tab ('\t') between cells, and new line between columns (and at the end of the matrix) except
* for Matrix<char>, than this operator prints no spaces between cells, and a single space between
* columns.
*
* @param out	the ostream object to output to.
* @param matrix	the matrix to output.
*
* @return out	for latter proccesing
*/
template<typename T> std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix);

/**
* @param num1 1st arg
* @param num2 2nd arg
* @return num1 + num2
*/
template<typename T> T myPlus(T const num1, T const num2);

/**
* @param num1 1st arg
* @param num2 2nd arg
* @return num1 - num2
*/
template<typename T> T myMinus(T const num1, T const num2);

/**
* function to negate a value
*
* @param num1 the value to negate
* @return -num1
*/
template<typename T> T myNegate(T const num1);

/**
* function that get 2 matrix and a function and return matrix with the items as the function on
* 2 matrix's items.
* WARNING: only works with sqaure, same size matrixes. otherwise will throw exception!
*
* @param func the function
* @param first 1st matrix
* @param second 2nd matrix
* @return matrix after func activate on both items
* @throw CantCalculateEx if the matrix not the same size
* @throw notSquareEx if the matrix not square
*/
template <typename T>
Matrix<T> mapFun(T(*func)(const T, const T),const Matrix<T>& first, const Matrix<T>& second);

/**
* exception when we want to calculate somthing and the matrixes parameters dont allow this
*/
class CantCalculateEx;

/**
* exception when we want to calculate somthing and the matrixes parameters dont allow this,
* because we need square matrixes.
*/
class notSquareEx;

/**
* The Matrix class that holds a matrix.
*/
template<typename T>
class Matrix
{
private:
	std::vector<std::vector<T>> _matrix;
	unsigned int _rows;

	unsigned int _cols;

	friend std::ostream &operator<<<>(std::ostream &out, const Matrix<T> &matrix);

	/***
	* helping method for Matrix<T>::det().
	* the method is using the recursive formula from linear algebra (SHURA & AMUDA in hebrew. I
	* 																 dont think it called row &
	* 																 col in english..)
	*
	* @param matrix the matrix we want to calculate its determinante
	* @param size the number of rows and cols (they must be equal)
	* @return the determinante
	*/
	T recursiveDet(Matrix<T> const matrix, unsigned int size) const
	{
		T det = 0;
		std::vector<T> vec;
		unsigned int i, j;
		if(size < 1)
		{
			throw std::invalid_argument("size can't be smaller than 1");
		}
		//base case
		if (size == 1)
		{
			det = matrix(0, 0);
		}
		//another base case
		else if (size == 2)
		{
			det = matrix(0, 0) * matrix(1, 1) - matrix(1, 0) * matrix(0, 1);
		}
		else
		{
			for (unsigned int k = 0; k < size; k++)
			{
				vec.erase(vec.begin(), vec.end());
				for (i = 1; i < size; i++)
				{
					for (j = 0; j < size; j++)
					{
						if (j == k)
						{
							continue;
						}
						vec.push_back(matrix(i, j));
					}
				}
				det += matrix(0, k) * pow(-1, k) * recursiveDet(Matrix(size - 1, size - 1,
																	   vec), size - 1);
			}
		}
		return det;
	}

public:

	/**
	* iterator class that iterate over all matrix cells start from the first row
	* (e,g: matrix(0, 0), matrix(0, 1) .. matrix(0, col - 1), matrix(1, 0) ...).
	* this iterator support the copy, assignment, increment, equality/inequality
	* and dereferencing operators.
	*/
	class iterator
	{
	private:
		Matrix<T> &_parent;
		unsigned int _posR;
		unsigned int _posC;

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef size_t size_type;

		/**
		* constructor
		* @param parnet the matrix we want to iterate. we need this so we'll have access
		* 		 to its variables
		* @param pos_r current row position
		* @param pos_c current col position
		*/
		iterator(Matrix<T> &parent, unsigned int pos_r = 0, unsigned int pos_c = 0) :
				_parent(parent), _posR(pos_r), _posC(pos_c)
		{
		}
		
		/**
		* overload operator++ to promote the iterator
		* @return the iterator after we promote it
		*/
		iterator &operator++()
		{
			if (++_posC == _parent._cols)
			{
				_posC = 0;
				_posR++;
			}
			return *this;
		}
		
		/**
		* overload operator++ to promote the iterator
		* @return the iterator before we promote it
		*/
		iterator operator++(int)
		{
			iterator iter = *this;
			operator++();
			return iter;
		}

		/**
		* overload opertor* to return the value where iterator points
		* @return the value
		* @throw invalid_argument if position is negative
		*/
		T &operator*()
		{
			if(_posR < 0 || _posC < 0)
			{
				throw std::invalid_argument("position can't be negative");
			}
			return _parent._matrix[_posR][_posC];
		}

		/**
		* overload opertor-> to return the refernce to the value where iterator points
		* @return the reference
		* @throw invalid_argument if position is negative
		*/
		T *operator->()
		{
			return &(operator*());
		}

		/**
		* overload operator== to return true iff the iterator points to the same point as rhs
		* @param rhs the other iterator
		* @return true iff the iterator points to the same point as rhs
		* @throw invalid_argument if position is negative
		*/
		bool operator==(iterator rhs)
		{
			if(_posR < 0 || _posC < 0 || rhs._posC < 0 || rhs._posR < 0)
			{
				throw std::invalid_argument("position can't be negative");
			}
			return _posC == rhs._posC && _posR == rhs._posR;
		}

		/**
		* overload operator!= to return true iff the iterator not pointing to the same point as rhs
		* @param rhs the other iterator
		* @return true iff the iterator not pointing to the same point as rhs
		*/
		bool operator!=(iterator rhs)
		{
			return !operator==(rhs);
		}
	};

	/**
	* const_iterator class that iterate over rows and cols (seperatlly) of matrix
	*/
	class const_iterator
	{
	private:
		const Matrix<T> &_parent;
		bool _isRow;
		unsigned int _pos;
		std::vector<T> _colVec;

		/**
		* helping function to build the vector for the column iterator
		* @return vector next column
		*/
		std::vector<T> _buildColVec() const
		{
			std::vector<T> colVec;
			//we reached the end
			if (_pos >= this->_parent._cols)
			{
				return colVec;
			}
			// add column values to vector:
			for (unsigned int i = 0; i < this->_parent._rows; i++)
			{
				colVec.push_back(this->_parent._matrix[i][_pos]);
			}
			return colVec;
		}

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef size_t size_type;
		typedef T difference_type;

		/**
		* constructor
		* @param parnet the matrix we want to iterate. we need this so we'll hav access to its
		* 		 variables
		* @param isRow flag that tells us if we iterate over rows or columns
		* @param pos position
		*/
		const_iterator(const Matrix<T> &parent, bool isRow, unsigned int pos = 0) :
				_parent(parent), _isRow(isRow), _pos(pos)
		{
			if (!isRow)
			{
				_colVec = _buildColVec();
			}
		}

		/**
		* overload operator++ to promote the iterator
		* @return the iterator after we promote it
		* @throw invalid_argument if position is negative
		*/
		const_iterator &operator++()
		{
			if(_pos < 0)
			{
				throw std::invalid_argument("position can't be negative");
			}
			++_pos;
			if(!_isRow)
			{
				if (_pos < _parent._cols)
				{
					_colVec = _buildColVec();
				}
			}
			return *this;
		}

		/**
		* overload operator++ to promote the iterator
		* @return the iterator before we promote it
		* @throw invalid_argument if position is negative
		*/
		const_iterator operator++(int)
		{
			const_iterator iter = *this;
			operator++();
			return iter;
		}

		/**
		* overload opertor* to return the value where iterator points (the current row/col)
		* @return the value
		* @throw invalid_argument if position is negative
		*/
		const std::vector<T> &operator*()
		{
			if(_pos < 0)
			{
				throw std::invalid_argument("position can't be negative");
			}
			if (_isRow)
			{
				if (_pos >= _parent._rows)
				{
					throw std::out_of_range("Matrix out of range");
				}
				return _parent._matrix[_pos];
			}
			else
			{
				return _colVec;
			}
		}

		/**
		* overload opertor-> to return the reference to the value where
		* iterator points (the current row/col)
		* @return the reference
		* @throw invalid_argument if position is negative
		*/
		const std::vector<T> *operator->()
		{
			return &(operator*());
		}

		/**
		* overload operator== to return true iff the iterator points to the same point as rhs
		* @param rhs the other iterator
		* @return true iff the iterator points to the same point as rhs
		* @throw invalid_argument if position is negative
		*/
		bool operator==(const const_iterator &rhs)
		{
			if(_pos < 0 || rhs._pos < 0)
			{
				throw std::invalid_argument("position can't be negative");
			}
			return _pos == rhs._pos && _isRow == rhs._isRow;
		}

		/**
		* overload operator!= to return true iff the iterator not pointing to the same point as rhs
		* @param rhs the other iterator
		* @return true iff the iterator not pointing to the same point as rhs
		* @throw invalid_argument if position is negative
		*/
		bool operator!=(const const_iterator &rhs)
		{
			return !operator==(rhs);
		}

		/**
		* overload operator=
		* @throw invalid_argument if position is negative
		*/
		const_iterator &operator=(const_iterator &other)
		{
			if(other._pos < 0)
			{
				throw std::invalid_argument("position can't be negative");
			}
			_parent = other._parent;
			_pos = other._pos;
			_colVec = other._colVec;
			_isRow = other._isRow;
			return *this;
		}
	};
	
	/**
	* default constructor, constructs 1X1 Matrix with the default value for type T
	* (the value assigned by default constructor of type T)
	*/
	Matrix()
	{
		_rows = _cols = DEFAULT_CTOR_HEIGHT;
		_matrix.resize(DEFAULT_CTOR_HEIGHT);
		for (unsigned int i = 0; i < DEFAULT_CTOR_HEIGHT; i++)
		{
			_matrix[i].resize(DEFAULT_CTOR_HEIGHT);
		}
	}

	/**
	* construct a matrix by size rowsXcols using values from cells.
	*
	* @param rows	number of rows in the matrix
	* @param cols	number of columns in the matrix
	* @param cells	a vector containing the values of the cells in the matrix
	* @throw invalid_argument if number of rows or is negative
	*/
	Matrix(unsigned int rows, unsigned int cols, const std::vector<T> &cells)
	{
		_rows = rows;
		_cols = cols;
		if(_rows < 0 || _cols < 0)
		{
			throw std::invalid_argument("rows and cols of matrix can't be negative");
		}
		_matrix.resize(rows);
		typename std::vector<T>::const_iterator cellsIter;
		unsigned int i;
		for (i = 0, cellsIter = cells.begin(); i < rows; i++)
		{

			_matrix[i].resize(cols);
			for (unsigned int j = 0; j < cols; j++)
			{
				_matrix[i][j] = *cellsIter;
				cellsIter++;
				if (cellsIter == cells.end() && j < cols - 1)
				{
					throw std::out_of_range("not_enogh_items");
				}
			}
		}
	}

	/**
	* copy constructor for Matrix class performs deep copy of the matrix.
	*
	* @param other	the Matrix to copy
	* @throw invalid_argument if number of rows or is negative
	*/
	Matrix(const Matrix<T> &other)
	{
		if(other._rows < 0 || other._cols < 0)
		{
			throw std::invalid_argument("rows and cols of matrix can't be negative");
		}
		_matrix.resize(other._rows);
		unsigned int i;
		for (i = 0; i < other._rows; i++)
		{
			_matrix.resize(other._cols);
			for (unsigned int j = 0; j < other._cols; j++)
			{
				_matrix[i].push_back(other._matrix[i][j]);
			}
		}
		_cols = other._cols;
		_rows = other._rows;
	}

	/**
	* move constructor for Matrix class copy the matrix.
	*
	* @param other	the Matrix to copy
	* @throw invalid_argument if number of rows or is negative
	*/
	Matrix(Matrix<T> &&other)
	{
		if(other._rows < 0 || other._cols < 0)
		{
			throw std::invalid_argument("rows and cols of matrix can't be negative");
		}
		*this = other;
	}

	/**
	* do a deep copy of another matrix into this one
	*
	* @param other	the matrix to copy
	* @return this, after copying other content.
	* @throw invalid_argument if number of rows or is negative
	*/
	Matrix &operator=(Matrix<T> &other)
	{
		if(other._rows < 0 || other._cols < 0)
		{
			throw std::invalid_argument("rows and cols of matrix can't be negative");
		}
		_matrix = other._matrix;
		_rows = other._rows;
		_cols = other._cols;
		return *this;
	}

	/**
	* return an iterator over all the matrix cells, start from the first row
	* (e,g: matrix(0, 0), matrix(0, 1) .. matrix(0, col - 1), matrix(1, 0) ...)
	*
	* @return an iterator over all the matrix cells 
	*/
	Matrix<T>::iterator begin()
	{
		return (iterator(*this));
	}

	/**
	* returns an iterator pointing to the past-the-end cell in the matrix
	*
	* @return an iterator pointing to the past-the-end cell in the matrix 
	*/
	iterator end()
	{
		return (iterator(*this, _rows, 0));
	}

	/**
	* return an iterator over all the matrix rows
	*
	* @return an iterator over all the matrix rows 
	*/
	const_iterator rowIteratorBegin() const
	{
		return (const_iterator(*this, true));
	}

	/**
	* returns an iterator pointing to the past-the-end row in the matrix
	*
	* @return an iterator pointing to the past-the-end row in the matrix 
	*/
	const_iterator rowIteratorEnd() const
	{
		return (const_iterator(*this, true, _rows));
	}

	/**
	* return an iterator over all the matrix cols
	*
	* @return an iterator over all the matrix cols 
	*/
	const_iterator colIteratorBegin() const
	{
		return (const_iterator(*this, false));
	}

	/**
	* returns an iterator pointing to the past-the-end col in the matrix
	*
	* @return an iterator pointing to the past-the-end col in the matrix 
	*/
	const_iterator colIteratorEnd() const
	{
		return (const_iterator(*this, false, _cols));
	}

	/**
	* returns the value in the [row, col] cell of the matrix
	*
	* @param row	the row
	* @param col	the column
	* @return the value in the [row, col] cell of the matrix
	* @throw invalid_argument if number of rows or is negative
	*/
	T operator()(int row, int col) const
	{
		if(row < 0 || col < 0)
		{
			throw std::invalid_argument("rows and cols of matrix can't be negative");
		}
		return _matrix[row][col];
	}

	/**
	* returns the reference in the [row, col] cell of the matrix
	*
	* @param row	the row
	* @param col	the column
	* @return the refernce in the [row, col] cell of the matrix
	* @throw invalid_argument if number of rows or is negative
	*/
	T &operator()(int row, int col)
	{
		if(row < 0 || col < 0)
		{
			throw std::invalid_argument("rows and cols of matrix can't be negative");
		}
		return _matrix[row][col];
	}

	/**
	* calc the determinant of the matrix
	*
	* @return the determinant of the matrix
	* @throw notSquareEx if the matrix not square
	*/
	T det() const
	{
		if (_rows != _cols)
		{
			throw notSquareEx();
		}
		return recursiveDet(*this, _rows);
	}

	/**
	* calc the trace of the matrix the trace of a matrix is the sum of it's main diagonal,
	* the diagonal from the upper left to the lower right.
	*
	* @return the trace of the matrix
	* @throw notSquareEx if the matrix not square
	*/
	T trace() const
	{
		if (_rows != _cols)
		{
			throw notSquareEx();
		}
		T trace = 0;
		for (unsigned int i = 0; i < _rows; i++)
		{
			trace += _matrix[i][i];
		}
		return trace;
	}

	/**
	* returns the transpose of the matrix.
	*
	* @return the transpose of the matrix. 
	*/
	Matrix<T> transpose() const
	{
		Matrix<T> trans;
		trans._rows = _cols;
		trans._cols = _rows;
		trans._matrix.resize(trans._rows);
		for (Matrix<T>::const_iterator iter = this->colIteratorBegin();
			 iter != this->colIteratorEnd(); iter++)
		{
			trans._matrix.assign(this->colIteratorBegin(), this->colIteratorEnd());
		}
		return trans;
	}

	/**
	* get the number of columns in this matrix
	*
	* @return the number of columns in this matrix 
	*/
	unsigned int getNumOfCols() const
	{
		return _cols;
	}

	/**
	* get the number of rows in this matrix
	*
	* @return the number of rows in this matrix 
	*/
	unsigned int getNumOfRows() const
	{
		return _rows;
	}

	/**
	* returns true iff two matrixes are equal
	*
	* @param other	the other matrix to compare with this one
	* @retun returns true iff two matrixes are equal
	*/
	bool operator==(const Matrix<T> &other) const
	{
		if (_rows != other._rows || _cols != other._cols)
		{
			return false;
		}
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < _cols; j++)
			{
				if (_matrix[i][j] != other(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}

	/**
	* returns true iff two matrixes are different
	*
	* @param other	the other matrix to compare with this one
	* @retun returns true iff two matrixes are different 
	*/
	bool operator!=(const Matrix<T> &other) const
	{
		return !operator==(other);
	}

	/**
	* run function on every item of the matrix. returns a mtrix of item item result.
	*
	* @param func a function to run on all matrix items
	* @return a matrix of item item result of function func 
	*/
	Matrix map(T(*func)(const T)) const
	{
		Matrix<T> temp = *this;
		std::vector<T> funcVec;
		typename Matrix<T>::iterator iter = temp.begin();
		while (iter != temp.end())
		{
			funcVec.push_back(func(*iter));
			iter++;
		}
		return Matrix(_rows, _cols, funcVec);
	}

	/**
	* returns dot product of matrixes each cell in the resulting matrix is the sum of multiplies
	* any cell in the equivalent column in the cell of the equivalent row.
	* (e,g: c = a * b => c_{i, j} = sum(a_{i, k} * b_{k, j})
	*
	* @param other the matrix to multiply by this matrix
	* @return dot product of matrixes
	* @throw CantCalculateEx if the matrix not the same size
	*/
	Matrix operator*(const Matrix<T> &other) const
	{
		if (_cols != other._rows)
		{
			throw CantCalculateEx();
		}
		std::vector<T> vec;
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < other._cols; j++)
			{
				T sum = 0;
				for (unsigned int k = 0; k < _cols; k++)
				{
					sum += _matrix[i][k] * other(k, j);
				}
				vec.push_back(sum);
			}
		}
		return Matrix(_rows, other._cols, vec);
	}

	/**
	* dot product of matrixes
	*
	* @param other the matrix to multiply by this matrix
	* @return this as the dot product of matrixes 
	*/
	Matrix &operator*=(const Matrix<T> &other)
	{
		Matrix<T> m = (*this * other);
		*this = m;
		return *this;
	}

	/**
	* returns val by val addition of matrixes
	*
	*@param other	the matrix to add to this matrix
	*@return val by val addition of matrixes 
	*/
	Matrix operator+(const Matrix<T> &other) const
	{
		return mapFun(myPlus, *this, other);
	}

	/**
	* returns val by val addition of matrixes
	*
	*@param other	the matrix to add to this matrix
	*@return this as the addition of matrixes 
	*/
	Matrix &operator+=(const Matrix<T> &other)
	{
		Matrix m = (*this + other);
		*this = m;
		return *this;
	}

	/**
	* returns val by val differnce of matrixes
	*
	*@param other	the matrix to subtruct from this matrix
	*@return val by val differnce of matrixes 
	*/
	Matrix operator-(const Matrix<T> &other) const
	{
		return mapFun(myMinus, *this, other);
	}

	/**
	* returns val by val differnce of matrixes
	*
	*@param other	the matrix to subtruct from this matrix
	*@return this as the differnce of matrixes 
	*/
	Matrix &operator-=(const Matrix<T> &other)
	{
		Matrix m = (*this - other);
		*this = m;
		return *this;
	}

	/**
	* returns val by val negatives of a matrix.
	*
	* @return val by val negatives of a matrix
	*/
	Matrix operator-()
	{
		return map(myNegate);
	}

};

/**
* function that get 2 matrix and a function and return matrix with the items as the function on
* 2 matrix's items.
* WARNING: only works with sqaure, same size matrixes.
*
* @param func the function
* @param first 1st matrix
* @param second 2nd matrix
* @return matrix after func activate on both items
* @throw CantCalculateEx if the matrix not the same size
* @throw notSquareEx if the matrix not square
*/
template <typename T>
Matrix<T> mapFun(T(*func)(const T, const T),const Matrix<T>& first, const Matrix<T>& second)
{
	if(first.getNumOfRows() != second.getNumOfRows() || first.getNumOfCols() != second.getNumOfCols())
	{
		throw CantCalculateEx();
	}
	if(first.getNumOfRows() != first.getNumOfCols())
	{
		throw notSquareEx();
	}
	std::vector<T> vec;
	for (unsigned int i = 0; i < first.getNumOfRows(); i++)
	{
		for (unsigned int j = 0; j < first.getNumOfCols(); j++)
		{
			vec.push_back(func(first(i,j), second(i,j)));
		}
	}
	return Matrix<T>(first.getNumOfRows(), first.getNumOfCols(), vec);
}
/**
* overloading friend operator<< for specific case of char
*/
std::ostream &operator<<(std::ostream &out, const Matrix<char> &matrix)
{
	for (unsigned int i = 0; i < matrix.getNumOfRows(); i++)
	{
		for (unsigned int j = 0; j < matrix.getNumOfCols(); j++)
		{
			out << matrix(i, j);
		}
		if (i != matrix.getNumOfRows() - 1)
		{
			out << " ";
		}
		else
		{
			out << std::endl;
		}
	}
	return out;
}

/**
* overloading friend operator<< for other cases (but the case of char)
*/
template<typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix)
{
	for (unsigned int i = 0; i < matrix.getNumOfRows(); i++)
	{
		for (unsigned int j = 0; j < matrix.getNumOfCols(); j++)
		{
			out << matrix(i, j);
			if (j != matrix.getNumOfCols() - 1)
			{
				out << '\t';
			}
		}
		out << std::endl;
	}
	return out;
}

/**
* @param num1 1st arg
* @param num2 2nd arg
* @return num1 + num2
*/
template<typename T>
T myPlus(T const num1, T const num2)
{
	return num1 + num2;
}

/**
* @param num1 1st arg
* @param num2 2nd arg
* @return num1 - num2
*/
template<typename T>
T myMinus(T const num1, T const num2)
{
	return num1 - num2;
}

/**
* function to negate a value
*
* @param num1 the value to negate
* @return -num1
*/
template<typename T>
T myNegate(T const num1)
{
	return 0 - num1;
}

/**
* exception when we want to calculate somthing and the matrixes parameters dont allow this
*/
class CantCalculateEx : public std::exception
{

public:
	virtual const char *what() const noexcept
	{
		return "Can't calculate this";
	}
};

/**
* exception when we want to calculate somthing and the matrixes parameters dont allow this,
* because we need square matrixes.
*/
class notSquareEx : public CantCalculateEx
{

public:
	virtual const char *what() const noexcept
	{
		return "This operation require the matrix to be square";
	}
};

#endif


