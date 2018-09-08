#include "stdafx.h"
#include "Hooks.h"
#include "CheatGame.h"

namespace Hooks
{
	D3DPresent g_pD3DPresent = nullptr;
	bool g_bInit = false;
	bool g_bShowWindow = true;
	bool g_bClose_ZEnable = false;
	bool g_bColouring = false;

	HRESULT __stdcall MyPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		if (!g_bInit)
		{
			g_bInit = true;

			HWND hWindow = FindWindow(NULL, L"Sniper3");
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)(&g_pDevice))))
			{
				pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)(&g_pDevice));
				g_pDevice->GetImmediateContext(&g_pContext);
			}

			ID3D11Texture2D* renderTargetTexture = nullptr;
			//获取后缓冲区地址
			if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
				reinterpret_cast<PVOID*>(&renderTargetTexture))))
			{
				//创建目标视图
				g_pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &g_pRenderTargetView);
				//释放后缓冲
				renderTargetTexture->Release();
			}

			//初始化ImGUI
			ImGui_ImplDX11_Init(hWindow, g_pDevice, g_pContext);
			ImGui_ImplDX11_CreateDeviceObjects();

			ImGui::StyleColorsDark();
		}

		g_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

		//不停的画插件界面
		ImGui_ImplDX11_NewFrame();

		if (g_bShowWindow)
		{
			ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(300, 300));

			ImGui::Begin(u8"Hooker：张亮", &g_bShowWindow);

			if (ImGui::CollapsingHeader(u8"功能"))
			{
				ImGui::Checkbox(u8"透视", &g_bClose_ZEnable);
				ImGui::Checkbox(u8"上色", &g_bColouring);
			}

			if (g_bClose_ZEnable)
			{
				//透视功能开启
				printf("开启透视\n");
			}

			if (g_bColouring)
			{
				printf("开始上色\n");
			}

			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return g_pD3DPresent(pSwapChain, SyncInterval, Flags);
	}

}