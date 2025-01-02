#pragma once
#include <EngineCore/Resources/EngineTexture.h>

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

struct FSpriteRect
{
	FVector2 CuttingPos = FVector2(0.0f, 0.0f);
	FVector2 CuttingSize = FVector2(1.0f, 1.0f);
	FVector2 Pivot = FVector2(0.5f, 0.5f);
	FVector2 Dummy;
};

struct FSpriteData
{
	UEngineTexture2D* Texture;
	FSpriteRect Rect;
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

	FSpriteData GetSpriteData(int _Index);

	ENGINE_API static std::shared_ptr<UEngineSprite> CreateSpriteFromFolder(std::string_view _Path);
	ENGINE_API static std::shared_ptr<UEngineSprite> CreateSpriteFromFolder(std::string_view _Name, std::string_view _Path);
	
	ENGINE_API void SetPivot(EPivotType _Pivot);
	ENGINE_API void SetPivot(FVector2 _Pos);
	ENGINE_API void SetPivot(FVector2 _Pos, Uint32 _Index);
protected:

private:
	std::vector<FSpriteData> SpriteDatas;
};
