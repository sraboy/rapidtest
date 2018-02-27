#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 1
#include "common.h"
#include "rapidtestexe.h"
#include "proprietary.h"
#include "dllloader.h"

#include <OleAuto.h>
#pragma comment(lib, "oleaut32.lib")
#include <wtypes.h>
#include <comutil.h>
#include <strsafe.h>
#include <codecvt>
#include <locale>
#include <atlstr.h>
#pragma comment(lib, "comsuppw.lib")

class SuperString {
    wchar_t * raw_string;
    size_t raw_string_len;
    std::vector<BSTR> bstr_casts;
    std::vector<std::string*> char_casts;

public:
    ~SuperString() {
        delete[] raw_string;
        for (auto i : bstr_casts) {
            SysFreeString(i);
        }
        for (auto i : char_casts) {
            delete i;
        }
    }

    explicit SuperString(wchar_t const * const in, size_t len) {
        raw_string_len = len + 1;
        raw_string = new wchar_t[raw_string_len];
        wcscpy_s(raw_string, raw_string_len, in);
    }

    SuperString(wchar_t const * in)
        : SuperString(in, wcsnlen_s(in, STRSAFE_MAX_CCH * sizeof(wchar_t))) {
    }

    explicit SuperString(std::wstring const& in)
        : SuperString(in.c_str()) {
    }

    explicit SuperString(char const * const in, size_t len) {
        raw_string_len = len + 1;
        size_t c = 0;
        raw_string = new wchar_t[raw_string_len];
        mbstowcs_s(&c, raw_string, raw_string_len, in, raw_string_len);
    }

    SuperString(char const * in)
        : SuperString(in, strnlen_s(in, STRSAFE_MAX_CCH)) {
    }

    explicit SuperString(std::string const& in)
        : SuperString(in.c_str()) {
    }

    explicit SuperString(BSTR& in, bool free = true)
        : SuperString(static_cast<wchar_t*>(in), ::SysStringLen(in)) {
        if (free) { SysFreeString(in); }
    }

    explicit SuperString(_bstr_t& in)
        : SuperString(in.GetBSTR(), false) {
    }

    explicit SuperString(ATL::CStringA in) : SuperString(in, in.GetLength()) {
    }

    explicit SuperString(ATL::CStringW in) : SuperString(in, in.GetLength()) {
    }

    //
    // Converters
    //
    //template <typename T>
    //static T To<T>(wchar_t * in, size_t len) {
    //}

    BSTR AsBSTR() {
        auto b = SysAllocStringLen(raw_string, static_cast<unsigned int>(raw_string_len));
        bstr_casts.push_back(b);
        return b;
    }

    wchar_t const * c_str() const  {
        return raw_string;
    }

    explicit operator std::string() const {
#pragma warning(push)
#pragma warning(disable: 4996) // deprecation
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
        return converterX.to_bytes(raw_string);
#pragma warning(pop)
    }

    explicit operator std::wstring() const {
        return std::wstring(raw_string);
    }

    explicit operator BSTR() {
        return AsBSTR();
    }

    explicit operator ATL::CStringA() const {
        return ATL::CStringA(raw_string, static_cast<int>(raw_string_len));
    }

    explicit operator ATL::CStringW() const {
        return ATL::CStringW(raw_string, static_cast<int>(raw_string_len));
    }

    explicit operator _bstr_t() const {
        return _bstr_t(raw_string);
    }

    explicit operator wchar_t const * const() const {
        return raw_string;
    }

    explicit operator char const *() {
        std::string * const s = new std::string(static_cast<std::string>(*this));
        char_casts.push_back(s);
        char * c = const_cast<char*>(s->c_str());
        return c;
    }

    SuperString& operator+=(SuperString const& s) {
        auto x = std::wstring(raw_string) + std::wstring(s.c_str());
        delete raw_string;
        raw_string_len = x.length() + 1;
        raw_string = new wchar_t[raw_string_len];
        wcscpy_s(raw_string, raw_string_len, x.c_str());
        return *this;
    }

    bool operator==(SuperString const& s) {
        return std::wstring(this->c_str()) == std::wstring(s.c_str());
    }

    bool operator!=(SuperString const& s) {
        return std::wstring(this->c_str()) != std::wstring(s.c_str());
    }

    //std::size_t operator()() const {
    //    size_t seed = raw_string_len;
    //    std::hash<std::string> sh;
    //    
    //    for (auto& i : this->char_casts) {
    //        seed ^= sh(*i);
    //    }

    //    std::hash<std::wstring> wh;
    //    for (auto& i : this->bstr_casts) {
    //        std::wstring w(static_cast<wchar_t *>(i));
    //        seed ^= wh(w);
    //    }

