#pragma once
#include <EngineCore/Resources/EngineTexture.h>

struct FSpriteRect
{
	FVector2 CuttingPos = { 0.0f, 0.0f };
	FVector2 CuttingSize = { 1.0f, 1.0f };
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

protected:

private:
	std::vector<FSpriteData> SpriteDatas;
};
