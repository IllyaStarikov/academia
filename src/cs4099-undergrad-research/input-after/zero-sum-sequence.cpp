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

  int arraySize = 3;
__lineNum__(1);
  int a[3] = {1, -1, 2};		
  int sum;
__lineNum__(2);
  bool solutionFound;
__lineNum__(3);
  int sequenceSize;
__lineNum__(4);
  int start = 0;
__lineNum__(5);
  int solutionStartAt = 0;
__lineNum__(6);
  int solutionSequenceSize = 0;
__lineNum__(7);

  solutionFound = false;
__lineNum__(8);
  sequenceSize = 1;
__lineNum__(9);
  WHILELOOP1:


    while ((! solutionFound) && 
           (start+sequenceSize <= arraySize))
    {
      sum = 0;
__lineNum__(10);
      int i = start;
__lineNum__(11);
FORLOOP1:


        sum += a[i];
__lineNum__(12);
      

 i++;
__lineNum__(13);
if ( i < start+sequenceSize) {
__lineNum__(14);
  goto FORLOOP1;
__lineNum__(15);
}

      if (sum == 0)
      {
        solutionFound = true;
__lineNum__(16);
      }
      else
      {
        start++;
__lineNum__(17);
      }
    }
    if (solutionFound)
    {
      solutionStartAt = start;
__lineNum__(18);
      solutionSequenceSize = sequenceSize;
__lineNum__(19);
    } 
    else
    {
      start = arraySize-1;           sequenceSize++;
__lineNum__(20);
    }
  

if ((! solutionFound) && (sequenceSize < arraySize)) {
  goto WHILELOOP1;
__lineNum__(21);
}


  cout << "start = " << solutionStartAt 
       << " sequence length = " 
       << solutionSequenceSize << endl;
__lineNum__(22);

  return(0);
}
