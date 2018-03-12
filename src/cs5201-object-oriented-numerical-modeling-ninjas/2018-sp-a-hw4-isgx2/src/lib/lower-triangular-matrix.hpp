//
//  lower-triangular-matrix.hpp
//  lib
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef lower_triangular_matrix_hpp
#define lower_triangular_matrix_hpp

/**
 *  @brief  Create a LowerTriangularMatrix of dimensions 0 x 0.
 *
 *  @pre    None.
 *  @post   None.
 **/
template <typename T>
LowerTriangularMatrix<T>::LowerTriangularMatrix() {
    this -> size = 0;
    this -> data = Vector<Vector<T>>();
}

/**
 *  @brief  Create a LowerTriangularMatrix of dimensions @p size x @p size.
 *
 *  @param  size The dimension of the matrix(@p size x @p size).
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(const int size) {
    this -> size = size;

    this -> data = Vector<Vector<T>>(size);
    for (int i = 0; i < this -> size; i++) {
        this -> data[i] = Vector<T>(i + 1);
    }
}

/**
 *  @brief  Create a LowerTriangularMatrix with dimensions @p size x @p size
 *          initial values @p initialValue.
 *
 *  @param  size The dimension of the matrix(@p size x @p size).
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(const int size, const T& initialValue) {
    this -> size = size;

    this -> data = Vector<Vector<T>>(size);
    for (int i = 0; i < this -> size; i++) {
        this -> data[i] = Vector<T>(i + 1, initialValue);
    }
}

/**
 *  @brief  Construct a LowerTriangularMatrix from an Initializer List.
 *
 *  @param  list The Initializer List to get the elements from.
 *
 *  @warning As this is a LowerTriangularMatrix, the Initializer List must also be in the form of a lower triangular matrix.
 * 
 *  @throws  ImproperArgument If the one of the lists are not in lower triangular form.
 *
 *  @pre    See `warning`.
 *  @post   See `brief`.
 **/
template <typename T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(const std::initializer_list<std::initializer_list<T>> list) {
    this -> size = list.size();
    this -> data = Vector<Vector<T>>(list.size());

    auto index = 0;
    for (auto& sublist : list) {
        if (static_cast<int>(sublist.size()) > index + 1) {
            throw ImproperArgument(list);
        }

        this -> data[index] = sublist;
        index++;
    }
}

/**
 *  @brief  Construct a LowerTraingularMatrix from @p other.
 *
 *  @param  other The LowerTriangularMatrix to get data from.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(const LowerTriangularMatrix& other) {
    this -> size = other.size;
    this -> data = other.data;
}

/**
 *  @brief  Destructor for the LowerTraingularMatrix.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
LowerTriangularMatrix<T>::~LowerTriangularMatrix() {}

/**
 *  @brief  Construct a Vector from @p other via assignment.
 *
 *  @return A reference to this.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
LowerTriangularMatrix<T>& LowerTriangularMatrix<T>::operator=(const LowerTriangularMatrix<T>& other) {
    if (this != &other) {
        this -> size = other.size;
        this -> data = other.data;
    }

    return *this;
}

/**
 *  @brief  Construct a Vector from @p other via move semantics.
 *
 *  @return A reference to this.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/

template <typename T>
LowerTriangularMatrix<T>& LowerTriangularMatrix<T>::operator=(const LowerTriangularMatrix<T>&& other) {
    if (this != &other) {
        this -> size = other.size;
        this -> data = std::move(other.data);
    }

    return *this;
}

/**
 *  @brief  Return the Vector at @p index.
 *
 *  @param  index The element (zero indexed) to return.
 *
 *  @warning If the index is not 0 => index > size, an `OutOfBounds` exception
 *           is thrown.
 *
 *  @return  The element as a reference.
 *
 *  @pre    See `warning`.
 *  @post   See `return`.
 **/
template <typename T>
Vector<T>& LowerTriangularMatrix<T>::operator[](const int index) {
    return this -> data[index];
}

/**
 *  @brief  Return the Vector at @p index.
 *
 *  @param  index The element (zero indexed) to return.
 *
 *  @warning If the index is not 0 => index > size, an `OutOfBounds` exception
 *           is thrown.
 *
 *  @return  The element as a `const` reference.
 *
 *  @pre    See `warning`.
 *  @post   See `return`.
 **/
template <typename T>
const Vector<T>& LowerTriangularMatrix<T>::operator[](const int& index) const {
    return this -> data[index];
}

#endif /* lower-triangular-matrix_hpp */
