#pragma once
#include <EngineCore/GUI/EngineImGuiWindow.h>
#include <EngineCore/Components/TilemapRendererComponent.h>

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

	UTilemapRendererComponent * TileMapRenderer = nullptr;
protected:

private:
	int TileCountX = 10;
	int TileCountY = 10;


	class ULevel* Level = nullptr;
	int SelectItem = 0;
};

