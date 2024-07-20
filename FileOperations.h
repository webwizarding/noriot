#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <vector>
#include <string>

void TerminateProcesses(const std::vector<std::wstring> &processNames);
void DeleteFilesAndDirectories(const std::vector<std::wstring> &paths);

#endif // FILEOPERATIONS_H
