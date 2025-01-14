#pragma once
#include "Collider2DComponent.h"

// Ό³Έν :
class UCapsuleCollider2DComponent :public UCollider2DComponent
{
public:
	// constrcuter destructer
	ENGINE_API UCapsuleCollider2DComponent();
	ENGINE_API ~UCapsuleCollider2DComponent();

	// delete Function
	UCapsuleCollider2DComponent(const UCapsuleCollider2DComponent& _Other) = delete;
	UCapsuleCollider2DComponent(UCapsuleCollider2DComponent&& _Other) noexcept = delete;
	UCapsuleCollider2DComponent& operator=(const UCapsuleCollider2DComponent& _Other) = delete;
	UCapsuleCollider2DComponent& operator=(UCapsuleCollider2DComponent&& _Other) noexcept = delete;
	ENGINE_API virtual void DebugRender(class UCameraComponent* _Camera, float _DeltaTime);
	virtual void TickComponent(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	b2Capsule CapsuleShape;

	FVector2 Center1;
	FVector2 Center2;
	float Radius;

};

