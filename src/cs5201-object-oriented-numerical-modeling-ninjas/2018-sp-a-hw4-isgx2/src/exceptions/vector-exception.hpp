//
//  vector-exception.hpp
//  exceptions
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//


/**
 *  @brief  Construct an error object from an improper argument @p argument.
 *
 *  @param  argument The improper argument.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
ImproperArgument<T>::ImproperArgument(T argument) {
    this -> argument = argument;
}

/**
 *  @brief  Generate a string description of the error object.
 *
 *  @return A string description of the error object.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
const std::string ImproperArgument<T>::what() const {
    auto ss = std::stringstream();
    ss << "Improper argument passed with " << this -> argument << ".";

    return ss.str();
}
