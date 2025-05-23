#include "EnginePCH.h"
#include "EngineFont.h"
#include <EngineCore/Constants/FontConst.h>
#include <EngineCore/ResourceManager.h>

UEngineFont::UEngineFont()
{
}

UEngineFont::~UEngineFont()
{
}

void UEngineFont::CreateNew(std::string_view _Name, UEngineDirectory _Dir)
{
	std::shared_ptr<UEngineFont> NewFont = std::make_shared<UEngineFont>();
	std::string TTFFile = std::string(_Name) + ".ttf";

	UEngineFile File = _Dir.GetFile(std::string(_Name) + ".ttf");
	NewFont->CreateFontAtlasImage(File);

	UEngineSerializer Ser;
	NewFont->Serialize(Ser);
	UEngineFile NewFile = _Dir.GetFile(std::string(_Name) + ".Font");
	NewFile.FileOpen("wb");
	NewFile.Write(Ser);


	UResourceManager::AddResource<UEngineFont>(NewFont, _Name, NewFile.ToString());
}

std::shared_ptr<UEngineFont> UEngineFont::Load(std::string_view _Name, std::string_view _Path)
{

	UEnginePath Path = _Path;
	std::string Name = Path.GetFileNameWithoutExtension();
	std::shared_ptr<UEngineFont> NewFont = std::make_shared<UEngineFont>();

	// Atlas 텍스쳐가 없으면 아틀라스 텍스쳐를 생성하고,
	if (UResourceManager::Find<UEngineTexture2D>(Name) == nullptr)
	{
		MSGASSERT("Font Atlas 텍스쳐가 생성되지 않았습니다. 텍스쳐를 생성하고 로드해주세요.");
		return nullptr;
	}
	// Atlas 텍스쳐가 있으면 아틀라스 텍스쳐를 로드하고 폰트를 생성한다.
	else
	{
		UEngineDirectory Dir(_Path);
		Dir.MoveParent();

		UEngineFile NewFile = Dir.GetFile(Name + ".Font");
		UEngineSerializer Ser;

		NewFile.FileOpen("rb");
		NewFile.Read(Ser);

		NewFont->Deserialize(Ser);

		NewFont->LoadFont(_Path);
	}

	UResourceManager::AddResource<UEngineFont>(NewFont, Name, _Path);
	return NewFont;
}

void UEngineFont::CreateFontAtlasImage(UEngineFile _Path)
{
	Data = std::make_shared<MSDFData>();
	AtlasTextureName = _Path.GetFileNameWithoutExtension();

	if (FreeTypeHandlePtr = msdfgen::initializeFreetype())
	{
		if (FontHandlePtr = msdfgen::loadFont(FreeTypeHandlePtr, _Path.ToString().c_str()))
		{
			Ranges = {
		{ 32, 126},
		{ 8200, 9900},
		{ 12593, 12643},
		{ 44032, 55203 }
			};

			//Ranges = { { 32, 126} };
			msdf_atlas::Charset CustomCharset;

			//for (int i = 0; i < 2350; i++)
			//{
			//	CustomCharset.add(static_cast<unsigned int>(KS1001[i]));
			//}

			
			FIntPoint Size = CalculateFontGeometry();

			AtlasTexture = CreateFontAtlasTexture<uint8_t, float, 3, msdf_atlas::msdfGenerator>(_Path, (float)20.0, Data->Glyphs, (UINT)Size.X, (UINT)Size.Y);
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
			FontatlasPacker.setScale(20.0);
			FontatlasPacker.pack(Data->Glyphs.data(), (int)Data->Glyphs.size());
			// Get final atlas dimensions
			int Width = 0, Height = 0;
			FontatlasPacker.getDimensions(Width, Height);

			msdfgen::destroyFont(FontHandlePtr);
		}
		msdfgen::deinitializeFreetype(FreeTypeHandlePtr);
	}
}

FIntPoint UEngineFont::CalculateFontGeometry()
{
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
	FontatlasPacker.setScale(20.0);
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
			}, (int)Data->Glyphs.size()).finish(THREAD_COUNT);
	}
	else {
		unsigned long long GlyphSeed = ColoringSeed;
		for (msdf_atlas::GlyphGeometry& Glyph : Data->Glyphs)
		{
			GlyphSeed *= LCG_MULTIPLIER;
			Glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, GlyphSeed);
		}
	}

	return FIntPoint(Width, Height);
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
