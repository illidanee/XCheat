#pragma once

namespace Hooks
{
	typedef HRESULT(__stdcall *D3DPresent)(
		IDXGISwapChain* pSwapChain, 
		UINT SyncInterval, 
		UINT Flags);
	extern D3DPresent g_pD3DPresent;

	typedef void(__stdcall *D3DDrawIndexed)(
		ID3D11DeviceContext* pContext,
		UINT IndexCount,
		UINT StartIndexLocation,
		INT BaseVertexLocation);
	extern D3DDrawIndexed g_pD3DDrawIndexed;

	HRESULT __stdcall MyPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	void __stdcall MyDrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
}


