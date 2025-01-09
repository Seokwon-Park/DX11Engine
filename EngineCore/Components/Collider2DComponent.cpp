#include "EnginePCH.h"
#include "Collider2DComponent.h"

UCollider2DComponent::UCollider2DComponent()
{
}

UCollider2DComponent::~UCollider2DComponent()
{
}

void UCollider2DComponent::BeginPlay()
{
	USceneComponent::BeginPlay();
}

void UCollider2DComponent::TickComponent(float _DeltaTime)
{
	USceneComponent::TickComponent(_DeltaTime);
}
