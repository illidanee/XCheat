#include "stdafx.h"
#include "Hooks.h"
#include "CheatGame.h"

namespace Hooks
{
	//车辆判断
#define Car (indesc.ByteWidth == 125616)

	//人物判断
#define Player ( (Stride == 40)\
	&&( (indesc.ByteWidth == 1146)\
	|| (indesc.ByteWidth == 1488)\
	|| (indesc.ByteWidth == 1404)\
	|| (indesc.ByteWidth == 1848)\
	|| (indesc.ByteWidth == 1836)\
	|| (indesc.ByteWidth == 1878)\
	|| (indesc.ByteWidth == 2154)\
	|| (indesc.ByteWidth == 3018)\
	|| (indesc.ByteWidth == 3024)\
	|| (indesc.ByteWidth == 3624)\
	|| (indesc.ByteWidth == 3720)\
	|| (indesc.ByteWidth == 5154)\
    || (indesc.ByteWidth == 6048)\
	|| (indesc.ByteWidth == 6300)\
	|| (indesc.ByteWidth == 12288)\
	|| (indesc.ByteWidth == 12708)\
	|| (indesc.ByteWidth == 13980)\
    || (indesc.ByteWidth == 19524)\
	|| (indesc.ByteWidth == 20940)\
    || (indesc.ByteWidth == 25842)\
	|| (indesc.ByteWidth == 26982)\
    || (indesc.ByteWidth == 34938)\
    || (indesc.ByteWidth == 36012)\
	|| (indesc.ByteWidth == 64170)\
	|| (indesc.ByteWidth == 115434)\
	))

	D3DPresent g_pD3DPresent = nullptr;
	D3DDrawIndexed g_pD3DDrawIndexed = nullptr;

	bool g_bInit = false;
	bool g_bShowWindow = true;
	bool g_bClose_ZEnable = false;
	bool g_bColouring = false;

	bool g_bStride = true;
	int  g_iStride = 40;

	bool g_binByteWidth = true;
	int  g_inByteWidth = 0;

	bool g_bveByteWidth = true;
	int  g_veByteWidth = 0;

	enum eDepthState
	{
		ENABLED,
		DISABLED,
		READ_NO_WRITE,
		NO_READ_NO_WRITE,
		_DEPTH_COUNT
	};

	ID3D11DepthStencilState* myDepthStencilStates[static_cast<int>(eDepthState::_DEPTH_COUNT)];

	ID3D11Buffer *veBuffer;
	UINT Stride = 0;
	UINT veBufferOffset = 0;
	D3D11_BUFFER_DESC vedesc;

	ID3D11Buffer *inBuffer;
	DXGI_FORMAT inFormat;
	UINT        inOffset;
	D3D11_BUFFER_DESC indesc;

	int test_value = 0;

	//上色用的
	ID3D11PixelShader* psRed = NULL;
	ID3D11PixelShader* psGreen = NULL;

	bool showCar = true;

	void SetDepthStencilState(eDepthState aState)
	{
		g_pContext->OMSetDepthStencilState(myDepthStencilStates[aState], 1);
	}

	HRESULT GenerateShader(ID3D11Device* pD3DDevice, ID3D11PixelShader** pShader, float r, float g, float b)
	{
		char szCast[] = "struct VS_OUT"
			"{"
			" float4 Position : SV_Position;"
			" float4 Color : COLOR0;"
			"};"

			"float4 main( VS_OUT input ) : SV_Target"
			"{"
			" float4 fake;"
			" fake.a = 1.0f;"
			" fake.r = %f;"
			" fake.g = %f;"
			" fake.b = %f;"
			" return fake;"
			"}";
		ID3D10Blob* pBlob;
		char szPixelShader[1000];

		sprintf(szPixelShader, szCast, r, g, b);

		ID3DBlob* d3dErrorMsgBlob;

		HRESULT hr = D3DCompile(szPixelShader, sizeof(szPixelShader), "shader", NULL, NULL, "main", "ps_4_0", NULL, NULL, &pBlob, &d3dErrorMsgBlob);

		if (FAILED(hr))
			return hr;

		hr = pD3DDevice->CreatePixelShader((DWORD*)pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pShader);

		if (FAILED(hr))
			return hr;

		return S_OK;
	}

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
			else
			{
				goto end;
			}

			//--------------------------------------------
			D3D11_DEPTH_STENCIL_DESC  stencilDesc;
			stencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
			stencilDesc.StencilEnable = true;
			stencilDesc.StencilReadMask = 0xFF;
			stencilDesc.StencilWriteMask = 0xFF;
			stencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			stencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			stencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			stencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			stencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			stencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			stencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			stencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			//ENABLED
			stencilDesc.DepthEnable = true;
			stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			g_pDevice->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::ENABLED)]);

			//DISABLED
			stencilDesc.DepthEnable = false;
			stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			g_pDevice->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::DISABLED)]);

			//NO_READ_NO_WRITE
			stencilDesc.DepthEnable = false;
			stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			stencilDesc.StencilEnable = false;
			stencilDesc.StencilReadMask = UINT8(0xFF);
			stencilDesc.StencilWriteMask = 0x0;
			g_pDevice->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::NO_READ_NO_WRITE)]);

			//READ_NO_WRITE
			stencilDesc.DepthEnable = true;
			stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			stencilDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
			stencilDesc.StencilEnable = false;
			stencilDesc.StencilReadMask = UINT8(0xFF);
			stencilDesc.StencilWriteMask = 0x0;

			stencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
			stencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
			stencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			stencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

			stencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
			stencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
			stencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_ZERO;
			stencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
			g_pDevice->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::READ_NO_WRITE)]);

			//红色
			if (!psRed)
				GenerateShader(g_pDevice, &psRed, 1.0f, 0.0f, 0.0f);

			//绿色
			if (!psGreen)
				GenerateShader(g_pDevice, &psGreen, 0.0f, 1.0f, 0.0f);

			//初始化ImGUI
			ImGui_ImplDX11_Init(hWindow, g_pDevice, g_pContext);
			ImGui_ImplDX11_CreateDeviceObjects();

			ImGui::StyleColorsDark();

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

			if (ImGui::CollapsingHeader(u8"过滤日志"))
			{
				ImGui::Checkbox("Stride Value", &g_bStride);
				if (g_bStride)
				{
					ImGui::InputInt("Stride", &g_iStride);
					ImGui::SliderInt("Stride: ", &g_iStride, 0, 100);
				}

				ImGui::Checkbox("In-Byte Width", &g_binByteWidth);
				if (g_binByteWidth)
				{
					ImGui::InputInt("inByte", &g_inByteWidth);
					ImGui::SliderInt("inByte: ", &g_inByteWidth, 0, 10000000);
				}

				ImGui::Checkbox("Ve-Byte Width", &g_bveByteWidth);
				if (g_bveByteWidth)
				{
					ImGui::InputInt("veByte", &g_veByteWidth);
					ImGui::SliderInt("veByte: ", &g_veByteWidth, 0, 10000000);
				}
			}

			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

