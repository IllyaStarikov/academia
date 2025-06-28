#include <iostream>
#include "arraylist.h"

using namespace std;
/*

// ---------------------------------------------------------
void test01()
{
  ArrayList<int> a;

  cout << endl << endl; 
  cout << " ***************** " << endl;
  cout << " *  TEST SET #1  * " << endl;
  cout << " ***************** " << endl;
 
  
  cout << "List a  is empty" << endl; 
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;
  
  //TEST : Inserting 10 numbers to a
  cout << endl << "TEST : Inserting 10 numbers to a" << endl;
  for (int k=0; k<10; k++){
    a.insert_back(k+1);
  } 
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;

  
  //TEST : Inserting elements in the middle
  cout << endl << "TEST : Inserting elements in the middle" << endl;
  for (int k=5; k<12; k++){
    a.insert(k+10, k);
  }
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;
  
  // TEST : Acessing individual elements;
  cout << endl << "TEST : Acessing individual elements" << endl;
  cout << "a.first() = " << a.first() << endl;
  cout << "a[5] = " << a[5] << endl;
  cout << "a[10] = " << a[10] << endl;
  cout << "a[13] = " << a[13] << endl;
  
  
  // TEST : Changing elements
  cout << endl << "TEST : Changing elements" << endl;
  for (int k=0; k<a.size(); k++){
    a[k] = a[k] * 5;
  }
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;

} // Destructor Called Here!!



// ---------------------------------------------------------
void test02()
{
  ArrayList<int> a;
  
  cout << endl << endl;
  cout << " ***************** " << endl;
  cout << " *  TEST SET #2  * " << endl;
  cout << " ***************** " << endl;

  cout << "ArrayList a" << endl;
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;

  //TEST : Inserting 8 elements to a
  cout << endl << "TEST : Inserting 8 elements to a" << endl;
  for (int k=0; k<8; k++){
    a.insert_back(k*8);
  } 
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;


  // TEST : Clearing the list
  cout << endl << "TEST : Clearing a" << endl;
  a.clear();
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;
    
    
  // TEST : Inserting 10 elements
  cout << endl << "TEST : Inserting 10 elements to a" << endl;
  for (int k=0; k<10; k++){
    a.insert_back(k*5);
  } 
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;

  
  // TEST : Removing Elements in the middle
  cout << endl << "TEST : Removing elements" << endl;
  a.remove(2);
  cout << a << endl;
  a.remove(4);  
  cout << a << endl;
  a.remove(6);
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;    


  // TEST : Removing first and last Elements
  cout << endl << "TEST : Removing last and first elements" << endl;
  cout << a << endl;
  a.remove(6);
  cout << a << endl;
  a.remove(0);  
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;    

    
  // TEST : Finding Particular elements  
  cout << endl << "TEST : Finding particular elements" << endl;
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;    
  cout << "15 is at location " << a.find(15) << endl;
  cout << "30 is at location " << a.find(30) << endl;
  cout << "50 is at location " << a.find(50) << endl;
  
  
  // TEST : Shrinking the underlaying array.  
  cout << endl << "TEST : Shrinking the underlaying array" << endl;
  a.clear();
  for (int k=0; k<1000; k++){
    a.insert_back(k*2);
  }   
  cout << "Size of a = " << a.size() << endl;   
  cout << "Capacity of a = " << a.max() << endl;     
  cout << "deleting 950 elements" << endl;
  for (int k=0; k<950; k++){
    a.remove(a.size()-1);
  }
  cout << "Size of a = " << a.size() << endl;   
  cout << "Capacity of a = " << a.max() << endl;
  cout << "so ArrayList is memory efficient :-)" << endl;
  
} // Destructor Called Here!!


// ---------------------------------------------------------
void test03()
{
  ArrayList<char> a;
  ArrayList<char> b;
  
  cout << endl << endl;
  cout << " ***************** " << endl;
  cout << " *  TEST SET #3  * " << endl;
  cout << " ***************** " << endl;
  
  cout << "List a is empty" << endl; 
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;
  
  //TEST : Inserting 10 elements to a
  cout << endl << "TEST : Inserting 10 elements to a" << endl;
  for (int k=0; k<10; k++){
    a.insert_back(static_cast<char>(k+97));
  } 
  cout << a << endl;
  cout << "Size of a = " << a.size() << endl;
  
  //TEST : Operator = 
  cout << endl << "TEST : Operator =" << endl;
  cout << "Before Copy" << endl;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  
  b = a; 
  cout << "After Copy" << endl;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
 
  cout << "changing elements of b (making sure its a deep copy)" << endl;
  b[0] += 10;
  b[1] += 10;
  b[2] += 10;
  b[3] += 10;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  
  //TEST : Copy Constructor 
  cout << endl << "TEST : Copy Constructor" << endl;
  ArrayList<char> c (b);
  cout << "b = " << b << endl;
  cout << "c = " << c << endl;
  cout << "changing elements of c (making sure its a deep copy)" << endl;
  c[0] += 10;
  c[1] += 10;
  c[2] += 10;
  c[3] += 10;
  cout << "b = " << b << endl;
  cout << "c = " << c << endl;
  
}


// ---------------------------------------------------------
void test04()
{
  ArrayList<char> a;
  ArrayList<char> b;
  
  cout << endl << endl;
  cout << " ***************** " << endl;
  cout << " *  TEST SET #4  * " << endl;
  cout << " ***************** " << endl;
  
  for (int k=0; k<10; k++){
    a.insert_back(static_cast<char>(k+97));
  } 

  //TEST : Swap
  cout << endl << "TEST : Swap (reversing some elements)" << endl;
  cout << a << endl;
  for (int k=0; k< a.size()/2; k++){
    a.swap(k,a.size()-1-k);
  }
  cout << a << endl;
  
  //TEST : append
  cout << endl << "TEST : append" << endl;
  for (int k=0; k<10; k++){
    b.insert_back(static_cast<char>(k+100));
  }  
  cout << "Before Append" << endl;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl; 
  a.append(b); 
  cout << "After Append" << endl;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  
  
  //TEST : Purge 
  cout << endl << "TEST : Purge" << endl;
  cout << "Before Purge" << endl;
  cout << "a = " << a << endl;
  a.purge(); 
  cout << "After Purge" << endl;
  cout << "a = " << a << endl;
}



// ---------------------------------------------------------
void test05()
{
  ArrayList<float> a;
  ArrayList<int> b;
  
  cout << endl << endl;
  cout << " ***************** " << endl;
  cout << " *  TEST SET #5  * " << endl;
  cout << " ***************** " << endl;


  cout << endl;
  for (int k=0; k<10; k++){
    a.insert_back(3.14 * k);
  }
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  
  //TEST : Graceful PANIC
  cout << endl << "TEST : checking for graceful error handling" << endl;
  cout << "b.first() : " << endl;
  b.first();
  cout << "a[5] = " << a[5] << endl;
  cout << "a[50] = " << a[50] << endl;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  
  //TEST : More Graceful PANIC
  cout << endl << "TEST : More checking for graceful error handling" << endl;
  cout << "a.insert(9.9, 20) : " << endl;
  a.insert(9.9, 20);
  cout << "a.remove(555) :" << endl;
  a.remove(555);
  cout << "a.swap(1,100) :" << endl;
  a.swap(1,100);
  cout << "a.swap(40,41) :" << endl;
  a.swap(40,41);
  
  cout << "a = " << a << endl; 
}



int main () {
  
  cout << "Hello World!!, This is the LARGE Tester" << endl;
        test01();
  test02();
  test03();
  test04();
  test05();
    
  cin.clear ();
  cout << "Press Any Key to Continue" << endl;
  cin.get();
  
  return 0;
}*/