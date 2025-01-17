#include "EnginePCH.h"
#include "EngineFont.h"


struct MSDFData
{
	std::vector<msdf_atlas::GlyphGeometry> Glyphs;
	msdf_atlas::FontGeometry FontGeometry;
};

EngineFont::EngineFont()
{
}

EngineFont::~EngineFont()
{
}



void EngineFont::Init()
{
	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("Resources");
	UEngineFile File = Dir.GetFile("NanumGothic.ttf");

	Data = new MSDFData();

	if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype()) 
	{
		if (msdfgen::FontHandle* font = msdfgen::loadFont(ft, File.ToString().c_str())) 
		{

			struct CharsetRange
			{
				uint32_t Begin, End;
			};
			static const CharsetRange Ranges[]
			{
				{ 32, 126},
				{ 8200, 9900},
				{ 12593, 12643},
				{ 44032, 55203 }
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
			Data->FontGeometry = msdf_atlas::FontGeometry(&Data->Glyphs);
			int glyphesLoaded = Data->FontGeometry.loadCharset(font, fontScale, charset);

			msdf_atlas::TightAtlasPacker atlasPacker;
			atlasPacker.setDimensionsConstraint(msdf_atlas::DimensionsConstraint::SQUARE);
			atlasPacker.setPixelRange(2.0);
			atlasPacker.setMiterLimit(2.0);
			atlasPacker.setPixelRange(2.0);
			atlasPacker.setScale(10.0);
			atlasPacker.pack(Data->Glyphs.data(), Data->Glyphs.size());
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
				msdf_atlas::Workload([&glyphs = Data->Glyphs, &coloringSeed](int i, int threadNo) -> bool {
					unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
					glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
					return true;
					}, Data->Glyphs.size()).finish(THREAD_COUNT);
			}
			else {
				unsigned long long glyphSeed = coloringSeed;
				for (msdf_atlas::GlyphGeometry& glyph : Data->Glyphs)
				{
					glyphSeed *= LCG_MULTIPLIER;
					glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
				}
			}

			Create<uint8_t, float, 3, msdf_atlas::msdfGenerator>("Test", (float)40.0, Data->Glyphs, Data->FontGeometry, width, height);
			//// The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
			//msdf_atlas::ImmediateAtlasGenerator<
			//	float, // pixel type of buffer for individual glyphs depends on generator function
			//	3, // number of atlas color channels
			//	&msdfGenerator, // function to generate bitmaps for individual glyphs
			//	msdf_atlas::BitmapAtlasStorage<byte, 3> // class that stores the atlas bitmap
			//	// For example, a custom atlas storage class that stores it in VRAM can be used.
			//> generator(width, height);
			//// GeneratorAttributes can be modified to change the generator's default settings.
			//msdf_atlas::GeneratorAttributes attributes;
			//generator.setAttributes(attributes);
			//generator.setThreadCount(4);
			//// Generate atlas bitmap
			//generator.generate(glyphs.data(), glyphs.size());

			//// The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
			//// The glyphs array (or fontGeometry) contains positioning data for typesetting text.
			//submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);
			

			//msdfgen::Shape shape;
			//if (msdfgen::loadGlyph(shape, font, 'A', msdfgen::FONT_SCALING_EM_NORMALIZED)) {
			//	shape.normalize();
			//	//                      max. angle
			//	msdfgen::edgeColoringSimple(shape, 3.0);
			//	//          output width, height
			//	msdfgen::Bitmap<float, 3> msdf(32, 32);
			//	//                            scale, translation (in em's)
			//	msdfgen::SDFTransformation t(msdfgen::Projection(32.0, msdfgen::Vector2(0.125, 0.125)), msdfgen::Range(0.125));
			//	msdfgen::generateMSDF(msdf, shape, t);
			//	msdfgen::savePng(msdf, "output.png");
			//}
			msdfgen::destroyFont(font);
		}
		msdfgen::deinitializeFreetype(ft);
	}
}