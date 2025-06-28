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

  bool keepGoing = true;
__lineNum__(1);
  int sum = 0;
__lineNum__(2);
  int additions = 0;
__lineNum__(3);
  int maxSum = 9;
__lineNum__(4);
  int maxAdditions = 6;
__lineNum__(5);
  int increment = 3;
__lineNum__(6);

  WHILELOOP1:


    if (sum >= maxSum)
    {
      keepGoing = false;
__lineNum__(7);
    }
    else
    {
      if (additions >= maxAdditions)
      {
        keepGoing = false;
__lineNum__(8);
      }
      else
      {
        sum += increment;
__lineNum__(9);
        additions++;
__lineNum__(10);
      }
    }
  

if (keepGoing) {
  goto WHILELOOP1;
__lineNum__(11);
}


  // Output results

  cout << sum << endl;
__lineNum__(12);
  cout << additions << endl;
__lineNum__(13);

  return(0);
}
