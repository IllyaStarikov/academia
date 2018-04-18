//
//  vector.hpp
//  lib
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef vector_hpp
#define vector_hpp

/**
 *  @brief  Construct a vector with initial values (size of 0 with no data).
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
Vector<T>::Vector() {
    this -> _size = 0;
    this -> data = nullptr;
}

/**
 *  @brief  An explicit constructor that takes a @p size and
 *          initialize the vector with said @p size.
 *
 *  @param  size The desired size of the Vector.
 *
 *  @throws  OutOfBoundsError If the size is not positive.
 *
 *  @warning If the size is less than one, an error will be thrown.
 *
 *  @pre    See `warning`.
 *  @post   None.
 **/
template <typename T>
Vector<T>::Vector(const size_t size) {
    if (size <= 0) {
        throw OutOfBoundsError(size);
    }

    this -> _size = size;
    this -> data = std::unique_ptr<T[]>(new T[size]);
}

/**
 *  @brief  An explicit constructor that takes a @p size and
 *          initialize the vector with said @p size with
 *          @p initial value @p initialValue.
 *
 *  @param  size The desired size of the vector.
 *  @param  initialValue The desired initial value of all the entrees.
 *
 *  @throws  OutOfBoundsError If the size is not positive.
 *
 *  @warning If the size is less than one, an error will be thrown.
 *
 *  @pre    See `warning`.
 *  @post   None.
 **/
template <typename T>
Vector<T>::Vector(const size_t size, const T& initialValue) {
    if (size <= 0) {
        throw OutOfBoundsError(size);
    }

    this -> _size = size;
    data = std::unique_ptr<T[]>(new T[size]);

    for (unsigned i = 0; i < size; i++) {
        this -> data[i] = initialValue;
    }
}

/**
 *  @brief  Construct a vector from an `std::initializer_list`.
 *
 *  @param  list An `std::initializer_list` that is to be copied
 *          from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
Vector<T>::Vector(const std::initializer_list<T> list) {
    this -> _size = list.size();
    data = std::unique_ptr<T[]>(new T[list.size()]);

    std::copy(list.begin(), list.end(), this -> data.get());
}

/**
 *  @brief  Construct a vector from @p other via copy constructing.
 *
 *  @param  other The Vector to copy data from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
    this -> _size = other._size;
    this -> data = std::unique_ptr<T[]>(new T[other._size]);

    std::copy(other.data.get(), other.data.get() + other._size, this -> data.get());
}

/**
 *  @brief  Construct a vector by `move`ing it.
 *
 *  @param  other The Vector to move data from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
Vector<T>::Vector(Vector&& other) {
    this -> _size = other._size;

    std::swap(this -> data, other.data);
}

/**
 *  @brief  Destructor.
 *
 *  @pre    None.
 *  @post   None.
 **/
template <typename T>
Vector<T>::~Vector() {}

