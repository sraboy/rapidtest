/*************************************************************************************************
* Copyright 2017 Steven Lavoie, Jr (steven.lavoiejr _AT_ gmail.com)
*
* BLUF: MIT LICENSE
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this
* software and associated documentation files (the "Software"), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify,
* merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*************************************************************************************************/

/*
* Use this to print debug statements for either user-mode or kernel-mode
* Windows programs. Update the PROJECT_NAME macro manually or add something
* like this to your project's PreProcessor Definitions:
* PROJECT_NAME="$(ProjectName)"
*
* If you don't want the full path displayed for __FILE__, disable "Use Full Paths"
* under the Advanced section of the project's C/C++ options. Additionally, under
* C/C++ General, you'll have to change "Program Database for Edit and Continue" to
* just "Program Database" and forgo the feature.
*
* NOTE: Strings passed in to DBGPRINT in the variadic arguments must be wchar_t *,
* so you must use the _T() macro or L prefix for constants and %S for char * variables.
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEBUG) || defined(_DEBUG)

#   ifndef PROJECT_NAME
#       define PROJECT_NAME "project"
#   endif 
#   ifdef _KERNEL_MODE
#       define PRINT DbgPrint
#       define FMT "[%s][%s:%d][%s()]: %s", PROJECT_NAME, __FILE__, __LINE__, __FUNCTION__
#   else
#       ifndef OutputDebugString
#           define USER_PRINT wprintf
#       else
#           define USER_PRINT OutputDebugString
#       endif
#       define PRINT USER_PRINT
#       define FMT _T("[%s][%s:%d][%s()]: %s"), _T(PROJECT_NAME), _T(__FILE__), __LINE__, _T(__FUNCTION__)
#   endif
#include <tchar.h>
#include <stdio.h>
#   define DBGSIZE 0x200
#   define DBGPRINT(fmtString, ...)                                                     \
    {                                                                                   \
        TCHAR pre_msg[DBGSIZE];                                                         \
        _sntprintf_s(pre_msg, DBGSIZE, _TRUNCATE, _T(fmtString), __VA_ARGS__);          \
        TCHAR dbg_msg[DBGSIZE];                                                         \
        _sntprintf_s(dbg_msg, DBGSIZE, _TRUNCATE, FMT, pre_msg);                        \
        PRINT(dbg_msg);                                                                 \
    }

#   define brk_when(condition, fmtString, ...) {                                        \
        if(condition) {                                                                 \
            DBGPRINT("ERROR: " fmtString "\n", __VA_ARGS__);                            \
            break;                                                                      \
        }                                                                               \
    }

#   define throw_when(condition, exc, fmtString, ...) {                                 \
        if(condition) {                                                                 \
            DBGPRINT("ERROR: " fmtString "\n", __VA_ARGS__);                            \
            throw exc;                                                                  \
        }                                                                               \
    }
#else
#   define DBGPRINT(...)        // nothing
#   define brk_when(...)        // nothing
#   define throw_when(...)      // nothing
#endif // DEBUG

#ifdef __cplusplus
}
#endif