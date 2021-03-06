// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "rapidtestdll.h"
#include "proprietary.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
   
    UNREFERENCED_PARAMETER(hModule);
    UNREFERENCED_PARAMETER(lpReserved);

    bool success = true;
    
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        success = rapidtestdll::proprietary::proprietary_test_process_attach();
        success = rapidtestdll::test_process_attach();
    case DLL_THREAD_ATTACH:
        success = rapidtestdll::proprietary::proprietary_test_thread_attach();
        success = rapidtestdll::test_thread_attach();
    case DLL_THREAD_DETACH:
        success = rapidtestdll::proprietary::proprietary_test_thread_detach();
        success = rapidtestdll::test_thread_detach();
    case DLL_PROCESS_DETACH:
        success = rapidtestdll::proprietary::proprietary_test_process_detach();
        success = rapidtestdll::test_process_detach();
        break;
    }

    return success;
}

