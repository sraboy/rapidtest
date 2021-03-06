//
// Copyright (C) 2018 Steven Lavoie 
// Copyright (C) 2013 Mohit Arora
//
// Modified from "Simple Windows Service in C++" on CodeProject:
//  https://www.codeproject.com/Articles/499465/Simple-Windows-Service-in-Cplusplus
//
// Original code: CPOL1.0 https://www.codeproject.com/info/cpol10.aspx
// Modifications: Public Domain or CC0 1.0
//
#include "proprietary.h"
#include "rapidtestservice.h"

namespace SimpleService {
    SimpleService service_instance;

    int main(int argc, char** argv) {
        UNREFERENCED_PARAMETER(argc);
        UNREFERENCED_PARAMETER(argv);
        DBGPRINT("Here\n");
        
        SERVICE_TABLE_ENTRY ServiceTable[] = {
            { (LPWSTR)service_instance.GetServiceName().data(), (LPSERVICE_MAIN_FUNCTION)ServiceMain },
            { NULL, NULL }
        };

        if (StartServiceCtrlDispatcher(ServiceTable) == FALSE) {
            return GetLastError();
        }

        return 0;
    }

    VOID WINAPI ServiceCtrlHandler(DWORD CtrlCode) {
        DBGPRINT("Here\n");

        switch (CtrlCode) {
        case SERVICE_CONTROL_STOP:

            if (service_instance.mServiceStatus.dwCurrentState != SERVICE_RUNNING)
                break;

            /*
            * Perform tasks necessary to stop the service here
            */

            service_instance.mServiceStatus.dwControlsAccepted = 0;
            service_instance.mServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
            service_instance.mServiceStatus.dwWin32ExitCode = 0;
            service_instance.mServiceStatus.dwCheckPoint = 4;

            if (SetServiceStatus(service_instance.mStatusHandle, &service_instance.mServiceStatus) == FALSE) {
                DBGPRINT("SetServiceStatus returned error\n");
            }

            // This will signal the worker thread to start shutting down
            SetEvent(service_instance.mServiceStopEvent);

            break;

        default:
            break;
        }
    }

    DWORD WINAPI ServiceWorkerThread(LPVOID lpParam) {
        UNREFERENCED_PARAMETER(lpParam);
        //  Periodically check if the service has been requested to stop
        while (WaitForSingleObject(service_instance.mServiceStopEvent, 0) != WAIT_OBJECT_0) {
            /*
            * Perform main service function here
            */

            //  Simulate some work by sleeping
            Sleep(3000);
        }

        return ERROR_SUCCESS;
    }

    VOID WINAPI ServiceMain(DWORD argc, LPTSTR *argv) {
        UNREFERENCED_PARAMETER(argc);
        UNREFERENCED_PARAMETER(argv);
        DBGPRINT("Here\n");

        // Register our service control handler with the SCM
        service_instance.mStatusHandle = RegisterServiceCtrlHandler(service_instance.GetServiceName().data(), ServiceCtrlHandler);

        do {
            if (service_instance.mStatusHandle == NULL) {
                break;
            }

            // Tell the service controller we are starting
            ZeroMemory(&service_instance.mServiceStatus, sizeof(service_instance.mServiceStatus));
            service_instance.mServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
            service_instance.mServiceStatus.dwControlsAccepted = 0;
            service_instance.mServiceStatus.dwCurrentState = SERVICE_START_PENDING;
            service_instance.mServiceStatus.dwWin32ExitCode = 0;
            service_instance.mServiceStatus.dwServiceSpecificExitCode = 0;
            service_instance.mServiceStatus.dwCheckPoint = 0;

            if (SetServiceStatus(service_instance.mStatusHandle, &service_instance.mServiceStatus) == FALSE) {
                DBGPRINT("SetServiceStatus returned error\n");
            }

            /*
            * Perform tasks necessary to start the service here
            */

            // Create a service stop event to wait on later
            service_instance.mServiceStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
            if (service_instance.mServiceStopEvent == NULL) {
                // Error creating event
                // Tell service controller we are stopped and exit
                service_instance.mServiceStatus.dwControlsAccepted = 0;
                service_instance.mServiceStatus.dwCurrentState = SERVICE_STOPPED;
                service_instance.mServiceStatus.dwWin32ExitCode = GetLastError();
                service_instance.mServiceStatus.dwCheckPoint = 1;

                if (SetServiceStatus(service_instance.mStatusHandle, &service_instance.mServiceStatus) == FALSE) {
                    DBGPRINT("SetServiceStatus returned error\n");
                }
                break;
            }

            // Tell the service controller we are started
            service_instance.mServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
            service_instance.mServiceStatus.dwCurrentState = SERVICE_RUNNING;
            service_instance.mServiceStatus.dwWin32ExitCode = 0;
            service_instance.mServiceStatus.dwCheckPoint = 0;

            if (SetServiceStatus(service_instance.mStatusHandle, &service_instance.mServiceStatus) == FALSE) {
                DBGPRINT("SetServiceStatus returned error\n");
            }

            // Start a thread that will perform the main task of the service
            HANDLE hThread = CreateThread(NULL, 0, ServiceWorkerThread, NULL, 0, NULL);

            // Wait until our worker thread exits signaling that the service needs to stop
            WaitForSingleObject(hThread, INFINITE);


            /*
            * Perform any cleanup tasks
            */

            CloseHandle(service_instance.mServiceStopEvent);

            // Tell the service controller we are stopped
            service_instance.mServiceStatus.dwControlsAccepted = 0;
            service_instance.mServiceStatus.dwCurrentState = SERVICE_STOPPED;
            service_instance.mServiceStatus.dwWin32ExitCode = 0;
            service_instance.mServiceStatus.dwCheckPoint = 3;

            if (SetServiceStatus(service_instance.mStatusHandle, &service_instance.mServiceStatus) == FALSE) {
                DBGPRINT("SetServiceStatus returned error\n");
            }

        } while (0);

        return;
    }

}