end:
		return g_pD3DPresent(pSwapChain, SyncInterval, Flags);
	}

	void __stdcall MyDrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &veBufferOffset);
		if (veBuffer)
		{
			veBuffer->GetDesc(&vedesc);
			veBuffer->Release();
			veBuffer = NULL;
		}
		else
			goto end;

		pContext->IAGetIndexBuffer(&inBuffer, &inFormat, &inOffset);
		if (inBuffer)
		{
			inBuffer->GetDesc(&indesc);
			inBuffer->Release();
			inBuffer = NULL;
		}
		else
			goto end;

		//--------测试用-------------
		if (GetAsyncKeyState('O') & 1) //-
		{
			test_value = 1000;
			g_inByteWidth -= test_value;
		}
		else if (GetAsyncKeyState('P') & 1) //+
		{
			test_value = 1000;
			g_inByteWidth += test_value;
		}
		else if (GetAsyncKeyState('U') & 1) //-
		{
			test_value = 100;
			g_inByteWidth -= test_value;
		}
		else if (GetAsyncKeyState('I') & 1) //+
		{
			test_value = 100;
			g_inByteWidth += test_value;
		}
		else if (GetAsyncKeyState('T') & 1) //-
		{
			test_value = 10;
			g_inByteWidth -= test_value;
		}
		else if (GetAsyncKeyState('Y') & 1) //+
		{
			test_value = 10;
			g_inByteWidth += test_value;
		}
		else if (GetAsyncKeyState('X') & 1) // == 0
		{
			g_inByteWidth = 0;
			test_value = 0;
		}

		{
			//if ((indesc.ByteWidth >= g_inByteWidth) &&
			//	(indesc.ByteWidth <= g_inByteWidth + test_value))
			//{
			//	printf("%d\n", indesc.ByteWidth);
			//	return g_pD3DDrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
			//}

			//if (indesc.ByteWidth == 115434
			//	|| indesc.ByteWidth == 11088
			//	|| indesc.ByteWidth == 5166)
			//{
			//	SetDepthStencilState(DISABLED);
			//	g_pD3DDrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
			//	SetDepthStencilState(ENABLED);
			//}
		}

		if (Player && (showCar || Car))
		{
			if (g_bClose_ZEnable)
				SetDepthStencilState(DISABLED);

			if (g_bColouring)
				pContext->PSSetShader(psRed, NULL, NULL);

			if (g_bClose_ZEnable)
				g_pD3DDrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);

			if (g_bClose_ZEnable)
				SetDepthStencilState(ENABLED);

			if (g_bColouring)
				pContext->PSSetShader(psGreen, NULL, NULL);
		}
end:
		return g_pD3DDrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
	}
}