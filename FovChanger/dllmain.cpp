#pragma once
#include <fstream>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <TlHelp32.h>
#include <vector>
#include "GetModule.h"
#include "OffsetAddress.h"
#include "config.h"
#include "menu.h"


DWORD WINAPI MainProject(LPVOID lpParam)
{
	MODULE->GetBaseAddress();
	menu::Initialize();
	while (true)
	{
		BOOL bPressed = FALSE;

		while (GetAsyncKeyState(VK_INSERT) & 0x8000)
		{
			if (!bPressed)
				window::Visible = !window::Visible;

			bPressed = TRUE;

			Sleep(10);
		}
		
		float current_fov = MODULE->RPM<float>(MODULE->BaseAddress + offset::Fov);
		bool result = MODULE->WPM<float>(MODULE->BaseAddress + offset::Fov, settings::fov_setting);
	}
	menu::Uninitialize();
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, 0, MainProject, lpReserved, 0, NULL);
	}
	return TRUE;
}