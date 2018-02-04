#pragma once

#include "common.h"
#include <functional>

#undef PROJECT_NAME
#define PROJECT_NAME "dllloader"
#include "debug.h"

#ifndef DLLCALLCONV
#define DLLCALLCONV __stdcall
#endif

namespace dllloader {
    //
    // Load a DLL by name and invoke arbitrary functions by name
    //
    class Dll {
    private:
        void LoadDll(std::string_view DllPath);
        void Unload();

    public:
        HINSTANCE dllHandle;
        
        Dll(std::string_view);
        ~Dll();

        template <typename _Rty, typename... _Params>
        static _Rty QuickCall(std::string_view DllPath, std::string_view FuncName, _Params... params);
        template <typename _Rty, typename... _Params>
        _Rty Invoke(std::string_view FuncName, _Params... params);
        
    };

    Dll::Dll(std::string_view DllPath) {
        this->LoadDll(DllPath);
    }

    Dll::~Dll() {
        if (!FreeLibrary(this->dllHandle)) {
            DBGPRINT("FreeLibrary() failed: 0x%08x\n", GetLastError());
        }
    }

    void Dll::Unload() {
        if (!FreeLibrary(dllHandle)) {
            auto err = GetLastError();
            std::cout << "FreeLibrary() failed: " << err << std::endl;
            throw std::bad_function_call();
        }
    }

    void Dll::LoadDll(std::string_view DllPath) {
        this->dllHandle = nullptr;
        dllHandle = LoadLibraryA(DllPath.data());
        throw_when(!dllHandle, std::bad_function_call(), "LoadLibraryA() failed: 0x%08x\n", GetLastError());
    }

    //
    // Call the specified function in the currently-loaded DLL
    //
    template <typename _Rty, typename... _Params>
    _Rty Dll::Invoke(std::string_view FuncName, _Params... params) {
        typedef _Rty(DLLCALLCONV* callable_t)(_Params... params);
        auto dllfunc = reinterpret_cast<callable_t>(GetProcAddress(this->dllHandle, FuncName.data()));
        throw_when(!dllfunc, std::bad_function_call(), "GetProcAddress() failed: 0x%08x\n", GetLastError());
        _Rty retVal = dllfunc(params...);
        return retVal;
    }

    //
    // Load the specified DLL, call the specified function and free the DLL
    //
    template <typename _Rty, typename... _Params>
    _Rty Dll::QuickCall(std::string_view DllPath, std::string_view FuncName, _Params... params) {
        HINSTANCE dllHandle = nullptr;
        dllHandle = LoadLibraryA(DllPath.data());

        if (!dllHandle) {
            auto err = GetLastError();
            std::cout << "LoadLibraryA() failed: " << err << std::endl;
            throw std::bad_function_call();
        }
        typedef _Rty(DLLCALLCONV* callable_t)(_Params... params);
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