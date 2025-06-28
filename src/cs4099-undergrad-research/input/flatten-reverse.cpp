#include <iostream>
using namespace std;

int main()
{
  int rowSize = 3;
  int colSize = 2;
  int a[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  int b[6] = {0,0,0,0,0,0};
  int k;
  int m;
  int m_last = -1;

  for (int i = 0; i < rowSize; i++)
  {
     for (int j = 0; j < colSize; j++)
     {
       m = i * rowSize + j; 
       if ((m >= rowSize * colSize) || (m <= m_last))
       {
         m = 1;
       }
       k = rowSize * colSize - m - 1;
       b[k] = a[i][j];
       m_last = m;
     }
  }

  // Output results

  for (int i = 0; i < (rowSize * colSize); i++)
    cout << b[i] << " ";
  cout << endl;

  return(0);
}
