#pragma once

namespace Hooks
{
	typedef HRESULT(__stdcall *D3DPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	extern D3DPresent g_pD3DPresent;

	HRESULT __stdcall MyPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
}


