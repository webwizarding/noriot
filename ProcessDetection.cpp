#include "ProcessDetection.h"
#include <windows.h>
#include <tlhelp32.h>

bool IsProcessRunning(const std::wstring &processName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize = sizeof(processEntry);

    if (Process32First(snapshot, &processEntry)) {
        do {
            if (processName == processEntry.szExeFile) {
                CloseHandle(snapshot);
                return true;
            }
        } while (Process32Next(snapshot, &processEntry));
    }
    CloseHandle(snapshot);
    return false;
}

bool IsAnyProcessRunning(const std::vector<std::wstring> &processNames) {
    for (const auto &processName : processNames) {
        if (IsProcessRunning(processName)) {
            return true;
        }
    }
    return false;
}

