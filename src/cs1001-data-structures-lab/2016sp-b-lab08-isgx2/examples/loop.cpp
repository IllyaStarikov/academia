#include<iostream>
using namespace std;

struct Pair
{
  int x;
  int y;
};

int main()
{
  Pair arr[6];
  for(int i = 1; i <= 6; i++)
  {
    arr[i-1].x = i;
    arr[i-1].y = 6 - i;
  }

  // Print the array 5 times
  int count;
  while(count < 5)
  {
    for(int i = 0; i < 6; i++)
    {
      cout << "(" << arr[i].x << "," << arr[i].y << ") ";
    }
    cout << endl;
  }

  return 0;
}
