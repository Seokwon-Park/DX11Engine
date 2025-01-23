#include "EnginePCH.h"
#include "DevTestWindow.h"
#include "EngineCore.h"

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

	for (std::pair<const std::string, std::shared_ptr<class ULevel>>& Pair : UEngineCore::Levels)
	{
		if (ImGui::Button(Pair.first.c_str()))
		{
			UEngineCore::OpenLevel(Pair.first);
		}
	}

	ImGui::End();
}