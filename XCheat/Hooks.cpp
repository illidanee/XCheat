#include "stdafx.h"
#include "Hooks.h"


namespace Hooks
{
	D3DPresent pD3DPresent = nullptr;
	bool bInit = false;

	HRESULT __stdcall MyPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		if (!bInit)
		{
			bInit = true;
		}

		//printf("11111111111111111111111111111\n");

		return pD3DPresent(pSwapChain, SyncInterval, Flags);
	}

}