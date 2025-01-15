#pragma once
#include <EngineBase/EngineMath.h>

struct FSpriteRect
{
	FVector2 CuttingPos = FVector2(0.0f, 0.0f);
	FVector2 CuttingSize = FVector2(1.0f, 1.0f);
	FVector2 Pivot = FVector2(0.5f, 0.5f);
	FVector2 Dummy;
};

struct FSpriteData
{
	std::shared_ptr<class UEngineTexture2D> Texture;
	FSpriteRect Rect;
}; 

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



struct FTileData
{
	bool IsBlock = false;
	bool IsFilped = false;
	int RotatedCount = 0;
	int SpriteIndex = -1;
	FTileIndex Index;
	FSpriteRect SpriteRect;
};