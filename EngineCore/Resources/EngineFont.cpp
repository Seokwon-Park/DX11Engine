#include "EnginePCH.h"
#include "EngineFont.h"


UEngineFont::UEngineFont()
{
}

UEngineFont::~UEngineFont()
{
	//FontGeometryMem = msdf_atlas::FontGeometry();
}

void UEngineFont::Create(UEngineFile _Path)
{
	std::shared_ptr<UEngineFont> NewFont = std::make_shared<UEngineFont>();
	NewFont->CreateFontAtlasImage(_Path);
}

void UEngineFont::CreateFontAtlasImage(UEngineFile _Path)
{
	if (msdfgen::FreetypeHandle* FreeTypeHandlePtr = msdfgen::initializeFreetype())
	{
		if (msdfgen::FontHandle* FontHandlePtr = msdfgen::loadFont(FreeTypeHandlePtr, _Path.ToString().c_str()))
		{
		//	Ranges = {
		//{ 32, 126},
		//{ 8200, 9900},
		//{ 12593, 12643},
		//{ 44032, 55203 }
		//	};

			Ranges = {
			{ 32, 126}
			};

			msdf_atlas::Charset charset;
			for (CharsetRange Range : Ranges)
			{
				for (uint32_t c = Range.Begin; c <= Range.End; c++)
				{
					charset.add(c);
				}
			}
			double fontScale = 1.0;
			FontGeometryMem = msdf_atlas::FontGeometry(&Glyphs);
			int glyphesLoaded = FontGeometryMem.loadCharset(FontHandlePtr, fontScale, charset);

			msdf_atlas::TightAtlasPacker atlasPacker;
			atlasPacker.setDimensionsConstraint(msdf_atlas::DimensionsConstraint::SQUARE);
			atlasPacker.setPixelRange(2.0);
			atlasPacker.setMiterLimit(2.0);
			atlasPacker.setPixelRange(2.0);
			atlasPacker.setScale(10.0);
			atlasPacker.pack(Glyphs.data(), Glyphs.size());
			// Get final atlas dimensions
			int width = 0, height = 0;
			atlasPacker.getDimensions(width, height);

#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREAD_COUNT 8
			// if MSDF || MTSDF

			uint64_t coloringSeed = 0;
			bool expensiveColoring = false;
			if (expensiveColoring)
			{
				msdf_atlas::Workload([&glyphs = Glyphs, &coloringSeed](int i, int threadNo) -> bool {
					unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
					glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
					return true;
					}, Glyphs.size()).finish(THREAD_COUNT);
			}
			else {
				unsigned long long glyphSeed = coloringSeed;
				for (msdf_atlas::GlyphGeometry& glyph : Glyphs)
				{
					glyphSeed *= LCG_MULTIPLIER;
					glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
				}
			}

			CreateFontAtlasTexture<uint8_t, float, 3, msdf_atlas::msdfGenerator>(_Path.GetFileNameWithoutExtension(), (float)40.0, Glyphs, width, height);
			msdfgen::destroyFont(FontHandlePtr);
		}
		msdfgen::deinitializeFreetype(FreeTypeHandlePtr);
	}
}