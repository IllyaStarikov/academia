#include <stdio.h>

char swap_bits(const char byte) {
	char low = byte << 4,
	high = byte >> 4;
	
	return low | high;
}

int main(int argc, char *argv[]) {
	 char number = 0x38;
	
	swap_bits(number);
	printf("%2x", swap_bits(number));
}