#include <iostream>

int main(int argc, char *argv[]) {
	std::string input;
	while (!std::cin.eof()) {
		std::getline (std::cin, input);
	
		if (!(input[0] == '#')) { std::cout << input << std::endl ; }
	}
}