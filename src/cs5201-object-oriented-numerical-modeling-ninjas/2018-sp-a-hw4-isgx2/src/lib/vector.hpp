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
    this -> size = 0;
    this -> data = nullptr;
}

/**
 *  @brief  An explicit constructor that takes a @p size and
 *          initialize the vector with said @p size.
 *
 *  @param  size The desired size of the Vector.
 * 
 *  @throws  ImproperArgument If the size is not positive.
 *
 *  @warning If the size is less than one, an error will be thrown.
 *
 *  @pre    See `warning`.
 *  @post   None.
 **/
template <typename T>
Vector<T>::Vector(const int size) {
    if (size <= 0) {
        throw ImproperArgument("size");
    }

    this -> size = size;
    this -> data = std::unique_ptr<T[]>(new T[size]);
}

/**
 *  @brief  An explicit constructor that takes a @p size and
 *          initialize the vector with said @p size with
 *          @p initial value @p initialValue.
 *
 *  @param  size The desired size of the Vector.
 *  @param  initialValue The desired initial value of all the entires.
 *
 *  @throws  ImproperArgument If the size is not positive.
 *
 *  @warning If the size is less than one, an error will be thrown.
 *
 *  @pre    See `warning`.
 *  @post   None.
 **/
template <typename T>
Vector<T>::Vector(const int size, const T& initialValue) {
    if (size <= 0) {
        throw ImproperArgument("size");
    }

    this -> size = size;
    data = std::unique_ptr<T[]>(new T[size]);

    for (int i = 0; i < size; i++) {
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
    this -> size = list.size();
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
    this -> size = other.size;
    this -> data = std::unique_ptr<T[]>(new T[other.size]);

    std::copy(other.data.get(), other.data.get() + other.size, this -> data.get());
}

/**
 *  @brief  Construct a vector by `move`ing it.
 *
 *  @param  other The vector to steal data from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
Vector<T>::Vector(Vector&& other) {
    this -> size = other.size;
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
 *  @brief  Construct a vector from @p other via move semantics.
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
        this -> size = other.size;
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
        this -> size = other.size;
        this -> data = std::unique_ptr<T[]>(new T[other.size]);

        std::copy(other.data.get(), other.data.get() + other.size, this -> data.get());
    }

    return *this;
}

/**
 *  @brief  Return the element at @p index.
 *
 *  @param  index The element (zero indexed) to return.
 *
 *  @warning If the index is not 0 => index > size, an `OutOfBounds` exception
 *           is thrown.
 *
 *  @throws  OutOfBounds If the value is outsize of the bounds.
 *
 *  @return  The element as a reference.
 *
 *  @pre    See `warning`.
 *  @post   See `return`.
 **/
template <typename T>
T& Vector<T>::operator[](int index) {
    if (index >= size || index < 0) {
        throw OutOfBounds(index);
    }

    return this -> data[index];
}

/**
 *  @brief  Return the element at @p index.
 *
 *  @param  index The element (zero indexed) to return.
 *
 *  @warning If the index is not 0 => index > size, an `OutOfBounds` exception
 *           is thrown.
 * 
 *  @throws  OutOfBounds If the value is outsize of the bounds.
 *
 *  @return  The element as a `const` reference.
 *
 *  @pre    See `warning`.
 *  @post   See `return`.
 **/
template <typename T>
const T& Vector<T>::operator[](const int index) const {
    if (index >= size || index < 0) {
        throw OutOfBounds(index);
    }

    return this -> data[index];
}


/**
 *  @brief Insert a string description of a **row Vector** into a stream.
 *
 *  @tparam S S must have the insertion operator defined.
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
template <typename S>
std::ostream& operator<<(std::ostream& os, const Vector<S>& other) {
    os << std::setprecision(other.precision) << std::fixed;

    for (int i = 0; i < other.magnitude() - 1; i++) {
        os << other[i] << " ";
    }

    os << other[other.magnitude() - 1];
    return os;
}

#endif /* vector_hpp */

