#pragma once
#include "SceneComponent.h"
#include "Rigidbody2DComponent.h"
#include <EngineCore/RenderUnit.h>
#include <EngineCore/ThirdParty/Box2D/include/box2d.h>

// Ό³Έν :
class UBoxCollider2DComponent : public USceneComponent
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

	ENGINE_API void DebugRender(UCameraComponent* _Camera, float _DeltaTime);
	ENGINE_API inline void SetRigidbody(URigidbody2DComponent* _RigidBody2D) { Rigidbody2D = _RigidBody2D; }
	ENGINE_API inline void SetRigidbody(std::shared_ptr<URigidbody2DComponent> _RigidBody2D) { Rigidbody2D = _RigidBody2D.get(); }
protected:
	virtual void BeginPlay();
	virtual void TickComponent(float _DeltaTime);

private:
	FVector2 Offset = { 0.0f, 0.0f };
	FVector2 Size = { 0.5f, 0.5f };

	float Density = 1.0f;
	float Friction = 0.5f;
	float Restitution = 0.0f;
	float RestitutionThreshold = 0.5f;

	b2BodyId BodyId;
	b2Polygon dynamicBox;
	b2ShapeDef shapeDef;

	std::shared_ptr<URenderUnit> ColliderDebugRenderUnit;
	URigidbody2DComponent* Rigidbody2D;
};

