#include <stdio.h>
#include <reg51.h>

typedef enum { false, true } bool;
sbit readFromROM = P2^1;

unsigned char fibonacci(const unsigned char number) reentrant;
unsigned char get_input();

void delay(int microsecond) {} // To prevent compiler errors
	
int main() {
	code unsigned char sequence[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377 };
	unsigned char input, i;
	
	P3 = 0x00; // Output port
	P1 = 0x0FF; // Input port
	
	readFromROM = true;
	input = get_input();
	
	for (i = 0; i < input; i++) {
		if (readFromROM) {
			P3 = sequence[i];
 		} else {
			P3 = fibonacci(i);
		}
		
		delay(27250);
	}
	
	if (i > 14) {
		CY = true;
	}
	
	return 0;
}

unsigned char fibonacci(const unsigned char number) reentrant {
	if (number == 0) {
		return 0;
	} else if (number == 1) {
		return 1;
	}
	
	return fibonacci(number - 1) + fibonacci(number - 2);
}

unsigned char get_input() {
	unsigned char input;

	do {
		input = P1 & 0x0F; // to clear upper four bits
	} while (input == 0);
	
	return input;
}
