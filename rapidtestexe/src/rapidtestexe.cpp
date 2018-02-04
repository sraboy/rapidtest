#include "common.h"
#include "rapidtestexe.h"
#include "proprietary.h"
#include "dllloader.h"


namespace rapidtestexe {
    
    int test_main(char ** argv, int argc) {
        
        //
        // Test code here
        //

        UNREFERENCED_PARAMETER(argv);
        UNREFERENCED_PARAMETER(argc);
        
        return 0;
    }

    int test_dll() {
#undef DLLCALLCONV
#define DLLCALLCONV __cdecl
        int cdeclval = dllloader::LoadDllCallFunction<int, bool, int, int, int, int>("rapidtestdll.dll", "do_things_cdecl", false, 1, 2, 3, 4);
#undef DLLCALLCONV
#define DLLCALLCONV __stdcall
        int stdcallval = dllloader::LoadDllCallFunction<int, bool, int, int, int, int>("rapidtestdll.dll", "do_things_stdcall", false, 1, 2, 3, 4);

        return cdeclval + stdcallval;
    }
}