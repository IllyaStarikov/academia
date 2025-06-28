#include <iostream>
using namespace std;

int main()
{
  int arraySize = 3;
  int a[3] = {1, -1, 2};		
  int sum;
  bool solutionFound;
  int sequenceSize;
  int start = 0;
  int solutionStartAt = 0;
  int solutionSequenceSize = 0;

  solutionFound = false;
  sequenceSize = 1;
  while ((! solutionFound) && (sequenceSize < arraySize))
  {
    while ((! solutionFound) && 
           (start+sequenceSize <= arraySize))
    {
      sum = 0;
      for (int i = start; i < start+sequenceSize; i++)
      {
        sum += a[i];
      }
      if (sum == 0)
      {
        solutionFound = true;
      }
      else
      {
        start++;
      }
    }
    if (solutionFound)
    {
      solutionStartAt = start;
      solutionSequenceSize = sequenceSize;
    } 
    else
    {
      start = arraySize-1;           sequenceSize++;
    }
  }

  cout << "start = " << solutionStartAt 
       << " sequence length = " 
       << solutionSequenceSize << endl;

  return(0);
}
