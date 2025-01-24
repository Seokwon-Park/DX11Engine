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
	// �� ���̾�
	ShapeDef.filter.categoryBits = Layer;
	// ���� �浹�ϸ� �ε����� �Ǵ� �ֵ� ��Ʈ����ŷ
	ShapeDef.filter.maskBits = UEnginePhysics::CollisionRule[Layer];
}

void UCollider2DComponent::TickComponent(float _DeltaTime)
{
	USceneComponent::TickComponent(_DeltaTime);
}
