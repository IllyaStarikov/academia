//
//  square-matrix.h
//  lib
//
//  Illya Starikov, Section 1A, 18183141
//  cs5211 – Object Oriented Numerical Modeling
//

#ifndef square_matrix_hpp
#define square_matrix_hpp

/**
 *  @brief  Construct a matrix with no size and no data.
 *
 *  @param  zero the zero element of the matrix. defaulted to the
 *          what the default constructor of `t` produced.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
SquareMatrix<T>::SquareMatrix(const T zero) {
    this -> data = nullptr;
    this -> zeroElement = zero;
    this -> dimension = 0;
}

/**
 *  @brief  Construct a matrix from an `std::initializer_list`.
 *
 *  @param  list The list to construct a matrix from.
 *  @param  zero The zero element of the matrix. Defaulted to the
 *          what the default constructor of `T` produced.
 *
 *  @throws MistmatchedDimensionsError When `list` is not in square matrix form.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
SquareMatrix<T>::SquareMatrix(const std::initializer_list<std::initializer_list<T>> list, const T zero) {
    auto size = list.size();

    this -> data = std::unique_ptr<Vector<T>[]>(new Vector<T>[size]);
    this -> dimension = size;
    this -> zeroElement = zero;

    auto iterator = list.begin();

    for (unsigned i = 0; i < size; i++) {
        if ((*iterator).size() != size) {
            throw MistmatchedDimensionsError();
        }

        this -> data[i] = *(iterator++);
    }

}

/**
 *  @brief  Construct a matrix with default values.
 *
 *  @param  size The default size.
 *  @param  zero The zero element of the matrix. Defaulted to the
 *          what the default constructor of `T` produced.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
SquareMatrix<T>::SquareMatrix(const size_t size, const T zero) {
    this -> data = std::unique_ptr<Vector<T>[]>(new Vector<T>[size]);
    this -> dimension = size;
    this -> zeroElement = zero;

    for (unsigned i = 0; i < size; i++) {
        data[i] = Vector<T>(size);
    }
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
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& other) {
    auto size = other.rows();

    this -> resize(size);
    this -> zeroElement = other.zero();

    for (unsigned i = 0; i < size; i++) {
        this -> data[i] = other.data[i];
    }
}

/**
 *  @brief  Construct a matrix from @p other via moving.
 *
 *  @param  other The matrix to construct this matrix from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
SquareMatrix<T>::SquareMatrix(SquareMatrix<T>&& other) {
    std::swap(this -> data, other.data);
    std::swap(this -> dimension, other.dimension);
    std::swap(this -> zeroElement, other.zeroElement);
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
SquareMatrix<T>& SquareMatrix<T>::operator=(SquareMatrix<T>& other) {
    auto size = other.rows();

    this -> resize(size);
    this -> zeroElement = other.zero();

    for (unsigned i = 0; i < size; i++) {
        this -> data[i] = other.data[i];
    }

    return *this;
}

/**
 *  @brief  Assign a matrix from another via moving.
 *
 *  @param  other The other matrix to assign from.
 *
 *  @return The reference of `*this`.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator=(SquareMatrix<T>&& other) {
    std::swap(this -> data, other.data);
    std::swap(this -> dimension, other.dimension);
    std::swap(this -> zeroElement, other.zeroElement);

    return *this;
}

/**
 *  @brief  Create a Matrix from the negations @p leftHandSide.
 *
 *  @param  leftHandSide The matrix to negate.
 *
 *  @return SquareMatrix The negated Matrix.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <class T>
SquareMatrix<T> operator-(const SquareMatrix<T>& leftHandSide) {
    auto size = leftHandSide.rows();
    auto zero = leftHandSide.zero();

    auto result = SquareMatrix<T>(size, zero);

    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
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
 *  @return SquareMatrix The transposed matrix.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <class T>
SquareMatrix<T> transpose(const SquareMatrix<T>& leftHandSide) {
    auto size = leftHandSide.rows();
    auto zero = leftHandSide.zero();

    auto result = SquareMatrix<T>(size, zero);

    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
            result(i, j) = leftHandSide(j, i);
        }
    }

    return result;
}

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
bool operator==(const SquareMatrix<T>& leftHandSide, const SquareMatrix<T>& rightHandSide) {
   if (leftHandSide.dimension != rightHandSide.dimension) {
        return false;
    }

    for (unsigned i = 0; i < leftHandSide.dimension; i++) {
        if (leftHandSide.data[i] != rightHandSide.data[i]) {
            return false;
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
bool operator!=(const SquareMatrix<T>& leftHandSide, const SquareMatrix<T>& rightHandSide) {
    return !(leftHandSide == rightHandSide);
}

/**
 *  @brief  Resize the Matrix to an @p rows x @p rows Matrix. Values ares reset back to `zero`.
 *
 *  @param  rows The new dimension of the matrix.
 *
 *  @warning The values are reset back to zero.
 *
 *  @pre    See `warning`.
 *  @post   See `brief`.
 **/
