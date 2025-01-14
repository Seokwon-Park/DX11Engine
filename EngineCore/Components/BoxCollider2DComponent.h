#pragma once
#include "SceneComponent.h"
#include "Collider2DComponent.h"




// Ό³Έν :
class UBoxCollider2DComponent : public UCollider2DComponent
{
public:
	// constrcuter destructer
	ENGINE_API UBoxCollider2DComponent();
	ENGINE_API ~UBoxCollider2DComponent();

	// delete Function
	UBoxCollider2DComponent(const UBoxCollider2DComponent& _Other) = delete;
	UBoxCollider2DComponent(UBoxCollider2DComponent&& _Other) noexcept = delete;
	UBoxCollider2DComponent& operator=(const UBoxCollider2DComponent& _Other) = delete;
	UBoxCollider2DComponent& operator=(UBoxCollider2DComponent&& _Other) noexcept = delete;

	virtual void DebugRender(UCameraComponent* _Camera, float _DeltaTime)override;

protected:
	virtual void BeginPlay();
	virtual void TickComponent(float _DeltaTime);

private:
	b2Polygon dynamicBox;
};

