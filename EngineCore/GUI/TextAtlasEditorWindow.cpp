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

	if (true == ImGui::Button("CreateFontAtlas"))
	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources");
		Dir.AppendDirectory("Fonts");
		UEngineFile File = Dir.GetFile("NanumGothic.ttf");
		UEngineFont::CreateNew("NanumGothic", Dir);
	}

	auto tex = UResourceManager::Find<UEngineTexture2D>("NanumGothic");
	if (tex != nullptr)
	{
		ImTextureID id = reinterpret_cast<ImTextureID>(tex->GetSRV());
		ImGui::Image(id, { 600,600 });
	}



	ImGui::End();
}
