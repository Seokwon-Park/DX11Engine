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

	FTileData& NewTile = Tilemap->TilemapData[Index.Key];

	NewTile.Index = Index;
	NewTile.SpriteIndex = _Spriteindex;
	NewTile.SpriteRect.CuttingPos = { 0.0f, 0.0f };
	NewTile.SpriteRect.CuttingSize = { 1.0f, 1.0f };
	NewTile.SpriteRect.Pivot = { 0.5f, 0.5f };
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
	ConvertVector.X = static_cast<int>(std::floor(static_cast<float>(_Pos.X) / ImageSize.X));
	ConvertVector.Y = static_cast<int>(std::floor(static_cast<float>(_Pos.Y) / ImageSize.Y));

	Result.X = ConvertVector.X;
	Result.Y = ConvertVector.Y;
	return Result;
}

FVector4 UTilemapComponent::TileIndexToWorldPos(FTileIndex _Pos)
{
	FVector4 Result;
	Result.X = _Pos.X * ImageSize.X + ImageSize.X / 2.0f;
	Result.Y = _Pos.Y * ImageSize.Y + ImageSize.Y / 2.0f;
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



