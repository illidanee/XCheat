#pragma once
#include <D3D11.h>
#include <D3Dcompiler.h>

class CCheatGame
{
public:
	CCheatGame();
	~CCheatGame();

	void Init();
	void Done();

private:
	ID3D11Device*  pDevice;
	ID3D11DeviceContext * pContext;
	IDXGISwapChain * pSwapChain;
};

