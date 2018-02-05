//
// This file is in the initial commit as a placeholder. To prevent git from
// committing your code, ensure you run:
//
// git update-index --assume-unchanged gitignore_src\proprietary.cpp
//
// It is automatically run as one of the project's pre-build commands
//
#include "../gitignore_inc/proprietary.h"

namespace rapidtestlinux {
    namespace proprietary {

        int proprietary_main(char ** argv, int argc) {

            //
            // Test code here that you don't want to get committed
            //

            (void*)argv;
            (int)argc;

            return 0;
        }

    } //proprietary
} //rapidtestlinux