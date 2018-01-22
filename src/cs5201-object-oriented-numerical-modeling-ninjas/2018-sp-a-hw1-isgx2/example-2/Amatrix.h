/*************************************************************
   FileName:    Amatrix.h
   Programmer:  Alex Berry
   Class:       CS328 - Dr. Hilgers
   Assignment:  5 - Matrix / Iterations
   Due:         10/14/2002 for Prog 5 - Matrix

   Desc:
      This file defines the parametrized class Amatrix.

      Most of the functions are not commented they should be
      simple enought to understand.

*************************************************************/

#ifndef AMATRIX_H_42431
#define AMATRIX_H_42431

#include "Avector.h"
#include <assert.h>
#include <iostream>

using std::ostream;
using std::istream;
using std::endl;

#include "signal.h"
#include <cmath>

//#define assert(exp) throw(CSignal("exp"))

typedef int UINT;
typedef const int CUINT;

template<class T>
class Amatrix;

template<typename T>
ostream& operator<<(ostream &, const Amatrix<T>& RHS);
template<typename T>
istream& operator>>(istream &, Amatrix<T>& RHS);

template<class _T>
class Amatrix
{
private:
   _T ** m_matrix;   /* Where the matrix is stored */
   UINT m_row;       /* number of rows */
   UINT m_col;       /* number of cols */
   bool m_del;       /* whether or not to delete memory */

   /*********** Memory Management stuff **************/
   /* Purpose: Allocates the memory for the vector
      Pre:     row and col must be > 0
      Post:    returns a pointer the the allocated memory of size [row][col]
      */
   _T** _MakeMatrix(UINT row,UINT col);

   /* Purpose: Deletes the memory for a matrix
      Pre:     None
      Post:    Deallocates teh memory pointed to by m_matrix and resets m_row
               and m_col to 0
      */
   void _DeleteMatrix();

public:

   /*******************Constructors / Destructors ***********************/
   /* Purpose: Constructor
      Pre:     None
      Post:    creaes a matrix with the give information
      */
   Amatrix(_T** mat,const UINT row,const UINT col,const bool del=true): 
         m_matrix(mat), m_row(row),m_col(col), m_del(del) {} 

   /* Purpose: Default constructor
      Pre:     None
      Post:    Sets member vars to default values
      */
   Amatrix(): m_matrix(NULL), m_row(0), m_col(0), m_del(true) {}

   /* Purpose: Copy constructor
      Pre:     none
      Post:    Copies the amatrix passed to it
      */
   Amatrix(const Amatrix<_T>&);

   /* Purpose: Constructor
      Pre:     row & col > 0
      Post:    makes itself a matrix of size row*col
      */
   Amatrix(CUINT row,CUINT col);

   /* Purpose: Destructor
      Pre:     None
      Post:    Calls _DeleteMatrix to deallocated matrix if needed
      */
   ~Amatrix();

   /************** OPERATORS ******************************************/

   /* Purpose: Matrix multiplicatoin operator
      Pre:     None
      Post:    Returns Amatrix that equals the caller * RHS
      */
   Amatrix<_T> operator *(const Amatrix<_T> & RHS);

   /* Purpose: Matrix-vector multiplication operator
      Pre:     None
      Post:    returns a Avector equal to caller * RHS
      */
   Avector<_T> operator *(const Avector<_T> & RHS);

   /* Purpose: Matrix = operator
      Pre:     None
      Post:    Sets the caller equal to the RHS
      */
   Amatrix<_T>& operator=(const Amatrix<_T> & RHS);

   /* Purpose: Matrix + operator
      Pre:     None
      Post:    Returns a Amatrix equal to the caller + RHs
      */
   Amatrix<_T> operator+(const Amatrix<_T> & RHS);

   /* Purpose: Matrix - operator
      Pre:     None
      Post:    Returns a Amatrix equal to the caller - RHs
      */
   Amatrix<_T> operator-(const Amatrix<_T> & RHS);
   Amatrix<_T> operator+(const _T RHS);
   Amatrix<_T> operator-(const _T RHS);
   Amatrix<_T> operator*(const _T RHS);

   /* Purpose: Matrix [] operator
      Pre:     None
      Post:    returns a pointer to the row at i
      */
   _T* operator[](CUINT i);
   _T* operator[](CUINT i)const;
   _T& operator()(CUINT i,CUINT j,_T nval)
   { return (((*this)[i][j])=nval); }
   _T& operator()(CUINT i,CUINT j)
   { return (*this)[i][j]; }

   /* Purpose: Logical equality operator
      Pre:     None
      Post:    true if the matricies are equal
      */
   bool operator==(const Amatrix<_T> & RHS)const;

   /* Purpose: IO Stream Input operator
      Pre:     None
      Post:    Inputs the vector from the input stream
      */
   friend istream& operator>> <>(istream &,Amatrix<_T> & RHS);

   /* Purpose: IO Stream Output operator
      Pre:     None
      Post:    Outputs teh vector to the output stream
      */
   friend ostream& operator<< <>(ostream &,const Amatrix<_T> & RHS); 
   

