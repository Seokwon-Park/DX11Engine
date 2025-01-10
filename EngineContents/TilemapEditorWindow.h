#pragma once
#include <EngineCore/GUI/EngineImGuiWindow.h>
#include <EngineCore/Components/TilemapRendererComponent.h>

// ���� :
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

	UTilemapRendererComponent * TilemapRenderer = nullptr;
protected:

private:
	FIntPoint Start{ 0,0 };
	FIntPoint TileSize = { 10,10 };



	class ULevel* Level = nullptr;
	int SelectItem = 0;
};

