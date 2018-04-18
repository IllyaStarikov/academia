//
//  symmetric-matrix.h
//  lib
//
//  Created by Illya Starikov on 04/16/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//


/**
 *  @brief  Construct a symmetric matrix with no size and no data.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
SymmetricMatrix<T>::SymmetricMatrix() {
    this -> data = nullptr;
    this -> dimension = 0;
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
SymmetricMatrix<T>::SymmetricMatrix(const size_t rows, const size_t columns) {
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
SymmetricMatrix<T>::SymmetricMatrix(SymmetricMatrix<T>&& other) {
    std::swap(this -> data, other.data);
    std::swap(this -> dimension, other.dimension);
}

/**
 *  @brief  Construct a symmetric matrix from @p other.
 *
 *  @param  other The symmetric matrix to construct this matrix from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
SymmetricMatrix<T>::SymmetricMatrix(const SymmetricMatrix<T>& other) {
    auto rows = other.rows(), columns = other.columns();
    this -> resize(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        this -> data[i] = other.data[i];
    }
}

/**
 *  @brief  Construct a symmetric matrix from an `std::initializer_list`.
 *
 *  @param  list The list to construct a matrix from.
 *
 *  @throws MistmatchedDimensionsError When `list` is not in symmetric matrix form.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
SymmetricMatrix<T>::SymmetricMatrix(const std::initializer_list<std::initializer_list<T>> list) {
    size_t listColumns, listRows = list.size();

    if (listRows > 0) {
        listColumns = list.begin() -> size();
    } else {
        listColumns = 0;
    }

    this -> resize(listRows, listColumns);
    auto iterator = list.begin();

    for (unsigned i = 0; i < listRows; i++, iterator++) {
        if ((*iterator).size() != listColumns) {
            throw MistmatchedDimensionsError();
        }

        auto sublistIterator = (*iterator).begin();
        for (unsigned j = 0; j <= i; j++, sublistIterator++) {
            this -> data[i][j] = *sublistIterator;
        }
    }

    iterator = list.begin();
    for (unsigned i = 0; i < listRows; i++, iterator++) {

        auto sublistIterator = (*iterator).begin();
        for (unsigned j = 0; j < listColumns; j++, sublistIterator++) {
            if ((*this)(i, j) != (*sublistIterator)) {
                throw NonSymmetricMatrixError();
            }
        }
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
SymmetricMatrix<T>& SymmetricMatrix<T>::operator=(SymmetricMatrix<T>& other) {
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
SymmetricMatrix<T>& SymmetricMatrix<T>::operator=(SymmetricMatrix<T>&& other) {
    std::swap(this -> data, other.data);
    std::swap(this -> dimension, other.dimension);

    return *this;
}


/**
 *  @brief  Add two symmetric matrices together and assign it to @p leftHandSide.
 *
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the symmetric matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T>
void SymmetricMatrix<T>::operator+=(const SymmetricMatrix<T>& rightHandSide) {
    *this = std::move(*this + rightHandSide);
}

/**
 *  @brief  Subtract two symmetric matrices together and assign it to @p leftHandSide.
 *
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the symmetric matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T>
void SymmetricMatrix<T>::operator-=(const SymmetricMatrix<T>& rightHandSide) {
    *this = std::move(*this - rightHandSide);
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
SymmetricMatrix<T> operator+(const SymmetricMatrix<T>& leftHandSide, const SymmetricMatrix<T>& rightHandSide) {
    if (leftHandSide.rows() != leftHandSide.rows() || leftHandSide.columns() != rightHandSide.columns()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = SymmetricMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j <= i; j++) {
            result(i, j) = leftHandSide(i, j) + rightHandSide(i, j);
        }
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
SymmetricMatrix<T> operator-(const SymmetricMatrix<T>& leftHandSide, const SymmetricMatrix<T>& rightHandSide) {
    if (leftHandSide.rows() != leftHandSide.rows() || leftHandSide.columns() != rightHandSide.columns()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = SymmetricMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j <= i; j++) {
            result(i, j) = leftHandSide(i, j) - rightHandSide(i, j);
        }
    }

    return result;
}


/**
 *  @brief  Create a symmetric matrix from the negations @p leftHandSide.
 *
 *  @param  leftHandSide The matrix to negate.
 *
 *  @return RectangularMatrix The negated Matrix.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <class T>
SymmetricMatrix<T> operator-(const SymmetricMatrix<T>& leftHandSide) {
    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = SymmetricMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j <= i; j++) {
            result(i, j) = -leftHandSide(i, j);
        }
    }

    return result;
}

/**
 *  @brief  Create a Matrix from the transpose of @p leftHandSide.
 *
 *  @param  leftHandSide The matrix to create a transpose from.
 *
 *  @return RectangularMatrix The transposed matrix.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <class T>
SymmetricMatrix<T> transpose(const SymmetricMatrix<T>& leftHandSide) {
    return leftHandSide;
}


/**
 *  @brief  Resize the symmetric matrix to an @p rows x @p columns symmetric matrix. Values are reset back to `zero`.
 *
 *  @param  rows The new dimension of the matrix.
 *
 *  @warning The values are reset back to zero.
 *
 *  @pre    See `warning`.
 *  @post   See `brief`.
 **/
template <typename T>
void SymmetricMatrix<T>::resize(const size_t rows, const size_t columns) {
    if (rows != columns) {
        throw NonSquareMatrixError();
    }
    // Could check for to see if I `have` to resize here, but this acts as a way to reinstantiate data in the this -> data
    auto newPointer = std::unique_ptr<Vector<T>[]>(new Vector<T>[rows]);

    for (unsigned i = 0; i < rows; i++) {
        newPointer[i] = Vector<T>(i + 1, BaseMatrix<T>::zero());
    }

    this -> data = std::move(newPointer);
    this -> dimension = rows;
}


/**
 *  @brief  An indexing operator into the symmetric matrix. Indexes as matrix(@row, @column).
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
T& SymmetricMatrix<T>::operator()(const int row, const int column) {
    if (row >= static_cast<int>(this -> dimension) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> dimension) || column < 0) {
        throw OutOfBoundsError(column);
    }

    if (row < column) {
        return data[column][row];
    }

    return this -> data[row][column];
}

/**
 *  @brief  Resize the symmetric matrix to an @p rows x @p columns symmetric matrix. Values are reset back to `zero`.
 *
 *  @param  rows The new dimension of the matrix.
 *
 *  @warning The values are reset back to zero.
 *
 *  @pre    See `warning`.
 *  @post   See `brief`.
 **/
template <typename T>
const T& SymmetricMatrix<T>::operator()(const int row, const int column) const {
    if (row >= static_cast<int>(this -> dimension) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> dimension) || column < 0) {
        throw OutOfBoundsError(column);
    }

    if (row < column) {
        return data[column][row];
    }

    return this -> data[row][column];
}


