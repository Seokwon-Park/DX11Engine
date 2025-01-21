#include "EnginePCH.h"
#include "EngineFont.h"
#include <EngineCore/ResourceManager.h>

UEngineFont::UEngineFont()
{
}

UEngineFont::~UEngineFont()
{
}

void UEngineFont::Create(std::string_view _Name, UEngineDirectory _Dir)
{
	std::shared_ptr<UEngineFont> NewFont = std::make_shared<UEngineFont>();
	std::string TTFFile = std::string(_Name) + ".ttf";
	
	NewFont->CreateFontAtlasImage(_Path.GetFile(TTFFile));

	UEngineDirectory Dir(_Path.ToString());
	Dir.MoveParent();

	UEngineSerializer Ser;
	NewFont->Serialize(Ser);
	UEngineFile NewFile = Dir.GetFile(_Path.GetFileNameWithoutExtension() + ".Font");
	NewFile.FileOpen("wb");
	NewFile.Write(Ser);


	UResourceManager::AddResource<UEngineFont>(NewFont, _Path.GetFileNameWithoutExtension(), _Path.ToString());
}

std::shared_ptr<UEngineFont> UEngineFont::Create(std::string_view _Name, std::string_view _Path)
{

	UEnginePath Path = _Path;
	std::string Name = Path.GetFileNameWithoutExtension();

	std::shared_ptr<UEngineFont> NewFont = std::make_shared<UEngineFont>();

	UEngineDirectory Dir(_Path);
	Dir.MoveParent();

	//UEngineFile NewFile = Dir.GetFile(Name + ".Font");
	//UEngineSerializer Ser;

	//NewFile.FileOpen("rb");
	//NewFile.Read(Ser);

	//NewFont->Deserialize(Ser);

	//NewFont->LoadFont(_Path);

	UResourceManager::AddResource<UEngineFont>(NewFont, Name, _Path);
	return NewFont;

}

void UEngineFont::CreateFontAtlasImage(UEngineFile _Path)
{
	Data = std::make_shared<MSDFData>();
	AtlasTextureName = _Path.GetFileNameWithoutExtension();

	if (msdfgen::FreetypeHandle* FreeTypeHandlePtr = msdfgen::initializeFreetype())
	{
		if (msdfgen::FontHandle* FontHandlePtr = msdfgen::loadFont(FreeTypeHandlePtr, _Path.ToString().c_str()))
		{
			Ranges = {
		{ 32, 126},
		{ 8200, 9900},
		{ 12593, 12643},
		{ 44032, 55203 }
			};

			//Ranges = { { 32, 126} };

			msdf_atlas::Charset CustomCharset;
			for (CharsetRange Range : Ranges)
			{
				for (uint32_t c = Range.Begin; c <= Range.End; c++)
				{
					CustomCharset.add(c);
				}
			}

			Data->FontGeometry = msdf_atlas::FontGeometry(&Data->Glyphs);
			int GlyphesLoaded = Data->FontGeometry.loadCharset(FontHandlePtr, FontScale, CustomCharset);

			msdf_atlas::TightAtlasPacker FontatlasPacker;
			FontatlasPacker.setDimensionsConstraint(msdf_atlas::DimensionsConstraint::SQUARE);
			FontatlasPacker.setPixelRange(2.0);
			FontatlasPacker.setMiterLimit(2.0);
			FontatlasPacker.setScale(40.0);
			FontatlasPacker.pack(Data->Glyphs.data(), (int)Data->Glyphs.size());
			// Get final atlas dimensions
			int Width = 0, Height = 0;
			FontatlasPacker.getDimensions(Width, Height);

#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREAD_COUNT 12
			// if MSDF || MTSDF

			uint64_t ColoringSeed = 0;
			bool expensiveColoring = false;
			if (expensiveColoring)
			{
				msdf_atlas::Workload([&glyphs = Data->Glyphs, &ColoringSeed](int i, int threadNo) -> bool
					{
						unsigned long long GlyphSeed = (LCG_MULTIPLIER * (ColoringSeed ^ i) + LCG_INCREMENT) * !!ColoringSeed;
						glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, GlyphSeed);
						return true;
					}, Data->Glyphs.size()).finish(THREAD_COUNT);
			}
			else {
				unsigned long long GlyphSeed = ColoringSeed;
				for (msdf_atlas::GlyphGeometry& Glyph : Data->Glyphs)
				{
					GlyphSeed *= LCG_MULTIPLIER;
					Glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, GlyphSeed);
				}
			}

			AtlasTexture = CreateFontAtlasTexture<uint8_t, float, 3, msdf_atlas::msdfGenerator>(_Path, (float)40.0, Data->Glyphs, Width, Height);
			msdfgen::destroyFont(FontHandlePtr);
		}
		msdfgen::deinitializeFreetype(FreeTypeHandlePtr);
	}
}

void UEngineFont::LoadFont(UEngineFile _Path)
{
	Data = std::make_shared<MSDFData>();
	AtlasTexture = UResourceManager::Find<UEngineTexture2D>(_Path.GetFileNameWithoutExtension());
	if (msdfgen::FreetypeHandle* FreeTypeHandlePtr = msdfgen::initializeFreetype())
	{
		if (msdfgen::FontHandle* FontHandlePtr = msdfgen::loadFont(FreeTypeHandlePtr, _Path.ToString().c_str()))
		{
			AtlasTexture = UResourceManager::Find<UEngineTexture2D>(_Path.GetFileNameWithoutExtension());

			msdf_atlas::Charset CustomCharset;
			for (CharsetRange Range : Ranges)
			{
				for (uint32_t c = Range.Begin; c <= Range.End; c++)
				{
					CustomCharset.add(c);
				}
			}

			Data->FontGeometry = msdf_atlas::FontGeometry(&Data->Glyphs);
			int GlyphesLoaded = Data->FontGeometry.loadCharset(FontHandlePtr, FontScale, CustomCharset);

			msdf_atlas::TightAtlasPacker FontatlasPacker;
			FontatlasPacker.setDimensionsConstraint(msdf_atlas::DimensionsConstraint::SQUARE);
			FontatlasPacker.setPixelRange(2.0);
			FontatlasPacker.setMiterLimit(2.0);
			FontatlasPacker.setScale(40.0);
			FontatlasPacker.pack(Data->Glyphs.data(), (int)Data->Glyphs.size());
			// Get final atlas dimensions
			int Width = 0, Height = 0;
			FontatlasPacker.getDimensions(Width, Height);

			msdfgen::destroyFont(FontHandlePtr);
		}
		msdfgen::deinitializeFreetype(FreeTypeHandlePtr);
	}
}

void UEngineFont::Serialize(UEngineSerializer& _Serializer)
{
	_Serializer << FontScale;
	_Serializer << Ranges.size();
	for (int i = 0; i < Ranges.size(); i++)
	{
		_Serializer.Write(&Ranges[i], sizeof(CharsetRange));
	}
}

void UEngineFont::Deserialize(UEngineSerializer& _Serializer)
{
	_Serializer >> FontScale;
	size_t RangeCount;
	_Serializer >> RangeCount;
	for (size_t i = 0; i < RangeCount; i++)
	{
		CharsetRange Range;
		_Serializer.Read(&Range, sizeof(CharsetRange));
		Ranges.push_back(Range);
	}
}
