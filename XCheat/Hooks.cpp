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
			//��ȡ�󻺳�����ַ
			if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
				reinterpret_cast<PVOID*>(&renderTargetTexture))))
			{
				//����Ŀ����ͼ
				g_pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &g_pRenderTargetView);
				//�ͷź󻺳�
				renderTargetTexture->Release();
			}

			//��ʼ��ImGUI
			ImGui_ImplDX11_Init(hWindow, g_pDevice, g_pContext);
			ImGui_ImplDX11_CreateDeviceObjects();

			ImGui::StyleColorsDark();
		}

		g_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

		//��ͣ�Ļ��������
		ImGui_ImplDX11_NewFrame();

		if (g_bShowWindow)
		{
			ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(300, 300));

			ImGui::Begin(u8"Hooker������", &g_bShowWindow);

			if (ImGui::CollapsingHeader(u8"����"))
			{
				ImGui::Checkbox(u8"͸��", &g_bClose_ZEnable);
				ImGui::Checkbox(u8"��ɫ", &g_bColouring);
			}

			if (g_bClose_ZEnable)
			{
				//͸�ӹ��ܿ���
				printf("����͸��\n");
			}

			if (g_bColouring)
			{
				printf("��ʼ��ɫ\n");
			}

			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return g_pD3DPresent(pSwapChain, SyncInterval, Flags);
	}

}