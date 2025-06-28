#include <stdio.h>
#include <reg51.h>

int power(int base, int exponent) reentrant;
int input();
int function(const int x);

int main() {
	int x = input();
	if (x >= 0 && x <= 3) {
		P2 = function(x);
	} else  {
		P2 = 0x00;
	}
	
	return 0;
}

int power(int base, int exponent) reentrant {
	if (exponent == 0) { 
		return 1;
	} 
		
	return base * power(base, exponent - 1);
}

int input() {
	P1 = 0x3; // To make an output port
	return P1;
}
	
int function(const int x) {
	return 2*power(x, 2) + 3*x + 1; 
}