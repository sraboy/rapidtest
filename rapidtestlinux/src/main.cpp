#include <iostream>
#include "../inc/rapidtestlinux.h"
#include "../gitignore_inc/proprietary.h"

//
// Simply runs the two stubs and reports the results. Put test code
// in the other files and there's no need to bother with this.
//
int main(char ** argv, int argc) {

    int r = rapidtestlinux::proprietary::proprietary_main(argv, argc);
    std::cout << "proprietary_main returned: " << r << std::endl;

    r = rapidtestlinux::test_main(argv, argc);
    std::cout << "test_main returned: " << r << std::endl;

    r = rapidtestlinux::test_so();
    std::cout << "test_dll returned: " << r << std::endl;

    // Rant, rawr, danger! Don't heckle me...
    system("pause");
    return 0;
}