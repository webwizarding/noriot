#ifndef PROCESSDETECTION_H
#define PROCESSDETECTION_H

#include <string>
#include <vector>

bool IsProcessRunning(const std::wstring &processName);
bool IsAnyProcessRunning(const std::vector<std::wstring> &processNames);

#endif // PROCESSDETECTION_H
