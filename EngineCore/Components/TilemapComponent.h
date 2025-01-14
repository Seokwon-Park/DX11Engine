#pragma once
#include "ActorComponent.h"
#include <EngineCore/Resources/EngineSprite.h>
#include <EngineCore/ResourceManager.h>

struct FTileIndex
{
	union
	{
		struct
		{
			int X;
			int Y;
		};
		long long Key;
	};
};

enum class ETileType
{
	Full,
	LeftHalf,
	RightHalf,
};


struct FTileData
{
	bool IsBlock = false;
	int SpriteIndex = -1;
	FTileIndex Index;
	FSpriteRect SpriteRect;
};

// 클래스 설명 :
class UTilemapComponent : public UActorComponent, public ISerializableObject
{
	friend class UTilemapRendererComponent;
	friend class UTilemapColliderComponent;
public:
	// Constrcuter Destructer
	ENGINE_API UTilemapComponent();
	ENGINE_API ~UTilemapComponent();

	// Delete Function
	UTilemapComponent(const UTilemapComponent& _Other) = delete;
	UTilemapComponent(UTilemapComponent&& _Other) noexcept = delete;
	UTilemapComponent& operator=(const UTilemapComponent& _Other) = delete;
	UTilemapComponent& operator=(UTilemapComponent&& _Other) noexcept = delete;

	ENGINE_API std::string GetCurSpriteName()
	{
		return Sprite->GetName();
	}


	ENGINE_API inline void SetTileSetting(std::string_view _SpriteName, FVector2 _ImageSize, FVector2 _Pivot)
	{
		Sprite = UResourceManager::Find<UEngineSprite>(_SpriteName).get();
		ImageSize = _ImageSize;
		TilePivot = _Pivot;
	}

	//Tile Data로 재구성
	ENGINE_API void SetTile(FIntPoint _MousePos, int _SpriteIndex);
	ENGINE_API void SetTile(int _TileCoordX, int _TileCoordY, int _SpriteIndex);
	ENGINE_API void RemoveTile(FIntPoint _MousePos);
	ENGINE_API void RemoveTile(int _TileCoordX, int _TileCoordY);



	ENGINE_API FTileData* GetTile(FIntPoint _MousePos);
	ENGINE_API FTileData* GetTile(FTileIndex _TileIndex);

	FTileIndex WorldPosToTileIndex(FIntPoint _Pos);

	// Inherited via ISerializableObject
	ENGINE_API void Serialize(UEngineSerializer& _Serializer) override;
	ENGINE_API void DeSerialize(UEngineSerializer& _Serializer) override;
protected:

private:
	//타일맵 스프라이트
	class UEngineSprite* Sprite = nullptr;
	
	FVector2 ImageSize;
	FVector2 TilePivot;

	std::unordered_map<long long, FTileData> Tiles;

};
