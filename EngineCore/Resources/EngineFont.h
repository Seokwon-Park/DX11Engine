#pragma once
#include <EngineCore/Resources/EngineTexture.h>

#include <EngineCore/ThirdParty/msdf-atlas-gen/msdf-atlas-gen.h>
#include <EngineCore/ThirdParty/msdf-atlas-gen/GlyphGeometry.h>

#include <EngineCore/Structures/EngineDataStructure.h>

struct CharsetRange
{
	uint32_t Begin, End;
};

// Create는 ResourceManager에서 로드할 때 쓰는 Create와
// Font Atlas Texture 가 없는 경우 생성하는 Create가 있다.
// 이걸 한 함수로 통합할 것인가? (없으면 텍스쳐도 생성하게 한다?)

// 설명 : 리소스를 로드할때는 ttf 파일을 확장자로 로드할 것.
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
		msdfgen::savePng(bitmap, FilePath.ToString().c_str());

		std::shared_ptr<UEngineTexture2D> texture = UEngineTexture2D::Load(FontName, FilePath.ToString());
		
		//texture->SetData(newData.data(), bitmap.width * bitmap.height * 4);

		return texture;
	};

	//용도 : Image아틀라스 파일을 지우고 새로 생성해야 하는 경우 사용.
	ENGINE_API static void CreateNew(std::string_view _Name, UEngineDirectory _Path);
	ENGINE_API static std::shared_ptr<UEngineFont> Load(std::string_view _Name, std::string_view _Path);
	ENGINE_API void CreateFontAtlasImage(UEngineFile _Path);
	ENGINE_API void LoadFont(UEngineFile _Path);
	void AddRange();
	
	ENGINE_API MSDFData* GetMSDFData() { return Data.get(); }
	ENGINE_API std::shared_ptr<UEngineTexture2D> GetFontAtlasTexture() { return AtlasTexture; }
protected:

private:
	FIntPoint CalculateFontGeometry();

	msdfgen::FreetypeHandle* FreeTypeHandlePtr;
	msdfgen::FontHandle* FontHandlePtr;

	double FontScale = 1.0;
	double Scale = 0.0f;

	std::vector<CharsetRange> Ranges;

	std::shared_ptr<MSDFData> Data;

	std::string AtlasTextureName;
	std::shared_ptr<UEngineTexture2D> AtlasTexture;

	// ISerializableObject을(를) 통해 상속됨
	ENGINE_API void Serialize(UEngineSerializer& _Serializer) override;
	ENGINE_API void Deserialize(UEngineSerializer& _Serializer) override;
};