   /****************** OTHER OPERATIONS ************************/
   /* Purpose: Sum of the abs values of the elements in teh row
      Pre:     None
      Post:    returns a vector that holds the sum of the abs values
               of each row of the matrix
      */
   Avector<_T> RowSums()const;

   /* Purpose: Erases the current matrix and resizes it to row*col
      Pre:     none
      Post:    matrix has been resized to row*col
      */
   void EraseAndReSize(CUINT row, CUINT col);
   void ReSize(CUINT row, CUINT col) { EraseAndReSize(row,col); }

   /* Purpose: Row sum Matrix Norm
      Pre:     none
      Post:    Returns the max of sum of abs values of the rows.
      */
   _T RowSumNorm()const;

   /* Purpose: GEt the Number of rows
      Pre:     None
      Post:    returns the number of rows
      */
   UINT  getNumRows()const { return m_row; }

      /* Purpose: GEt the Number of colss
      Pre:     None
      Post:    returns the number of cols
      */
   UINT  getNumCols()const { return m_col; }

   /* Purpose: Find the larges eigen value of a matrix
      Pre:     Matrix is square - can break if eigen values are close
      Post:    Returns the largest eigen vale
      */
   _T LargestEigenValue();
};

template<class _T>
Amatrix<_T>::Amatrix(const Amatrix<_T> & RHS)
{
      /*  Make the matricies equal */
   m_row=RHS.m_row;
   m_col=RHS.m_col;
   m_del=true;
   m_matrix=_MakeMatrix(m_row,m_col);

   for(int i=0;i<m_row;i++)
      for(int j=0;j<m_col;j++)
         m_matrix[i][j]=RHS.m_matrix[i][j];
}

template<class _T>
Amatrix<_T>::Amatrix(CUINT row,CUINT col)
{
   m_row=row;
   m_col=col;
   m_del=true;
   m_matrix=_MakeMatrix(row,col);
}

template<class _T>
Amatrix<_T>::~Amatrix()
{
   if(m_del)
      _DeleteMatrix();
}

template<class _T>
_T** Amatrix<_T>::_MakeMatrix(CUINT row,CUINT col)
{
      /* allocating the memory for the matrix */
   _T** temp;
   assert((row >0) && (col >0));
   
   temp= new _T*[row];
   for(int i=0;i<static_cast<int>(row);i++)
      temp[i]=new _T[col];

   return temp;
}

template<class _T>
void Amatrix<_T>::_DeleteMatrix()
{
      /* deleting the memory of the matrix if it exists */
   if(m_matrix==NULL)
      return;

   for(int i=0;i<static_cast<int>(m_row);i++)
   {
      if(m_matrix[i])
         delete [] m_matrix[i];
      m_matrix[i]=NULL;
   }
   delete [] m_matrix;
   m_matrix=NULL;
   m_col=m_row=0;
}

template<class _T>
_T* Amatrix<_T>::operator [](CUINT i)
{
      /* return the pointer to the row */
   return m_matrix[i];
}

template<class _T>
_T* Amatrix<_T>::operator [](CUINT i)const
{
      /* return the pointer to the row */
   return m_matrix[i];
}

template<class _T>
Amatrix<_T> Amatrix<_T>::operator*(const Amatrix<_T> & RHS)
{
   assert(m_col == RHS.m_row);

   _T ** temp;
   temp = _MakeMatrix(m_row,RHS.m_col);

      /* Perform the multiplication */
   for(int i=0;i<m_row;i++)
   {
      for(int j=0;j<RHS.m_col;j++)
      {
            /* Initialize each point in the new matrix as it goes */
         temp[i][j]=0;
         for(int k=0;k<m_col;k++)
            temp[i][j]+=m_matrix[i][k]*RHS.m_matrix[k][j];
      }
   }
   return Amatrix<_T>(temp,m_row,RHS.m_col);
}

template<class _T>
Avector<_T> Amatrix<_T>::operator*(const Avector<_T> & RHS)
{
   assert(m_col == RHS.GetDim());

   _T * temp;
   temp = new _T[m_row];
      /* Performt the multiplication (using vector dot product*/
   for(int j=0;j<m_row;j++)
      temp[j]=Avector<_T>(m_matrix[j],m_col,false)*RHS;

   return Avector<_T>(temp,m_row);
}

template<class _T>
Amatrix<_T>& Amatrix<_T>::operator=(const Amatrix<_T> & RHS)
{
      /* Make the matricies equivalent */
   _DeleteMatrix();
   m_row=RHS.m_row;
   m_col=RHS.m_col;
   m_matrix=_MakeMatrix(m_row,m_col);
   for(int i=0;i<m_row;i++)
      for(int k=0;k<m_col;k++)
         m_matrix[i][k]=RHS.m_matrix[i][k];

   return *this;
}

template<class _T>
Amatrix<_T> Amatrix<_T>::operator+(const Amatrix<_T> & RHS)
{
      /* Addup the two matricies if the are of equalivant size */
   assert((m_row==RHS.m_row) && (m_col==RHS.m_col));
   _T ** temp=_MakeMatrix(m_row,m_col);
   for(int i=0;i<m_row;i++)
      for(int k=0;k<m_col;k++)
         temp[i][k]=m_matrix[i][k]+RHS.m_matrix[i][k];

  return Amatrix<_T>(temp,m_row,m_col);
}

