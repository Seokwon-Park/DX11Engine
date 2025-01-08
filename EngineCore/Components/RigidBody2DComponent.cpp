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

void RigidBody2DComponent::TickComponent(float _DeltaTime)
{
    b2WorldId Id = GetOwner()->GetLevel()->GetPhysicsWorld();
    b2World_Step(Id, 1.0f/(1.0f/_DeltaTime), 4);
    FVector2 xy = { b2Body_GetPosition(bodyId).x, b2Body_GetPosition(bodyId).y };
    Parent->SetLocation({ xy.X, xy.Y, 0.0f, 1.0f });
    
    b2Rot rotation = b2Body_GetRotation(bodyId);
    std::cout << b2Body_GetPosition(bodyId).y << '\n';
}

void RigidBody2DComponent::BeginPlay()
{
    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2)(0.0f, 4.0f);
    bodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &bodyDef);

    dynamicBox = b2MakeBox(1.0f, 1.0f);
    shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}
