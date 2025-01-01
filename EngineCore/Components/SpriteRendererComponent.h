#pragma once
#include "RendererComponent.h"
#include <EngineCore/Resources/EngineSprite.h>

// Ό³Έν :
class USpriteRendererComponent : public URendererComponent
{
public:
	// constrcuter destructer
	ENGINE_API USpriteRendererComponent();
	ENGINE_API ~USpriteRendererComponent();

	// delete Function
	USpriteRendererComponent(const USpriteRendererComponent& _Other) = delete;
	USpriteRendererComponent(USpriteRendererComponent&& _Other) noexcept = delete;
	USpriteRendererComponent& operator=(const USpriteRendererComponent& _Other) = delete;
	USpriteRendererComponent& operator=(USpriteRendererComponent&& _Other) noexcept = delete;

	ENGINE_API void SetSprite(UEngineSprite* _Sprite, uint32 _Index);
	ENGINE_API void SetSprite(std::string_view _Name, uint32 _Index);
	ENGINE_API void SetSprite(std::shared_ptr<UEngineSprite> _Sprite, uint32 _Index);

	//void SetSpriteData(FSpriteData _Data)
	//{
	//	for (int i = 0; i < 2; i++)
	//	{
	//		SpriteData.CuttingPos[i] = _Data.CuttingPos[i];
	//		SpriteData.CuttingSize[i] = _Data.CuttingSize[i];
	//	}
	//}

protected:
	ENGINE_API void BeginPlay() override;
	void Render(float _DeltaTime) override;
	virtual void TickComponent(float _DeltaTime)override;

private:
	UEngineSprite* Sprite;
	FSpriteData SpriteData;

};

