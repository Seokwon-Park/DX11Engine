#pragma once
#include <EngineCore/GUI/EngineImGuiWindow.h>

// Ό³Έν :
class UTextAtlasEditorWindow : public UEngineImGuiWindow
{
public:
	// constrcuter destructer
	ENGINE_API UTextAtlasEditorWindow();
	ENGINE_API ~UTextAtlasEditorWindow();

	// delete Function
	UTextAtlasEditorWindow(const UTextAtlasEditorWindow& _Other) = delete;
	UTextAtlasEditorWindow(UTextAtlasEditorWindow&& _Other) noexcept = delete;
	UTextAtlasEditorWindow& operator=(const UTextAtlasEditorWindow& _Other) = delete;
	UTextAtlasEditorWindow& operator=(UTextAtlasEditorWindow&& _Other) noexcept = delete;

	virtual void OnImGuiRender() override;
protected:

private:

};

