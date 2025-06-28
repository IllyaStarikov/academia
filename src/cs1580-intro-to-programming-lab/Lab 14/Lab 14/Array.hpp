// Programmer: Illya Starikov
// Section: 3E
// File: Array.hpp
// Description: To calculate with arrays.

#include <fstream>

const int SIZE_OF_ARRAY = 4;
const int DEFAULT_ARRAY_VALUE = 0;

template <class T>
Array_Class<T>::Array_Class(T m_0, T m_1, T m_2, T m_3)
{
    m[0] = m_0;
    m[1] = m_1;
    m[2] = m_2;
    m[3] = m_3;
}

template <class T>
Array_Class<T>::Array_Class(T m_array[])
{
    for (int i = 0; i < SIZE_OF_ARRAY; ++i)
    {
        m[i] = m_array[i];
    }
}

template <class T>
Array_Class<T>::Array_Class()
{
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
    {
        m[i] = DEFAULT_ARRAY_VALUE;
    }
}

template <class T>
Array_Class<T> Array_Class<T>::operator *=
(const Array_Class<T> & rhs)
{
    for (int i = 0; i < SIZE_OF_ARRAY; i ++)
    {
        m[i] *= rhs.m[i];
    }

    return *this;
}


// FRIENDS
template <class T>
Array_Class<T> operator + (const Array_Class<T> & lhs,
    const Array_Class<T> & rhs)
{
    Array_Class<T> returnArray;

    for (int i = 0; i < SIZE_OF_ARRAY; i ++)
    {
        returnArray.m[i] = lhs.m[i] + rhs.m[i];
    }

    return returnArray;
}

template <class T>
ostream & operator<< (ostream & stream, const Array_Class<T> &array)
{
    stream << "| ";
    for (int i = 0; i < SIZE_OF_ARRAY; i ++)
    {
        stream << array.m[i] << ", ";
    }
    stream << " |" << endl;

    return stream;
}