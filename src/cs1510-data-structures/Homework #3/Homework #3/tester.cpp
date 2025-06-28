#include <iostream>
#include "linkedlist.h"

using namespace std;


//---------------------------------------------------------------------
void test01() {
  
  LinkedList < int > A;
  
  cout << endl << endl; 
  cout << " ***************** " << endl;
  cout << " *  TEST SET #1  * " << endl;
  cout << " ***************** " << endl;


  cout << "Is the list empty? " << boolalpha << A.isEmpty() <<endl; 
  cout << A << endl;
  cout << "Size of A = " << A.size() << endl;


  //TEST : Inserting 10 numbers to a
  cout << endl << "TEST : Inserting 10 numbers to A" << endl;
  for (int k=0; k<10; k++){
    A.insert_front(k+1);
  } 
  cout << A << endl;
  cout << "Size of a = " << A.size() << endl;

  //TEST : Clearing A
  cout << endl << "TEST : Clearing A" << endl;
  A.clear();
  cout << A << endl;
  cout << "Size of A = " << A.size() << endl << endl;


  cout << "Test 01 - Done!" << endl;
} 



//---------------------------------------------------------------------
void test02() {
  
  LinkedList <int> A;
  LinkedList <int>* p;
  
  cout << endl << endl; 
  cout << " ***************** " << endl;
  cout << " *  TEST SET #2  * " << endl;
  cout << " ***************** " << endl;

  //TEST : Inserting 13 numbers to a
  cout << endl << "TEST : Inserting 13 numbers into A" << endl;
  for (int k=0; k<13; k++){
    A.insert_front(k*2);
  } 
  cout << A << endl;
  cout << "Size of a = " << A.size() << endl;

  // TEST : Acessing elements;
  cout << endl << "TEST : Accessing elements" << endl;
  p = A.getFirstPtr();
  cout << "First = " << p->m_data << endl;
  p = A.getLastPtr();
  cout << "Last = " << p->m_data << endl;
  p = A.getAtPtr(5);
  cout << "5th = " << p->m_data << endl;
  

  //TEST : Clearing A
  cout << endl << "TEST : Clearing A" << endl;
  A.clear();
  cout << A << endl;
  cout << "Size of A = " << A.size() << endl << endl;
  

  cout << "Test 02 - Done!" << endl;
} 



//---------------------------------------------------------------------
void test03() {
  
  LinkedList <char> A;
  LinkedList <char>* p;
  int ix;
  
  cout << endl << endl; 
  cout << " ***************** " << endl;
  cout << " *  TEST SET #3  * " << endl;
  cout << " ***************** " << endl;

  //TEST : Inserting 10 elements to a
  cout << endl << "TEST : Inserting 10 elements into A" << endl;
  for (int k=0; k<10; k++){
    A.insert_front(k+'a');
  } 
  cout << A << endl;
  cout << "Size of a = " << A.size() << endl;

  // TEST : Inserting elements;
  cout << endl << "TEST : Inserting elements at 5 and 7" << endl;
  p = A.getAtPtr(5); 
  A.insert('w', p);
  p = A.getAtPtr(7);
  A.insert('w', p);
  cout << A << endl;

  // TEST : Removing elements;
  cout << endl << "TEST : Removing elements 4 and 8" << endl;
  p = A.getAtPtr(4);
  A.remove(p);
  p = A.getAtPtr(8);
  A.remove(p);
  cout << A << endl;

  
  // TEST : Removing elements;
  cout << endl << "TEST : Finding e" << endl;
  p = A.find('e');
  cout << "e has been found! " << p->m_data << endl;

  
  //TEST : Clearing A
  cout << endl << "TEST : Clearing A" << endl;
  A.clear();
  cout << A << endl;
  cout << "Size of A = " << A.size() << endl << endl;
  

  cout << "Test 03 - Done!" << endl;
} 



