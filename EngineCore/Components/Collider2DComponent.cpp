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
	BodyDef = b2DefaultBodyDef();

	ShapeDef = b2DefaultShapeDef();
	// 내 레이어
	ShapeDef.isSensor = IsTrigger;
	ShapeDef.filter.categoryBits = Layer;
	// 내가 충돌하면 부딪혀야 되는 애들 비트마스킹
	ShapeDef.filter.maskBits = UEnginePhysics::CollisionRule[Layer];

	if (Rigidbody2D != nullptr)
	{
		BodyId = Rigidbody2D->GetBodyId();
	}
	else
	{
		BodyDef.type = b2_kinematicBody;
		BodyDef.position = { Parent->GetLocation().X / FMath::BOX2DSCALE, Parent->GetLocation().Y / FMath::BOX2DSCALE };
		BodyDef.userData = GetOwner();
		BodyDef.fixedRotation = true;
		BodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);
	}
}

void UCollider2DComponent::TickComponent(float _DeltaTime)
{
	USceneComponent::TickComponent(_DeltaTime);
}
