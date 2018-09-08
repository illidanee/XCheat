#pragma once

extern ID3D11Device*				g_pDevice;
extern ID3D11DeviceContext*			g_pContext;
extern IDXGISwapChain*				g_pSwapChain;
extern ID3D11RenderTargetView*		g_pRenderTargetView;

class CCheatGame
{
public:
	CCheatGame();
	~CCheatGame();

	void Init();
	void Done();
};

