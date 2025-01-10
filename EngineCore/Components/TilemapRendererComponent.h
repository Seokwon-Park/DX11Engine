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

// ���� :
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

	// �����Ҷ� ��ũ�⸦ �� ���ϰ� �����մϴ�.
	// �׷��� Unordered map�̵Ǹ� �߰��� �󸶵��� ũ�⸦ ���� �ֽ��ϴ�.
	// ENGINEAPI void CreateTileMap(int _X, int _Y, )

	ENGINE_API void SetTileSetting(std::string_view _Name, FVector2 _TileSize, FVector2 _ImageSize, FVector2 _Pivot);

	ENGINE_API void SetTile(FIntPoint _Pos, int _SpriteIndex);
	// ������ ������.
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
	// map���� ������.
// hash ����� ���̴�.
// �̰� �� �̷������� ���Ŀ� ��������� �մϴ�.
// std::vector<std::vector> 
// �߰� Ȯ���� �ɼ� �ִ�.
// 2D �̹����� ����
	std::unordered_map<__int64, FTileData> Tiles;
};
