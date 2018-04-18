//
//  banded-matrix.h
//  lib
//
//  Created by Illya Starikov on 04/15/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//


/**
 *  @brief  Construct a banded matrix with no size and no data.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
BandedMatrix<T>::BandedMatrix() {
    this -> upperBand = Vector<T>();
    this -> middleBand = Vector<T>();
    this -> lowerBand = Vector<T>();

    this -> _rows = 0;
    this -> _columns = 0;
}

/**
 *  @brief  Construct a banded matrix with default values.
 *
 *  @param  rows The number of rows.
 *  @param  columns The number of columns.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
BandedMatrix<T>::BandedMatrix(const size_t rows, const size_t columns) {
    this -> resize(rows, columns);
}

/**
 *  @brief  Construct a banded matrix from @p other via `move`ing.
 *
 *  @param  other The banded matrix to construct this matrix from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
BandedMatrix<T>::BandedMatrix(BandedMatrix<T>&& other) {
    std::swap(this -> upperBand, other.upperBand);
    std::swap(this -> middleBand, other.middleBand);
    std::swap(this -> lowerBand, other.lowerBand);

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
BandedMatrix<T>::BandedMatrix(const BandedMatrix<T>& other) {
    auto rows = other.rows(), columns = other.columns();

    this -> resize(rows, columns);
    this -> upperBand = other.upperBand;
    this -> middleBand = other.middleBand;
    this -> lowerBand = other.lowerBand;
}

/**
 *  @brief  Construct a banded matrix from an `std::initializer_list`.
 *
 *  @param  list The list to construct a matrix from.
 *
 *  @throws MistmatchedDimensionsError When `list` is not in banded matrix form.
 *  @throws BandedMatrixDimensionError When `list` has dimensions < 3 x 3.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
BandedMatrix<T>::BandedMatrix(const std::initializer_list<std::initializer_list<T>> list) {
    size_t listColumns, listRows = list.size();

    if (listRows > 0) {
        listColumns = list.begin() -> size();
    } else {
        listColumns = 0;
    }

    if (listRows < 3 || listColumns < 3) {
        throw BandedMatrixDimensionError();
    }

    this -> resize(listRows, listColumns);
    auto size = std::max(std::max(this -> lowerBand.size(), this -> middleBand.size()), this -> upperBand.size());

    auto iterator = list.begin();

    for (unsigned i = 0; i < size; i++) {

        if ((*iterator).size() != listColumns) {
            throw MistmatchedDimensionsError();
        }

        if (i < upperBand.size()) {
            this -> upperBand[i] = *(iterator -> begin() + i + 1);
        }

        if (i - 1 < lowerBand.size() && i - 1 >= 0 ) {
            this -> lowerBand[i - 1] = *(iterator -> begin() + i - 1);
        }

        if (i < middleBand.size()) {
            this -> middleBand[i] = *(iterator -> begin() + i);
        }

        iterator++;
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
BandedMatrix<T>& BandedMatrix<T>::operator=(BandedMatrix<T>& other) {
    auto rows = other.rows(), columns = other.columns();

    this -> resize(rows, columns);
    this -> upperBand = other.upperBand;
    this -> middleBand = other.middleBand;
    this -> lowerBand = other.lowerBand;

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
BandedMatrix<T>& BandedMatrix<T>::operator=(BandedMatrix<T>&& other) {
    std::swap(this -> upperBand, other.upperBand);
    std::swap(this -> middleBand, other.middleBand);
    std::swap(this -> lowerBand, other.lowerBand);

    std::swap(this -> _rows, other._rows);
    std::swap(this -> _columns, other._columns);

    return *this;
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
void BandedMatrix<T>::operator+=(const BandedMatrix<T>& rightHandSide) {
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
void BandedMatrix<T>::operator-=(const BandedMatrix<T>& rightHandSide) {
    *this = std::move(*this - rightHandSide);
}


/**
 *  @brief  Add two banded matrices together.
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
BandedMatrix<T> operator+(const BandedMatrix<T>& leftHandSide, const BandedMatrix<T>& rightHandSide) {
    if (leftHandSide.rows() != leftHandSide.rows() || leftHandSide.columns() != rightHandSide.columns()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = BandedMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rightHandSide.upperBand.size(); i++) {
        result.upperBand[i] = leftHandSide.upperBand[i] + rightHandSide.upperBand[i];
    }

    for (unsigned i = 0; i < rightHandSide.middleBand.size(); i++) {
        result.middleBand[i] = leftHandSide.middleBand[i] + rightHandSide.middleBand[i];
    }

    for (unsigned i = 0; i < rightHandSide.lowerBand.size(); i++) {
        result.lowerBand[i] = leftHandSide.lowerBand[i] + rightHandSide.lowerBand[i];
    }

    return result;
}


/**
 *  @brief  Subtract two banded matrices together.
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
BandedMatrix<T> operator-(const BandedMatrix<T>& leftHandSide, const BandedMatrix<T>& rightHandSide) {
    if (leftHandSide.rows() != leftHandSide.rows() || leftHandSide.columns() != rightHandSide.columns()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = BandedMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rightHandSide.upperBand.size(); i++) {
        result.upperBand[i] = leftHandSide.upperBand[i] - rightHandSide.upperBand[i];
    }

    for (unsigned i = 0; i < rightHandSide.middleBand.size(); i++) {
        result.middleBand[i] = leftHandSide.middleBand[i] - rightHandSide.middleBand[i];
    }

    for (unsigned i = 0; i < rightHandSide.lowerBand.size(); i++) {
        result.lowerBand[i] = leftHandSide.lowerBand[i] - rightHandSide.lowerBand[i];
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
BandedMatrix<T> operator-(const BandedMatrix<T>& leftHandSide) {
    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();

    auto result = leftHandSide;

    for (unsigned i = 0; i < leftHandSide.upperBand.size(); i++) {
        result.upperBand[i] = -leftHandSide.upperBand[i];
    }

    for (unsigned i = 0; i < leftHandSide.middleBand.size(); i++) {
        result.middleBand[i] = -leftHandSide.middleBand[i];
    }

    for (unsigned i = 0; i < leftHandSide.lowerBand.size(); i++) {
        result.lowerBand[i] = -leftHandSide.lowerBand[i];
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
BandedMatrix<T> transpose(const BandedMatrix<T>& leftHandSide) {
    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();

    auto result = BandedMatrix<T>(columns, rows);

    result.upperBand = leftHandSide.lowerBand;
    result.middleBand = leftHandSide.middleBand;
    result.lowerBand = leftHandSide.upperBand;

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
void BandedMatrix<T>::resize(const size_t rows, const size_t columns) {
    // Could check for to see if I `have` to resize here, but this acts as a way to reinstantiate data in the this -> data

    auto lowerBandSize = std::min(rows, columns) - 1;
    auto middleBandSize = std::min(rows, columns);
    auto upperBandSize = std::min(rows, columns) - 1;

    if (rows > columns) {
        lowerBandSize++;
    } else if (columns > rows) {
        upperBandSize++;
    }

    this -> lowerBand = Vector<T>(lowerBandSize);
    this -> middleBand = Vector<T>(middleBandSize);
    this -> upperBand = Vector<T>(upperBandSize);

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
T& BandedMatrix<T>::operator()(const int row, const int column) {
    if (row >= static_cast<int>(this -> _rows) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> _columns) || column < 0) {
        throw OutOfBoundsError(column);
    }

    if (std::abs(row - column) > 1) {
        return BaseMatrix<T>::zero();
    } else if (row == column) {
        return middleBand[row];
    } else {
        return row > column ? upperBand[row] : lowerBand[column];
    }
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
const T& BandedMatrix<T>::operator()(const int row, const int column) const {
    if (row >= static_cast<int>(this -> _rows) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> _columns) || column < 0) {
        throw OutOfBoundsError(column);
    }

    if (std::abs(row - column) > 1) {
        return BaseMatrix<T>::zero();
    } else if (row == column) {
        return middleBand[row];
    } else {
        return row > column ? lowerBand[column] : upperBand[row];
    }
}
