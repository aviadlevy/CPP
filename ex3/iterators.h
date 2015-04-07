	/**
	 * cells iterator class implementation.
	 * this iterator starts from the first row
	 * (e,g: matrix(0, 0), matrix(0, 1) .. matrix(0, col - 1), matrix(1, 0) ...)
     */
	class Iter
	{
	public:
		/**
	     * cells iterator constructor.
	     * @param matrix the Matrix to iterate over.
	     */
		Iter(std::vector< std::vector< T > > matrix,
			 unsigned int row = DEFAULT_VALUE, unsigned int column = DEFAULT_VALUE) :
		_iterMatrix(matrix), _row(row), _column(column)
		{

		}

		/**
	     * implementation of operator ++. increase iterator.
	     * @return a reference to this iterator.
	     */
		Iter& operator++()
		{
			// if reached end of line, go to next line:
			if (++_column == _iterMatrix[DEFAULT_VALUE].size())
			{
				_column = DEFAULT_SIZE;
				_row ++;
			}
			return *this;
		}

		/**
	     * implementation of operator ++(). increase iterator and than operate.
	     * @return this iterator.
	     */
		const Iter operator++(int)
		{
			Iter iter = *this;

			// if reached end of line, go to next line:
			if (++ _column == _iterMatrix[DEFAULT_VALUE].size())
			{
				_column = DEFAULT_SIZE;
				_row ++;
			}
			return iter;
		}

		/**
	     * implementation of operator *. dereference iterator.
	     * @return the value in current matrix cell.
	     */
		T& operator*() const { return _iterMatrix[_row][_column]; }

		/**
	     * implementation of operator ->. dereference iterator.
	     * @return the matrix this iterator iterates over.
	     */
		T* operator->() const { return &(operator*()); }

		/**
	     * implementation of operator ==. compares iterators.
	     * @return true if iterators iterates same matrix
	     * and they are at same point, or false if not.
	     */
		bool operator==(const Iter& rhs) const
		{
			return _iterMatrix == rhs._iterMatrix && _row == rhs._row && _column == rhs._column;
		}

		/**
	     * implementation of operator !=. compares iterators.
	     * @return false if iterators iterates same matrix
	     * and they are at same point, or true if not.
	     */
		bool operator!=(const Iter& rhs) const { return !(operator==(rhs)); }
	
	private:
		std::vector< std::vector< T > > _iterMatrix;
		/**< a 2D matrix board to iterate over. */
		unsigned int _row; /**< current row in iteration. */
		unsigned int _column; /**< current column in iteration. */
	};

	/**
	 * columns iterator class implementation.
	 * this iterator iterates over matrix columns.
     */
	class ColIter
	{
	public:
		/**
	     * columns iterator constructor.
	     * @param matrix the Matrix to iterate over.
	     * @param rows number of rows in the matrix.
	     * @param columns number of columns in the matrix.
	     * @param column column to start iterate from.
	     */
		ColIter(const std::vector< std::vector< T > >& matrix, unsigned int rows,
				unsigned int columns, unsigned int column = DEFAULT_VALUE) :
		_colIterMatrix(matrix), _rows(rows), _columns(columns), _column(column),
		_columnVector(_getColumnVector(matrix))
		{

		}

		/**
	     * implementation of operator ++. increase iterator.
	     * @return a reference to this iterator.
	     */
		ColIter& operator++()
		{
			++ _column;
			if (_column < _columns)
			{
				_columnVector = _getColumnVector(_colIterMatrix);
			}
			return *this;
		}

		/**
	     * implementation of operator ++(). increase iterator and than operate.
	     * @return this iterator.
	     */
		const ColIter operator++(int)
		{
			ColIter iter = *this;
			++ _column;
			if (_column < _columns)
			{
				_columnVector = _getColumnVector(_colIterMatrix);
			}
			return iter;
		}

		/**
	     * implementation of operator *. dereference iterator.
	     * @return current iteration matrix column.
	     */
		const std::vector<T>& operator*() const { return _columnVector; }

		/**
	     * implementation of operator ->. dereference iterator.
	     * @return a pointer to current iteration matrix column.
	     */
		const std::vector<T>* operator->() const { return &(operator*()); }

		/**
	     * implementation of operator ==. compares iterators.
	     * @return true if iterators iterates same matrix
	     * and they are at same point, or false if not.
	     */
		bool operator==(const ColIter& rhs) const
		{
			return _colIterMatrix == rhs._colIterMatrix && _column == rhs._column;
		}

		/**
	     * implementation of operator !=. compares iterators.
	     * @return false if iterators iterates same matrix
	     * and they are at same point, or true if not.
	     */
		bool operator!=(const ColIter& rhs) const { return !(operator==(rhs)); }

		/**
		 * operator = do a deep copy of another columns iterator into this one.
		 * @param other	the iterator to copy.
		 * @return this, after copying other content.
		 */
		ColIter& operator=(ColIter& other)
		{
			_rows = other._rows;
			_columns = other._columns;
			_column = other._column;
			_columnVector = other._columnVector;
			_colIterMatrix = other._colIterMatrix;
		}

	private:
		std::vector< std::vector< T > > _colIterMatrix;
		/**< a 2D matrix board to iterate over. */
		unsigned int _rows; /**< number of rows in matrix. */
		unsigned int _columns; /**< number of columns in matrix. */
		unsigned int _column; /**< current iteration column. */
		std::vector<T> _columnVector; /**< a column vector to iterate over. */
		

		/**
	     * convert column values to a column vector.
	     * @param matrix matrix to get a column vector from.
	     * @return an iterator over all the matrix cells.
	     */
		std::vector< T > _getColumnVector(const std::vector< std::vector< T > >& matrix) const
		{
			std::vector< T > columnVector;
			// in case we got last col:
			if (_column >= _columns)
			{
				return columnVector;
			}

			// add column values to vector:
			for (unsigned int i = 0 ; i < _rows ; i ++)
			{
				columnVector.push_back(matrix[i][_column]);
			}
			return columnVector;
		}

	};

	/**
	 * rows iterator class implementation.
	 * this iterator iterates over matrix rows.
     */
	class RowIter
	{
	public:
		/**
	     * rows iterator constructor.
	     * @param matrix the Matrix to iterate over.
	     * @param rows number of rows in the matrix.
	     * @param row row to start iterate from.
	     */
		RowIter(const std::vector< std::vector< T > >& matrix, unsigned int rows,
				unsigned int row = DEFAULT_VALUE) :
		_rowIterMatrix(matrix), _rows(rows), _row(row)
		{

		}

		/**
	     * implementation of operator ++. increase iterator.
	     * @return a reference to this iterator.
	     */
		RowIter& operator++()
		{
			++ _row;
			return *this;
		}

		/**
	     * implementation of operator ++(). increase iterator and than operate.
	     * @return this iterator.
	     */
		const RowIter operator++(int)
		{
			RowIter iter = *this;
			++ _row;
			return iter;
		}

		/**
	     * implementation of operator *. dereference iterator.
	     * @return current row of this iterator.
	     */
		const std::vector<T>& operator*() const
		{
			// in case we got last row:
			if (_row >= _rows)
			{
				throw IndexOutOfRangeException();
			}
			return _rowIterMatrix[_row];
		}

		/**
	     * implementation of operator ->. dereference iterator.
	     * @return a pointer to current row of this iterator.
	     */
		const std::vector<T>* operator->() const { return &(operator*()); }

		/**
	     * implementation of operator ==. compares iterators.
	     * @return true if iterators iterates same matrix
	     * and they are at same point, or false if not.
	     */
		bool operator==(const RowIter& rhs) const
		{
			return _rowIterMatrix == rhs._rowIterMatrix && _row == rhs._row;
		}

		/**
	     * implementation of operator !=. compares iterators.
	     * @return false if iterators iterates same matrix
	     * and they are at same point, or true if not.
	     */
		bool operator!=(const RowIter& rhs) const { return !(operator==(rhs)); }

		/**
		 * operator = do a deep copy of another row iterator into this one.
		 * @param other	the iterator to copy.
		 * @return this, after copying other content.
		 */
		RowIter& operator=(RowIter& other)
		{
			_row = other._row;
			_rows = other._rows;
			_rowIterMatrix = other._rowIterMatrix;
		}
	
	private:
		std::vector< std::vector< T > > _rowIterMatrix;
		/**< a 2D matrix board to iterate over. */
		// std::vector<T> _columnVector; /**< a column vector to iterate over. */
		unsigned int _rows; /**< number of rows in matrix. */
		unsigned int _row; /**< current iteration row. */

	};

	/**
     * an iterator over all the matrix cells, start from the first row
     * (e,g: matrix(0, 0), matrix(0, 1) .. matrix(0, col - 1), matrix(1, 0) ...).
     *  this iterator support the copy, assignment, increment,
     * equality/inequality and dereferencing operators. 
     * @return an iterator over all the matrix cells.
     */
	Iter begin() { return Iter(_matrix); }

	/**
     * an iterator pointing to the past-the-end cell in the matrix.
     * @return an iterator pointing to the past-the-end cell in the matrix.
     */
	Iter end() { return Iter(_matrix, _rows - 1, _columns - 1); }

	/**
     * an iterator over all the matrix cols.
     * @return an iterator over all the matrix cols.
     */
	ColIter colIteratorBegin() const { return ColIter(_matrix, _rows, _columns); }

	/**
     * an iterator pointing to the past-the-end col in the matrix.
     * @return an iterator pointing to the past-the-end col in the matrix.
     */
	ColIter colIteratorEnd() const { return ColIter(_matrix, _rows, _columns, _columns); }

	/**
     * an iterator over all the matrix rows.
     * @return an iterator over all the matrix rows.
     */
	RowIter rowIteratorBegin() const { return RowIter(_matrix, _rows); }

	/**
     * an iterator pointing to the past-the-end row in the matrix.
     * @return an iterator pointing to the past-the-end row in the matrix.
     */
	RowIter rowIteratorEnd() const { return RowIter(_matrix, _rows, _rows); }