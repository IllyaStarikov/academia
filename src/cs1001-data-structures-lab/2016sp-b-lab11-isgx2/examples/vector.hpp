// Constructor
template<class T>
Vector<T>::Vector()
{
  sz = 4;
  max = 0;
  array = new T[4];
}

// Copy Constructor
template<class T>
Vector<T>::Vector(const Vector<T>& v)
{
  sz = v.sz;
  max = v.max;
  array = new T[sz];
  for(unsigned int i = 0; i < max; i++)
  {
    array[i] = v.array[i];
  }
}

// Destructor
template<class T>
Vector<T>::~Vector()
{
  delete [] array;
}

// Add elements to the vector
template<class T>
void Vector<T>::push_back(T v)
{
  // Expand vector if needed
  if(max == sz)
  {
    sz = sz * 2;
    T* new_array = new T[sz];
    for(unsigned int i = 0; i < max; i++)
    {
      new_array[i] = array[i];
    }

    delete[] array;
    array = new_array;
  }

  array[max] = v;
  max++;
}

// Read elements of the vector
template<class T>
T& Vector<T>::operator[](const unsigned int idx)
{
  if(idx < 0 || idx >= max)
  {
    throw invalid_argument("Index out of range");
  }

  return array[idx];
}

// length getter
template<class T>
unsigned int Vector<T>::length() const
{
  return max;
}

// size getter
template<class T>
unsigned int Vector<T>::size() const
{
  return sz;
}

