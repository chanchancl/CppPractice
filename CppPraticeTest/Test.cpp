
#include "Test.h"

void _EXCEPT(bool bexpression, std::string expression, std::string file, long line)
{
    total++;
    if (bexpression)
    {
        pass++;
    }
    else
    {
        error++;
        std::cerr << expression << " at file : " << file << "  line : " << line << std::endl;
    }
}

void Reset(const char* name)
{
    using namespace std;
    total = pass = error = 0;
    cout << "Test " << setw(15) << setiosflags(ios::left) << name ;
    
}

void Report()
{
    using namespace std;
    cout << setw(4) << resetiosflags(ios::left) << pass << '/'
         << setw(5) << error << '/' 
         << setw(5) << total << " (" 
         << showpoint << setprecision(5) << (pass/float(total)*100) << '%' << ')' << endl;
    
}