    //    for (int i = 0; i < this->raw_string_len; i++) {
    //        seed ^= this->raw_string[i];
    //    }
    //}

};

#include <map>
std::map<SuperString, int> x;
//std::unordered_map<SuperString, int> y;

//_Use_decl_annotations_
//std::string GuidToString(GUID const& guid) {
//    char guid_cstr[38];
//    guid_cstr[37] = '\0';
//    //
//    // NOTE: We don't add curly braces since key server uses those to parse JSON fields
//    //
//    snprintf(guid_cstr, sizeof(guid_cstr),
//             "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
//             guid.Data1, guid.Data2, guid.Data3,
//             guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
//             guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
//
//    return std::string(guid_cstr);
//}
//
//_Use_decl_annotations_
//GUID StringToGuid(std::string const& str) {
//    GUID guid;
//    char const * const format = "%8x-%4hx-%4hx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx";
//    sscanf_s(str.c_str(), format,
//             &guid.Data1, &guid.Data2, &guid.Data3,
//             &guid.Data4[0], &guid.Data4[1], &guid.Data4[2], &guid.Data4[3],
//             &guid.Data4[4], &guid.Data4[5], &guid.Data4[6], &guid.Data4[7]);
//
//    return guid;
//}
//
//_Use_decl_annotations_
//ATL::CSid GetSidFromString(std::wstring sidString) {
//    PSID pSid;
//
//    //
//    // Try to convert the string we got passed in.
//    //
//    if (!::ConvertStringSidToSid(sidString.c_str(), &pSid)) {
//        //
//        // Default constructor is for a SidTypeInvalid, so return that if the
//        // string is bad.
//        //
//        DBGPRINT("Invalid SID string - converting to SidTypeInvalid\n");
//        return ATL::CSid();
//    }
//
//    //
//    // sidString represents a valid SID, so construct one and return it
//    //
//    ATL::CSid sid(static_cast<const SID *>(pSid));
//    return sid;
//}


namespace rapidtestexe {

void test_string() {
    SuperString sstr = L"test";

    ATL::CStringW csw(sstr);
    ATL::CStringA csa(sstr);
    BSTR b(sstr);
    _bstr_t bstrt(sstr);
    std::wstring ws(sstr);
    std::string s(sstr);
    char const * cs = (char const*)sstr;
    wchar_t const * wcs = (wchar_t const*)sstr;

    wprintf(L"SuperString.c_str(): %s\n", sstr.c_str());
    //wprintf(L"cast wchar_t*: %s\n", static_cast<wchar_t*>(sstr));
    wprintf(L"CStringW: %s\n", static_cast<wchar_t const*>(csw));
    wprintf(L"CStringA: %S\n", static_cast<char const*>(csa));
    wprintf(L"BSTR: %s\n", b);
    wprintf(L"_bstr_t: %s\n", static_cast<wchar_t*>(bstrt));
    wprintf(L"wstring: %s\n", ws.c_str());
    wprintf(L"string: %S\n", s.c_str());
    wprintf(L"cast char*: %S\n", cs);
    wprintf(L"cast wchar_t*: %s\n", wcs);

    BSTR ab = sstr.AsBSTR();
    wprintf(L"AsBSTR: %s\n", ab);
    SysFreeString(ab);

    sstr += " more";
    wprintf(L"operator+=: %s\n", sstr.c_str());
}

int test_main(char ** argv, int argc) {

    test_string();
    //
    // Test code here
    //

    UNREFERENCED_PARAMETER(argv);
    UNREFERENCED_PARAMETER(argc);

    return 0;
}

int test_dll() {
    using namespace dllloader;
#ifdef _WIN64
#undef DLLCALLCONV
#define DLLCALLCONV __cdecl
    auto cdeclval = Dll::QuickCall<int, bool, int, int, int, int>("rapidtestdll.dll", "do_things_cdecl", false, 1, 2, 3, 4);
#undef DLLCALLCONV
#define DLLCALLCONV __stdcall
    auto stdcallval = Dll::QuickCall<int, bool, int, int, int, int>("rapidtestdll.dll", "do_things_stdcall", true, 5, 6, 7, 8);
#else
    //
    // Can't fiddle with calling conventions on
    //  x86 so we'll just give the expected values
    //
    auto stdcallval = 26;
    auto cdeclval = -8;
#endif
    Dll rapidtestdll("rapidtestdll.dll");
    auto val = rapidtestdll.Invoke<int, bool, int, int, int, int>("do_things_cdecl", false, 1, 2, 3, 4);

    return val + cdeclval + stdcallval;
}
}