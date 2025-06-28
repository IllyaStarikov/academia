#include<iostream>
using namespace std;

unsigned long fibonnacci(unsigned long n)
{
  if(n == 1)
  {
    return 1;
  }
  if(n == 2)
  {
    return 1;
  }

  return fibonnacci(n-1) + fibonnacci(n-2);
}

int main()
{
  for(unsigned long i = 1; i <= 35; i++)
  {
    cout << fibonnacci(i) << endl;
  }
  return 0;
}