#pragma once
#include "SceneComponent.h"
#include <EngineCore/ThirdParty/Box2D/include/box2d.h>

enum class EBodyType
{
	Static,
	Dynamic,
	Kinematic
};
// ���� :
class URigidbody2DComponent : public USceneComponent
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
	ENGINE_API FVector2 GetVelocity() { return { b2Body_GetLinearVelocity(BodyId).x,b2Body_GetLinearVelocity(BodyId).y }; }
	b2BodyId GetBodyId() { return BodyId; }
	virtual void TickComponent(float _DeltaTime);
	virtual void BeginPlay();

	ENGINE_API void SetZeroGravity() { b2Body_SetGravityScale(BodyId, 0.0f); }
	ENGINE_API void SetGravity(float _GravityScale = 1.0f) { b2Body_SetGravityScale(BodyId, _GravityScale); }
protected:

private:
	b2Vec2 Velocity;
	EBodyType Type;

	b2BodyDef BodyDef;
	b2BodyId BodyId;
};

