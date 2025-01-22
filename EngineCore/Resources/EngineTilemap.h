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
	
	// 만들어놓은 타일맵을 로드하는 함수
	ENGINE_API static std::shared_ptr<UEngineTilemap> Load(std::string_view _Name, std::string_view _Path);
	void LoadTilemapFromPath(std::string_view _Path);
	ENGINE_API static std::shared_ptr<UEngineTilemap> Create(std::string_view _SpriteName, FVector2 _TileSize, FVector2 _TilePivot);

	//타일맵 로드
	ENGINE_API void Serialize(UEngineSerializer& _Serializer) override;
	ENGINE_API void Deserialize(UEngineSerializer& _Serializer) override;
private:
	std::string SpriteName;
	FVector2 TileSize;
	FVector2 TilePivot;

	std::unordered_map<long long, FTileData> TilemapData;
};

