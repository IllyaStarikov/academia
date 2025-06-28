// Programmer: Illya Starikov
// Section: 3E
// File: main.cpp
// Description: Create a C++ syle ajax a-sync callback to the server.

#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

const int cACCOUNT_STRINGS = 15;
const int cMIN_PASSWORDLENGTH = 7;
const int cMAX_PASSWORDLENGTH = 15;

struct sAccount
{
    char m_charFirstName[cACCOUNT_STRINGS];
    char m_charLastName[cACCOUNT_STRINGS];
    char m_charPassword[cACCOUNT_STRINGS];

    char m_charUserName[cACCOUNT_STRINGS * 2]; // First + Last Name
};

/*
 Description:     Greet the user.
 Pre-Condition:   None.
 Post-Condition:  Side effects. Cout statements.
 */
void funcGreeting();

/*
 Description:    Read in values for the user account.
 Pre-Condition:  An sAccount struct must be intitilized.
 Also, respective functions (all maintenance functions) should be implemented
 correctly.
 Post-Condition: Values for sAccount will be assigned.
 */
void funcReadIn(sAccount &accountUser);

/*
 Description:     Post user info.
 Pre-Condition:   An sAccount struct must be intitilized.
 Also, respective functions (all maintenance functions) should be implemented
 correctly.
 Post-Condition:  Side effects. cout statements.
 */
void funcPrintOut(const sAccount &accountUser);
/*
 Description:    Prints out the passwords.
 Pre-Condition:  charPassword must have valid values.
 Post-Condition: Side effects. Cout statements.
 */
void funcPrintPassword(const char charPassword[]);

/*
 Description:    Sign off message. To say our farewells :(
 Pre-Condition:  None.
 Post-Condition: Cout statements. Side effects.
 */
void funcSignoff();

/*
 Description:    Maintenance function, validates if the string is of proper length.
 Pre-Condition:  charToValidate, intMaxSize, and intMinSize must be valid.
 Post-Condition: returns a bool based if the it is a proper length.
 */
bool funcStringValidation(const char charToValidate[], const unsigned int intMaxSize, const unsigned int intMinSize);

/*
 Description:    Ensures the strings match.
 Pre-Condition:  charToValidate, intMaxSize, and intMinSize must be valid.
 Post-Condition: returns a bool if the C-Strings match.
 */
bool funcStringMatch(const char charOriginal[], const char charNew[], const unsigned int intSize);

int main()
{
    sAccount mainAccount;

    funcGreeting();
    funcReadIn(mainAccount);
    funcPrintOut(mainAccount);
    funcSignoff();
}


void funcGreeting()
{
    cout << "Welcome! Please enter your information to sign up" << endl;

    return;
}

void funcReadIn(sAccount &accountUser)
{
    bool boolValid;
    bool boolStringMatch;

    char charTempArray[cACCOUNT_STRINGS];


    cout << "Enter your First Name: ";
    cin >> accountUser.m_charFirstName;

    cout << "Enter your Last Name: ";
    cin >> accountUser.m_charLastName;

    // First do-while to ensure password security
    // Second do-while to ensure password match
    do
    {
        do
        {
            cout << "Enter your Password: ";
            cin >> accountUser.m_charPassword;
            boolValid = funcStringValidation(accountUser.m_charPassword, cMAX_PASSWORDLENGTH, cMIN_PASSWORDLENGTH);
        } while (boolValid == false);

        cout << "Confirm your password: ";
        cin >> charTempArray;
        boolStringMatch = funcStringMatch(accountUser.m_charPassword, charTempArray, cACCOUNT_STRINGS);
    } while (boolStringMatch == false);

    // Can't Assign To, Therefore strncat twice.
    strncat(accountUser.m_charUserName, accountUser.m_charFirstName, cACCOUNT_STRINGS * 2);
    strncat(accountUser.m_charUserName, accountUser.m_charLastName, cACCOUNT_STRINGS * 2);

    return;
}

void funcPrintOut(const sAccount &accountUser)
{
    const int cMANIP_LENGTH = 15;

    cout << "*********************************" << endl <<
    "Account information Summary:" << endl << endl;

    cout << endl
    << setw(cMANIP_LENGTH) << left << "User ID:" << accountUser.m_charUserName << endl
    << setw(cMANIP_LENGTH) << left << "First Name:" << accountUser.m_charFirstName << endl
    << setw(cMANIP_LENGTH) << left << "Last Name:" << accountUser.m_charLastName << endl
    << setw(cMANIP_LENGTH) << left << "Password:";
    funcPrintPassword(accountUser.m_charPassword);

    return;
}

void funcSignoff()
{
    cout << endl << endl << "Thanks!";
    return;
}

bool funcStringValidation(const char charToValidate[], const unsigned int intMaxSize, const unsigned int intMinSize)
{
    return (strlen(charToValidate) <= intMaxSize) && (strlen(charToValidate) >= intMinSize) ? true : false;
}

bool funcStringMatch(const char charOriginal[], const char charNew[], const unsigned int intSize)
{
    return strncmp(charOriginal, charNew, intSize) == 0 ? true : false;
}

void funcPrintPassword(const char charPassword[])
{
    for (unsigned int i = 0; i < strlen(charPassword); i++)
    {
        cout << "*";
    }
    return;
}