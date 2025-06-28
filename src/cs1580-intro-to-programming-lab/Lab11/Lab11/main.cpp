// Programmer: Illya Starikov
// Section: 3E
// File:
// Description:
#include <iostream>
#include <fstream>
#include <ctype.h>
using namespace std;

int main() {
	const int cLENGTHOFNAMES = 10, cTHISYEAR = 2015; // Assuming you don't want us to do this to the current date via CTime.
	const char cNAME_SEPERTATOR = '_';

	char charFirstName[cLENGTHOFNAMES], charLastName[cLENGTHOFNAMES], charReadInPossible;
	int intYearOfBirth, intAge;
	
	char charUserName[cLENGTHOFNAMES * 2]; // because the username is first + last
	cout << "Welcome" << endl;
	
	ifstream ifReadIn;
	ifReadIn.open("input.txt");
	
	ofstream ofReadOut;
	ofReadOut.open("output.txt");
	
	ifReadIn >> charReadInPossible;
	while (!ifReadIn.eof()) {
		ifReadIn >> charFirstName[cLENGTHOFNAMES];
		ifReadIn >> charLastName[cLENGTHOFNAMES];
		ifReadIn >> intYearOfBirth;
		
		intAge = cTHISYEAR - intYearOfBirth;
		
		
		toupper(charFirstName[0]); // 0 because require array index, not size
		strcat(charUserName, charFirstName);
		strcat(charUserName, &cNAME_SEPERTATOR);
		strcat(charUserName, charLastName);
		
		ofReadOut << charFirstName << charLastName << charUserName << intAge << endl;
	}
	ifReadIn >> charReadInPossible;
	
	ofReadOut.close();
	ifReadIn.close();
	
	return 0;
}
