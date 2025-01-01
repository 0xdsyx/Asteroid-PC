#ifndef IMGUIDX11MANAGED_H
#define IMGUIDX11MANAGER_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <d3d11.h>
#include <filesystem>
#include <fstream>

#include "IL2CPP_Resolver.hpp"
#include "ImGuiNotify.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "menufeatures.h"
#include "fslog.hpp"
#include "FontAwesome.h"
#include "Byte.h"
#include "obfusheader.h"
#include "utils.h"
#include "json.h"
#include "../mods/Fields.h"
#include "../mods/Pointers.h"
#include "../mods/Hooks.h"
#include "../mods/Game/globvars.h"
#include "../defs.h"
#include "../auth/auth.h"
#include "fa-solid-900.h"
#include "config.h"


typedef long(__stdcall* present)(IDXGISwapChain*, UINT, UINT);


LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param);
long __stdcall detour_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags);
#define SPACING2() ImGui::Spacing(); ImGui::Spacing();
#define SETCURSORPOSY10() ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);

class ImguiDX11Manager {
public:
	present p_present;
	present p_present_target;
	bool init;
	bool menuclosed;
	float dxWidth;
	float dxHeight;
	WNDPROC oWndProc;
	HWND window;
	ID3D11Device* p_device;
	ID3D11DeviceContext* p_context;
	ID3D11RenderTargetView* mainRenderTargetView;


	static ImguiDX11Manager& instance() {
		static ImguiDX11Manager hinstance;
		return hinstance;
	}
	
	bool get_present_pointer();
	void render();
	void render_overlays();
	void cleanup();
	void ProcessKeyInput();
	void SaveKeyToJson(int key);
	void LoadKeyFromJson();

	ImguiDX11Manager(const ImguiDX11Manager&) = delete;
	void operator=(const ImguiDX11Manager&) = delete;
private:
	ImguiDX11Manager() : p_present(nullptr), p_present_target(nullptr), init(false), menuclosed(true), oWndProc(nullptr), window(nullptr), p_device(nullptr), p_context(nullptr), mainRenderTargetView(nullptr) {};
};

namespace cursorfix {
	inline void keep_mouse_inmiddle();
}

#endif