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

  int rowSize = 3;
__lineNum__(1);
  int colSize = 2;
__lineNum__(2);
  int a[3][2] = {{1, 2}, {3, 4}, {5, 6}};
__lineNum__(3);
  int b[6] = {0,0,0,0,0,0};
__lineNum__(4);
  int k;
__lineNum__(5);
  int m;
__lineNum__(6);
  int m_last = -1;
__lineNum__(7);

  int i = 0;
__lineNum__(8);
FORLOOP1:


     int j = 0;
__lineNum__(9);
FORLOOP2:


       m = i * rowSize + j; 
       if ((m >= rowSize * colSize) || (m <= m_last))
       {
         m = 1;
__lineNum__(10);
       }
       k = rowSize * colSize - m - 1;
__lineNum__(11);
       b[k] = a[i][j];
__lineNum__(12);
       m_last = m;
__lineNum__(13);
     

 j++;
__lineNum__(14);
if ( j < colSize) {
__lineNum__(15);
  goto FORLOOP2;
__lineNum__(16);
}

  

 i++;
__lineNum__(17);
if ( i < rowSize) {
__lineNum__(18);
  goto FORLOOP1;
__lineNum__(19);
}


  // Output results

  for (int i = 0; i < (rowSize * colSize); i++)
    cout << b[i] << " ";
__lineNum__(20);
  cout << endl;
__lineNum__(21);

  return(0);
}
