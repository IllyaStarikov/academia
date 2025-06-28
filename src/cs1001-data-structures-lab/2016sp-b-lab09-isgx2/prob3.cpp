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
    Vector(const Vector &v)
    {
      sz = v.sz;
      max = v.max;
      
    int* new_array = new int[sz];
    for(int i = 0; i < max; i++)
    {
      new_array[i] = v.array[i];
    }


    array = new_array;
      
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

  for(int i = 0; i < 10; i++)
  {
    vect->push_back(i);
  }

  Vector* copy = new Vector(*vect);

  delete vect;

  for(int i = 0; i < 10; i++)
  {
    cout << (*copy)[i] << endl;
  }
  
  delete copy;
  return 0;
}


