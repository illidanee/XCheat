#include "stdafx.h"
#include "CheatGame.h"

#include <iostream>

#include "Helpers.h"
#include "Hooks.h"
#include "Render.h"

ID3D11Device*  pDevice;
ID3D11DeviceContext * pContext;
IDXGISwapChain * pSwapChain;

CCheatGame::CCheatGame()
{
}


CCheatGame::~CCheatGame()
{
}


void CCheatGame::Init()
{
	AllocConsole();
	freopen("CON", "w", stdout);
	SetConsoleTitle(L"Cheat Game");


	HWND hWindow = FindWindow(NULL, L"Sniper3");

	//������
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));   //���0

	scd.BufferCount = 1;                              //����ֻ����һ���󻺳壨˫���壩���Ϊ1
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  //������ɫ��ʽ,����ʹ��RGBA
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;  //���ű�
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //ɨ����
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  //��ȾĿ�����
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //����ģʽ�л�
	scd.OutputWindow = hWindow;  //����Ϸ�����ڲ���������һ������
	scd.SampleDesc.Count = 1;                      //1�ز���
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;      //���ò���
	scd.Windowed = ((GetWindowLongPtr(hWindow, GWL_STYLE) & WS_POPUP) != 0) ? false : true;  //�Ƿ�ȫ��
	scd.BufferDesc.Width = 1920;
	scd.BufferDesc.Height = 1080;
	scd.BufferDesc.RefreshRate.Numerator = 144;     //ˢ����
	scd.BufferDesc.RefreshRate.Denominator = 1;     //��ĸ
	scd.SampleDesc.Quality = 0;                     //�����ȼ�

	D3D_FEATURE_LEVEL featrueLevel = D3D_FEATURE_LEVEL_11_0;

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL, &featrueLevel,
		1,
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		NULL,
		&pContext
	);

	printf("pSwapChain:%X\n", pSwapChain);
	printf("pDevice:%X\n", pDevice);
	printf("pContext:%X\n", pContext);

	DWORD_PTR** pSwapChainObj = reinterpret_cast<DWORD_PTR**>(pSwapChain);

	DWORD_PTR* pSwapChainVT = pSwapChainObj[0];

	Hooks::pD3DPresent = reinterpret_cast<Hooks::D3DPresent>(pSwapChainVT[8]);

	Render::GetInstance().Init();

	CHelpers::HookFunction(reinterpret_cast<PVOID*>(&Hooks::pD3DPresent), Hooks::MyPresent);
}


void CCheatGame::Done()
{
	CHelpers::UnHookFunction(reinterpret_cast<PVOID*>(&Hooks::pD3DPresent), Hooks::MyPresent);

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();
}