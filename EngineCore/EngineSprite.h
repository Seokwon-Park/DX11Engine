#pragma once

#include "Graphics/EngineTexture.h"

// 클래스 설명 :
class UEngineSprite 
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
protected:

private:
	UEngineTexture2D* Texture;
	//std::vector<FSpriteData> SpriteDatas;
};
