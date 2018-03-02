#include <iostream>
#include <sstream>
#include <unistd.h>
void __bbinstr(const char bbid []) {
    std::cerr << bbid << std::endl;
    return;
}
#include <iostream>

using namespace std;
/*:B6:*/int main()/*:/B6:*/
{
/*:B5:*/ __bbinstr("B5");int a  = /*%a%*/ 0/*%~a%*/;/*:/B5:*/
/*:B5:*/double d = 1.1;/*:/B5:*/
for (int i=0;__bbinstr("B4"), i<10;__bbinstr("B2"), i++)
{
/*:B3:*/ __bbinstr("B3");cout << "hi" << endl;/*:/B3:*/
}
/*:B1:*/ __bbinstr("B1");return 0;/*:/B1:*/
}