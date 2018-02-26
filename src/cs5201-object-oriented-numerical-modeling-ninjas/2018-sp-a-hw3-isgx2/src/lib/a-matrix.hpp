//
//  a-matrix.hpp
//  lib
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//


/**
 *  @brief Insert a string description of a square matrix into a stream.
 *
 *  @param os The stream to put a string description of the Square
 *         Matrix into.
 *
 *  @param object The polar pair to generate a string description from.
 *
 *  @return The stream with the string description of the @p object in it.
 *
 *  @pre None.
 *  @post See `return`.
 **/
template <typename T>
std::ostream& operator<<(std::ostream& os, const SquareMatrix<T>& object) {
    for (int row = 0; row < object.magnitude(); row ++) {
        os << "| ";
        for (int column = 0; column < object[row].magnitude(); column++) {
            os << object[row][column] << " ";
        }
        os << "|\n";
    }

    return os;
}

/**
 *  @brief  Get the Main Diagonal as a Vector<T>.
 *
 *  @return A `Vector<T>` where all entries are the diagonal.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
const Vector<T> SquareMatrix<T>::mainDiagonal() {
    auto vector = Vector<T>(this -> size);

    for (int i = 0; i < this -> size; i++) {
        vector[i] = data[i][i];
    }

    return vector;
}

