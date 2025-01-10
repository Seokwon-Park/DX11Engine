#pragma once
#include "RendererComponent.h"
#include <EngineCore/Resources/EngineSprite.h>

struct FTileIndex
{
	union
	{
		struct
		{
			int X;
			int Y;
		};
		__int64 Key;
	};
};


struct FTileData
{
	bool IsBlock = false;
	int SpriteIndex = 0;
	FTileIndex Index;
	FSpriteData SpriteData;
};

// 설명 :
class UTilemapRendererComponent : public URendererComponent
{
public:
	// constrcuter destructer
	ENGINE_API UTilemapRendererComponent();
	ENGINE_API ~UTilemapRendererComponent();

	// delete Function
	UTilemapRendererComponent(const UTilemapRendererComponent& _Other) = delete;
	UTilemapRendererComponent(UTilemapRendererComponent&& _Other) noexcept = delete;
	UTilemapRendererComponent& operator=(const UTilemapRendererComponent& _Other) = delete;
	UTilemapRendererComponent& operator=(UTilemapRendererComponent&& _Other) noexcept = delete;

	ENGINE_API std::string GetCurSpriteName()
	{
		return Sprite->GetName();
	}

	// 시작할때 맵크기를 다 정하고 시작합니다.
	// 그런데 Unordered map이되면 중간에 얼마든지 크기를 기울수 있습니다.
	// ENGINEAPI void CreateTileMap(int _X, int _Y, )

	ENGINE_API void SetTileSetting(std::string_view _Name, FVector2 _TileSize, FVector2 _ImageSize, FVector2 _Pivot);

	ENGINE_API void SetTile(FIntPoint _Pos, int _SpriteIndex);
	// 없으면 만들어요.
	ENGINE_API void SetTile(int _X, int _Y, int _SpriteIndex);

	FVector4 TileIndexToWorldPos(FTileIndex _Pos);
	FTileIndex WorldPosToTileIndex(FIntPoint _Pos);

protected:
	ENGINE_API void Render(class UCameraComponent* _Camera, float _DeltaTime) override;
	void BeginPlay() override;
	void TickComponent(float _DeltaTime) override;

private:
	std::shared_ptr<URenderUnit> Unit;
	bool IsAutoScale = true;
	float AutoScaleRatio = 1.0f;

	FVector2 TileSize;
	FVector2 ImageSize;
	FVector2 TilePivot;

	class UEngineSprite* Sprite = nullptr;
	// map보다 빠르다.
// hash 기반의 맵이다.
// 이건 꼭 이론적으로 추후에 설명해줘야 합니다.
// std::vector<std::vector> 
// 중간 확장이 될수 있다.
// 2D 이미지만 가능
	std::unordered_map<__int64, FTileData> Tiles;
};
