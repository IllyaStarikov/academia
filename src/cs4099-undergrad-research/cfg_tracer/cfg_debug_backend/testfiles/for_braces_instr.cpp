#include <fstream>
#include <sstream>
#include <unistd.h>
void __bbinstr(const char bbid []) {
    std::stringstream fname;
    fname << getpid() << ".bbtrace";
    std::ofstream tracefile(fname.str().c_str(), std::ofstream::app);
    tracefile << bbid << std::endl;
    return;
}
#include <iostream>

using namespace std;
/*B6*/int main()
/*B6*/{__bbinstr("B6");
/*B5*/ __bbinstr("B5");int a = 0;
/*B5*/double d = 1.1;
for (int i=0;__bbinstr("B4"), i<10;__bbinstr("B2"), i++)
{
/*B3*/ __bbinstr("B3");cout << "hi" << endl;
}
/*B1*/ __bbinstr("B1");return 0;
}
