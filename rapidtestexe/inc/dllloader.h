#pragma once

#include "common.h"
#include <functional>

#ifndef DLLCALLCONV
#define DLLCALLCONV __stdcall
#endif

namespace dllloader {

    template <typename _Rty, typename... _Params>
    _Rty LoadDllCallFunction(std::string_view DllPath, std::string_view FuncName, _Params... params) {
        
        typedef _Rty(DLLCALLCONV* callable_t)(_Params... params);
        HINSTANCE dllHandle = nullptr;
        dllHandle = LoadLibraryA(DllPath.data());

        if (!dllHandle) {
            auto err = GetLastError();
            std::cout << "LoadLibraryA() failed: " << err << std::endl;
            throw std::bad_function_call();
        }

        auto dllfunc = reinterpret_cast<callable_t>(GetProcAddress(dllHandle, FuncName.data()));

        if (!dllfunc) {
            auto err = GetLastError();
            std::cout << "GetProcAddress() failed: " << err << std::endl;
            throw std::bad_function_call();
        }

        _Rty retVal = dllfunc(params...);
        if (!FreeLibrary(dllHandle)) {
            auto err = GetLastError();
            std::cout << "FreeLibrary() failed: " << err << std::endl;
            throw std::bad_function_call();
        }
        return retVal;
    }

}