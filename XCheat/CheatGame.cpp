#include "stdafx.h"
#include "CheatGame.h"

#include "Helpers.h"
#include "Hooks.h"
#include "Render.h"

#include "UserInterface.h"
#include "Input.h"

ID3D11Device*				g_pDevice;
ID3D11DeviceContext*		g_pContext;
IDXGISwapChain*				g_pSwapChain;
ID3D11RenderTargetView*		g_pRenderTargetView;

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

	//交换链
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));   //填充0

	scd.BufferCount = 1;                              //我们只创建一个后缓冲（双缓冲）因此为1
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  //设置颜色格式,我们使用RGBA
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;  //缩放比
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //扫描线
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  //渲染目标输出
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //允许模式切换
	scd.OutputWindow = hWindow;  //在游戏窗体内部绘制另外一个窗口
	scd.SampleDesc.Count = 1;                      //1重采样
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;      //常用参数
	scd.Windowed = ((GetWindowLongPtr(hWindow, GWL_STYLE) & WS_POPUP) != 0) ? false : true;  //是否全屏
	scd.BufferDesc.Width = 1920;
	scd.BufferDesc.Height = 1080;
	scd.BufferDesc.RefreshRate.Numerator = 144;     //刷新率
	scd.BufferDesc.RefreshRate.Denominator = 1;     //分母
	scd.SampleDesc.Quality = 0;                     //采样等级

	D3D_FEATURE_LEVEL featrueLevel = D3D_FEATURE_LEVEL_11_0;

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL, &featrueLevel,
		1,
		D3D11_SDK_VERSION,
		&scd,
		&g_pSwapChain,
		&g_pDevice,
		NULL,
		&g_pContext
	);

	printf("pSwapChain:%X\n", g_pSwapChain);
	printf("pDevice:%X\n", g_pDevice);
	printf("pContext:%X\n", g_pContext);

	DWORD_PTR** pSwapChainObj = reinterpret_cast<DWORD_PTR**>(g_pSwapChain);
	DWORD_PTR** pContextObj = reinterpret_cast<DWORD_PTR**>(g_pContext);

	DWORD_PTR* pSwapChainVT = pSwapChainObj[0];
	DWORD_PTR* pContextVT = pContextObj[0];

	Hooks::g_pD3DPresent = reinterpret_cast<Hooks::D3DPresent>(pSwapChainVT[8]);
	Hooks::g_pD3DDrawIndexed = reinterpret_cast<Hooks::D3DDrawIndexed>(pContextVT[12]);

	Render::GetInstance().Init();
	UserInterface::GetInstance()->SetStyle();
	Input::GetInstance()->StartThread();

	CHelpers::HookFunction(reinterpret_cast<PVOID*>(&Hooks::g_pD3DPresent), Hooks::MyPresent);
	CHelpers::HookFunction(reinterpret_cast<PVOID*>(&Hooks::g_pD3DDrawIndexed), Hooks::MyDrawIndexed);
}


void CCheatGame::Done()
{
	CHelpers::UnHookFunction(reinterpret_cast<PVOID*>(&Hooks::g_pD3DPresent), Hooks::MyPresent);
	CHelpers::UnHookFunction(reinterpret_cast<PVOID*>(&Hooks::g_pD3DDrawIndexed), Hooks::MyDrawIndexed);

	Input::GetInstance()->StopThread();

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();
}