/*************************************************************
   FileName:    Avector.h
   Programmer:  Alex Berry
   Class:       CS328 - Dr. Hilgers
   Assignment:  3 - GramSchmidt / Vector
   Due:         9/23/2002
   Updated:     10/30/2002 for Prog 4 - Mod Gram Schmidt
   Updated:     10/13/2002 for Prog 5 - Matrix

   Desc:
      This file defines the parametrized class Avector.

      Most of the functions are not commented they should be
      simple enought to understand.

*************************************************************/

#ifndef AVECTOR_H_42431
#define AVECTOR_H_42431

#include <iostream>
#include <assert.h>
#include <iomanip>

using namespace std;

//#define assert(exp) throw(CSignal("exp"))

template<class T>
class Avector;

template<typename T>
ostream& operator<<(ostream &,const Avector<T>& RHS);
template<typename T>
istream& operator>>(istream &,Avector<T>& RHS);

template<class T>
class Avector
{
private:
   T * m_vec;     /* This is where the data will be stored */
   int m_dim;     /* This the dimension of the vector */
   bool m_del;

public:

   /* Purpose: Overloaded Const
      Pre:     Valid vec, and associated dim
      Post:    Sets m_vec=vec and m_dim=dim
      */
   Avector(T* vec,int dim,bool del=true): m_vec(vec), m_dim(dim), m_del(del) {} 
   
         /*********** Constructors-Destructors ***********/
   /* Purpose: Default constructor
      Pre:     None
      Post:    Sets vector vars to default values
      */
   Avector(): m_vec(NULL), m_dim(0), m_del(true) {}

   /* Purpose: Constructor - Creates vector of size Dim 
      Pre:     None
      Post:    Creates vector of size dim if dim>0, otherwise
               sets vars to default values
      */
   Avector(int dim): m_vec((dim>0)?new T[dim]:NULL), m_del(true), 
                                 m_dim((dim>0)?dim:0) {}
   
   /* Purpose: Copy Constructor 
      Pre:     None
      Post:    Resizes itself and Copies RHS onto itself
      */
   Avector(const Avector<T> & RHS);

   /* Purpose: Destructor
      Pre:     None
      Post:    Deletes Dynamic Memory 
      */
   ~Avector();

          /************* Operators ***************/
   /* Purpose: operator[] alloes aa[4]=3.0; or cout<<aa[4]; (two versions)
      Pre:     None
      Post:    Returns reference to i'th element of m_vec
      */
   T& operator[](unsigned int i);
   const T& operator[](unsigned int i)const;

   /* Purpose: Assignment Operator 
      Pre:     None
      Post:    Copies size and data of RHS onto itself returns a 
               const reference of itself
      */
   const Avector<T> & operator=(const Avector<T> & RHS);

   /* Purpose: Addition Operator
      Pre:     None
      Post:    Returns sum vector of Adds coresponding elements of 
               2 vectors
      */
   Avector<T> operator+(const Avector<T> & RHS) const;

   /* Purpose: Subtraction Operator
      Pre:     None
      Post:    Returns difference vector of coresponding elements of 
               RHS from itself
      */
   Avector<T> operator-(const Avector<T> & RHS) const;

   /* Purpose: Multiplication operator ( DOT PRODUCT )
      Pre:     None
      Post:    Performs the dot product of itself and the rhs
      */
   T operator*(const Avector<T> & RHS) const;

   /* Purpose: Scalar Addition Operator
      Pre:     None
      Post:    Returns vector in whcih RHS has been added to each 
               element
      */
   Avector<T> operator+(const T & RHS) const;

   /* Purpose: Scalar Subtraction Operator
      Pre:     None
      Post:    Returns vector in whcih RHS has been subtracted from
               each element
      */
   Avector<T> operator-(const T & RHS) const;

   /* Purpose: Scalar Mult Operator
      Pre:     None
      Post:    Returns vector in whcih RHS has been multiplied by
               each element
      */
   Avector<T> operator*(const T & RHS) const;

   /* Purpose: Scalar division operator
      Pre:     None
      Post:    Returns vector in whcih RHS has been divided into each
               element
      */
   Avector<T> operator/(const T & RHS) const;

   /* Purpose: IO Stream Input operator
      Pre:     None
      Post:    Inputs the vector from the input stream
      */
   friend istream& operator>> <>(istream &,Avector<T>& RHS);

   /* Purpose: IO Stream Output operator
      Pre:     None
      Post:    Outputs teh vector to the output stream
      */
   friend ostream& operator<< <>(ostream &,const Avector<T>& RHS);

   /* Purpose: Logically equal operator
      Pre:     None
      Post:    REturns false if dimesions do not match or any two
               corresponding elements not matching
      */
   bool operator==(const Avector<T> & RHS) const;

   /* Purpose: Logically less than operator
      Pre:     None
      Post:    REturns false if dimesions do not match or any two
               corresponding elements not matching
      */
   bool operator<(const Avector<T> & RHS) const;

      /***************** Other Functions ***************/
   /* Purpose: Erases the vector and resizes it
      Pre:     None
      Post:    Vector has be resized to dim
      */
   void EraseAndReSize(int dim);
   /* Purpose: Get Dimension
      Pre:     None
      Post:    Returns the dimension of the vector
      */
   int GetDim()const;
};

