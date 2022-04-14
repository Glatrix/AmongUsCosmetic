// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include "mem.h";
#include "proc.h";
#include <iostream>
#include <TlHelp32.h>


DWORD WINAPI HackThread(HMODULE hModule) 
{
    AllocConsole();
    FILE * f;
    freopen_s(&f, "CONOUT$","w",stdout);

    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_handle, FOREGROUND_BLUE);

    const char* hackname = "[AmongUsUnlocker] ";
    std::cout << hackname << "Enabled (By: Glatrix)\n";
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");
    std::cout << hackname << "Patching...\n";
    mem::Nop((BYTE*)(moduleBase + 0x7B560B), 2);
    std::cout << hackname << "Unlocked Pets\n";
    mem::Nop((BYTE*)(moduleBase + 0x7B550B), 2);
    std::cout << hackname << "Unlocked Hats\n";
    mem::Nop((BYTE*)(moduleBase + 0x7B559B), 2);
    std::cout << hackname << "Unlocked Name Plates\n";
    mem::Nop((BYTE*)(moduleBase + 0x7B567B), 2);
    std::cout << hackname << "Unlocked Skins\n";
    mem::Nop((BYTE*)(moduleBase + 0x7B56EB), 2);
    std::cout << hackname << "Unlocked Visors\n";
    std::cout << hackname << "Done!!!\n";

    std::cout << "[AmongUsUnlocker] Press Delete to eject 'AmongUsUnlocker.dll'\n";

    while (true)
    {
        if (GetAsyncKeyState(VK_DELETE)) 
        {
            break;
        }
    }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: 
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

