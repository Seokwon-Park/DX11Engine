#include "EnginePCH.h"
#include "RigidBody2DComponent.h"
#include "Actor.h"
#include "Level.h"


RigidBody2DComponent::RigidBody2DComponent()
{

}

RigidBody2DComponent::~RigidBody2DComponent()
{
}

void RigidBody2DComponent::SetVelocity(FVector2 _Velocity)
{
	Velocity = b2Vec2(_Velocity.X, _Velocity.Y); // 오른쪽으로 힘 가하기
}

void RigidBody2DComponent::TickComponent(float _DeltaTime)
{
	b2WorldId Id = GetOwner()->GetLevel()->GetPhysicsWorld();
	b2Body_SetLinearVelocity(bodyId, Velocity + b2World_GetGravity(Id));
	b2World_Step(Id, 1.0f / 60.0f, 4);
	b2Vec2 XY = b2Body_GetPosition(bodyId);

	Parent->SetLocation({ XY.x, XY.y, 0.0f, 1.0f });

	b2Rot rotation = b2Body_GetRotation(bodyId);
	//std::cout << b2Body_GetPosition(bodyId).y << '\n';
}

void RigidBody2DComponent::BeginPlay()
{
	bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { Parent->GetLocation().X, Parent->GetLocation().Y };
	bodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &bodyDef);

	dynamicBox = b2MakeBox(1.0f, 1.0f);
	shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;
	b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}
