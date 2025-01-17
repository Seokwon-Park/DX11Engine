#pragma once
#include <EngineCore/Resources/EngineTexture.h>
#include <EngineCore/ThirdParty/msdf-atlas-gen/msdf-atlas-gen.h>
#include <EngineCore/ThirdParty/msdf-atlas-gen/GlyphGeometry.h>

struct MSDFData;

// Ό³Έν :
class EngineFont : public UEngineResource
{
public:
	// constrcuter destructer
	ENGINE_API EngineFont();
	ENGINE_API ~EngineFont();

	// delete Function
	EngineFont(const EngineFont& _Other) = delete;
	EngineFont(EngineFont&& _Other) noexcept = delete;
	EngineFont& operator=(const EngineFont& _Other) = delete;
	EngineFont& operator=(EngineFont&& _Other) noexcept = delete;
	
	template<typename T, typename S,int N, msdf_atlas::GeneratorFunction<S,N> GenFunc>
	static std::shared_ptr<UEngineTexture2D> Create(const std::string& _FontName, float fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs,
		const msdf_atlas::FontGeometry& fontGeometry, uint32_t _Width, uint32_t _Height)
	{
		msdf_atlas::GeneratorAttributes attributes;
		attributes.config.overlapSupport = true;
		attributes.scanlinePass = true;

		msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(_Width, _Height);
		generator.setAttributes(attributes);
		generator.setThreadCount(std::thread::hardware_concurrency());
		generator.generate(glyphs.data(), (int)glyphs.size());

		msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();
		std::shared_ptr<UEngineTexture2D> texture = UEngineTexture2D::Create(_FontName, _Width, _Height);
		msdfgen::savePng(bitmap, "output.png");
		texture->SetData((void*)bitmap.pixels, bitmap.width * bitmap.height * 3);
		return texture;
	};

	ENGINE_API void Init();
protected:

private:
	MSDFData* Data;
};

