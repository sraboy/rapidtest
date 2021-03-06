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
        using namespace dllloader;
#undef DLLCALLCONV
#define DLLCALLCONV __cdecl
        auto cdeclval = Dll::QuickCall<int, bool, int, int, int, int>("rapidtestdll.dll", "do_things_cdecl", false, 1, 2, 3, 4);
#undef DLLCALLCONV
#define DLLCALLCONV __stdcall
        auto stdcallval = Dll::QuickCall<int, bool, int, int, int, int>("rapidtestdll.dll", "do_things_stdcall", true, 5, 6, 7, 8);

        Dll rapidtestdll("rapidtestdll.dll");
        auto val = rapidtestdll.Invoke<int, bool, int, int, int, int>("do_things_stdcall", false, 1, 2, 3, 4);

        return val + cdeclval + stdcallval;
    }
}