/**
 *  @brief  Construct a vector from @p other by `move`ing it.
 *
 *  @param  other The Vector to move data from.
 *
 *  @return A reference to the current Vector.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
    if (this != &other) {
        this -> _size = other._size;
        std::swap(this -> data, other.data);
    }

    return *this;
}

/**
 *  @brief  Construct a vector from @p other via assignment.
 *
 *  @param  other The Vector to copy data from.
 *
 *  @return A reference to the current Vector.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        this -> _size = other._size;
        this -> data = std::unique_ptr<T[]>(new T[other._size]);

        std::copy(other.data.get(), other.data.get() + other._size, this -> data.get());
    }

    return *this;
}

/**
 *  @brief  Create a negated vector.
 *
 *  @param  leftHandSide The vector to negate.
 *
 *  @return A negated vector.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <class T>
Vector<T> operator-(const Vector<T>& leftHandSide) {
    auto size = leftHandSide.size();
    auto result = Vector<T>(size);

    for (unsigned i = 0; i < size; i++) {
        result[i] = -leftHandSide[i];
    }

    return result;
}

/**
 *  @brief  Calculate the L2 Norm of @p leftHandSide.
 *
 *  @param  leftHandSide The vector to find the L2 Norm for.
 *
 *  @return The L2 Norm.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <class T>
T norm(const Vector<T>& leftHandSide) {
    T sum = 0;

    for (const auto& element : leftHandSide) {
        sum += element * element;
    }

    return static_cast<T>(sqrt(sum));
}

/**
 *  @brief  Determine if two vectors are equal, element-wise.
 *
 *  @param  leftHandSide The first vector to compare.
 *  @param  rightHandSide The second vector to compare.
 *
 *  @return `true` if the vectors are equal, `false` otherwise.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
bool operator==(const Vector<T>& leftHandSide, const Vector<T>& rightHandSide) {
    if (leftHandSide.size() != rightHandSide.size()) {
        return false;
    }

    auto size = leftHandSide.size();
    auto precision = std::max(leftHandSide.precision, rightHandSide.precision);

    for (unsigned i = 0; i < size; i++) {
        if (std::abs(leftHandSide[i] - rightHandSide[i]) >= precision) {
            return false;
        }
    }

    return true;
}

/**
 *  @brief  Determine if two vectors are not equal, element-wise.
 *
 *  @param  leftHandSide The first vector to compare.
 *  @param  rightHandSide The second vector to compare.
 *
 *  @return `true` if the vectors are the same, `false` otherwise.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
bool operator!=(const Vector<T>& leftHandSide, const Vector<T>& rightHandSide) {
    return !(leftHandSide == rightHandSide);
}

/**
 *  @brief  Multiply two vectors.
 *
 *  @param  leftHandSide The left hand side of the equation.
 *  @param  rightHandSide The right hand side of the equation.
 *
 *  @throws MistmatchedDimensionsError If @p leftHandSide and @p rightHandSide are not the same size.
 *
 *  @return The scalar result from the vector multiplication.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
T operator*(const Vector<T>& leftHandSide, const Vector<T>& rightHandSide) {
    if (leftHandSide.size() != rightHandSide.size()) {
        throw MistmatchedDimensionsError();
    }

    auto size = rightHandSide.size();
    auto result = T();

    for (unsigned i = 0; i < size; i++) {
        result += leftHandSide[i] * rightHandSide[i];
    }

    return result;
}

/**
 *  @brief  Add two vectors.
 *
 *  @param  leftHandSide The left hand side of the equation.
 *  @param  rightHandSide The right hand side of the equation.
 *
 *  @throws MistmatchedDimensionsError If @p leftHandSide and @p rightHandSide are not the same size.
 *
 *  @return The resultant from applying the addition operation.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
Vector<T> operator+(const Vector<T>& leftHandSide, const Vector<T>& rightHandSide) {
    if (leftHandSide.size() != rightHandSide.size()) {
        throw MistmatchedDimensionsError();
    }

    auto size = rightHandSide.size();
    auto result = Vector<T>(size);

    for (unsigned i = 0; i < size; i++) {
        result[i] = leftHandSide[i] + rightHandSide[i];
    }

    return result;
}

/**
 *  @brief  Subtract two vectors.
 *
 *  @param  leftHandSide The left hand side of the equation.
 *  @param  rightHandSide The right hand side of the equation.
 *
 *  @throws MistmatchedDimensionsError If @p leftHandSide and @p rightHandSide are not the same size.
 *
 *  @return The resultant from applying the subtraction operation.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
Vector<T> operator-(const Vector<T>& leftHandSide, const Vector<T>& rightHandSide) {
    if (leftHandSide.size() != rightHandSide.size()) {
        throw MistmatchedDimensionsError();
    }

    auto size = rightHandSide.size();
    auto result = Vector<T>(size);

    for (unsigned i = 0; i < size; i++) {
        result[i] = leftHandSide[i] - rightHandSide[i];
    }

    return result;
}

/**
 *  @brief  Multiply a vector by a scalar.
 *
 *  @param  scalar The scalar to multiply the vector by.
 *  @param  vector The vector to multiply the scalar by.
 *
 *  @return The resultant from applying the multiplication operation.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
void Vector<T>::operator*=(const T& scalar) {
    for (unsigned i = 0; i < this -> _size; i++) {
        data[i] *= scalar;
    }
}

/**
 *  @brief  Add two vectors.
 *
 *  @param  leftHandSide The left hand side of the equation, the `Vector` to assign to.
 *  @param  rightHandSide The right hand side of the equation.
 *
 *  @throws MistmatchedDimensionsError If @p leftHandSide and @p rightHandSide are not the same size.
 *
 *  @return The resultant from applying the multiplication operation.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
void Vector<T>::operator+=(const Vector<T>& rightHandSide) {
    *this = std::move(*this + rightHandSide);
}

/**
 *  @brief  Subtract two vectors, follow by assigning one to another.
 *
 *  @param  leftHandSide The left hand side of the equation, the `Vector` to assign to.
 *  @param  rightHandSide The right hand side of the equation.
 *
 *  @throws MistmatchedDimensionsError If @p leftHandSide and @p rightHandSide are not the same size.
 *
 *  @return The resultant from applying the subtraction operation.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
void Vector<T>::operator-=(const Vector<T>& rightHandSide) {
    *this = std::move(*this - rightHandSide);
}

/**
 *  @brief  Multiply a vector by a scalar.
 *
 *  @param  scalar The scalar to multiply the vector by.
 *  @param  vector The vector to multiply the scalar by.
 *
 *  @return The resultant from applying the multiplication operation.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
Vector<T> operator*(const T& scalar, const Vector<T>& vector) {
    auto size = vector.size();
    auto result = Vector<T>(size);

    for (unsigned i = 0; i < size; i++) {
        result[i] = scalar * vector[i];
    }

    return result;
}

/**
 *  @brief  Return the element at @p index.
 *
 *  @param  index The element (zero indexed) to return.
 *
 *  @warning If the index is not 0 => index > size, an `OutOfBoundsError` exception
 *           is thrown.
 *
 *  @throws  OutOfBoundsError If the value is outsize of the bounds.
 *
 *  @return  The element as a reference.
 *
 *  @pre    See `warning`.
 *  @post   See `return`.
 **/
