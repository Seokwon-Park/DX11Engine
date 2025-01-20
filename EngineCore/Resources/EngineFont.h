#pragma once
#include <EngineCore/Resources/EngineTexture.h>

#include <EngineCore/ThirdParty/msdf-atlas-gen/msdf-atlas-gen.h>
#include <EngineCore/ThirdParty/msdf-atlas-gen/GlyphGeometry.h>

#include <EngineCore/Structures/EngineDataStructure.h>

struct CharsetRange
{
	uint32_t Begin, End;
};

// 설명 :
class UEngineFont : public UEngineResource, public ISerializableObject
{
public:
	// constrcuter destructer
	UEngineFont();
	~UEngineFont();

	// delete Function
	UEngineFont(const UEngineFont& _Other) = delete;
	UEngineFont(UEngineFont&& _Other) noexcept = delete;
	UEngineFont& operator=(const UEngineFont& _Other) = delete;
	UEngineFont& operator=(UEngineFont&& _Other) noexcept = delete;

	template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
	static std::shared_ptr<UEngineTexture2D> CreateFontAtlasTexture(UEngineFile _Path, float fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs,
		uint32_t _Width, uint32_t _Height)
	{
		msdf_atlas::GeneratorAttributes attributes;
		attributes.config.overlapSupport = true;
		attributes.scanlinePass = true;

		msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(_Width, _Height);
		generator.setAttributes(attributes);
		generator.setThreadCount(std::thread::hardware_concurrency());
		generator.generate(glyphs.data(), (int)glyphs.size());

		std::string FontName = _Path.GetFileNameWithoutExtension();
		_Path.MoveParent();
		UEngineDirectory Dir(_Path.ToString());
		UEngineFile FilePath = Dir.GetFile(FontName + ".png");

		msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();
		std::shared_ptr<UEngineTexture2D> texture = UEngineTexture2D::Create(FontName, _Width, _Height);
		msdfgen::savePng(bitmap, FilePath.ToString().c_str());
		texture->SetData((void*)bitmap.pixels, bitmap.width * bitmap.height * 3);

		return texture;
	};

	ENGINE_API static void Create(UEngineFile _Path);

	ENGINE_API void CreateFontAtlasImage(UEngineFile _Path);
	
	ENGINE_API MSDFData* GetMSDFData() { return Data.get(); }
	ENGINE_API std::shared_ptr<UEngineTexture2D> GetFontAtlasTexture() { return AtlasTexture; }

protected:

private:
	std::vector<CharsetRange> Ranges;

	std::shared_ptr<MSDFData> Data;

	std::string AtlasTextureName;
	std::shared_ptr<UEngineTexture2D> AtlasTexture;

	// ISerializableObject을(를) 통해 상속됨
	ENGINE_API void Serialize(UEngineSerializer& _Serializer) override;
	ENGINE_API void Deserialize(UEngineSerializer& _Serializer) override;
};

