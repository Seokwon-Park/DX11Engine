#include "EnginePCH.h"
#include "TilemapComponent.h"

UTilemapComponent::UTilemapComponent()
{
}

UTilemapComponent::~UTilemapComponent()
{
}

void UTilemapComponent::SetTile(FIntPoint _Pos, FTileData _TileSetting)
{
	FTileIndex Index = WorldPosToTileIndex(_Pos);

	SetTile(Index.X, Index.Y, _TileSetting);
}

void UTilemapComponent::SetTile(int _X, int _Y, FTileData _TileSetting)
{
	FTileIndex Index = { _X,  _Y };

	_TileSetting.Index = Index;
	Tilemap->TilemapData[Index.Key] = _TileSetting;
}

void UTilemapComponent::RemoveTile(FIntPoint _MousePos)
{
	FTileIndex Index = WorldPosToTileIndex(_MousePos);

	RemoveTile(Index.X, Index.Y);
}

void UTilemapComponent::RemoveTile(int _TileCoordX, int _TileCoordY)
{
	FTileIndex Index = { _TileCoordX,  _TileCoordY };

	if (false == Tilemap->Contains(Index))
	{
		return;
	}

	Tilemap->Erase(Index);
}

FTileData* UTilemapComponent::IsTileExist(FIntPoint _Pos)
{
	FTileIndex Index = WorldPosToTileIndex(_Pos);

	return GetTile(Index);
}

FTileData* UTilemapComponent::GetTile(FTileIndex _TileIndex)
{
	if (false == Tilemap->Contains(_TileIndex))
	{
		return nullptr;
	}
	return &Tilemap->GetTile(_TileIndex);
}

FTileIndex UTilemapComponent::WorldPosToTileIndex(FIntPoint _Pos)
{
	FTileIndex Result = FTileIndex();
	FIntPoint ConvertVector;

	// 정수 나눗셈 대신 내림(floor) 사용
	ConvertVector.X = static_cast<int>(std::floor(static_cast<float>(_Pos.X) / TileSize.X));
	ConvertVector.Y = static_cast<int>(std::floor(static_cast<float>(_Pos.Y) / TileSize.Y));

	Result.X = ConvertVector.X;
	Result.Y = ConvertVector.Y;
	return Result;
}

FVector4 UTilemapComponent::TileIndexToWorldPos(FTileIndex _Index)
{
	FVector4 Result;
	Result.X = _Index.X * TileSize.X + TileSize.X * TilePivot.X;
	Result.Y = _Index.Y * TileSize.Y + TileSize.Y * TilePivot.Y;
	return Result;
}

void UTilemapComponent::SaveTilemap(UEngineDirectory _Dir, std::string_view _FileName)
{
	UEngineSerializer Ser;
	Tilemap->Serialize(Ser);
	UEngineFile NewFile = _Dir.GetFile(_FileName);

	NewFile.FileOpen("wb");
	NewFile.Write(Ser);
}



