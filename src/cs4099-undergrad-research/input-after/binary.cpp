#include <fstream>
using namespace std;
bool __fileOpened__ = false;
void __lineNum__(int n);
void __lineNum__(int n)
{
  static ofstream fout;
  if (! __fileOpened__) fout.open("executionTrace.txt");
  fout << n << " ";
  __fileOpened__ = true;
}

#include <iostream>
using namespace std;

int main()							
{__lineNum__(0);

  int n = 10;	
  int m;
__lineNum__(1);
  int sum;
__lineNum__(2);
  int previous_power = 0;
__lineNum__(3);

  WHILELOOP1:


    m = 0;
__lineNum__(4);
    // following should always be sum = 1
    if (n % 2)
    {
      sum = 1;
__lineNum__(5);
    }
    else 
    {
      sum = 2;
__lineNum__(6);
    }
    WHILELOOP2:


      sum *= 2;
__lineNum__(7);
      m++;
__lineNum__(8);
    

if (sum * 2 <= n) {
  goto WHILELOOP2;
__lineNum__(9);
}

    int gap = 1;
__lineNum__(10);
FORLOOP1:


      cout << 0;
__lineNum__(11);
    

 gap++;
__lineNum__(12);
if ( gap < previous_power - m) {
__lineNum__(13);
  goto FORLOOP1;
__lineNum__(14);
}

    cout << 1;
__lineNum__(15);
    n = n - sum;
__lineNum__(16);
    previous_power = m;
__lineNum__(17);
  

if (n > 0) {
  goto WHILELOOP1;
__lineNum__(18);
}

  
  int trailingZero = m;
__lineNum__(19);
FORLOOP2:


    cout << 0;
__lineNum__(20);
  

 trailingZero--;
__lineNum__(21);
if ( trailingZero > 0) {
__lineNum__(22);
  goto FORLOOP2;
__lineNum__(23);
}

  cout << endl;
__lineNum__(24);

  return(0);
}
