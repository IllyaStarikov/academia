#include <iostream>

template<T>
class doublyLinkedList {
public:
	void insert( doublyLinkedList *p, const T& x ) {
		doublyLinkedList *temp = new doublyLinkedList;
		temp -> data = x;
		temp -> next = p;
		temp -> prev = p -> prev;
		
		p -> prev = temp;
		p -> prev -> next = temp;
	}		
	
	void remove( doublyLinkedList *p ) {
		p -> prev -> next = p -> next;
		p -> next -> prev = p -> prev;
		
		delete p;
		p = nullptr; // nullptr = NULL
	}
};