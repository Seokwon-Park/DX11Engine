#include "EnginePCH.h"
#include "TextAtlasEditorWindow.h"
#include <EngineCore/ResourceManager.h>
#include <EngineCore/Resources/EngineFont.h>


UTextAtlasEditorWindow::UTextAtlasEditorWindow()
{
	SetName("TextAtlasEditor");
}

UTextAtlasEditorWindow::~UTextAtlasEditorWindow()
{
}

void UTextAtlasEditorWindow::OnImGuiRender()
{
	ImGui::Begin(GetName().c_str());

	//auto List = UResourceManager::GetAllResources<UEngineFont>();
	//std::vector<const char*> temp;
	//for (auto a : List)
	//{
	//	temp.push_back(a->GetName().c_str());
	//}
	//ImGui::ListBox("Font", nullptr, temp.data(), List.size());

	ImGui::End();
}
