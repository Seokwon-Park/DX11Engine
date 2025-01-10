#pragma once
#include <EngineCore/GUI/EngineImGuiWindow.h>

// Ό³Έν :
class UTilemapEditorWindow : public UEngineImGuiWindow
{
public:
	// constrcuter destructer
	UTilemapEditorWindow(class ULevel* _Level);
	~UTilemapEditorWindow();

	// delete Function
	UTilemapEditorWindow(const UTilemapEditorWindow& _Other) = delete;
	UTilemapEditorWindow(UTilemapEditorWindow&& _Other) noexcept = delete;
	UTilemapEditorWindow& operator=(const UTilemapEditorWindow& _Other) = delete;
	UTilemapEditorWindow& operator=(UTilemapEditorWindow&& _Other) noexcept = delete;

	virtual void OnImGuiRender() override;

protected:

private:
	class ULevel* Level = nullptr;
	int SelectItem = 0;
};

