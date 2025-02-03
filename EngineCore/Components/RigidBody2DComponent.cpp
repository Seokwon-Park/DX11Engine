#include "EnginePCH.h"
#include "Rigidbody2DComponent.h"
#include "Actor.h"
#include "Level.h"

// 1pixel / 100.0f = box2D unit
URigidbody2DComponent::URigidbody2DComponent()
{

}

URigidbody2DComponent::~URigidbody2DComponent()
{
}

void URigidbody2DComponent::SetVelocity(FVector2 _Velocity)
{
	Velocity = b2Vec2(_Velocity.X , _Velocity.Y );
	b2Body_SetLinearVelocity(BodyId, Velocity);

}

void URigidbody2DComponent::TickComponent(float _DeltaTime)
{
	b2WorldId Id = GetOwner()->GetLevel()->GetPhysicsWorld();
	//Velocity = Velocity + b2World_GetGravity(Id);
	//Velocity.y = b2MaxFloat(Velocity.y, b2World_GetGravity(Id).y);
	//std::cout << b2Body_GetLinearVelocity(BodyId).x << " ," << b2Body_GetLinearVelocity(BodyId).y << '\n';
	//b2Body_SetLinearVelocity(BodyId, Velocity);
	//b2World_Step(Id, 1.0f / 60.0f, 4);
	b2Vec2 XY = b2Body_GetPosition(BodyId);
	Parent->SetLocation(FVector4(XY.x * FMath::BOX2DSCALE, XY.y * FMath::BOX2DSCALE, 0.0f, 1.0f));
	b2Rot rotation = b2Body_GetRotation(BodyId);
	//std::cout << b2Body_GetPosition(bodyId).y << '\n';

	int bodyContactCapacity = b2Body_GetContactCapacity(BodyId);
	std::cout << "Contacts - " << bodyContactCapacity << '\n';
	b2ContactEvents contactEvents = b2World_GetContactEvents(Id);
	std::cout << "ContactEvents - " << contactEvents.beginCount<< '\n';
}

void URigidbody2DComponent::BeginPlay()
{
	BodyDef = b2DefaultBodyDef();
	BodyDef.type = b2_dynamicBody;
	BodyDef.position = { Parent->GetLocation().X / FMath::BOX2DSCALE, Parent->GetLocation().Y / FMath::BOX2DSCALE };
	BodyDef.fixedRotation = true;
	BodyDef.userData = GetOwner();
	BodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);

	//std::cout << b2Body_GetPosition(BodyId).x << ',' << b2Body_GetPosition(BodyId).y << '\n';
}
