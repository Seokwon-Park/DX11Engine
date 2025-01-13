#include "EnginePCH.h"
#include "TilemapComponent.h"

UTilemapComponent::UTilemapComponent()
{
}

UTilemapComponent::~UTilemapComponent()
{
}

void UTilemapComponent::SetTile(FIntPoint _Pos, int _SpriteIndex)
{
	FTileIndex Index = WorldPosToTileIndex(_Pos);

	SetTile(Index.X, Index.Y, _SpriteIndex);
}

void UTilemapComponent::SetTile(int _X, int _Y, int _Spriteindex)
{
	FTileIndex Index = { _X,  _Y };

	FTileData& NewTile = Tiles[Index.Key];

	NewTile.Index = Index;
	NewTile.SpriteIndex = _Spriteindex;
	NewTile.SpriteRect.CuttingPos = { 0.0f, 0.0f };
	NewTile.SpriteRect.CuttingSize = { 1.0f, 1.0f };
	NewTile.SpriteRect.Pivot = { 0.5f, 0.5f };
}

FTileData* UTilemapComponent::GetTile(FIntPoint _Pos)
{
	FTileIndex Index = WorldPosToTileIndex(_Pos);

	return GetTile(Index);
}

FTileData* UTilemapComponent::GetTile(FTileIndex _TileIndex)
{
	if (false ==Tiles.contains(_TileIndex.Key))
	{
		return nullptr;
	}
	return &Tiles[_TileIndex.Key];
}

FTileIndex UTilemapComponent::WorldPosToTileIndex(FIntPoint _Pos)
{
	FTileIndex Result = FTileIndex();
	FIntPoint ConvertVector;

	// 정수 나눗셈 대신 내림(floor) 사용
	ConvertVector.X = static_cast<int>(std::floor(static_cast<float>(_Pos.X) / ImageSize.X));
	ConvertVector.Y = static_cast<int>(std::floor(static_cast<float>(_Pos.Y) / ImageSize.Y));

	Result.X = ConvertVector.X;
	Result.Y = ConvertVector.Y;
	return Result;
}

void UTilemapComponent::Serialize(UEngineSerializer& _Serializer)
{
	_Serializer << ImageSize;
	_Serializer << TilePivot;
	std::string Name = Sprite->GetName();
	_Serializer << Name;

	_Serializer << static_cast<int>(Tiles.size());
	for (std::pair<const long long, FTileData>& Pair : Tiles)
	{
		_Serializer.Write(&Pair.second, sizeof(FTileData));
	}
}

void UTilemapComponent::DeSerialize(UEngineSerializer& _Serializer)
{
	Tiles.clear();

	_Serializer >> ImageSize;
	_Serializer >> TilePivot;
	std::string Name;
	_Serializer >> Name;


	int Count = 0;
	_Serializer >> Count;
	for (size_t i = 0; i < Count; i++)
	{
		FTileData TileData;
		_Serializer.Read(&TileData, sizeof(TileData));
		Tiles.insert({ TileData.Index.Key, TileData });
	}
}
