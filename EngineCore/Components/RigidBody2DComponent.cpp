#include "EnginePCH.h"
#include "Rigidbody2DComponent.h"
#include "Actor.h"
#include "Level.h"

URigidbody2DComponent::URigidbody2DComponent()
{

}

URigidbody2DComponent::~URigidbody2DComponent()
{
}

void URigidbody2DComponent::SetVelocity(FVector2 _Velocity)
{
	Velocity = b2Vec2(_Velocity.X, _Velocity.Y); // 오른쪽으로 힘 가하기
}

void URigidbody2DComponent::TickComponent(float _DeltaTime)
{
	b2WorldId Id = GetOwner()->GetLevel()->GetPhysicsWorld();
	b2Body_SetLinearVelocity(BodyId, Velocity + b2World_GetGravity(Id));
	b2World_Step(Id, 1.0f / 60.0f, 4);
	b2Vec2 XY = b2Body_GetPosition(BodyId);
	Parent->SetLocation({ XY.x, XY.y, 0.0f, 1.0f });
	b2Rot rotation = b2Body_GetRotation(BodyId);
	//std::cout << b2Body_GetPosition(bodyId).y << '\n';
}

void URigidbody2DComponent::BeginPlay()
{
	BodyDef= b2DefaultBodyDef();
	BodyDef.type = b2_dynamicBody;
	BodyDef.position = { Parent->GetLocation().X, Parent->GetLocation().Y };
	BodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);
}
