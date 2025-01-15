#pragma once
#include "EngineResource.h"
#include <unordered_map>
#include <EngineBase/EngineIO.h>
#include <EngineCore/Structures/EngineDataStructure.h>

// 설명 :
class UEngineTilemap : public UEngineResource, public ISerializableObject
{
	friend class UTilemapComponent;
public:
	UEngineTilemap();
	virtual ~UEngineTilemap();

	// delete Function
	UEngineTilemap(const UEngineTilemap& _Other) = delete;
	UEngineTilemap(UEngineTilemap&& _Other) noexcept = delete;
	UEngineTilemap& operator=(const UEngineTilemap& _Other) = delete;
	UEngineTilemap& operator=(UEngineTilemap&& _Other) noexcept = delete;

	inline FVector2 GetTileSize() const { return TileSize; }
	inline FVector2 GetTilePivot() const { return TilePivot; }
	inline std::string GetSpriteName() const { return SpriteName; }

	inline void Erase(FTileIndex _Index) { TilemapData.erase(_Index.Key); }
	inline bool Contains(FTileIndex _Index) { return TilemapData.contains(_Index.Key); }
	inline size_t GetSize() { return TilemapData.size(); }
	inline FTileData& GetTile(FTileIndex _Index) { return TilemapData[_Index.Key]; }
	inline std::unordered_map<long long, FTileData>& GetTilemapData() { return TilemapData; }
	
	//타일맵 로드
	ENGINE_API void Serialize(UEngineSerializer& _Serializer) override;
	ENGINE_API void DeSerialize(UEngineSerializer& _Serializer) override;
private:
	std::string SpriteName;
	FVector2 TileSize;
	FVector2 TilePivot;

	std::unordered_map<long long, FTileData> TilemapData;
};

