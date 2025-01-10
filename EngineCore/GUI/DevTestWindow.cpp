#include "EnginePCH.h"
#include "DevTestWindow.h"

UDevTestWindow::UDevTestWindow()
{
	SetName("DevTest");
}

UDevTestWindow::~UDevTestWindow()
{
}

void UDevTestWindow::OnImGuiRender()
{
	ImGui::Begin(GetName().c_str());

	ImGui::End();
}