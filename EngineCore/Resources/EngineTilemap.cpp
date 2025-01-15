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

std::shared_ptr<UEngineTilemap> UEngineTilemap::Create(std::string_view _Name, std::string_view _Path)
{
	std::shared_ptr<UEngineTilemap> NewTilemap = std::make_shared<UEngineTilemap>();
	UEnginePath Path = _Path;
	std::string Name = Path.GetFileNameWithoutExtension();
	NewTilemap->LoadTilemapFromPath(_Path);
	UResourceManager::AddResource<UEngineTilemap>(NewTilemap, Name, _Path);
	return NewTilemap;
}

void UEngineTilemap::LoadTilemapFromPath(std::string_view _Path)
{
	UEngineFile NewFile = _Path;
	UEngineSerializer Ser;

	NewFile.FileOpen("rb");
	NewFile.Read(Ser);

	Deserialize(Ser);
}

std::shared_ptr<UEngineTilemap> UEngineTilemap::Create(std::string_view _SpriteName, FVector2 _TileSize, FVector2 _TilePivot)
{
	std::shared_ptr<UEngineTilemap> NewTilemap = std::make_shared<UEngineTilemap>();
	NewTilemap->TileSize = _TileSize;
	NewTilemap->TileSize = _TileSize;

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

ENGINE_API void UEngineTilemap::Deserialize(UEngineSerializer& _Serializer)
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


