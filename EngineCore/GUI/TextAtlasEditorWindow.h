#pragma once
#include <EngineCore/GUI/EngineImGuiWindow.h>

// Ό³Έν :
class TextAtlasEditorWindow : public UEngineImGuiWindow
{
public:
	// constrcuter destructer
	TextAtlasEditorWindow();
	~TextAtlasEditorWindow();

	// delete Function
	TextAtlasEditorWindow(const TextAtlasEditorWindow& _Other) = delete;
	TextAtlasEditorWindow(TextAtlasEditorWindow&& _Other) noexcept = delete;
	TextAtlasEditorWindow& operator=(const TextAtlasEditorWindow& _Other) = delete;
	TextAtlasEditorWindow& operator=(TextAtlasEditorWindow&& _Other) noexcept = delete;

	virtual void OnImGuiRender() override;
protected:

private:

};

