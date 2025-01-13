#pragma once
#include <EngineCore/GUI/EngineImGuiWindow.h>
#include <EngineCore/Components/TilemapComponent.h>
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

	UTilemapComponent * Tilemap = nullptr;
protected:

private:
	FIntPoint Start{ 0,0 };
	FIntPoint TileSize = { 10,10 };



	class ULevel* Level = nullptr;
	size_t SelectItem = 0;
};

