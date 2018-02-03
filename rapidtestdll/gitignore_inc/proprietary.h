//
// This file is in the initial commit as a placeholder. To prevent git from
// committing your code, ensure you run:
//
// git update-index --assume-unchanged gitignore_inc\proprietary.h
//
// It is automatically run as one of the project's pre-build commands
//
#pragma once
#include "common.h"

namespace rapidtestdll {
    namespace proprietary {

        bool test_process_attach();
        bool test_process_detach();
        bool test_thread_attach();
        bool test_thread_detach();

    }
}