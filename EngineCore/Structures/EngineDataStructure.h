#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineCore/Enums/DataLayer.h>
#include <EngineCore/ThirdParty/msdf-atlas-gen/msdf-atlas-gen.h>


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
	int RotatedCount = 0;
	bool IsBlock = false;
	bool IsFlip = false;
	FIntPoint Multiplier = { 1,1 };
	size_t SpriteIndex = 0;
	ETilePolygon PolygonType = ETilePolygon::Default;
	FTileIndex Index;
	FSpriteRect SpriteRect;
};


struct MSDFData
{
	std::vector<msdf_atlas::GlyphGeometry> Glyphs;
	msdf_atlas::FontGeometry FontGeometry;
};


