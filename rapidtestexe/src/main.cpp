#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_WINDOWS_CRTDBG
#include "catch.hpp"
#include "common.h"
#include <iostream>
#include "rapidtestexe.h"
#include "proprietary.h"

int run_all(char ** argv, int argc, bool run_prop, bool run_main, bool run_dll);

#ifndef CATCH_CONFIG_MAIN
int main(char ** argv, int argc) {
    bool run_dll = false;
    bool run_prop = false;
    bool run_main = true;

    run_all(argv, argc, run_prop, run_main, run_dll);

    // Rant, rawr, danger! Don't heckle me...
    system("pause");
    return 0;
}
#endif

int run_all(char ** argv, int argc, bool run_prop, bool run_main, bool run_dll) {
    int r = 0;
    
    if (run_prop) {
        r = rapidtestexe::proprietary::proprietary_main(argv, argc);
        std::cout << "proprietary_main returned: " << r << std::endl;
    }

    if (run_main) {
        r = rapidtestexe::test_main(argv, argc);
        std::cout << "test_main returned: " << r << std::endl;
    }

    if (run_dll) {
        r = rapidtestexe::test_dll() == 10 ? 0 : 1;
        std::cout << "test_dll returned: " << r << std::endl;
    }

    return r;
}

//TEST_CASE("All mains succeed", "[run_all]") {
//    REQUIRE(run_all(nullptr, 0, true, true, true) == 0);
//}

TEST_CASE("Made strings") {
    REQUIRE(rapidtestexe::test_main(nullptr, 0) == 0);
}