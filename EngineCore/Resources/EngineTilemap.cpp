#include "EnginePCH.h"
#include "EngineTilemap.h"
#include "EngineSprite.h"
#include "ResourceManager.h"

UEngineTilemap::UEngineTilemap()
{
}

UEngineTilemap::~UEngineTilemap()
{
}

void UEngineTilemap::Serialize(UEngineSerializer& _Serializer)
{
	_Serializer << TileSize;
	_Serializer << TilePivot;
	_Serializer << SpriteName;

	_Serializer << static_cast<int>(TilemapData.size());
	for (std::pair<const long long, FTileData>& Pair : TilemapData)
	{
		_Serializer.Write(&Pair.second, sizeof(FTileData));
	}
}

ENGINE_API void UEngineTilemap::DeSerialize(UEngineSerializer& _Serializer)
{
	TilemapData.clear();

	_Serializer >> TileSize;
	_Serializer >> TilePivot;
	_Serializer >> SpriteName;

	int Count = 0;
	_Serializer >> Count;
	for (size_t i = 0; i < Count; i++)
	{
		FTileData TileData;
		_Serializer.Read(&TileData, sizeof(TileData));
		TilemapData.insert({ TileData.Index.Key, TileData });
	}
}


