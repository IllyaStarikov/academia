#include <stdio.h>
#include <reg51.h>

unsigned char getInput();
void output(const char low, const char high);

int main() {
	unsigned char input = getInput();
	unsigned char low, high;
	
	if (input <= 99) {
		high = (input & 0x0F0) >> 4; // The clears the low bits, 
		// but it's still the tens place. shift bits to make make it a ones place
		low = input & 0x0F;
		output(low, high);
	} else {
 		P0 = 0xFF;
		P1 = 0xFF;
	}
	
	return 0;
}

unsigned char getInput() {
	P0 = 0xFF; // Make P0 output port
	return P0;
}

void output(const char low, const char high) {
	unsigned char asciiLow = 0x30 | low,
	asciiHigh = 0x30 | high;
	
	P1 = asciiLow;
	P2 = asciiHigh;
}
