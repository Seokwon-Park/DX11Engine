#pragma once
#include <EngineCore/Resources/EngineTexture.h>
#include <EngineCore/Structures/EngineDataStructure.h>

enum class EPivotType
{
	TopLeft,
	TopCenter,
	TopRight,
	LeftCenter,
	Center,
	RightCenter, 
	BottomLeft,
	BottomCenter,
	BottomRight
};


// 클래스 설명 :
class UEngineSprite : public UEngineResource
{
public:
	// Constrcuter Destructer
	UEngineSprite();
	~UEngineSprite();

	// Delete Function
	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	ENGINE_API FSpriteData GetSpriteByIndex(size_t _Index);
	ENGINE_API inline size_t GetSpriteCount() { return SpriteData.size(); }
	ENGINE_API inline std::vector<FSpriteData> GetSpriteData() {return SpriteData; }

	ENGINE_API static std::shared_ptr<UEngineSprite> CreateSprite(std::shared_ptr<UEngineTexture2D> _Texture);
	ENGINE_API static std::shared_ptr<UEngineSprite> CreateSpriteFromFolder(std::string_view _Path);
	ENGINE_API static std::shared_ptr<UEngineSprite> CreateSpriteFromFolder(std::string_view _Name, std::string_view _Path);
	
	ENGINE_API void SetPivot(EPivotType _Pivot);
	ENGINE_API void SetPivot(FVector2 _Pos);
	ENGINE_API void SetPivot(FVector2 _Pos, Uint32 _Index);
protected:

private:
	std::vector<FSpriteData> SpriteData;
};
