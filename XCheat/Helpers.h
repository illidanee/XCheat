#pragma once
class CHelpers
{
public:
	static void HookFunction(PVOID *ppPointer, PVOID pDetour);
	static void UnHookFunction(PVOID *ppPointer, PVOID pDetour);
};