template <typename T>
void SquareMatrix<T>::resize(const size_t rows) {
    // Could check for to see if I `have` to resize here, but this acts as a way to reinstantiate data in the this -> data
    auto newPointer = std::unique_ptr<Vector<T>[]>(new Vector<T>[rows]);

    for (unsigned i = 0; i < rows; i++) {
        newPointer[i] = Vector<T>(rows);
    }

    this -> data = std::move(newPointer);
    this -> dimension = rows;
}

/**
 *  @brief  Resize the Matrix to an @p rows x @p rows Matrix. Values ares reset back to `zero`.
 *
 *  @param  rows The new dimension of the matrix.
 *
 *  @warning The values are reset back to zero.
 *
 *  @pre    See `warning`.
 *  @post   See `brief`.
 **/
template <typename T>
void SquareMatrix<T>::resize(const size_t rows, const size_t columns) {
    if (rows != columns) {
        throw MistmatchedDimensionsError();
    }

    this -> resize(rows);

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
template <typename T, typename S>
SquareMatrix<T> operator*(const SquareMatrix<T>& leftHandSide, const SquareMatrix<S>& rightHandSide) {
    if (leftHandSide.columns() != rightHandSide.rows()) {
        throw MistmatchedDimensionsError();
    }

    auto size = leftHandSide.rows();
    auto zero = leftHandSide.zero();

    auto result = SquareMatrix<T>(size, zero);

    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
            result(i, j) = zero;

            for (unsigned k = 0; k < size; k++) {
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
template <typename T, typename S>
SquareMatrix<T> operator+(const SquareMatrix<T>& leftHandSide, const SquareMatrix<S>& rightHandSide) {
    if (leftHandSide.columns() != rightHandSide.rows()) {
        throw MistmatchedDimensionsError();
    }

    auto size = leftHandSide.rows();
    auto zero = leftHandSide.zero();

    auto result = SquareMatrix<T>(size, zero);

    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
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
template <typename T, typename S>
SquareMatrix<T> operator-(const SquareMatrix<T>& leftHandSide, const SquareMatrix<S>& rightHandSide) {
    if (leftHandSide.columns() != rightHandSide.rows()) {
        throw MistmatchedDimensionsError();
    }

    auto size = leftHandSide.rows();
    auto zero = leftHandSide.zero();

    auto result = SquareMatrix<T>(size, zero);

    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
            result(i, j) = leftHandSide(i, j) - rightHandSide(i, j);
        }
    }

    return result;
}

/**
 *  @brief  Multiply two matrices together and assign it to @p leftHandSide.
 *
 *  @param  leftHandSide The left hand side of the of the operand.
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the Matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T, typename S>
void operator*=(SquareMatrix<T>& leftHandSide, const SquareMatrix<S>& rightHandSide) {
    leftHandSide = std::move(leftHandSide * rightHandSide);
}

/**
 *  @brief  Add two matrices together and assign it to @p leftHandSide.
 *
 *  @param  leftHandSide The left hand side of the of the operand.
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the Matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T, typename S>
void operator+=(SquareMatrix<T>& leftHandSide, const SquareMatrix<S>& rightHandSide) {
    leftHandSide = std::move(leftHandSide + rightHandSide);
}

/**
 *  @brief  Subtract two matrices together and assign it to @p leftHandSide.
 *
 *  @param  leftHandSide The left hand side of the of the operand.
 *  @param  rightHandSide The right hand side of the operand.
 *
 *  @throws MistmatchedDimensionsError If the Matrices are not of equal dimension.
 *
 *  @pre    See `throws`.
 *  @post   See `brief`.
 **/
template <typename T, typename S>
void operator-=(SquareMatrix<T>& leftHandSide, const SquareMatrix<S>& rightHandSide) {
    leftHandSide = std::move(leftHandSide - rightHandSide);
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
template <typename T, typename S>
SquareMatrix<T> operator*(const T leftHandSide, const SquareMatrix<S>& rightHandSide) {
    auto size = rightHandSide.rows();
    auto zero = rightHandSide.zero();

    auto result = SquareMatrix<T>(size, zero);

    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
            result(i, j) = leftHandSide * rightHandSide(i, j);
        }
    }

    return result;
}

/**
 *  @brief  Multiply a scalar by a Matrix.
 *
 *  @param  leftHandSide The Matrix to multiply the Vector by.
 *  @param  rightHandSide The Vector to multiply the Matrix by.
 *
 *  @return The resultant of @p leftHandSide * @p rightHandSide.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T, typename S>
Vector<T> operator*(const SquareMatrix<T> leftHandSide, const Vector<S>& rightHandSide) {
    if (leftHandSide.columns() != rightHandSide.size()) {
        throw MistmatchedDimensionsError();
    }

    auto size = leftHandSide.rows();
    auto zero = leftHandSide.zero();

    auto result = Vector<T>(size, zero);

    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
            result[i] += leftHandSide(i, j) * rightHandSide[j];
        }
    }

    return result;
}

/**
 *  @brief  An indexing operator into the matrix. Indexes as Matrix[@row][@column].
 *
 *  @param  row The row to index into.
 *  @param  row The column to index into.
 *
 *  @throws OutOfBoundsError If the @p row > the dimension or @p column > dimension.
 *
 *  @return A reference to the A[@p row][@p column].
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
T& SquareMatrix<T>::operator()(const int row, const int column) {
    if (row >= static_cast<int>(this -> dimension) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> dimension) || column < 0) {
        throw OutOfBoundsError(column);
    }

    return this -> data[row][column];
}

/**
 *  @brief  An indexing operator into the matrix. Indexes as Matrix[@row][@column].
 *
 *  @param  row The row to index into.
 *  @param  row The column to index into.
 *
 *  @throws OutOfBoundsError If the @p row > the dimension or @p column > dimension.
 *
 *  @return A const reference to the A[@p row][@p column].
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
const T& SquareMatrix<T>::operator()(const int row, const int column) const {
    if (row >= static_cast<int>(this -> dimension) || row < 0) {
        throw OutOfBoundsError(row);
    }

    if (column >= static_cast<int>(this -> dimension) || column < 0) {
        throw OutOfBoundsError(column);
    }

    return this -> data[row][column];
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
std::ostream& operator<<(std::ostream& os, const SquareMatrix<T>& other) {
    os << std::setprecision(other.precision) << std::fixed;

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
            auto totalNumberOfDigits = numberOfDigits(max) + other.precision + 2;

            os << std::setw(totalNumberOfDigits) << std::right << other(i, j) << " ";
        }
        os << "]\n";
    }

    return os;
}

#endif

