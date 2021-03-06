#pragma once

#include "common.h"

#undef PROJECT_NAME
#define PROJECT_NAME "rapidtestservice"
#include "debug.h"

EXTERN_C_START

namespace SimpleService {

    class SimpleService {
    private:
        std::wstring_view ServiceName = L"SimpleService";

    public:
        SERVICE_STATUS        mServiceStatus = { 0 };
        SERVICE_STATUS_HANDLE mStatusHandle = NULL;
        HANDLE                mServiceStopEvent = INVALID_HANDLE_VALUE;

        SimpleService() = default;
        SimpleService(std::wstring_view service_name) { this->ServiceName = service_name; }
        std::wstring_view GetServiceName() { return this->ServiceName; }

    };

    VOID WINAPI ServiceMain(DWORD argc, LPTSTR *argv);
    VOID WINAPI ServiceCtrlHandler(DWORD);
    DWORD WINAPI ServiceWorkerThread(LPVOID lpParam);
    int main(int argc, char** argv);
}

EXTERN_C_END