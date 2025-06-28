#include <iostream>
#include "funcs.h"
#include "TrianglePrinter.h"

using namespace std;

int main()
{
    TrianglePrinter t;
	unsigned int i;

    for(i = 0; i < 10; i++)
    {
        cout << factorial(i) << endl;
    }
	
	i = 10;
	
	for (int j = 5; j < 15; j++) {
		cout << combination(i, j) << endl;
		i++;
	}
	
    return 0;
}
