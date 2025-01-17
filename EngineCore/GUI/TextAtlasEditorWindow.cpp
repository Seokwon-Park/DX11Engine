#include "EnginePCH.h"
#include "TextAtlasEditorWindow.h"
#include <EngineCore/ResourceManager.h>
#include <EngineCore/Resources/EngineFont.h>


TextAtlasEditorWindow::TextAtlasEditorWindow()
{
	SetName("TextAtlasEditor");
}

TextAtlasEditorWindow::~TextAtlasEditorWindow()
{
}

void TextAtlasEditorWindow::OnImGuiRender()
{
	ImGui::Begin(GetName().c_str());

	auto List = UResourceManager::GetAllResources<UEngineFont>();

	ImGui::End();
}
