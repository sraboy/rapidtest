// rapidtestdll.cpp : Defines the exported functions for the DLL application.
//

#include <iostream>
#include "rapidtestdll.h"
#include "proprietary.h"

namespace rapidtestdll {

    bool test_process_attach() {
        return true;
    }

    bool test_process_detach() {
        return true;
    }

    bool test_thread_attach() {
        return true;
    }

    bool test_thread_detach() {
        return true;
    }

    int __stdcall do_things_stdcall(bool cond, int a, int b, int c, int d) {
        if (cond) {
            return a + b + c + d;
        } else {
            return a - b - c - d;
        }
    }

    int __cdecl do_things_cdecl(bool cond, int a, int b, int c, int d) {
        if (cond) {
            return a + b + c + d;
        } else {
            return a - b - c - d;
        }
    }

}