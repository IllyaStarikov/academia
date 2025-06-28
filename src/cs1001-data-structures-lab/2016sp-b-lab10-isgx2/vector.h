#include<stdexcept> // for invalid_argument
using namespace std;

template<class T>
class Vector
{
  public:
    // Constructor
    Vector()
    {
      sz = 4;
      max = 0;
      array = new T[4];
    }

    // Copy Constructor
    Vector(const Vector<T>& v)
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
    ~Vector()
    {
      delete [] array;
    }

    // Add elements to the vector
    void push_back(T v)
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
    T& operator[](const unsigned int idx)
    {
      if(idx < 0 || idx >= max)
      {
        throw invalid_argument("Index out of range");
      }

      return array[idx];
    }

    // length getter
    unsigned int length() const
    {
      return max;
    }

    // size getter
    unsigned int size() const
    {
      return sz;
    }

  private:
    unsigned int sz;
    unsigned int max;
    T* array;
};

