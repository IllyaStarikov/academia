//
//  square-matrix.h
//  lib
//
//  Illya Starikov, Section 1A, 18183141
//  cs5211 – Object Oriented Numerical Modeling
//


/**
 *  @brief  Construct a matrix with no size and no data.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
RectangularMatrix<T>::RectangularMatrix() {
    this -> data = nullptr;
    this -> _rows = 0;
    this -> _columns = 0;
}

/**
 *  @brief  Construct a matrix with default values.
 *
 *  @param  rows The number of rows.
 *  @param  columns The number of columns.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
RectangularMatrix<T>::RectangularMatrix(const size_t rows, const size_t columns) {
    this -> resize(rows, columns);
}

/**
 *  @brief  Construct a matrix from @p other via `move`ing.
 *
 *  @param  other The matrix to construct this matrix from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
RectangularMatrix<T>::RectangularMatrix(RectangularMatrix<T>&& other) {
    std::swap(this -> data, other.data);
    std::swap(this -> _rows, other._rows);
    std::swap(this -> _columns, other._columns);
}

/**
 *  @brief  Construct a matrix from @p other.
 *
 *  @param  other The matrix to construct this matrix from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
RectangularMatrix<T>::RectangularMatrix(const RectangularMatrix<T>& other) {
    auto rows = other.rows(), columns = other.columns();
    this -> resize(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        this -> data[i] = other.data[i];
    }
}

/**
 *  @brief  Construct a matrix from an `std::initializer_list`.
 *
 *  @param  list The list to construct a matrix from.
 *
 *  @throws MistmatchedDimensionsError When `list` is not in rectangular matrix form.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
RectangularMatrix<T>::RectangularMatrix(const std::initializer_list<std::initializer_list<T>> list) {
    size_t listColumns, listRows = list.size();

    if (listRows > 0) {
        listColumns = list.begin() -> size();
    } else {
        listColumns = 0;
    }

    this -> resize(listRows, listColumns);
    auto iterator = list.begin();

    for (unsigned i = 0; i < listRows; i++) {
        if ((*iterator).size() != listColumns) {
            throw MistmatchedDimensionsError();
        }

        this -> data[i] = *(iterator++);
    }
}

/**
 *  @brief  Assign a matrix from another.
 *
 *  @param  other The other matrix to assign from.
 *
 *  @return The reference of `*this`.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
RectangularMatrix<T>& RectangularMatrix<T>::operator=(RectangularMatrix<T>& other) {
    auto rows = other.rows(), columns = other.columns();

    this -> resize(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        this -> data[i] = other.data[i];
    }

    return *this;
}

/**
 *  @brief  Assign a matrix from another via `move`ing.
 *
 *  @param  other The other matrix to assign from.
 *
 *  @return The reference of `*this`.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
RectangularMatrix<T>& RectangularMatrix<T>::operator=(RectangularMatrix<T>&& other) {
    std::swap(this -> data, other.data);
    std::swap(this -> _rows, other._rows);
    std::swap(this -> _columns, other._columns);

    return *this;
}


/**
 *  @brief  Multiply two matrices together and assign it to `*this`.
 *
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the matrices are not of equal dimensions.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T>
void RectangularMatrix<T>::operator*=(const RectangularMatrix<T>& rightHandSide) {
    *this = std::move(*this * rightHandSide);
}


/**
 *  @brief  Add two matrices together and assign it to *this.
 *
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T>
void RectangularMatrix<T>::operator+=(const RectangularMatrix<T>& rightHandSide) {
    *this = std::move(*this + rightHandSide);
}

/**
 *  @brief  Subtract two matrices together and assign it to *this.
 *
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T>
void RectangularMatrix<T>::operator-=(const RectangularMatrix<T>& rightHandSide) {
    *this = std::move(*this - rightHandSide);
}


/**
 *  @brief  Multiply a scalar by a Matrix.
 *
 *  @param  leftHandSide The scalar to multiply the Matrix by.
 *  @param  rightHandSide The Matrix to multiply the scalar by.
 *
 *  @return The resultant of @p leftHandSide * @p rightHandSide.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
RectangularMatrix<T> operator*(const T& leftHandSide, const RectangularMatrix<T>& rightHandSide) {
    auto rows = rightHandSide.rows(), columns = rightHandSide.columns();
    auto result = RectangularMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < columns; j++) {
            result(i, j) = leftHandSide * rightHandSide(i, j);
        }
    }

    return result;
}

/**
 *  @brief  Multiply two matrices together.
 *
 *  @param  leftHandSide The left hand side of the of the operand.
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the Matrices are not of equal dimension.
 *
 *  @return The resultant of @p leftHandSide * @p rightHandSide.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
RectangularMatrix<T> operator*(const RectangularMatrix<T>& leftHandSide, const RectangularMatrix<T>& rightHandSide) {
    if (leftHandSide.columns() != rightHandSide.rows()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = rightHandSide.columns(), inner = rightHandSide.rows();
    auto zero = leftHandSide.zero();

    auto result = RectangularMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < columns; j++) {
            result(i, j) = zero;

            for (unsigned k = 0; k < inner; k++) {
                result(i, j) += leftHandSide(i, k) * rightHandSide(k, j);
            }
        }
    }

    return result;
}


/**
 *  @brief  Resize the matrix to an @p rows x @p columns matrix. Values are reset back to `zero`.
 *
 *  @param  rows The new dimension of the matrix.
 *
 *  @warning The values are reset back to zero.
 *
 *  @pre    See `warning`.
 *  @post   See `brief`.
 **/
template <typename T>
void RectangularMatrix<T>::resize(const size_t rows, const size_t columns) {
    // Could check for to see if I `have` to resize here, but this acts as a way to reinstantiate data in the this -> data
    auto newPointer = std::unique_ptr<Vector<T>[]>(new Vector<T>[rows]);

    for (unsigned i = 0; i < rows; i++) {
        newPointer[i] = Vector<T>(columns, BaseMatrix<T>::zero());
    }

    this -> data = std::move(newPointer);
    this -> _rows = rows;
    this -> _columns = columns;
}

/**
 *  @brief  An indexing operator into the matrix. Indexes as matrix(@row, @column).
 *
 *  @param  row The row to index into.
 *  @param  row The column to index into.
 *
 *  @throws OutOfBoundsError If the @p row > the dimension or @p column > dimension.
 *
 *  @return A reference to the A(@p row, @p column).
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
T& RectangularMatrix<T>::operator()(const int row, const int column) {
    if (row >= static_cast<int>(this -> _rows) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> _columns) || column < 0) {
        throw OutOfBoundsError(column);
    }

    return this -> data[row][column];
}


/**
 *  @brief  An indexing operator into the matrix. Indexes as matrix(@row, @column).
 *
 *  @param  row The row to index into.
 *  @param  row The column to index into.
 *
 *  @throws OutOfBoundsError If the @p row > the dimension or @p column > dimension.
 *
 *  @return A const reference to the A(@p row, @p column).
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
const T& RectangularMatrix<T>::operator()(const int row, const int column) const {
    if (row >= static_cast<int>(this -> _rows) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> _columns) || column < 0) {
        throw OutOfBoundsError(column);
    }

    return this -> data[row][column];
}

