#include "stdafx.h"
#include "Helpers.h"

#include "detours.h"

void CHelpers::HookFunction(PVOID *ppPointer, PVOID pDetour)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	DetourAttach(ppPointer, pDetour);

	DetourTransactionCommit();
}


void CHelpers::UnHookFunction(PVOID *ppPointer, PVOID pDetour)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	DetourDetach(ppPointer, pDetour);

	DetourTransactionCommit();
}
