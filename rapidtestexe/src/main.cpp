#include <iostream>
#include "rapidtestexe.h"
#include "proprietary.h"

//
// Simply runs the two stubs and reports the results. Put test code
// in the other files and there's no need to bother with this.
//
int main(char ** argv, int argc) {

    int r = rapidtestexe::proprietary::proprietary_main(argv, argc);
    std::cout << "proprietary_main returned: " << r << std::endl;
    
    r = rapidtestexe::test_main(argv, argc);
    std::cout << "test_main returned: " << r << std::endl;

    r = rapidtestexe::test_dll();
    std::cout << "test_dll returned: " << r << std::endl;

    // Rant, rawr, danger! Don't heckle me...
    system("pause");
    return 0;
}