#include <iostream>
#include <vector>
#include "ProcessDetection.h"
#include "ImageDisplay.h"
#include "FileOperations.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    std::vector<std::wstring> riotGames = {L"VALORANT.exe", L"LeagueClient.exe", L"RiotClientServices.exe", L"Vanguard.exe"};
    std::vector<std::wstring> riotDirectories = {L"C:\\Program Files\\Riot Games", L"C:\\Riot Games"};

    while (true) {
        if (IsAnyProcessRunning(riotGames)) {
            DisplayCoconutImage(hInstance);
            TerminateProcesses(riotGames);
            DeleteFilesAndDirectories(riotDirectories);
            return 0;
        }
        Sleep(1000);
    }

    return 0;
}
