#include<iostream>
using namespace std;

void fibonnacci(unsigned int nums[], unsigned int n)
{
  nums[0] = 1;
  nums[1] = 1;

  for(unsigned int i = 2; i < n; i++)
  {
    nums[i] = nums[i-1] + nums[i-2];
  }

  return;
}

int main()
{
  unsigned int fibs[35];
  fibonnacci(fibs, 35);

  for(unsigned int i = 0; i < 35; i++)
  {
    cout << fibs[i] << endl;
  }

  return 0;
}