template<class T>
Avector<T>::Avector(const Avector<T> & RHS)
{  
   static int counter=1;
   cout<<"Copyconstructor Call#: "<<counter++<<endl; 
      /* Copy dimension and copy data */
   m_dim=RHS.m_dim;
   m_vec=new T[m_dim];
   m_del=true;
      /* Copy the m_vec directly from RHS to this */
   for(int i=0;i<m_dim;i++)
      m_vec[i]=RHS.m_vec[i];

}

template<class T>
Avector<T>::~Avector()
{
   if(m_del &&(m_vec != NULL))
      delete [] m_vec;
}

template<class T>
T& Avector<T>::operator[](unsigned int i)
{
  /* Make sure it is a valid index */
  assert(i < m_dim && i >= 0);
  return m_vec[i];
}
template<class T>
const T& Avector<T>::operator[](unsigned int i)const
{
      /* Make sure it is a valid index */
   assert(i < m_dim && i >= 0);
   return m_vec[i];
}

template<class T>
const Avector<T>& Avector<T>::operator=(const Avector<T> & RHS)
{
   EraseAndReSize(RHS.m_dim);
      /* Copy the m_vec directly from RHS to this */
   for(int i=0;i<m_dim;i++)
      m_vec[i]=RHS.m_vec[i];
   return *this;
}

template<class T>
Avector<T> Avector<T>::operator+(const Avector<T> & RHS)const
{
      /* Check if dimensions match */
   assert(m_dim == RHS.m_dim);
   T *sum=new T[m_dim];
   for(int i=0;i<m_dim;i++)
      sum[i]=m_vec[i]+RHS.m_vec[i];
   return Avector<T>(sum,m_dim);
}

template<class T>
Avector<T> Avector<T>::operator-(const Avector<T> & RHS)const
{
      /* Check if dimensions match */
   assert(m_dim == RHS.m_dim);
   T *dif=new T[m_dim];
   for(int i=0;i<m_dim;i++)
      dif[i]=m_vec[i]-RHS.m_vec[i];
   return Avector<T>(dif,m_dim);
}

template<class T>
T Avector<T>::operator*(const Avector<T> & RHS)const
{
      /* Check if dimensions match */
   assert(m_dim == RHS.m_dim);
   T temp=0.0;
      /* Perform the DOT PRODUCT */
   for(int i=0;i<static_cast<int>(m_dim);i++)
      temp+=m_vec[i]*RHS.m_vec[i];
   return temp;
}

template<class T>
Avector<T> Avector<T>::operator+(const T & RHS)const
{
   T *sum=new T[m_dim];
   for(int i=0;i<m_dim;i++)
      sum[i]=m_vec[i]+RHS;
   return Avector<T>(sum,m_dim);
}

template<class T>
Avector<T> Avector<T>::operator-(const T & RHS)const
{
   T *dif=new T[m_dim];
   for(int i=0;i<m_dim;i++)
      dif[i]=m_vec[i]-RHS;
   return Avector<T>(dif,m_dim);
}

template<class T>
Avector<T> Avector<T>::operator*(const T & RHS)const
{
   T *prod=new T[m_dim];
   for(int i=0;i<m_dim;i++)
      prod[i]=m_vec[i]*RHS;
   return Avector<T>(prod,m_dim);
}

template<class T>
Avector<T> Avector<T>::operator/(const T & RHS)const
{
   T *prod=new T[m_dim];
   for(int i=0;i<m_dim;i++)
      prod[i]=m_vec[i]/RHS;
   return Avector<T>(prod,m_dim);
}

template<class T>
istream& operator>>(istream & is,Avector<T> & RHS)
{
   for(int i=0;i<RHS.m_dim;i++)
      is>>RHS.m_vec[i];
   return is;
}

template<class T>
ostream& operator<<(ostream & os,const Avector<T> & RHS)
{
   os<<"[ ";
   for(int i=0;i<RHS.m_dim;i++)
   {
      os<<setw(2)<<RHS.m_vec[i];
      if(RHS.m_dim != (i+1))
         os<<" | ";         /* Gives Neater Output */
   }
   os<<" ]";
   return os;
}

template<class T>
bool Avector<T>::operator==(const Avector<T> & RHS)const
{
   if(m_dim != RHS.m_dim)
      return false;        /* Fail if dimensions dont match */
   for(int i=0;i<m_dim;i++)
   {
      if(m_vec[i] != RHS.m_vec[i])  /* Fail on first nonmatch element */
         return false;
   }
   return true;
}

template<class T>
bool Avector<T>::operator<(const Avector<T> & RHS)const
{
   if(m_dim != RHS.m_dim)
      return false;        /* Fail if dimensions dont match */
   for(int i=0;i<m_dim;i++)
   {
      if(m_vec[i] >= RHS.m_vec[i])  /* Fail on first > or = element */
         return false;
   }
   return true;
}

template<class T>
void Avector<T>::EraseAndReSize(int dim)
{
   assert(dim > 0);
   m_dim=dim;
   if(m_vec!=NULL)
      delete [] m_vec;
   m_vec=new T[dim];
}

template<class T>
int Avector<T>::GetDim()const
{
   return m_dim;
}

#endif /* AVECTOR_H_42431 */

