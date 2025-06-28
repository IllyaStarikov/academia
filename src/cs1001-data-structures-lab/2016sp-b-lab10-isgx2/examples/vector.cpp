#include<iostream>
#include<stdexcept> // for invalid_argument
using namespace std;

class Vector
{
  public:
    // Constructor
    Vector()
    {
      sz = 4;
      max = 0;
      array = new int[4];
    }

    // Copy Constructor
    Vector(const Vector& v)
    {
      sz = v.sz;
      max = v.max;
      array = new int[sz];
      for(int i = 0; i < max; i++)
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
    void push_back(int v)
    {
      // Expand vector if needed
      if(max == sz)
      {
        sz = sz * 2;
        int* new_array = new int[sz];
        for(int i = 0; i < max; i++)
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
    int& operator[](const int idx)
    {
      if(idx < 0 || idx >= max)
      {
        throw invalid_argument("Index out of range");
      }

      return array[idx];
    }

  private:
    int sz;
    int max;
    int* array;
};

int main()
{
  Vector* vect = new Vector;

  cout << "Allocating some memory..." << endl;

  for(int i = 0; i < 100000; i++)
  {
    vect->push_back(i);
  }

  cout << "Okay now freeing it..." << endl;

  delete vect;
}

