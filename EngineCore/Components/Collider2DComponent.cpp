#include "EnginePCH.h"
#include "Collider2DComponent.h"
#include <EngineCore/EnginePhysics.h>

UCollider2DComponent::UCollider2DComponent()
{
}

UCollider2DComponent::~UCollider2DComponent()
{
}

void UCollider2DComponent::BeginPlay()
{
	USceneComponent::BeginPlay();
	ShapeDef = b2DefaultShapeDef();
	// 내 레이어
	ShapeDef.filter.categoryBits = Layer;
	// 내가 충돌하면 부딪혀야 되는 애들 비트마스킹
	ShapeDef.filter.maskBits = UEnginePhysics::CollisionRule[Layer];
}

void UCollider2DComponent::TickComponent(float _DeltaTime)
{
	USceneComponent::TickComponent(_DeltaTime);
}
