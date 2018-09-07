#include "stdafx.h"
#include "Render.h"

#include "../ImGui/imgui.h"

Render& Render::GetInstance()
{
	static Render _Ins;
	return _Ins;
}

void Render::Init()
{
	printf("Render Init");

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();

	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Courier New.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesChinese());

}