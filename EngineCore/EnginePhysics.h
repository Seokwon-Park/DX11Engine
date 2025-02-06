#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineCore/Enums/EngineLayer.h>
#include <EngineCore/ThirdParty/Box2D/include/box2d.h>
#include <EngineCore/Components/Collider2DComponent.h>

struct RayCastContext
{
	b2ShapeId shapeId;
	b2Vec2 point;
	b2Vec2 normal;
	float fraction;
};



// Ό³Έν :
class UEnginePhysics
{
public:
	// constrcuter destructer
	UEnginePhysics();
	~UEnginePhysics();

	// delete Function
	UEnginePhysics(const UEnginePhysics& _Other) = delete;
	UEnginePhysics(UEnginePhysics&& _Other) noexcept = delete;
	UEnginePhysics& operator=(const UEnginePhysics& _Other) = delete;
	UEnginePhysics& operator=(UEnginePhysics&& _Other) noexcept = delete;

	ENGINE_API static bool RayCast(FVector4 _Position, FVector4 _Direction, float _Distance, ECollisionLayer _Layer);


	ENGINE_API static std::vector<UCollider2DComponent> CircleCollider(FVector4 _Position, float _Radius, ECollisionLayer _Layer);
	//b2Shape_GetBody(ShapeId);


	static class ULevel* CurLevel;

	ENGINE_API static std::map<ECollisionLayer, unsigned long long> CollisionRule;
protected:

private:
};

