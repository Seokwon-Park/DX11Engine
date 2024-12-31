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

void USpriteRendererComponent::SetSprite(std::string_view _Name, uint32 _Index)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	Sprite = UResourceManager::Find<UEngineSprite>(UpperName);
}

void USpriteRendererComponent::BeginPlay()
{
	URendererComponent::BeginPlay();
}

void USpriteRendererComponent::Render(float _DeltaTime)
{
	URendererComponent::Render(_DeltaTime);
	Shader->SetSpriteConstants(SpriteData.Rect);
}



