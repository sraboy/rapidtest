#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "resource.h"

namespace rapidtestgui {

    int const MaxResStrLen = 100;

    HINSTANCE hInst;                                // current instance
    WCHAR szTitle[MaxResStrLen];                  // The title bar text
    WCHAR szWindowClass[MaxResStrLen];            // the main window class name

    ATOM                RegisterWindowClass(HINSTANCE hInstance);
    BOOL                InitInstance(HINSTANCE, int);
    LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
    INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

    EXTERN_C int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                                   _In_opt_ HINSTANCE hPrevInstance,
                                   _In_ LPWSTR    lpCmdLine,
                                   _In_ int       nCmdShow);

}