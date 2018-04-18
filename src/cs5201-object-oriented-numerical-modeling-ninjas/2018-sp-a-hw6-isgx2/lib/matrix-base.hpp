//
//  matrix-base.hpp
//  lib
//
//  Created by Illya Starikov on 04/17/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

template <typename T>
T BaseMatrix<T>::_zero = T();

/**
 *  @brief  Determine if two matrices are equal.
 *
 *  @param  leftHandSide The first matrix to compare.
 *  @param  rightHandSide The second matrix to compare.
 *
 *  @return true if @p leftHandSide and @p rightHandSide are equal. false otherwise.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
bool operator==(const BaseMatrix<T>& leftHandSide, const BaseMatrix<T>& rightHandSide) {
    if (leftHandSide.rows() != rightHandSide.rows()) {
        return false;
    }

    if (leftHandSide.columns() != rightHandSide.columns()) {
        return false;
    }

    for (unsigned i = 0; i < leftHandSide.rows(); i++) {
        for (unsigned j = 0; j < leftHandSide.columns(); j++) {
            if (leftHandSide(i, j) != rightHandSide(i, j)) {
                return false;
            }
        }
    }

    return true;
}

/**
 *  @brief  Determine if two matrices are not equal.
 *
 *  @param  leftHandSide The first matrix to compare.
 *  @param  rightHandSide The second matrix to compare.
 *
 *  @return true if @p leftHandSide and @p rightHandSide are not equal. false otherwise.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
bool operator!=(const BaseMatrix<T>& leftHandSide, const BaseMatrix<T>& rightHandSide) {
    return !(leftHandSide == rightHandSide);
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
RectangularMatrix<T> operator*(const BaseMatrix<T>& leftHandSide, const BaseMatrix<T>& rightHandSide) {
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
RectangularMatrix<T> operator+(const BaseMatrix<T>& leftHandSide, const BaseMatrix<T>& rightHandSide) {
    if (leftHandSide.rows() != leftHandSide.rows() || leftHandSide.columns() != rightHandSide.columns()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = RectangularMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < columns; j++) {
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
RectangularMatrix<T> operator-(const BaseMatrix<T>& leftHandSide, const BaseMatrix<T>& rightHandSide) {
    if (leftHandSide.rows() != leftHandSide.rows() || leftHandSide.columns() != rightHandSide.columns()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = RectangularMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < columns; j++) {
            result(i, j) = leftHandSide(i, j) - rightHandSide(i, j);
        }
    }

    return result;
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
RectangularMatrix<T> operator*(const T& leftHandSide, const Matrix<T>& rightHandSide) {
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
 *  @brief  Multiply a matrix by a vector.
 *
 *  @param  leftHandSide The Matrix to multiply the Vector by.
 *  @param  rightHandSide The Vector to multiply the Matrix by.
 *
 *  @return The resultant of @p leftHandSide * @p rightHandSide.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
Vector<T> operator*(const Matrix<T>& leftHandSide, const Vector<T>& rightHandSide) {
    if (leftHandSide.columns() != rightHandSide.size()) {
        throw MistmatchedDimensionsError();
    }

    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = Vector<T>(rows, leftHandSide.zero());

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < columns; j++) {
            result[i] += leftHandSide(i, j) * rightHandSide[j];
        }
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
RectangularMatrix<T> operator-(const BaseMatrix<T>& leftHandSide) {
    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = RectangularMatrix<T>(rows, columns);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < columns; j++) {
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
RectangularMatrix<T> transpose(const BaseMatrix<T>& leftHandSide) {
    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();
    auto result = RectangularMatrix<T>(columns, rows);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < columns; j++) {
            result(j, i) = leftHandSide(i, j);
        }
    }

    return result;
}


template <class T>
bool isDiagonallyDominant(const BaseMatrix<T>& leftHandSide) {
    auto rows = leftHandSide.rows(), columns = leftHandSide.columns();

    T sum, diagonal;

    for (unsigned i = 0; i < rows; i++) {
        sum = 0;

        for (unsigned j = 0; j < columns; j++) {
            if (i == j) {
                diagonal = leftHandSide(i, j);
            } else {
                sum += leftHandSide(i, j);
            }
        }

        if (sum > diagonal) {
            return false;
        }
    }

    return true;
}


/**
 *  @brief  Get the zero element, and reset it to zero.
 *
 *  @return A reference to the zero element.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
T& BaseMatrix<T>::zero() const noexcept {
    BaseMatrix<T>::_zero = T();
    return _zero;
}


/**
 *  @brief Insert a string description of a Matrix into a stream.
 *
 *  @tparam T T must have the insertion operator defined.
 *
 *  @param os The stream to put a string description of the Matrix into.
 *
 *  @param object The polar pair to generate a string description from.
 *
 *  @return The stream with the string description of the @p object in it.
 *
 *  @pre `@tparam`.
 *  @post See `return`.
 **/
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& other) {
    const int precision = 8;

    os << std::setprecision(precision) << std::fixed;

    T max = std::numeric_limits<T>::min();
    auto numberOfDigits = [](const T number) { return number > 0 ? static_cast<int>(log10(number)) + 1 : 1; };

    for (unsigned i = 0; i < other.rows(); i++) {
        for (unsigned j = 0; j < other.columns(); j++) {
            max = std::max(max, other(i, j));
        }
    }

    for (unsigned i = 0; i < other.rows(); i++) {
        os << "[";
        for (unsigned j = 0; j < other.columns(); j++) {
            auto totalNumberOfDigits = numberOfDigits(max) + precision + 2;

            os << std::setw(totalNumberOfDigits) << std::right << other(i, j) << " ";
        }
        os << "]\n";
    }

    return os;
}