template <typename T>
T& Vector<T>::operator[](int index) {
    if (index >= static_cast<int>(_size) || index < 0) {
        throw OutOfBoundsError(index);
    }

    return this -> data[index];
}

/**
 *  @brief  Return the element at @p index.
 *
 *  @param  index The element (zero indexed) to return.
 *
 *  @warning If the index is not 0 => index > size, an `OutOfBoundsError` exception
 *           is thrown.
 *
 *  @throws  OutOfBoundsError If the value is outsize of the bounds.
 *
 *  @return  The element as a `const` reference.
 *
 *  @pre    See `warning`.
 *  @post   See `return`.
 **/
template <typename T>
const T& Vector<T>::operator[](const int index) const {
    if (index >= static_cast<int>(_size) || index < 0) {
        throw OutOfBoundsError(index);
    }

    return this -> data[index];
}

/**
 *  @brief  Return a pointer to the beginning of @p vector.
 *
 *  @param  vector The vector to return a pointer to the beginning of to.
 *
 *  @return A pointer to the beginning of @p vector.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
T* begin(const Vector<T> vector) {
    return vector.data.get();
}

/**
 *  @brief  Return a pointer to the end of @p vector.
 *
 *  @param  vector The vector to return a pointer to the end of to.
 *
 *  @return A pointer to the end of @p vector.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
T* end(const Vector<T> vector) {
    return vector.data.get() + vector.size();
}


/**
 *  @brief Insert a string description of a **row Vector** into a stream.
 *
 *  @tparam T T must have the insertion operator defined.
 *
 *  @param os The stream to put a string description of the Vector into.
 *
 *  @param object The polar pair to generate a string description from.
 *
 *  @return The stream with the string description of the @p object in it.
 *
 *  @pre `@tparam`.
 *  @post See `return`.
 **/
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& other) {
    os << std::setprecision(other.precision) << std::fixed;

    for (unsigned i = 0; i < other.size(); i++) {
        os << "[" << other[i] << "]\n";
    }

    return os;
}

#endif /* vector_hpp */
