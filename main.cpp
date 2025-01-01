#define WIN32_LEAN_AND_MEAN
#define CURL_STATICLIB
#include <windows.h>


#include "IL2CPP_Resolver/IL2CPP_Resolver.hpp"
#include "menu/mods/Hooks.h"
#include "menu/ui/imgui_menu.h"
#include "helpers/fslog.hpp"
#include "MinHook.h"
#include "helpers/utils.h"
#include "menu/mods/Pointers.h"
#include "menu/mods/Hooks.h"
#include "menu/ui/menufeatures.h"
#include "menu/auth/auth.h"

HINSTANCE dll_handle;

DWORD __stdcall EjectThread(LPVOID lp_param) {
	Sleep(100);
	FreeLibraryAndExitThread(dll_handle, 0);
	Sleep(100);
	return 0;
}

int WINAPI main() {
	ImguiDX11Manager& menu = ImguiDX11Manager::instance();
	create_console();
	SetConsoleTitle(OBF(L"Asteroid | Pixel Gun 3D v25.0.1 - discord.gg/pg3d"));
	SetConsoleOutputCP(CP_UTF8);
	auth::checkProxyStatus(authVars::isUsingProxy);

	if (authVars::isUsingProxy) {
		fslog::error(OBF("A proxy has been detected! Please disable it before using Asteroid."));
		return 1;
	}

	bool res = IL2CPP::Initialize();
	if (res == false) {
		fslog::error(OBF("Failed initializing IL2CPP"));
		fslog::error(OBF("Join our discord server for Asteroid updates! https://discord.com/invite/3cnQwMWnFh"));
		MessageBoxA(0, OBF("Asteroid is not up to date. Please wait for a new version of Asteroid by joining our Discord server"), OBF("Error"), MB_OK | MB_ICONERROR);
		return 1;
	}
	if (!menu.get_present_pointer()) {
		fslog::error(OBF("Failed getting present pointer for rendering imgui"));
		fslog::error(OBF("This usually happens when you inject too early, please try again"));
		return 1;
	}
	MH_STATUS status = MH_Initialize();
	if (status != MH_OK) {
		fslog::error(OBF("Failed initializing Minhook"));
		return 1;
	}
	loadObfuscatedClass();
	initPointers();
	if (!hook(reinterpret_cast<void**>(menu.p_present_target), &detour_present, reinterpret_cast<void**>(&menu.p_present), "IMGUI PRESENT HOOK")) {
		fslog::error(OBF("Failed hooking present"));
		return 1;
	}
	Hooks::init_hooks();
	fslog::info(OBF("Successfully initialized Asteroid!\n"));
	printf(OBF("Keybinds to open Asteroid:\n [1] - %s [Main]\n [2] - F11\n [3] - Left Ctrl + Del\n [4] - Left Ctrl + Insert\n"), Variables::menuToggleBindKey.c_str());
	if (!authVars::gotNewsletter) {
		authVars::getnewsletter = OBF(true);
		authVars::gotNewsletter = OBF(false);
	}
	while (true) {
		Sleep(50);
	}
	menu.cleanup();
	CreateThread(0, 0, EjectThread, 0, 0, 0);
}


BOOL WINAPI DllMain(HINSTANCE hinst_dll, DWORD fdw_reason, LPVOID lpv_reserved) {
	switch (fdw_reason) {
	case DLL_PROCESS_ATTACH:
		dll_handle = hinst_dll;
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		if (lpv_reserved != nullptr) {
			break;
		}
		//cleanup if needed
		break;
	}
	return TRUE;
}