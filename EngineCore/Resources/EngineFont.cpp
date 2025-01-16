#include "EnginePCH.h"
#include "EngineFont.h"

using namespace msdfgen;

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
	Dir.GetFile("NanumGothic.ttf");

	if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype()) {
		if (msdfgen::FontHandle* font = msdfgen::loadFont(ft, Dir.ToString().c_str())) {
			msdfgen::Shape shape;
			if (msdfgen::loadGlyph(shape, font, 'A', FONT_SCALING_EM_NORMALIZED)) {
				shape.normalize();
				//                      max. angle
				msdfgen::edgeColoringSimple(shape, 3.0);
				//          output width, height
				msdfgen::Bitmap<float, 3> msdf(32, 32);
				//                            scale, translation (in em's)
				msdfgen::SDFTransformation t(Projection(32.0, Vector2(0.125, 0.125)), Range(0.125));
				msdfgen::generateMSDF(msdf, shape, t);
				msdfgen::savePng(msdf, "output.png");
			}
			msdfgen::destroyFont(font);
		}
		msdfgen::deinitializeFreetype(ft);
	}
}