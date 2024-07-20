#include "FileOperations.h"
#include <windows.h>
#include <tlhelp32.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <string>

void TerminateProcessByName(const std::wstring &processName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize = sizeof(processEntry);

    if (Process32First(snapshot, &processEntry)) {
        do {
            if (processName == processEntry.szExeFile) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processEntry.th32ProcessID);
                if (hProcess != NULL) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                }
            }
        } while (Process32Next(snapshot, &processEntry));
    }
    CloseHandle(snapshot);
}

void TerminateProcesses(const std::vector<std::wstring> &processNames) {
    for (const auto &processName : processNames) {
        TerminateProcessByName(processName);
    }
}

void DeleteFilesRecursively(const std::wstring &path) {
    SHFILEOPSTRUCT fileOp = {0};
    fileOp.wFunc = FO_DELETE;
    fileOp.pFrom = path.c_str();
    fileOp.fFlags = FOF_NO_UI;
    SHFileOperation(&fileOp);
}

void DeleteFilesAndDirectories(const std::vector<std::wstring> &paths) {
    for (const auto &path : paths) {
        DeleteFilesRecursively(path);
    }
}
