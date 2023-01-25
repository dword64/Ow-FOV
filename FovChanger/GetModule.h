#pragma once
#include <Windows.h>
#include <iostream>

class modu
{
public:
	HANDLE hProcess;
	DWORD64 BaseAddress;

	void GetBaseAddress()
	{
		hProcess = GetCurrentProcess();
		BaseAddress = (DWORD64)GetModuleHandleA("Overwatch.exe");
	}

	template <typename RPMType>
	RPMType RPM(DWORD64 Address)
	{
		RPMType Buffer;
		ReadProcessMemory(hProcess, LPVOID(Address), &Buffer, sizeof(Buffer), NULL);
		return Buffer;
	}

	template <typename WPMType>
	BOOL WPM(DWORD64 Address, WPMType value)
	{
		return WriteProcessMemory(hProcess, LPVOID(Address), &value, sizeof(value), NULL);
	}
};

extern modu* MODULE = new modu();