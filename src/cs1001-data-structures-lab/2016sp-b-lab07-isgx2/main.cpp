#include <iostream>
#include "funcs.h"
#include "TrianglePrinter.h"

using namespace std;

int main()
{
    TrianglePrinter t;

    for(unsigned int i = 0; i < 10; i++)
    {
        cout << factorial(i) << endl;
    }


    for(unsigned int n = 0; n <=15; n++)
    {
      for(unsigned int m = 0; m <= n; m++)
      {
        t.add(factorial(n) / (factorial(m) * factorial(n-m)));
      }

      t.newrow();
    }

    t.print();

    return 0;
}
