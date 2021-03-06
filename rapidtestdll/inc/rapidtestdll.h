#pragma once
#include "common.h"

EXTERN_C_START

namespace rapidtestdll {

    bool test_process_attach();
    bool test_process_detach();
    bool test_thread_attach();
    bool test_thread_detach();

    __declspec(dllexport) int __stdcall do_things_stdcall(bool cond, int a, int b, int c, int d);
    __declspec(dllexport) int _cdecl do_things_cdecl(bool cond, int a, int b, int c, int d);

}

EXTERN_C_END