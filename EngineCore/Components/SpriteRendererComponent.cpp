#include "EnginePCH.h"
#include "SpriteRendererComponent.h"

USpriteRendererComponent::USpriteRendererComponent()
{
}

USpriteRendererComponent::~USpriteRendererComponent()
{
}

void USpriteRendererComponent::SetSprite(std::string_view _Name, uint32 _Index)
{

}

void USpriteRendererComponent::BeginPlay()
{
	URendererComponent::BeginPlay();
}

void USpriteRendererComponent::Render(float _DeltaTime)
{
	URendererComponent::Render(_DeltaTime);
	Shader->SetSpriteConstants(SpriteData);
}



