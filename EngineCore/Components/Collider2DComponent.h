#pragma once
#include "SceneComponent.h"
#include <EngineCore/Enums/EngineLayer.h>
#include <EngineCore/ThirdParty/Box2D/include/box2d.h>
#include "Rigidbody2DComponent.h"
#include <EngineCore/RenderUnit.h>

// Ό³Έν :
class UCollider2DComponent : public USceneComponent
{
public:
	// constrcuter destructer
	UCollider2DComponent();
	~UCollider2DComponent();

	// delete Function
	UCollider2DComponent(const UCollider2DComponent& _Other) = delete;
	UCollider2DComponent(UCollider2DComponent&& _Other) noexcept = delete;
	UCollider2DComponent& operator=(const UCollider2DComponent& _Other) = delete;
	UCollider2DComponent& operator=(UCollider2DComponent&& _Other) noexcept = delete;

	ENGINE_API virtual void DebugRender(class UCameraComponent* _Camera, float _DeltaTime) = 0;
	virtual void TickComponent(float _DeltaTime) override;

	ENGINE_API inline void SetRigidbody(URigidbody2DComponent* _RigidBody2D) { Rigidbody2D = _RigidBody2D; }
	ENGINE_API inline void SetRigidbody(std::shared_ptr<URigidbody2DComponent> _RigidBody2D) { Rigidbody2D = _RigidBody2D.get(); }

	ENGINE_API inline void SetTrigger(bool _Value) { IsTrigger = _Value; }

	inline void SetCollisionLayer(ECollisionLayer _Layer) { 
		Layer = _Layer; 
		ShapeDef.filter.categoryBits = Layer;
	}


protected:	
	virtual void BeginPlay() override;

	FVector2 Offset = { 0.0f, 0.0f };
	FVector2 Size = { 0.5f, 0.5f };

	b2BodyId BodyId;
	b2BodyDef BodyDef;
	b2ShapeDef ShapeDef;

	float Density = 1.0f;
	float Friction = 0.5f;
	float Restitution = 0.0f;
	float RestitutionThreshold = 0.5f;

	bool IsTrigger = false;

	ECollisionLayer Layer;

	std::shared_ptr<URenderUnit> ColliderDebugRenderUnit;
	URigidbody2DComponent* Rigidbody2D;
private:

};