//---------------------------------------------------------------------
void test04() {
  
  LinkedList <int> A;
  LinkedList <int> B;
  LinkedList <int> C;
  LinkedList <int>* p;
  int ix;
  
  cout << endl << endl; 
  cout << " ***************** " << endl;
  cout << " *  TEST SET #4  * " << endl;
  cout << " ***************** " << endl;

  //TEST : Inserting 10 elements to a
  cout << endl << "TEST : Inserting 10 elements into A" << endl;
  for (int k=0; k<10; k++){
    A.insert_front(k*10);
  } 
  cout << A << endl;
  cout << "Size of A = " << A.size() << endl;


  //TEST : Inserting 10 elements into b
  cout << endl << "TEST : Inserting 10 elements into B" << endl;
  for (int k=0; k<10; k++){
    B.insert_front(20+k*5);
  } 
  cout << B << endl;
  cout << "Size of B = " << B.size() << endl;

  // TEST : Comparison;
  cout << endl << "TEST : Comparison" << endl;
  cout << "Is A == B ? " << boolalpha << (A == B) << endl;


  // TEST : Operator=
  cout << endl << "TEST : Operator=" << endl;
  C = A;
  cout << "A = " << A << endl;
  cout << "C = " << C << endl;
  cout << "Is A == C ? " << boolalpha << (A == C) << endl;

  cout << endl << "Making sure is a deep copy" << endl;
  C.insert_front(42);
  C.insert_front(43);
  cout << "A = " << A << endl;
  cout << "C = " << C << endl;


  // TEST : Operator=
  cout << endl << "TEST : Copy Constructor" << endl;
  LinkedList<int> D ( A );
  cout << "A = " << A << endl;
  cout << "D = " << D << endl;
  cout << "Is A == D ? " << boolalpha << (A == D) << endl;

  cout << endl << "Making sure is a deep copy" << endl;
  D.insert_front(111);
  D.insert_front(222);
  cout << "A = " << A << endl;
  cout << "D = " << D << endl;


  // TEST : Append
  cout << endl << "TEST : Append B into A" << endl;
  A.append(B);
  cout << A << endl;


  // TEST : Purge;
  cout << endl << "TEST : Reversing A" << endl;
  A.reverse();
  cout << A << endl;

  
  //TEST : Clearing A
  cout << endl << "TEST : Clearing A" << endl;
  A.clear();
  cout << A << endl;
  cout << "Size of A = " << A.size() << endl << endl;

  // Clearing other lists
	B.clear();
	C.clear();
	D.clear();
  cout << "Test 04 - Done!" << endl;
}


//---------------------------------------------------------------------
void test05() {
  
  LinkedList<int> A;
  LinkedList<int>* tmp;
  
  cout << endl << endl; 
  cout << " ***************** " << endl;
  cout << " *  TEST SET #5  * " << endl;
  cout << " ***************** " << endl;


  //TEST : Panics on an empty list
  cout << endl << "TEST : Panics on an empty list" << endl;
  cout << A << endl;
  cout << "Size of A = " << A.size() << endl;
  tmp = A.getFirstPtr();
  cout << "First = " << tmp << endl;
  tmp = A.getLastPtr();
  cout << "Last = " << tmp << endl;

  //TEST : Inserting 10 elements to a
  cout << endl << "TEST : Inserting 10 elements into A" << endl;
  for (int k=0; k<10; k++){
    A.insert_front(k*11);
  } 
  cout << A << endl;
  cout << "Size of A = " << A.size() << endl;


  //TEST : Panics on Invalid Index
  cout << endl << "TEST : Panic on Invalid Index" << endl;
  tmp = A.getAtPtr(99);
  cout << tmp << endl;
  //A.insert(42,99);
  //A.remove(100);

  
  //TEST : Clearing A
  cout << endl << "TEST : Clearing A" << endl;
  A.clear();
  cout << A << endl;
  cout << "Size of A = " << A.size() << endl << endl;

  cout << "Test 05 - Done!" << endl;
} 



int main () {
  
  cout << "Hello World!!, This is the LinkedList LARGE Tester" << endl; 
  
  test01();
  test02();
  test03();
  test04();
  test05();


  cout << "LARGE Done!" << endl;
  return 0;
}
