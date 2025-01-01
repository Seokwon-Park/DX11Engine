#include "EnginePCH.h"
#include "SpriteRendererComponent.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/ResourceManager.h>

USpriteRendererComponent::USpriteRendererComponent()
{
}

USpriteRendererComponent::~USpriteRendererComponent()
{
}

void USpriteRendererComponent::SetSprite(UEngineSprite* _Sprite, uint32 _Index)
{
	Sprite = _Sprite;
	SpriteData = Sprite->GetSpriteData(_Index);
}

void USpriteRendererComponent::SetSprite(std::string_view _Name, uint32 _Index)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	SetSprite(UResourceManager::Find<UEngineSprite>(UpperName), _Index);
}

void USpriteRendererComponent::SetSprite(std::shared_ptr<UEngineSprite> _Sprite, uint32 _Index)
{
	SetSprite(_Sprite.get(), _Index);
}

void USpriteRendererComponent::BeginPlay()
{
	URendererComponent::BeginPlay();
}

void USpriteRendererComponent::Render(float _DeltaTime)
{
	URendererComponent::Render(_DeltaTime);
	Shader->SetSpriteConstants(SpriteData.Rect);
	SpriteData.Texture->Bind();
}

void USpriteRendererComponent::TickComponent(float _DeltaTime)
{
	URendererComponent::TickComponent(_DeltaTime);


}



