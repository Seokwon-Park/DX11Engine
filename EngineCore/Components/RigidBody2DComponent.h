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
class RigidBody2DComponent: public USceneComponent
{
public:
	// constrcuter destructer
	ENGINE_API RigidBody2DComponent();
	ENGINE_API ~RigidBody2DComponent();

	// delete Function
	RigidBody2DComponent(const RigidBody2DComponent& _Other) = delete;
	RigidBody2DComponent(RigidBody2DComponent&& _Other) noexcept = delete;
	RigidBody2DComponent& operator=(const RigidBody2DComponent& _Other) = delete;
	RigidBody2DComponent& operator=(RigidBody2DComponent&& _Other) noexcept = delete;

	virtual void TickComponent(float _DeltaTime);
	virtual void BeginPlay();
protected:

private:
	EBodyType Type;

	b2BodyDef bodyDef;
	b2BodyId bodyId;
	b2Polygon dynamicBox;
	b2ShapeDef shapeDef;


};

