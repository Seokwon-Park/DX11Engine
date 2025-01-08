#pragma once
#include "SceneComponent.h"
#include <EngineCore/ThirdParty/Box2D/include/box2d.h>

enum class EBodyType
{
	Static,
	Dynamic,
	Kinematic
};
// Ό³Έν :
class URigidbody2DComponent: public USceneComponent
{
public:
	// constrcuter destructer
	ENGINE_API URigidbody2DComponent();
	ENGINE_API ~URigidbody2DComponent();

	// delete Function
	URigidbody2DComponent(const URigidbody2DComponent& _Other) = delete;
	URigidbody2DComponent(URigidbody2DComponent&& _Other) noexcept = delete;
	URigidbody2DComponent& operator=(const URigidbody2DComponent& _Other) = delete;
	URigidbody2DComponent& operator=(URigidbody2DComponent&& _Other) noexcept = delete;

	ENGINE_API void SetVelocity(FVector2 _Velocity);
	b2BodyId GetBodyId() { return BodyId; }
	virtual void TickComponent(float _DeltaTime);
	virtual void BeginPlay();
protected:

private:
	b2Vec2 Velocity;
	EBodyType Type;

	b2BodyDef BodyDef;
	b2BodyId BodyId;
};

