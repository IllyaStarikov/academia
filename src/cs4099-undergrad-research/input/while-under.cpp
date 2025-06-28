#include <iostream>
using namespace std;

int main()
{
  bool keepGoing = true;
  int sum = 0;
  int additions = 0;
  int maxSum = 9;
  int maxAdditions = 6;
  int increment = 3;

  while (keepGoing)
  {
    if (sum >= maxSum)
    {
      keepGoing = false;
    }
    else
    {
      if (additions >= maxAdditions)
      {
        keepGoing = false;
      }
      else
      {
        sum += increment;
        additions++;
      }
    }
  }

  // Output results

  cout << sum << endl;
  cout << additions << endl;

  return(0);
}
