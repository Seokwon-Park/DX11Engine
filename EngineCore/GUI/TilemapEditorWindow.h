#pragma once
#include <EngineCore/GUI/EngineImGuiWindow.h>
#include <EngineCore/Components/TilemapComponent.h>
#include <EngineCore/Components/TilemapRendererComponent.h>

// Ό³Έν :
class UTilemapEditorWindow : public UEngineImGuiWindow
{
public:
	// constrcuter destructer
	ENGINE_API UTilemapEditorWindow(class ULevel* _Level);
	ENGINE_API ~UTilemapEditorWindow();

	// delete Function
	UTilemapEditorWindow(const UTilemapEditorWindow& _Other) = delete;
	UTilemapEditorWindow(UTilemapEditorWindow&& _Other) noexcept = delete;
	UTilemapEditorWindow& operator=(const UTilemapEditorWindow& _Other) = delete;
	UTilemapEditorWindow& operator=(UTilemapEditorWindow&& _Other) noexcept = delete;

	virtual void OnImGuiRender() override;

	ENGINE_API void SetTilemap(std::shared_ptr<UTilemapComponent> _TilemapComponent) { SetTilemap(_TilemapComponent.get()); }
	ENGINE_API void SetTilemap(UTilemapComponent* _TilemapComponent) { TilemapComponent = _TilemapComponent; }

	UTilemapComponent* TilemapComponent = nullptr;
protected:

private:
	FIntPoint Start{ 0,0 };
	FIntPoint TileSize = { 10,10 };

	bool IsFlip = false;

	std::shared_ptr<URenderUnit> PreviewTile;

	class ULevel* Level = nullptr;
	size_t SelectItem = 0;
};

