#include <iostream>
using namespace std;

int main()							
{
  int n = 10;	
  int m;
  int sum;
  int previous_power = 0;

  while (n > 0)
  {
    m = 0;
    // following should always be sum = 1
    if (n % 2)
    {
      sum = 1;
    }
    else 
    {
      sum = 2;
    }
    while (sum * 2 <= n)
    {
      sum *= 2;
      m++;
    }
    for (int gap = 1; gap < previous_power - m; gap++)
    {
      cout << 0;
    }
    cout << 1;
    n = n - sum;
    previous_power = m;
  }
  
  for (int trailingZero = m; trailingZero > 0; trailingZero--)
  {
    cout << 0;
  }
  cout << endl;

  return(0);
}
