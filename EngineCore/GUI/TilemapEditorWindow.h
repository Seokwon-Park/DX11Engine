#pragma once
#include <EngineCore/GUI/EngineImGuiWindow.h>
#include <EngineCore/Components/TilemapComponent.h>
#include <EngineCore/Components/TilemapColliderComponent.h>
#include <EngineCore/Components/TilemapRendererComponent.h>

// 설명 :
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

	ENGINE_API void SetTilemapCollider(std::shared_ptr<UTilemapColliderComponent> _TilemapColliderComponent) { SetTilemapCollider(_TilemapColliderComponent.get()); }
	ENGINE_API void SetTilemapCollider(UTilemapColliderComponent* _TilemapColliderComponent) { TilemapColliderComponent = _TilemapColliderComponent; }

	UTilemapComponent* TilemapComponent = nullptr;
	UTilemapColliderComponent* TilemapColliderComponent = nullptr;

protected:

private:
	// 타일의 모양을 결정하는 블럭
	int currentIndex = 0;

	FTileData EditorSetting;

	FIntPoint Start{ 0,0 };
	FIntPoint TileSize = { 10,10 };

	bool IsFlip = false;
	Uint32 Rotate = 0;

	std::shared_ptr<URenderUnit> PreviewTile;

	class ULevel* Level = nullptr;
	size_t SelectItem = 0;
	int SelectSprite = 0;
};

