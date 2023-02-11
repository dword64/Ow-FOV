#pragma once
#include <d3d11.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "detours.h"
#include "config.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "detours.lib")

namespace window
{
	BOOL Visible = TRUE;

	void Initialize(ID3D11Device* g_pd3dDevice, ID3D11DeviceContext* g_pd3dDeviceContext, HWND hWnd)
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	}

	void Render()
	{
		if (!Visible)
			return;

#pragma region Styling
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 5.0f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
#pragma endregion

		ImGui::SetNextWindowSize(ImVec2(400, 100));
		ImGui::Begin("FovChanger (Menu Key: Insert) :)", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);

		ImGui::SliderFloat("FOV", &settings::fov_setting, 1, 179, "%1.f");
		ImGui::End();
	}
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace menu
{
	DWORD64 m_ulOldWndProc;
	LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Initialize();
	void CreateRenderTarget(IDXGISwapChain* pSwapChain);
	void CleanupRenderTarget();


	typedef HRESULT(__stdcall* fn_D3D11CreateDeviceAndSwapChain_t)(IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE, HMODULE, UINT, D3D_FEATURE_LEVEL*, UINT, UINT, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);

	typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef HRESULT(__stdcall* D3D11ResizeBuffersHook) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

	HRESULT __stdcall hkD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	HRESULT __stdcall hookD3D11ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);


	DWORD Width, Height;

	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;

	bool firstTime = true;
	D3D11PresentHook phookD3D11Present = NULL;
	D3D11ResizeBuffersHook phookD3D11ResizeBuffer = NULL;
	ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

	DWORD LastPressedKey = 0;

	HRESULT __stdcall hkD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		if (firstTime)
		{
			firstTime = false;

			pSwapChain->GetDevice(__uuidof(pDevice), (PVOID*)&pDevice);
			pDevice->GetImmediateContext(&pContext);

			HWND owWindow = FindWindowA("TankWindowClass", NULL);

			window::Initialize(pDevice, pContext, owWindow);

			m_ulOldWndProc = SetWindowLongPtrA(owWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

			CreateRenderTarget(pSwapChain);
		}


		pContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		window::Render();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return phookD3D11Present(pSwapChain, SyncInterval, Flags);

	}

	void CleanupRenderTarget()
	{
		if (nullptr != g_mainRenderTargetView)
		{
			g_mainRenderTargetView->Release();
			g_mainRenderTargetView = nullptr;
		}
	}

	HRESULT __stdcall hookD3D11ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		ImGui_ImplDX11_InvalidateDeviceObjects();
		CleanupRenderTarget();
		HRESULT toReturn = phookD3D11ResizeBuffer(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
		CreateRenderTarget(pSwapChain);
		ImGui_ImplDX11_CreateDeviceObjects();

		return toReturn;
	}

	void CreateRenderTarget(IDXGISwapChain* pSwapChain)
	{
		DXGI_SWAP_CHAIN_DESC sd;
		pSwapChain->GetDesc(&sd);
		// Create the render target
		ID3D11Texture2D* pBackBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
		ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
		render_target_view_desc.Format = sd.BufferDesc.Format;
		render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)&pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, &render_target_view_desc, &g_mainRenderTargetView);
		pContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);

		// GetBufferSize
		D3D11_TEXTURE2D_DESC desc;
		pBackBuffer->GetDesc(&desc);
		Width = desc.Width;
		Height = desc.Height;

		pBackBuffer->Release();
	}

	bool Initialize()
	{
		IDXGISwapChain* pSwapChain;
		HWND hWnd = FindWindowA("TankWindowClass", NULL);

		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.Windowed = TRUE; //((GetWindowLong(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		fn_D3D11CreateDeviceAndSwapChain_t D3D11CreateDeviceAndSwapChain_t = (fn_D3D11CreateDeviceAndSwapChain_t)(GetProcAddress(GetModuleHandleA("d3d11.dll"), "D3D11CreateDeviceAndSwapChain"));

		if (FAILED(D3D11CreateDeviceAndSwapChain_t(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &featureLevel, 1
			, D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, NULL, &pContext)))
		{
			MessageBox(hWnd, "Failed to create D3D11 device and DXGISwapChain!", "Error", MB_ICONERROR);
			return false;
		}

		DWORD_PTR* pSwapChainVtable = (DWORD64*)pSwapChain;
		pSwapChainVtable = (DWORD64*)pSwapChainVtable[0];


		phookD3D11Present = (D3D11PresentHook)(DWORD64*)pSwapChainVtable[8];
		phookD3D11ResizeBuffer = (D3D11ResizeBuffersHook)(DWORD64*)pSwapChainVtable[13];

		pSwapChain->Release();
		pDevice->Release();
		pContext->Release();

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		if (DetourAttach(&(LPVOID&)phookD3D11Present, hkD3D11Present) != NO_ERROR)
			MessageBox(hWnd, "Failed to Detours", "Error", MB_ICONERROR);
		if (DetourAttach(&(LPVOID&)phookD3D11ResizeBuffer, hookD3D11ResizeBuffers) != NO_ERROR)
			MessageBox(hWnd, "Failed to Detours", "Error", MB_ICONERROR);
		DetourTransactionCommit();


		return true;
	}

	bool Uninitialize()
	{
		HWND hWnd = FindWindowA("TankWindowClass", NULL);

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		if (DetourDetach(&(PVOID&)phookD3D11Present, (PBYTE)hkD3D11Present) != NO_ERROR)
			MessageBox(hWnd, "Failed to Detours", "Error", MB_ICONERROR);
		if (DetourDetach(&(PVOID&)phookD3D11ResizeBuffer, (PBYTE)hookD3D11ResizeBuffers) != NO_ERROR)
			MessageBox(hWnd, "Failed to Detours", "Error", MB_ICONERROR);
		DetourTransactionCommit();
		return true;
	}


	LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
		{
			switch (wParam)
			{
			case MK_MBUTTON:
				LastPressedKey = VK_MBUTTON;
				break;
			case MK_XBUTTON1:
				LastPressedKey = VK_XBUTTON1;
				break;
			case MK_XBUTTON2:
				LastPressedKey = VK_XBUTTON2;
				break;
			default:
				LastPressedKey = wParam;
				break;
			}
			break;
		}
		case WM_KEYDOWN:
		{
			LastPressedKey = wParam;
			break;
		}
		}


		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return TRUE;


		return CallWindowProcA((WNDPROC)m_ulOldWndProc, hWnd, msg, wParam, lParam);
	}
}