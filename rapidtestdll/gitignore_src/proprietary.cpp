//
// This file is in the initial commit as a placeholder. To prevent git from
// committing your code, ensure you run:
//
// git update-index --assume-unchanged gitignore_src\proprietary.cpp
//
// It is automatically run as one of the project's pre-build commands
//
#include "proprietary.h"

namespace rapidtestdll {
    namespace proprietary {

        bool proprietary_test_process_attach() {
            return true;
        }

        bool proprietary_test_process_detach() {
            return true;
        }

        bool proprietary_test_thread_attach() {
            return true;
        }

        bool proprietary_test_thread_detach() {
            return true;
        }

        int __stdcall proprietary_do_things_stdcall(bool cond) {
            if (cond) {
                return 0;
            } else {
                return 1;
            }
        }

        int __cdecl proprietary_do_things_cdecl(bool cond) {
            if (cond) {
                return 0;
            } else {
                return 1;
            }
        }

    } //proprietary
} //rapidtestdll