template<class _T>
Amatrix<_T> Amatrix<_T>::operator-(const Amatrix<_T> & RHS)
{
      /* subtract the matricies if they are of equalivant size */
   assert((m_row==RHS.m_row) && (m_col==RHS.m_col));
   _T ** temp=_MakeMatrix(m_row,m_col);
   for(int i=0;i<m_row;i++)
      for(int k=0;k<m_col;k++)
         temp[i][k]=m_matrix[i][k]-RHS.m_matrix[i][k];

  return Amatrix<_T>(temp,m_row,m_col);
}

template<class _T>
bool Amatrix<_T>::operator ==(const Amatrix<_T> &RHS)const
{
      /* False if dimensions do not match */
   if((m_row != RHS.m_row) || (m_col != RHS.m_col))
      return false;

   for(int i=0;i<m_row;i++)
   {
      for(int j=0;j<m_col;j++)
      {  /* False if any corresponing elements do not match */
         if(m_matrix[i][j] != RHS.m_matrix[i][j])
            return false;
      }
   }
      /* otherwise it must be true */
   return true;
}

template<class _T>
istream& operator>>(istream &is,Amatrix<_T> & RHS)
{
   for(int i=0;i<RHS.m_row;i++)
      for(int k=0;k<RHS.m_col;k++)
         is>>RHS.m_matrix[i][k];
   return is;
}

template<class _T>
ostream& operator<<(ostream &os,const Amatrix<_T> & RHS)
{     /* output it vector style so i dont have to recod eit */
   for(int i=0;i<RHS.m_row;i++)
      cout<<Avector<_T>(RHS.m_matrix[i],RHS.m_col,false)<<endl;
   return os;
}

template<class _T>
Avector<_T> Amatrix<_T>::RowSums()const
{
      /* Calculate the abs row sums and return it */
   _T* temp=new _T[m_row];
   for(int i=0;i<m_row;i++)
   {
      temp[i]=0;
      for(int j=0;j<m_col;j++)
      {     /* the if-else takes care of abs */
         if(m_matrix[i][j]<0.0)
            temp[i]-=m_matrix[i][j];
         else
            temp[i]+=m_matrix[i][j];
      }
   }
   return Avector<_T>(temp,m_row);
}

template<class _T>
void Amatrix<_T>::EraseAndReSize(CUINT row,CUINT col)
{
   _DeleteMatrix();
   m_row=row;
   m_col=col;
   m_matrix=_MakeMatrix(row,col);
}

template<class _T>
_T Amatrix<_T>::RowSumNorm()const
{
   _T max=0;
      /* Get the row sums */
   Avector<_T> Sum=RowSums();

      /* Get the max */
   for(int i=0;i<m_row;i++)
   {
      if(max<Sum[i])
         max=Sum[i];
   }
   return max;
}

template<class _T>
_T Amatrix<_T>::LargestEigenValue()
{
   assert(m_row==m_col);

   _T temp1=1,temp2,eval=1,ival=-1;
   Avector<_T> x1(m_col),x2(m_col);

   for(int i=0;i<m_col;i++)
      x1[i]=x2[i]=1;

      /* I protects from close eigen values, which make this algorithm
         worthless */
   int i=0;
   while(eval!=ival && i<200)
   {
      x1=operator*(x1);
      temp1=sqrt(x1*x1);
      temp2=sqrt(x2*x2);
      x2=x1;
      ival=eval;
      eval=temp1/temp2;
      i++;
   }
   
   return eval;
}

template<class _T>
Amatrix<_T> Amatrix<_T>::operator+(const _T RHS)
{
      /* Addup the two matricies if the are of equalivant size */
   _T ** temp=_MakeMatrix(m_row,m_col);
   for(int i=0;i<m_row;i++)
      for(int k=0;k<m_col;k++)
         temp[i][k]=m_matrix[i][k]+RHS;

  return Amatrix<_T>(temp,m_row,m_col);
}
template<class _T>
Amatrix<_T> Amatrix<_T>::operator-(const _T RHS)
{
   /* Addup the two matricies if the are of equalivant size */
   _T ** temp=_MakeMatrix(m_row,m_col);
   for(int i=0;i<m_row;i++)
      for(int k=0;k<m_col;k++)
         temp[i][k]=m_matrix[i][k]-RHS;
  
  return Amatrix<_T>(temp,m_row,m_col);
}
template<class _T>
Amatrix<_T> Amatrix<_T>::operator*(const _T RHS)
{
      /* Addup the two matricies if the are of equalivant size */
   _T ** temp=_MakeMatrix(m_row,m_col);
   for(int i=0;i<m_row;i++)
      for(int k=0;k<m_col;k++)
         temp[i][k]=m_matrix[i][k]*RHS;

  return Amatrix<_T>(temp,m_row,m_col);
}

#endif /* AMATRIX_H_42431 */

