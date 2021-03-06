#include "mem.h"

namespace ph
{
	bool Memory::get_process(const char * ProcessName)
	{
		HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		pEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hPID, &pEntry))
		{
			do
			{
				if (!strcmp(pEntry.szExeFile, ProcessName))
				{
					dwPID = pEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hPID, &pEntry));
		}
		CloseHandle(hPID);

		if (dwPID)
		{
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
			HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
			mEntry.dwSize = sizeof(MODULEENTRY32);
			if (!Module32First(hModule, &mEntry))
				//exit(2);

				Module32First(hModule, &mEntry);
			dwBase = (DWORD_PTR)mEntry.modBaseAddr;

			CloseHandle(hModule);

			return true;
		}
		return false;
	}

	DWORD64 Memory::get_module(const char * lModule)
	{
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
		mEntry.dwSize = sizeof(MODULEENTRY32);
		do
		{
			if (!strcmp(mEntry.szModule, lModule))
			{
				CloseHandle(hModule);
				return (DWORD_PTR)mEntry.modBaseAddr;
			}
		} while (Module32Next(hModule, &mEntry));

		CloseHandle(hModule);
		return 5;
	}
	Memory mem;

}