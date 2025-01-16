#pragma once
#include "ActorComponent.h"
#include <EngineCore/ResourceManager.h>
#include <EngineCore/Resources/EngineTilemap.h>
#include <EngineBase/EngineDebug.h>


// 클래스 설명 :
class UTilemapComponent : public UActorComponent
{
	friend class UTilemapRendererComponent;
	friend class UTilemapColliderComponent;
	friend class UTilemapEditorWindow;
public:
	// Constrcuter Destructer
	ENGINE_API UTilemapComponent();
	ENGINE_API ~UTilemapComponent();

	// Delete Function
	UTilemapComponent(const UTilemapComponent& _Other) = delete;
	UTilemapComponent(UTilemapComponent&& _Other) noexcept = delete;
	UTilemapComponent& operator=(const UTilemapComponent& _Other) = delete;
	UTilemapComponent& operator=(UTilemapComponent&& _Other) noexcept = delete;

	// 게임 실행시 타일맵 로드 함수
	ENGINE_API inline void Load(std::string_view _TilemapName)
	{
		Tilemap = UResourceManager::Find<UEngineTilemap>(_TilemapName);
		if (Tilemap == nullptr)
		{
			MSGASSERT("Fail");
			return;
		}
		SpriteName = Tilemap->SpriteName;
		TileSize = Tilemap->TileSize;
		TilePivot = Tilemap->TilePivot;
	}

	//타일맵 에디터에서 사용할 함수
	ENGINE_API inline void CreateNewTilemap(std::string _SpriteName, FVector2 _TileSize, FVector2 _TilePivot)
	{
		Tilemap = std::make_shared<UEngineTilemap>();
		Tilemap->SpriteName = _SpriteName;
		Tilemap->TileSize = _TileSize;
		Tilemap->TilePivot = _TilePivot;
		SpriteName = _SpriteName;
		TileSize = _TileSize;
		TilePivot = _TilePivot;
	}

	//Tile Data로 재구성
	ENGINE_API void SetTile(FIntPoint _MousePos, FTileData _TileSetting);
	ENGINE_API void SetTile(int _TileCoordX, int _TileCoordY, FTileData _TileSetting);
	ENGINE_API void RemoveTile(FIntPoint _MousePos);
	ENGINE_API void RemoveTile(int _TileCoordX, int _TileCoordY);

	ENGINE_API FTileData* IsTileExist(FIntPoint _MousePos);
	ENGINE_API FTileData* GetTile(FTileIndex _TileIndex);

	inline size_t GetSize() { return Tilemap->GetSize(); }

	FTileIndex WorldPosToTileIndex(FIntPoint _Pos);
	FVector4 TileIndexToWorldPos(FTileIndex _Index);

	void SaveTilemap(UEngineDirectory _Dir, std::string_view _FileName);
protected:

private:
	std::string SpriteName;
	FVector2 TileSize;
	FVector2 TilePivot;

	std::shared_ptr<UEngineTilemap> Tilemap;
};
