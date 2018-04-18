//
//  diagonal-matrix.h
//  lib
//
//  Created by Illya Starikov on 04/15/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

/**
 *  @brief  Construct a symmetric matrix with no size and no data.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
DiagonalMatrix<T>::DiagonalMatrix() {
    this -> data = Vector<T>();
    this -> _rows = 0;
    this -> _columns = 0;
}

/**
 *  @brief  Construct a symmetric matrix with default values.
 *
 *  @param  rows The number of rows.
 *  @param  columns The number of columns.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(const size_t rows, const size_t columns) {
    this -> resize(rows, columns);
}

/**
 *  @brief  Construct a symmetric matrix from @p other via `move`ing.
 *
 *  @param  other The symmetric matrix to construct this matrix from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(DiagonalMatrix<T>&& other) {
    std::swap(this -> data, other.data);
    std::swap(this -> _rows, other._rows);
    std::swap(this -> _columns, other._columns);
}

/**
 *  @brief  Construct a banded matrix from @p other.
 *
 *  @param  other The banded matrix to construct this matrix from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(const DiagonalMatrix<T>& other) {
    auto rows = other.rows(), columns = other.columns();

    this -> resize(rows, columns);
    this -> data = other.data;
}

/**
 *  @brief  Construct a banded matrix from an `std::initializer_list`.
 *
 *  @param  list The list to construct a matrix from.
 *
 *  @throws MistmatchedDimensionsError When `list` is not in banded matrix form.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(const std::initializer_list<std::initializer_list<T>> list) {
    size_t listColumns, listRows = list.size();

    if (listRows > 0) {
        listColumns = list.begin() -> size();
    } else {
        listColumns = 0;
    }

    this -> resize(listRows, listColumns);
    auto iterator = list.begin();

    for (unsigned i = 0; i < this -> data.size(); i++) {
        if ((*iterator).size() != listColumns) {
            throw MistmatchedDimensionsError();
        }

        this -> data[i] = *(iterator -> begin() + i);
        iterator++;
    }
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
DiagonalMatrix<T>& DiagonalMatrix<T>::operator=(DiagonalMatrix<T>& other) {
    auto rows = other.rows(), columns = other.columns();
    this -> resize(rows, columns);
    this -> data = other.data;

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
DiagonalMatrix<T>& DiagonalMatrix<T>::operator=(DiagonalMatrix<T>&& other) {
    std::swap(this -> data, other.data);
    std::swap(this -> _rows, other._rows);
    std::swap(this -> _columns, other._columns);

    return *this;
}


/**
 *  @brief  Multiply two banded matrices together and assign it to *this.
 *
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the banded matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T>
void DiagonalMatrix<T>::operator*=(const DiagonalMatrix<T>& rightHandSide) {
    *this = std::move(*this * rightHandSide);
}

/**
 *  @brief  Add two banded matrices together and assign it to *this.
 *
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the banded matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T>
void DiagonalMatrix<T>::operator+=(const DiagonalMatrix<T>& rightHandSide) {
    *this = std::move(*this + rightHandSide);
}

/**
 *  @brief  Subtract two banded matrices together and assign it to *this.
 *
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the banded matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T>
void DiagonalMatrix<T>::operator-=(const DiagonalMatrix<T>& rightHandSide) {
    *this = std::move(*this - rightHandSide);
}


/**
 *  @brief  Multiply two diagonal matrices together.
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
DiagonalMatrix<T> operator*(const DiagonalMatrix<T>& leftHandSide, const DiagonalMatrix<T>& rightHandSide) {
    if (leftHandSide.columns() != rightHandSide.rows()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = rightHandSide.rows(), columns = rightHandSide.columns();
    auto size = rightHandSide.data.size();

    auto result = DiagonalMatrix<T>(rows, columns);

    for (unsigned i = 0; i < size; i++) {
        result(i, i) = leftHandSide(i, i) * rightHandSide(i, i);
    }

    return result;
}

/**
 *  @brief  Add two matrices together.
 *
 *  @param  leftHandSide The left hand side of the of the operand.
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the Matrices are not of equal dimension.
 *
 *  @return The resultant of @p leftHandSide + @p rightHandSide.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
DiagonalMatrix<T> operator+(const DiagonalMatrix<T>& leftHandSide, const DiagonalMatrix<T>& rightHandSide) {
    if (leftHandSide.rows() != leftHandSide.rows() || leftHandSide.columns() != rightHandSide.columns()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = DiagonalMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        result(i, i) = leftHandSide(i, i) + rightHandSide(i, i);
    }

    return result;
}

/**
 *  @brief  Subtract two matrices together.
 *
 *  @param  leftHandSide The left hand side of the of the operand.
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the Matrices are not of equal dimension.
 *
 *  @return The resultant of @p leftHandSide - @p rightHandSide.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
DiagonalMatrix<T> operator-(const DiagonalMatrix<T>& leftHandSide, const DiagonalMatrix<T>& rightHandSide) {
    if (leftHandSide.rows() != leftHandSide.rows() || leftHandSide.columns() != rightHandSide.columns()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = DiagonalMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        result(i, i) = leftHandSide(i, i) - rightHandSide(i, i);
    }

    return result;
}


/**
 *  @brief  Multiply a scalar by a diagonal matrix.
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
DiagonalMatrix<T> operator*(const T& leftHandSide, const DiagonalMatrix<T>& rightHandSide) {
    auto rows = rightHandSide.rows(), columns = rightHandSide.columns();
    auto size = rightHandSide.data.size();

    auto result = DiagonalMatrix<T>(rows, columns);

    for (unsigned i = 0; i < size; i++) {
        result(i, i) = leftHandSide * rightHandSide(i, i);
    }

    return result;
}


/**
 *  @brief  Create a Matrix from the negations @p leftHandSide.
 *
 *  @param  leftHandSide The matrix to negate.
 *
 *  @return RectangularMatrix The negated Matrix.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <class T>
DiagonalMatrix<T> operator-(const DiagonalMatrix<T>& leftHandSide) {
    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto size = leftHandSide.data.size();

    auto result = DiagonalMatrix<T>(rows, columns);

    for (unsigned i = 0; i < size; i++) {
        result(i, i) = -leftHandSide(i, i);
    }

    return result;
}


/**
 *  @brief  Create a diagonal matrix from the transpose of @p leftHandSide.
 *
 *  @param  leftHandSide The matrix to create a transpose from.
 *
 *  @return RectangularMatrix The transposed matrix.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <class T>
DiagonalMatrix<T> transpose(const DiagonalMatrix<T>& leftHandSide) {
    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto size = leftHandSide.data.size();

    auto result = DiagonalMatrix<T>(columns, rows);

    for (unsigned i = 0; i < size; i++) {
        result(i, i) = leftHandSide(i, i);
    }

    return result;
}


/**
 *  @brief  Resize the banded matrix to an @p rows x @p columns banded matrix. Values are reset back to `zero`.
 *
 *  @param  rows The new dimension of the matrix.
 *
 *  @warning The values are reset back to zero.
 *
 *  @pre    See `warning`.
 *  @post   See `brief`.
 **/
template <typename T>
void DiagonalMatrix<T>::resize(const size_t rows, const size_t columns) {
    // Could check for to see if I `have` to resize here, but this acts as a way to reinstantiate data in the this -> data

    this -> data = Vector<T>(std::min(rows, columns));
    this -> _rows = rows;
    this -> _columns = columns;
}


/**
 *  @brief  An indexing operator into the banded matrix. Indexes as matrix(@row, @column).
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
T& DiagonalMatrix<T>::operator()(const int row, const int column) {
    if (row >= static_cast<int>(this -> _rows) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> _columns) || column < 0) {
        throw OutOfBoundsError(column);
    }

    if (row != column) {
        return BaseMatrix<T>::zero();
    }

    return this -> data[row];
}

/**
 *  @brief  An indexing operator into the banded matrix. Indexes as matrix(@row, @column).
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
const T& DiagonalMatrix<T>::operator()(const int row, const int column) const {
    if (row >= static_cast<int>(this -> _rows) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> _columns) || column < 0) {
        throw OutOfBoundsError(column);
    }

    if (row != column) {
        return BaseMatrix<T>::zero();
    }

    return this -> data[row];
}
