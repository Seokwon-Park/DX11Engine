#pragma once
#include "ActorComponent.h"
#include <EngineCore/ResourceManager.h>
#include <EngineCore/Resources/EngineTilemap.h>


// 클래스 설명 :
class UTilemapComponent : public UActorComponent
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

	ENGINE_API inline void Load(std::string_view _TilemapName)
	{
		Tilemap = UResourceManager::Find<UEngineTilemap>(_TilemapName);
		SpriteName = Tilemap->SpriteName;
		TileSize = Tilemap->TileSize;
		TilePivot = Tilemap->TilePivot;
	}

	ENGINE_API inline void CreateNewTilemap(FVector2 _ImageSize, FVector2 )
	{
		Tilemap = std::make_shared<UEngineTilemap>();
	}

	//Tile Data로 재구성
	ENGINE_API void SetTile(FIntPoint _MousePos, int _SpriteIndex);
	ENGINE_API void SetTile(int _TileCoordX, int _TileCoordY, int _SpriteIndex);
	ENGINE_API void RemoveTile(FIntPoint _MousePos);
	ENGINE_API void RemoveTile(int _TileCoordX, int _TileCoordY);

	ENGINE_API FTileData* IsTileExist(FIntPoint _MousePos);
	ENGINE_API FTileData* GetTile(FTileIndex _TileIndex);

	inline size_t GetSize() { return Tilemap->GetSize(); }

	FTileIndex WorldPosToTileIndex(FIntPoint _Pos);
	FVector4 TileIndexToWorldPos(FTileIndex _Pos);

	void SaveTilemap(UEngineDirectory _Dir, std::string_view _FileName);
protected:

private:
	std::string SpriteName;
	FVector2 TileSize;
	FVector2 TilePivot;

	std::shared_ptr<UEngineTilemap> Tilemap;
};
