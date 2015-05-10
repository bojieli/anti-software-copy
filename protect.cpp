#include<stdafx.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define MAXPATH 256
#define EXECUTABLE "PHX.dll"
 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    char cwd[MAXPATH];
    GetCurrentDirectoryA(MAXPATH, cwd);

    char path[MAXPATH] = "\\\\.\\";
    strcat_s(path, cwd);
    strcat_s(path, "\\COM1");

    if (INVALID_HANDLE_VALUE == CreateFileA(path, 0, 0, NULL, OPEN_EXISTING, 0, NULL)) {
        MessageBoxA(NULL, "Failed to open resource file", NULL, MB_OK);
        exit(1);
    }
    
    if (!(FILE_ATTRIBUTE_SYSTEM & GetFileAttributesA(EXECUTABLE))) {
        MessageBoxA(NULL, "Failed to open resource file", NULL, MB_OK);
        exit(1);
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    CreateProcessA(
        EXECUTABLE,     // module name
        EXECUTABLE,     // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi );          // Pointer to PROCESS_INFORMATION structure
}
